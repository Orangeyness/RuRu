#include "example/buffs/SplitAttackBuff.h"
#include "example/components/ShootingComponent.h"
#include "example/attacks/PlayerSplitAttack.h"

SplitAttackBuff::SplitAttackBuff() { }

void SplitAttackBuff::bind(RuRu::EntityManager& em, RuRu::EntityHandle_t entityToBuff)
{
	RuRu::Entity* e = em.tryGet(entityToBuff);
	if (e == nullptr) return;

	if (e->hasComponent<ShootingComponent>())
	{
		ShootingComponent* sc = e->getComponent<ShootingComponent>();
		
		sc->addAttack(IAttack::instance<PlayerSplitAttack>());
	}
}

void SplitAttackBuff::unbind(RuRu::EntityManager& em, RuRu::EntityHandle_t entityToDebuff)
{
	RuRu::Entity* e = em.tryGet(entityToDebuff);
	if (e == nullptr) return;

	if (e->hasComponent<ShootingComponent>())
	{
		ShootingComponent* sc = e->getComponent<ShootingComponent>();
		
		sc->disableAttack(IAttack::instance<PlayerSplitAttack>());
	}
}

int SplitAttackBuff::getBuffType()
{
	return 1;
}

int SplitAttackBuff::getLifeTime()
{
	return 40 * 30;
}
