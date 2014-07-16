#ifndef H_DAMAGEABLE_COMPONENT
#define H_DAMAGEABLE_COMPONENT

#include "ruru/components/ComponentMixin.h"
#include "example/components/ComponentTypes.h"
	
class DamageableComponent : public RuRu::ComponentMixin
{
	private:
		int m_MaxDamageCapacity;
		int m_DamageCapacityRemaining;
		int m_Team;

	public:
		constexpr static const RuRu::ComponentType_t Type = COMPONENT_TYPE_DAMAGEABLE;
		constexpr static const size_t InitialAllocation = RuRu::COMPONENT_DEFAULT_ALLOCATION;
		
		DamageableComponent(int team, int damageCapacity)
			: m_MaxDamageCapacity(damageCapacity), m_DamageCapacityRemaining(damageCapacity), m_Team(team) { }

		inline int team() { return m_Team; }
		inline bool alive() { return m_DamageCapacityRemaining > 0; }
		inline void addDamage(int damage) { m_DamageCapacityRemaining -= damage; }

};

#endif
