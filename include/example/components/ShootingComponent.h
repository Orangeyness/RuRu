#ifndef H_SHOOTING_COMPONENT
#define H_SHOOTING_COMPONENT

#include "ruru/entity/EntityManager.h"
#include "ruru/components/ComponentAccessor.h"
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

class ShootingComponent
{
	private:
		RuRu::ComponentAccessor<PositionComponent> m_Position;
		std::array<AttackData, MAX_ATTACKS> m_Attacks;

	public:
		bool active;

		constexpr static const RuRu::ComponentType_t Type = COMPONENT_TYPE_SHOOTING;
		constexpr static const size_t InitialAllocation = RuRu::COMPONENT_DEFAULT_ALLOCATION;

		ShootingComponent(RuRu::ComponentAccessor<PositionComponent> position, int team);
		ShootingComponent* addAttack(IAttack* attack);
		void disableAttack(int attackSlot);
		void shoot(RuRu::EntityManager& em);
};

#endif
