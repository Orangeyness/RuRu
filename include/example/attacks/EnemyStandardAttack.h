#ifndef H_ENEMY_STANDARD_ATTACK
#define H_ENEMY_STANDARD_ATTACK

#include "example/attacks/IAttack.h"

class EnemyStandardAttack : public IAttack
{
	friend IAttack;

	protected:
		EnemyStandardAttack();

	public:
		virtual int getReloadTime() const;
		virtual int getAttackType() const;
		virtual void cast(double x, double y, RuRu::EntityManager& em) const;
};

#endif
