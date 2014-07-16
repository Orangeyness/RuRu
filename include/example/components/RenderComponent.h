#ifndef H_RENDER_COMPONENT
#define H_RENDER_COMPONENT

#include "ruru/components/ComponentMixin.h"
#include "example/components/ComponentTypes.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

enum RenderType { TRIANGLE_UP, TRIANGLE_DOWN, CIRCLE };

class RenderComponent : public RuRu::ComponentMixin
{
	private:
		double m_Size;
		ALLEGRO_COLOR m_Color;
		RenderType m_Type;
		bool m_Flashing;
		ALLEGRO_COLOR m_FlashColor;

	public:
		constexpr static const RuRu::ComponentType_t Type = COMPONENT_TYPE_RENDER;
		constexpr static const size_t InitialAllocation = RuRu::COMPONENT_DEFAULT_ALLOCATION;
	
		RenderComponent(double radius, ALLEGRO_COLOR color) 
			: m_Size(radius), m_Color(color), m_Type(TRIANGLE_DOWN), m_Flashing(false) { }

		RenderComponent(double radius, ALLEGRO_COLOR color, RenderType type) 
			: m_Size(radius), m_Color(color), m_Type(type), m_Flashing(false) { }

		inline void setFlash() { m_Flashing = true; m_FlashColor = al_map_rgb(255, 255, 255); }
		inline void setFlash(ALLEGRO_COLOR flashColor) { m_Flashing = true; m_FlashColor = flashColor; }

		inline void render(double x, double y)
		{
			ALLEGRO_COLOR color = m_Flashing ? m_FlashColor : m_Color;

			switch(m_Type)
			{
			case TRIANGLE_UP:
				al_draw_filled_triangle(x, y - m_Size, x - m_Size/2, y + m_Size/2, x + m_Size/2, y + m_Size/2, color);
				break;

			case TRIANGLE_DOWN:
				al_draw_filled_triangle(x, y + m_Size, x - m_Size/2, y - m_Size/2, x + m_Size/2, y - m_Size/2, color);
				break;

			case CIRCLE:
				al_draw_filled_circle(x, y, m_Size, color);
				break;
			}

			m_Flashing = false;
		}

};


#endif
