#ifndef H_SHOOTING_SYSTEM
#define H_SHOOTING_SYSTEM

#include "ruru/entity/EntityManager.h"

#include "example/EntitySpawner.h"
#include "example/components/ShootingComponent.h"

class ShootingSystem
{
	public:
		static void Shoot(	RuRu::ComponentIterator<ShootingComponent> begin,
							RuRu::ComponentIterator<ShootingComponent> end,
							EntitySpawner& es);

};



#endif
