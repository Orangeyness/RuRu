#include "example/systems/ShootingSystem.h"

void ShootingSystem::Shoot(RuRu::EntityManager& em)
{
	auto begin = em.component_begin<ShootingComponent>();
	auto end = em.component_end<ShootingComponent>();
	
	for (	auto shootingComponent = begin; 
			shootingComponent != end;
			shootingComponent++
		)
	{
		shootingComponent->shoot(em);
	}	
}
