#ifndef H_IATTACK
#define H_IATTACK

#include "ruru/entities/EntityManager.h"

class IAttack
{
	public:
		template<class T>
		static IAttack* instance()
		{
			static T* instance = new T();
			return instance;
		}

		virtual int getReloadTime() const = 0;
		virtual int getAttackType() const = 0;

		virtual void cast(double x, double y, RuRu::EntityManager& em) const = 0;
};

#endif
