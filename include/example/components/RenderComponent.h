#ifndef H_RENDER_COMPONENT
#define H_RENDER_COMPONENT

#include "example/components/ComponentTypes.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

class RenderComponent 
{
	private:
		double radius;
		ALLEGRO_COLOR color;

	public:
		constexpr static const RuRu::ComponentType_t Type = COMPONENT_TYPE_RENDER;
		constexpr static const size_t InitialAllocation = RuRu::COMPONENT_DEFAULT_ALLOCATION;
	
		RenderComponent(double _radius, ALLEGRO_COLOR _color) : radius(_radius), color(_color) { }

		inline void render(double x, double y)
		{
			al_draw_filled_triangle(x, y - radius, x - radius/2, y + radius/2, x + radius/2, y + radius/2, color);
		}

};


#endif
