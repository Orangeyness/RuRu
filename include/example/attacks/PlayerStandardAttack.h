#ifndef H_PLAYER_STANDARD_ATTACK
#define H_PLAYER_STANDARD_ATTACK

#include "example/attacks/IAttack.h"

class PlayerStandardAttack : public IAttack
{
	friend IAttack;

	protected:
		PlayerStandardAttack();

	public:
		virtual int getReloadTime() const;
		virtual int getAttackType() const;
		virtual void cast(double x, double y, RuRu::EntityManager& em) const;
};

#endif
