#include "example/systems/LifeTimeSystem.h"
#include "example/components/RenderComponent.h"

void LifeTimeSystem::runSingle(RuRu::EntityManager& em, const RuRu::ServiceLocator& sl,
	LifeTimeComponent& ltc)
{
	int timeLeft = ltc.tick();

	if (timeLeft < 0)
	{
		em.deleteFlagEntity(ltc.entity());
	}
	else if (timeLeft <= 100 && timeLeft % 10 == 0 && ltc.hasSiblingComponent<RenderComponent>())
	{
		RenderComponent& renderer = ltc.getSiblingComponent<RenderComponent>();

		renderer.setFlash();
	}
}
