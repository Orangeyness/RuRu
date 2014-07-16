#ifndef H_ENTITY_SPAWNER
#define H_ENTITY_SPAWNER

#include "ruru/entities/EntityManager.h"
#include "example/buffs/IBuff.h"

#define PLAYER_TEAM 0 
#define ENEMY_TEAM 1

#define ENTITY_BASIC 			0
#define ENTITY_PLAYER 			1
#define ENTITY_ENEMY			3

using RuRu::EntityHandle_t;

class EntitySpawner
{
	private:
		RuRu::EntityManager* m_Em;

	public:
		EntitySpawner(RuRu::EntityManager* em);

		EntityHandle_t spawnPlayer(double x, double y);
		EntityHandle_t spawnEnemy(double x, double y);
		EntityHandle_t spawnBuff(double x, double y, IBuff* buff);
};


#endif
