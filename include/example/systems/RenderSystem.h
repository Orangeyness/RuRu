#ifndef H_RENDER_SYSTEM
#define H_RENDER_SYSTEM

#include "ruru/systems/SystemMixin.h"

#include "example/components/PositionComponent.h"
#include "example/components/RenderComponent.h"

class RenderSystem : public RuRu::SystemMixin<RenderSystem, PositionComponent, RenderComponent>
{
	public:
		void runSingle(RuRu::EntityManager& entityManager, const RuRu::ServiceLocator& sl,
				PositionComponent& pc, RenderComponent& rc);

		using RuRu::SystemMixin<RenderSystem, PositionComponent, RenderComponent>::run;
};


#endif
