#include "example/EntitySpawner.h"

#include "example/components/EntityIdentifierComponent.h"
#include "example/components/PositionComponent.h"
#include "example/components/PhysicsComponent.h"
#include "example/components/PlayerControlComponent.h"
#include "example/components/RenderComponent.h"
#include "example/components/BoundryCheckComponent.h"
#include "example/components/CollisionComponent.h"
#include "example/components/ShootingComponent.h"
#include "example/components/DamageDealingComponent.h"
#include "example/components/DamageableComponent.h"

EntitySpawner::EntitySpawner(RuRu::EntityManager* em)
	: m_Em(em) { }

EntityHandle_t EntitySpawner::spawnPlayer(double x, double y)
{
	EntityHandle_t entity = m_Em->createEntity();
	m_Em->addComponent<EntityIdentifierComponent>(entity, ENTITY_PLAYER);
	m_Em->addComponent<PositionComponent>(entity, x, y);
	m_Em->addComponent<RenderComponent>(entity, 25.0, al_map_rgb(0, 160, 0));
	m_Em->addComponent<PhysicsComponent>(entity, 15, 0.5, 0.75);
	m_Em->addComponent<BoundryCheckComponent>(entity, BoundryCheckComponent::PUSH_ENTITY, true, true, true, true);
	m_Em->addComponent<CollisionComponent>(entity, m_Em->getComponentAccessor<PositionComponent>(entity), 20.0, 20.0);
	m_Em->addComponent<PlayerControlComponent>(entity, ALLEGRO_KEY_LEFT, ALLEGRO_KEY_RIGHT, ALLEGRO_KEY_UP, ALLEGRO_KEY_DOWN, ALLEGRO_KEY_SPACE);
	m_Em->addComponent<ShootingComponent>(entity, m_Em->getComponentAccessor<PositionComponent>(entity), 20, PLAYER_TEAM);
	m_Em->addComponent<DamageableComponent>(entity, PLAYER_TEAM, 500);

	return entity;
}

EntityHandle_t EntitySpawner::spawnPlayerBullet(double x, double y)
{
	EntityHandle_t entity = m_Em->createEntity();
	m_Em->addComponent<PositionComponent>(entity, x, y);
	m_Em->addComponent<RenderComponent>(entity, 5, al_map_rgb(200, 160, 0));
	m_Em->addComponent<BoundryCheckComponent>(entity, BoundryCheckComponent::DESTROY_ENTITY, true, true, true, true);
	m_Em->addComponent<CollisionComponent>(entity, m_Em->getComponentAccessor<PositionComponent>(entity), 5.0, 5.0);
	m_Em->addComponent<PhysicsComponent>(entity, 17, 17, 0)->accelerateY(-1);
	m_Em->addComponent<DamageDealingComponent>(entity, PLAYER_TEAM, 250, false);

	return entity;
}

EntityHandle_t EntitySpawner::spawnEnemyBullet(double x, double y)
{
	EntityHandle_t entity = m_Em->createEntity();
	m_Em->addComponent<PositionComponent>(entity, x, y);
	m_Em->addComponent<RenderComponent>(entity, 5, al_map_rgb(250, 20, 0));
	m_Em->addComponent<BoundryCheckComponent>(entity, BoundryCheckComponent::DESTROY_ENTITY, true, true, true, true);
	m_Em->addComponent<CollisionComponent>(entity, m_Em->getComponentAccessor<PositionComponent>(entity), 5.0, 5.0);
	m_Em->addComponent<PhysicsComponent>(entity, 17, 17, 0)->accelerateY(1);
	m_Em->addComponent<DamageDealingComponent>(entity, ENEMY_TEAM, 250, false);

	return entity;
}

EntityHandle_t EntitySpawner::spawnEnemy(double x, double y)
{
	EntityHandle_t entity = m_Em->createEntity();
	m_Em->addComponent<EntityIdentifierComponent>(entity, ENTITY_ENEMY);
	m_Em->addComponent<PositionComponent>(entity, x, y);
	m_Em->addComponent<RenderComponent>(entity, 20, al_map_rgb(160, 0, 0));
	m_Em->addComponent<BoundryCheckComponent>(entity, BoundryCheckComponent::DESTROY_ENTITY, false, false, false, true);
	m_Em->addComponent<CollisionComponent>(entity, m_Em->getComponentAccessor<PositionComponent>(entity), 20.0, 20.0);
	m_Em->addComponent<PhysicsComponent>(entity, 8, 8, 0)->accelerateY(1);
	m_Em->addComponent<DamageDealingComponent>(entity, ENEMY_TEAM, 1000, true);
	m_Em->addComponent<DamageableComponent>(entity, ENEMY_TEAM, 500);
	m_Em->addComponent<ShootingComponent>(entity, m_Em->getComponentAccessor<PositionComponent>(entity), 20, ENEMY_TEAM);
	
	return entity;
}
