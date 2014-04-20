#include "example/systems/RenderSystem.h"

#include "example/components/PositionComponent.h"
#include "example/components/RenderComponent.h"

void RenderSystem::Run(const RuRu::EntityManager& entityManager)
{
	for(auto entity : entityManager)
	{
		if (! entity.hasComponent<PositionComponent>()) continue;
		if (! entity.hasComponent<RenderComponent>()) continue;

		PositionComponent* position = entity.getComponent<PositionComponent>();
		RenderComponent* render = entity.getComponent<RenderComponent>();
		
		render->render(position->x, position->y);	
	}
}
