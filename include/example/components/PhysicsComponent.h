#ifndef H_PHYSICS_COMPONENT
#define H_PHYSICS_COMPONENT

#include "ruru/components/ComponentMixin.h"
#include "example/components/ComponentTypes.h"
#include "example/components/PositionComponent.h"

class PhysicsComponent : public RuRu::ComponentMixin
{
	private:
		double m_SpeedMax;
		double m_Acceleration;
		double m_Friction;
		double m_SpeedX;
		double m_SpeedY;
	
		double updateSpeed(double speed);
		double limitSpeed(double speed);
		
	public:
		constexpr static const RuRu::ComponentType_t Type = COMPONENT_TYPE_PHYSICS;
		constexpr static const size_t InitialAllocation = RuRu::COMPONENT_DEFAULT_ALLOCATION;

		PhysicsComponent(double speedMax, double acceleration, double friction);

		void update(PositionComponent& position);
		void accelerate(double x, double y);
		void accelerateX(double x);
		void accelerateY(double y);
};


#endif
