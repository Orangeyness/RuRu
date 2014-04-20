#include "example/systems/ShootingSystem.h"

void ShootingSystem::Shoot(	RuRu::ComponentIterator<ShootingComponent> begin,
							RuRu::ComponentIterator<ShootingComponent> end,
							EntitySpawner& es)
{
	for (	auto shootingComponent = begin; 
			shootingComponent != end;
			shootingComponent++
		)
	{
		shootingComponent->shoot(es);
	}	
}
