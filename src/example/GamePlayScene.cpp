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
	: m_EventService(std::cout), m_ExplosionParticles(5000), m_Spawner(&m_EntityManager)
{
	srand(time(NULL));

	m_ScreenWidth = 600;
	m_ScreenHeight = 960;

	al_set_new_bitmap_format(ALLEGRO_PIXEL_FORMAT_ANY_WITH_ALPHA);
	m_ParticleBuffer = al_create_bitmap(m_ScreenWidth, m_ScreenHeight);

	m_Player = m_Spawner.spawnPlayer(200, m_ScreenHeight - 200);

	m_Spawner.spawnEnemy(200, -1000);
	m_Spawner.spawnEnemy(120, 0);
	
	m_EventService.addEventDelegate<EntityDestroyEvent>(
		std::bind(&GamePlayScene::explosionParticleSpawner, this, _1)
		);

	m_EventService.addEventDelegate<EntityDestroyEvent>(
		std::bind(&GamePlayScene::enemySpawner, this, _1)
		);

	RuRu::ServiceLocator::AddService<RuRu::LoggedEventService>(&m_EventService);
}

GamePlayScene::~GamePlayScene()
{
	al_destroy_bitmap(m_ParticleBuffer);

	RuRu::ServiceLocator::RemoveService<RuRu::LoggedEventService>(&m_EventService);
}

void GamePlayScene::pause() { }
void GamePlayScene::resume() { }
void GamePlayScene::update(RuRu::Game* game)
{
	int particleCount = rand() % 4;
	for (int i = 0; i < particleCount; i++)
	{
		double speed = 5.0 + (double)(rand() % 100) / 10.0;

		m_ExplosionParticles.emplace(
			rand() % m_ScreenWidth,
			0,
			(double)((rand() % 10) - (rand() % 10)) / 10.0,
			speed, 
			5 + m_ScreenHeight / speed,
			al_map_rgb(180 + rand() % 60, 180 + rand() % 60, 180 + rand() % 60)
			);
	}

	m_EventService.processEvents();

	PlayerControlSystem::ProcessInput(m_EntityManager.tryGet(m_Player));

	ShootingSystem::Shoot(m_EntityManager);

	MovementSystem::Move(m_EntityManager);
	MovementSystem::BoundryCheck(m_EntityManager, m_ScreenWidth, m_ScreenHeight);

	m_CollisionSystem.resolveCollisions(m_EntityManager);
	m_EntityManager.deleteFlaggedEntities();
	m_ExplosionParticles.update();
}

void GamePlayScene::explosionParticleSpawner(const RuRu::Event* args)
{
	const EntityDestroyEvent* event = args->get<EntityDestroyEvent>();

	if (event->entityType == ENTITY_PLAYER || event->entityType == ENTITY_ENEMY)
	{
		int particleCount = rand() % 100 + 100;
		
		for (int i = 0; i < particleCount; i++)
		{
			m_ExplosionParticles.emplace(
				event->x,
				event->y,
				(double)((rand() % 150) - (rand() % 150)) / 10.0,
				(double)((rand() % 150) - (rand() % 150)) / 10.0,
				(rand() % 60 + 40),
				al_map_rgba(154 + rand() % 100, rand() % 200, rand() % 200, 255)
				);
		}	
	}
}

void GamePlayScene::enemySpawner(const RuRu::Event* args)
{
	const EntityDestroyEvent* event = args->get<EntityDestroyEvent>();

	if (event->entityType == ENTITY_ENEMY)
	{
		int enemyCount = 1 + rand() % 2;
		
		for (int i = 0; i < enemyCount; i++)
		{
			m_Spawner.spawnEnemy(100 + (rand() % (m_ScreenWidth - 200)), -(100 + rand() % 1000));
		}
	}
}

void GamePlayScene::draw(RuRu::Game* game)
{
	ALLEGRO_STATE state;
	al_store_state(&state, ALLEGRO_STATE_TARGET_BITMAP);

	al_set_target_bitmap(m_ParticleBuffer);
	al_clear_to_color(al_map_rgba(0, 0, 0, 0));
	al_lock_bitmap(m_ParticleBuffer, ALLEGRO_PIXEL_FORMAT_ANY, ALLEGRO_LOCK_READWRITE);
	
	m_ExplosionParticles.render();

	al_unlock_bitmap(m_ParticleBuffer);

	al_restore_state(&state);

	al_clear_to_color(al_map_rgb(0, 0, 0));
	al_draw_bitmap(m_ParticleBuffer, 0, 0, 0);

	RenderSystem::Run(m_EntityManager);
}
