#ifndef H_PLAYER_SPLIT_ATTACK
#define H_PLAYER_SPLIT_ATTACK

#include "example/attacks/IAttack.h"

class PlayerSplitAttack : public IAttack
{
	friend IAttack;

	protected:
		PlayerSplitAttack();

	public:
		virtual int getReloadTime() const;
		virtual int getAttackType() const;
		virtual void cast(double x, double y, RuRu::EntityManager& em) const;
};

#endif
