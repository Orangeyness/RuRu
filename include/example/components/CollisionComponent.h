#ifndef H_COLLISION_COMPONENT
#define H_COLLISION_COMPONENT

#include "ruru/components/ComponentMixin.h"
#include "example/components/ComponentTypes.h"
#include "example/components/PositionComponent.h"

class CollisionComponent : public RuRu::ComponentMixin
{
	private:
		double m_Width;
		double m_Height;

	public:
		constexpr static const RuRu::ComponentType_t Type = COMPONENT_TYPE_COLLISION;
		constexpr static const size_t InitialAllocation = RuRu::COMPONENT_DEFAULT_ALLOCATION;

		CollisionComponent(double width, double height)
		{
			m_Width = width/2;
			m_Height = height/2;
		}

		inline double left() const { return getSiblingComponent<PositionComponent>().x - m_Width; }
		inline double right() const { return getSiblingComponent<PositionComponent>().x + m_Width; }
		inline double top() const { return getSiblingComponent<PositionComponent>().y - m_Height; } 
		inline double bot() const { return getSiblingComponent<PositionComponent>().y + m_Height; }

		inline bool colliding(const CollisionComponent& other) const
		{
			return !(right() < other.left() || left() > other.right() || bot() < other.top() || top() > other.bot());
		}
};


#endif
