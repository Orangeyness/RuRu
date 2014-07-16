#include "example/systems/RenderSystem.h"

void RenderSystem::runSingle(RuRu::EntityManager& entityManager, const RuRu::ServiceLocator& sl,
		PositionComponent& pc, RenderComponent& rc)
{
	rc.render(pc.x, pc.y);
}
