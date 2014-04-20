#ifndef H_SHOOTING_COMPONENT
#define H_SHOOTING_COMPONENT

#include "ruru/components/ComponentAccessor.h"
#include "example/EntitySpawner.h"
#include "example/components/ComponentTypes.h"
#include "example/components/PositionComponent.h"

class ShootingComponent
{
	private:
		RuRu::ComponentAccessor<PositionComponent> m_Position;
		int m_ReloadTime;
		int m_ReloadTimeRemaining;
		int m_Team;

	public:
		bool active;

		constexpr static const RuRu::ComponentType_t Type = COMPONENT_TYPE_SHOOTING;
		constexpr static const size_t InitialAllocation = RuRu::COMPONENT_DEFAULT_ALLOCATION;
		ShootingComponent(RuRu::ComponentAccessor<PositionComponent> position, int reloadTime, int team)
			: 	m_Position(position), 
				m_ReloadTime(reloadTime), 
				m_ReloadTimeRemaining(0), 
				m_Team(team),
				active(true) 
		{ }

		void shoot(EntitySpawner& es)
		{
			m_ReloadTimeRemaining --;

			if (active && m_ReloadTimeRemaining < 0)
			{	
				if (m_Team == PLAYER_TEAM) 
					es.spawnPlayerBullet(m_Position->x, m_Position->y - 20);
				else
					es.spawnEnemyBullet(m_Position->x, m_Position->y - 20);

				m_ReloadTimeRemaining = m_ReloadTime;
			}
		}

};


#endif
