#ifndef H_COLLISION_COMPONENT
#define H_COLLISION_COMPONENT

#include "ruru/components/ComponentAccessor.h"
#include "example/components/ComponentTypes.h"
#include "example/components/PositionComponent.h"

class CollisionComponent
{
	private:
		RuRu::ComponentAccessor<PositionComponent> m_Position;
		double m_Width;
		double m_Height;

	public:
		constexpr static const RuRu::ComponentType_t Type = COMPONENT_TYPE_COLLISION;
		constexpr static const size_t InitialAllocation = RuRu::COMPONENT_DEFAULT_ALLOCATION;

		CollisionComponent(RuRu::ComponentAccessor<PositionComponent> position, double width, double height)
			: m_Position(position)
		{
			m_Width = width/2;
			m_Height = height/2;
		}

		inline double left() const { return m_Position->x - m_Width; }
		inline double right() const { return m_Position->x + m_Width; }
		inline double top() const { return m_Position->y - m_Height; } 
		inline double bot() const { return m_Position->y + m_Height; }

		inline bool colliding(const CollisionComponent& other) const
		{
			return !(right() < other.left() || left() > other.right() || bot() < other.top() || top() > other.bot());
		}

		inline RuRu::EntityHandle_t entity() const
		{
			return m_Position.entity();
		}
};


#endif
