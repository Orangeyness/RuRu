#ifndef H_SHOOTING_SYSTEM
#define H_SHOOTING_SYSTEM

#include "ruru/entities/EntityManager.h"
#include "ruru/systems/SystemMixin.h"

#include "example/EntitySpawner.h"
#include "example/components/ShootingComponent.h"

class ShootingSystem : public RuRu::SystemMixin<ShootingSystem, ShootingComponent>
{
	public:
		void runSingle(RuRu::EntityManager& em, const RuRu::ServiceLocator& sl, 
				ShootingComponent& shooting);

		using RuRu::SystemMixin<ShootingSystem, ShootingComponent>::run;
};


#endif
