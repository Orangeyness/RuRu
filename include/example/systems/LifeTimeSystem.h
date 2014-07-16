#ifndef H_LIFE_TIME_SYSTEM
#define H_LIFE_TIME_SYSTEM

#include "ruru/systems/SystemMixin.h"

#include "example/components/LifeTimeComponent.h"

class LifeTimeSystem : public RuRu::SystemMixin<LifeTimeSystem, LifeTimeComponent>
{

	public:
		void runSingle(RuRu::EntityManager& em, const RuRu::ServiceLocator& sl,
				LifeTimeComponent& ltc);

	using RuRu::SystemMixin<LifeTimeSystem, LifeTimeComponent>::run;

};

#endif
