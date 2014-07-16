#ifndef H_SHOOTING_COMPONENT
#define H_SHOOTING_COMPONENT

#include "ruru/entities/EntityManager.h"
#include "ruru/components/ComponentMixin.h"

#include "example/components/ComponentTypes.h"
#include "example/components/PositionComponent.h"
#include "example/attacks/IAttack.h"

#include <array>

const int MAX_ATTACKS = 10;

struct AttackData
{
	AttackData() 
	{
		Active = false;
		ReloadTime = 0;
		Handle = nullptr;
	}

	bool Active;
	int ReloadTime;
	IAttack* Handle;
};

class ShootingComponent : public RuRu::ComponentMixin
{
	private:
		std::array<AttackData, MAX_ATTACKS> m_Attacks;

	public:
		constexpr static const RuRu::ComponentType_t Type = COMPONENT_TYPE_SHOOTING;
		constexpr static const size_t InitialAllocation = RuRu::COMPONENT_DEFAULT_ALLOCATION;

		bool active;

		ShootingComponent(int team);
		ShootingComponent* addAttack(IAttack* attack);
		void disableAttack(IAttack* attack);
		void shoot(RuRu::EntityManager& em);
};

#endif
