#ifndef H_GAME_PLAY_SCENE
#define H_GAME_PLAY_SCENE

#include "ruru/IScene.h"
#include "ruru/entities/EntityManager.h"
#include "ruru/events/LoggedEventService.h"
#include "ruru/particles/ParticleManager.h"
#include "ruru/services/ServiceLocator.h"


#include "example/particles/ExplosionParticle.h"

#include "example/EntitySpawner.h"
#include "example/systems/PlayerControlSystem.h"
#include "example/systems/CollisionSystem.h"
#include "example/systems/MovementSystem.h"
#include "example/systems/ShootingSystem.h"
#include "example/systems/RenderSystem.h"
#include "example/systems/LifeTimeSystem.h"

#include <vector>
#include <allegro5/allegro.h>

class GamePlayScene : public RuRu::IScene
{
	private:
		//Utilities
		RuRu::ServiceLocator m_ServiceLocator;
		RuRu::LoggedEventService m_EventService;
		RuRu::EntityManager m_EntityManager;
		RuRu::EntityHandle_t m_Player;
		RuRu::ParticleManager<ExplosionParticle> m_ExplosionParticles;
		EntitySpawner m_Spawner;

		// Systems
		CollisionSystem m_CollisionSystem;
		MovementSystem m_MovementSystem;
		BoundrySystem m_BoundrySystem;
		ShootingSystem m_ShootingSystem;
		RenderSystem m_RenderSystem;
		LifeTimeSystem m_LifeTimeSystem;

		// Resoures
		ALLEGRO_BITMAP* m_ParticleBuffer;

		int m_ScreenWidth;
		int m_ScreenHeight;

	public:
		GamePlayScene(RuRu::ServiceLocator* engineServices);
		~GamePlayScene();
	
		virtual void pause();
		virtual void resume();

		virtual void update(RuRu::Game* game);
		virtual void draw(RuRu::Game* game);

		void explosionParticleSpawner(const RuRu::Event* args);
		void enemySpawner(const RuRu::Event* args);
};


#endif


