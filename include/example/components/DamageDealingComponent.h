#ifndef H_DAMAGE_DEALING_COMPONENT
#define H_DAMAGE_DEALING_COMPONENT

#include "example/components/ComponentTypes.h"

class DamageDealingComponent
{
	private:
		int m_Damage;
		int m_Team;
		bool m_Pierce;
		
	public:
		constexpr static const RuRu::ComponentType_t Type = COMPONENT_TYPE_DAMAGE_DEALING;
		constexpr static const size_t InitialAllocation = RuRu::COMPONENT_DEFAULT_ALLOCATION;

		DamageDealingComponent(int team, int damage, bool pierce)
			: m_Damage(damage), m_Team(team), m_Pierce(pierce) { }

		inline int team() { return m_Team; }
		inline int damage() { return m_Damage; }
		inline bool pierce() { return m_Pierce; }
};


#endif
