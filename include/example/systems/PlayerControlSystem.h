#ifndef H_PLAYER_CONTROL_SYSTEM
#define H_PLAYER_CONTROL_SYSTEM

#include "ruru/entities/Entity.h"

class PlayerControlSystem
{
	public:
		static void ProcessInput(RuRu::Entity* player);
};


#endif
