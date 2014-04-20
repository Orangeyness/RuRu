#include "example/systems/MovementSystem.h"

#include "example/components/PositionComponent.h"
#include "example/components/PhysicsComponent.h"
#include "example/components/BoundryCheckComponent.h"

void MovementSystem::Move(const RuRu::EntityManager& entityManager)
{
	for (auto entity : entityManager)
	{
		if (! entity.hasComponent<PhysicsComponent>()) continue;
		if (! entity.hasComponent<PositionComponent>()) continue;
		
		PhysicsComponent* movement = entity.getComponent<PhysicsComponent>();
		PositionComponent* position = entity.getComponent<PositionComponent>();

		movement->update(position);
	}
}

void MovementSystem::BoundryCheck(RuRu::EntityManager& entityManager, double width, double height)
{
	for (auto entity : entityManager)
	{
		if (! entity.hasComponent<BoundryCheckComponent>()) continue;
		if (! entity.hasComponent<PositionComponent>()) continue;
		
		BoundryCheckComponent* boundryChecker = entity.getComponent<BoundryCheckComponent>();
		PositionComponent* position = entity.getComponent<PositionComponent>();

		if (boundryChecker->behaviour() == BoundryCheckComponent::DESTROY_ENTITY)
		{
			if (boundryChecker->checkTop(position->y) 			||
				boundryChecker->checkBot(position->y, height) 	||
				boundryChecker->checkLeft(position->x)			||
				boundryChecker->checkRight(position->x, width))
			{
				entityManager.deleteFlagEntity(entity.getEntityId());
			}
		}
		else
		{
			if (boundryChecker->checkTop(position->y)) position->y = 0;
			else if (boundryChecker->checkBot(position->y, height)) position->y = height;
		
			if (boundryChecker->checkLeft(position->x)) position->x = 0;
			else if (boundryChecker->checkRight(position->x, width)) position->x = width;
		}
	}
	
}
