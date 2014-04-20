#ifndef H_SPLIT_ATTACK_BUFF
#define H_SPLIT_ATTACK_BUFF

#include "example/buffs/IBuff.h"

class SplitAttackBuff : public IBuff
{
	friend IBuff;

	protected:
		SplitAttackBuff();

	public:
		virtual void bind(RuRu::EntityManager& em, RuRu::EntityHandle_t entityToBuff);
		virtual void unbind(RuRu::EntityManager& em, RuRu::EntityHandle_t entityToDebuff);
		virtual int getBuffType();
		virtual int getLifeTime();

};


#endif
