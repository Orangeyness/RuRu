#include "example/components/ShootingComponent.h"

ShootingComponent::ShootingComponent(RuRu::ComponentAccessor<PositionComponent> position, int team)
	: 	m_Position(position), 
		m_Attacks(),
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
			attack.Handle->cast(m_Position->x, m_Position->y, em);
			attack.ReloadTime = attack.Handle->getReloadTime();
		}
	}
}
