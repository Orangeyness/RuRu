#include "example/GamePlayScene.h"

#include "example/systems/PlayerControlSystem.h"
#include "example/systems/MovementSystem.h"
#include "example/systems/RenderSystem.h"
#include "example/systems/ShootingSystem.h"

#include "example/components/ShootingComponent.h"
#include "example/components/CollisionComponent.h"
#include "example/components/DamageDealingComponent.h"
#include "example/components/DamageableComponent.h"

#include "example/events/EntityDestroyEvent.h"

#include <allegro5/allegro.h>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <functional>
using std::placeholders::_1;


GamePlayScene::GamePlayScene()
	: m_EventService(std::cout), m_Spawner(&m_EntityManager)
{
	srand(time(NULL));

	m_ScreenWidth = 600;
	m_ScreenHeight = 960;

	m_Player = m_Spawner.spawnPlayer(200, m_ScreenHeight - 200);

	m_Spawner.spawnEnemy(200, -1000);
	m_Spawner.spawnEnemy(120, 0);
	
	m_EventService.addEventDelegate<EntityDestroyEvent>(
		std::bind(&GamePlayScene::explosionParticleSpawner, this, _1)
		);

	particles.reserve(1000);

	RuRu::ServiceLocator::AddService<RuRu::LoggedEventService>(&m_EventService);
}

GamePlayScene::~GamePlayScene()
{
	RuRu::ServiceLocator::RemoveService<RuRu::LoggedEventService>(&m_EventService);
}

void GamePlayScene::pause() { }
void GamePlayScene::resume() { }
void GamePlayScene::update(RuRu::Game* game)
{
	m_EventService.processEvents();

	PlayerControlSystem::ProcessInput(m_EntityManager.tryGet(m_Player));

	ShootingSystem::Shoot(	m_EntityManager.component_begin<ShootingComponent>(),
							m_EntityManager.component_end<ShootingComponent>(),
							m_Spawner);

	MovementSystem::Move(m_EntityManager);
	MovementSystem::BoundryCheck(m_EntityManager, m_ScreenWidth, m_ScreenHeight);

	m_CollisionSystem.resolveCollisions(m_EntityManager);

	m_EntityManager.deleteFlaggedEntities();

	size_t i = 0;
	while (i < particles.size())
	{
		bool particleAlive = particles[i].update();

		if (!particleAlive)
		{
			size_t lastIndex = particles.size() - 1;
			if (i != lastIndex)
			{
				std::swap(particles[i], particles[lastIndex]);
			}
	
			particles.pop_back();
		}
		else
		{
			i++;
		}
	}	
}

void GamePlayScene::explosionParticleSpawner(const RuRu::Event* args)
{
	const EntityDestroyEvent* event = args->get<EntityDestroyEvent>();

	if (event->entityType == ENTITY_PLAYER || event->entityType == ENTITY_ENEMY)
	{
		int particleCount = rand() % 100 + 100;
		
		for (int i = 0; i < particleCount; i++)
		{
			particles.emplace_back(
				event->x,
				event->y,
				(double)((rand() % 150) - (rand() % 150)) / 10.0,
				(double)((rand() % 150) - (rand() % 150)) / 10.0,
				(rand() % 60 + 40),
				al_map_rgb(154 + rand() % 100, rand() % 200, rand() % 200)
				);
		}	
	}
}

void GamePlayScene::draw(RuRu::Game* game)
{
	al_clear_to_color(al_map_rgb(0, 0, 0));

	for(auto& particle : particles)
	{
		particle.render();
	}

	RenderSystem::Run(m_EntityManager);
}
