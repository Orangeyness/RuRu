#ifndef H_EXPLOSION_PARTICLE
#define H_EXPLOSION_PARTICLE

#include <allegro5/allegro.h>

class ExplosionParticle
{
	private:
		double m_X;
		double m_Y;
		double m_SpeedX;
		double m_SpeedY;
		int m_Life;
		ALLEGRO_COLOR m_Color;

	public:
		ExplosionParticle(double x, double y, double speedX, double speedY, int life, ALLEGRO_COLOR color);

		bool update();
		void render() const;
};

#endif
