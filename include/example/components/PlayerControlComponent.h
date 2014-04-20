#ifndef H_PLAYER_CONTROL_COMPONENT
#define H_PLAYER_CONTROL_COMPONENT

#include "example/components/ComponentTypes.h"

class PlayerControlComponent 
{
	public:
		constexpr static const RuRu::ComponentType_t Type = COMPONENT_TYPE_PLAYER_CONTROL;
		constexpr static const size_t InitialAllocation = RuRu::COMPONENT_DEFAULT_ALLOCATION;

		typedef size_t Key_t;

		PlayerControlComponent(Key_t left, Key_t right, Key_t up, Key_t down, Key_t space)
			: leftKey(left), rightKey(right), upKey(up), downKey(down), spaceKey(space) { }		

		Key_t leftKey;
		Key_t rightKey;
		Key_t upKey;
		Key_t downKey;
		Key_t spaceKey;
};


#endif
