#ifndef H_LIFE_TIME_COMPONENT
#define H_LIFE_TIME_COMPONENT

#include "example/components/ComponentTypes.h"

class LifeTimeComponent : public RuRu::ComponentMixin
{
	private:
		int m_LifeTimeRemaining;

	public:
		constexpr static const size_t InitialAllocation = RuRu::COMPONENT_DEFAULT_ALLOCATION;
		constexpr static const RuRu::ComponentType_t Type = COMPONENT_TYPE_LIFETIME;

		LifeTimeComponent(int life)
			: m_LifeTimeRemaining(life) { } 

		int tick() { return --m_LifeTimeRemaining; }

};

#endif
