#include "example/systems/MovementSystem.h"

#include <exception>

void MovementSystem::runSingle(RuRu::EntityManager& em, const RuRu::ServiceLocator& sl,
	PhysicsComponent& phys, PositionComponent& pos)
{
	phys.update(pos);
}

void BoundrySystem::runSingle(RuRu::EntityManager& em, const RuRu::ServiceLocator& sl,
	BoundryCheckComponent& boundryChecker, PositionComponent& position)
{
	if (boundryChecker.behaviour() == BoundryCheckComponent::DESTROY_ENTITY)
	{
		if (boundryChecker.checkTop(position.y) 			||
			boundryChecker.checkBot(position.y, m_Height) 	||
			boundryChecker.checkLeft(position.x)			||
			boundryChecker.checkRight(position.x, m_Width))
		{
			em.deleteFlagEntity(boundryChecker.entity());
		}
	}
	else
	{
		if (boundryChecker.checkTop(position.y)) position.y = 0;
		else if (boundryChecker.checkBot(position.y, m_Height)) position.y = m_Height;
	
		if (boundryChecker.checkLeft(position.x)) position.x = 0;
		else if (boundryChecker.checkRight(position.x, m_Width)) position.x = m_Width;
	}
}

void BoundrySystem::setDimensions(size_t width, size_t height)
{ 
	m_Width = width; 
	m_Height = height; 
} 
