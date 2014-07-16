#ifndef H_MOVEMENT_SYSTEM
#define H_MOVEMENT_SYSTEM

#include "ruru/entities/EntityManager.h"
#include "ruru/systems/SystemMixin.h"

#include "example/components/PositionComponent.h"
#include "example/components/PhysicsComponent.h"
#include "example/components/BoundryCheckComponent.h"

class MovementSystem : public RuRu::SystemMixin<MovementSystem, PhysicsComponent, PositionComponent>
{
	public:
		void runSingle(RuRu::EntityManager& em, const RuRu::ServiceLocator& sl,
				PhysicsComponent& phys, PositionComponent& pos);

		using RuRu::SystemMixin<MovementSystem, PhysicsComponent, PositionComponent>::run;
};

class BoundrySystem : public RuRu::SystemMixin<BoundrySystem, BoundryCheckComponent, PositionComponent>
{
	private:
		size_t m_Width;
		size_t m_Height;

	public:

		void runSingle(RuRu::EntityManager& em, const RuRu::ServiceLocator& sl,
			BoundryCheckComponent& boundry, PositionComponent& pos);

		BoundrySystem() { }

		BoundrySystem(size_t width, size_t height)
			: m_Width(width), m_Height(height) { }
	
		void setDimensions(size_t width, size_t height);

		using RuRu::SystemMixin<BoundrySystem, BoundryCheckComponent, PositionComponent>::run;

};

#endif
