#include "example/components/ShootingComponent.h"

ShootingComponent::ShootingComponent(int team)
	:	m_Attacks(),
		active(true) { }

ShootingComponent* ShootingComponent::addAttack(IAttack* attack)
{
	m_Attacks[attack->getAttackType()].Handle = attack;
	m_Attacks[attack->getAttackType()].ReloadTime = attack->getReloadTime();
	m_Attacks[attack->getAttackType()].Active = true;

	return this;
}

void ShootingComponent::disableAttack(IAttack* attack)
{
	m_Attacks[attack->getAttackType()].Active = false;
}

void ShootingComponent::shoot(RuRu::EntityManager& em)
{
	for(auto& attack : m_Attacks)
	{
		if (! attack.Active) continue;

		attack.ReloadTime --;
		
		if (active && attack.ReloadTime < 0)
		{
			PositionComponent& position = getSiblingComponent<PositionComponent>();

			attack.Handle->cast(position.x, position.y, em);
			attack.ReloadTime = attack.Handle->getReloadTime();
		}
	}
}
