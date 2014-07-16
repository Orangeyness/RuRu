#include "example/systems/ShootingSystem.h"

void ShootingSystem::runSingle(RuRu::EntityManager& em, const RuRu::ServiceLocator& sl, 
	ShootingComponent& shootingComponent)
{
	shootingComponent.shoot(em);
}
