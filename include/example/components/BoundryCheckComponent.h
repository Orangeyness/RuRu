#ifndef H_BOUNDRY_CHECK_COMPONENT
#define H_BOUNDRY_CHECK_COMPONENT

#include "ruru/components/ComponentMixin.h"
#include "example/components/ComponentTypes.h"

typedef bool BoundryBehaviour_t;

class BoundryCheckComponent : public RuRu::ComponentMixin
{
	private:
		BoundryBehaviour_t m_Behaviour;
		bool m_CheckTop;
		bool m_CheckBot;
		bool m_CheckLeft;
		bool m_CheckRight;

	public:
		constexpr static const RuRu::ComponentType_t Type = COMPONENT_TYPE_BOUNDRY_CHECK;
		constexpr static const size_t InitialAllocation = RuRu::COMPONENT_DEFAULT_ALLOCATION;
	
		static const BoundryBehaviour_t DESTROY_ENTITY;
		static const BoundryBehaviour_t PUSH_ENTITY;

		BoundryCheckComponent(BoundryBehaviour_t behaviour, bool left, bool right, bool top, bool bot)
			: m_Behaviour(behaviour), m_CheckTop(top), m_CheckBot(bot), m_CheckLeft(left), m_CheckRight(right) { }

		inline bool checkTop(double y) { return (m_CheckTop && y < 0); }
		inline bool checkBot(double y, double height) { return (m_CheckTop && y > height); }
		inline bool checkLeft(double x) { return (m_CheckLeft && x < 0); }
		inline bool checkRight(double x, double width) { return (m_CheckRight && x > width); }

		inline BoundryBehaviour_t behaviour() { return m_Behaviour; }


};


#endif
