#ifndef H_POSITION_COMPONENT
#define H_POSITION_COMPONENT

#include "example/components/ComponentTypes.h"

class PositionComponent
{
	public:
		constexpr static const RuRu::ComponentType_t Type = COMPONENT_TYPE_POSITION;
		constexpr static const size_t InitialAllocation = RuRu::COMPONENT_DEFAULT_ALLOCATION;

		PositionComponent() : x(0), y(0) { }
		PositionComponent(double _x, double _y) : x(_x), y(_y) { }

		double x;
		double y;
};


#endif
