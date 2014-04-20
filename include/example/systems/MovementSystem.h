#ifndef H_MOVEMENT_SYSTEM
#define H_MOVEMENT_SYSTEM

#include "ruru/entity/EntityManager.h"

class MovementSystem
{
	public:
		static void Move(const RuRu::EntityManager& entityManager);
		static void BoundryCheck(RuRu::EntityManager& entityManager, double width, double height);
};


#endif
