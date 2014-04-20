#include "example/components/PhysicsComponent.h"

#include <algorithm>

PhysicsComponent::PhysicsComponent(double speedMax, double acceleration, double friction)
	: m_SpeedMax(speedMax), m_Acceleration(acceleration), m_Friction(friction), m_SpeedX(0), m_SpeedY(0) { }

double PhysicsComponent::updateSpeed(double speed)
{
	if (speed < 0) 
		return std::min(speed + m_Friction, 0.0);

	if (speed > 0)
		return std::max(speed - m_Friction, 0.0);
	
	return speed;
}

double PhysicsComponent::limitSpeed(double speed)
{
	if (speed > m_SpeedMax)
		return m_SpeedMax;
	
	if (speed < -m_SpeedMax)
		return -m_SpeedMax;

	return speed;
}

void PhysicsComponent::update(PositionComponent* position)
{
	m_SpeedX = updateSpeed(m_SpeedX);
	m_SpeedY = updateSpeed(m_SpeedY);

	position->x += m_SpeedX;
	position->y += m_SpeedY;
}

void PhysicsComponent::accelerateX(double x)
{
	m_SpeedX = limitSpeed(m_SpeedX + x * (m_Acceleration + m_Friction));
}

void PhysicsComponent::accelerateY(double y)
{
	m_SpeedY = limitSpeed(m_SpeedY + y * (m_Acceleration + m_Friction));
}

void PhysicsComponent::accelerate(double x, double y)
{
	m_SpeedX = limitSpeed(m_SpeedX + x * (m_Acceleration + m_Friction));
	m_SpeedY = limitSpeed(m_SpeedY + y * (m_Acceleration + m_Friction));
}
