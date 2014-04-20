#ifndef H_GAME_PLAY_SCENE
#define H_GAME_PLAY_SCENE

#include "ruru/IScene.h"
#include "ruru/entity/EntityManager.h"
#include "ruru/events/LoggedEventService.h"
#include "ruru/particles/ParticleManager.h"
#include "ruru/services/ServiceLocator.h"


#include "example/particles/ExplosionParticle.h"

#include "example/EntitySpawner.h"
#include "example/systems/CollisionSystem.h"

#include <vector>
#include <allegro5/allegro.h>

class GamePlayScene : public RuRu::IScene
{
	private:
		RuRu::LoggedEventService m_EventService;
		RuRu::EntityManager m_EntityManager;
		RuRu::EntityHandle_t m_Player;
		RuRu::ParticleManager<ExplosionParticle> m_ExplosionParticles;
		EntitySpawner m_Spawner;
		CollisionSystem m_CollisionSystem;
		ALLEGRO_BITMAP* m_ParticleBuffer;

		int m_ScreenWidth;
		int m_ScreenHeight;

	public:
		GamePlayScene();
		~GamePlayScene();
	
		virtual void pause();
		virtual void resume();

		virtual void update(RuRu::Game* game);
		virtual void draw(RuRu::Game* game);

		void explosionParticleSpawner(const RuRu::Event* args);
		void enemySpawner(const RuRu::Event* args);
};


#endif


