#ifndef H_IBUFF
#define H_IBUFF

#include "ruru/entity/EntityManager.h"

class IBuff
{
	public:
		template<class T>
		static IBuff* instance()
		{
			static T* instance = new T();
			return instance;
		}

		virtual void bind(RuRu::EntityManager& em, RuRu::EntityHandle_t entityToBuff) = 0;
		virtual void unbind(RuRu::EntityManager& em, RuRu::EntityHandle_t entityToDebuff) = 0;
		virtual int getBuffType() = 0;
		virtual int getLifeTime() = 0;

};


#endif
