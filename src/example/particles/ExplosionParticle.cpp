#include "example/particles/ExplosionParticle.h"

ExplosionParticle::ExplosionParticle(double x, double y, double speedX, double speedY, int life, ALLEGRO_COLOR color)
	: m_X(x), m_Y(y), m_SpeedX(speedX), m_SpeedY(speedY), m_Life(life), m_Color(color) { }

bool ExplosionParticle::update()
{
	m_X += m_SpeedX;
	m_Y += m_SpeedY;
	m_Life --;
	
	return (m_Life > 0);
}

void ExplosionParticle::render() const
{
	al_put_pixel((int)m_X, (int)m_Y, m_Color);
}
