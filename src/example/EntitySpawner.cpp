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
#include "example/components/BuffableComponent.h"
#include "example/components/BuffHolderComponent.h"
#include "example/components/LifeTimeComponent.h"

#include "example/attacks/PlayerStandardAttack.h"
#include "example/attacks/PlayerSplitAttack.h"
#include "example/attacks/EnemyStandardAttack.h"

#include "example/buffs/SplitAttackBuff.h"

EntitySpawner::EntitySpawner(RuRu::EntityManager* em)
	: m_Em(em) { }

EntityHandle_t EntitySpawner::spawnPlayer(double x, double y)
{
	EntityHandle_t entity = m_Em->createEntity();
	m_Em->addComponent<EntityIdentifierComponent>(entity, ENTITY_PLAYER);
	m_Em->addComponent<PositionComponent>(entity, x, y);
	m_Em->addComponent<RenderComponent>(entity, 25.0, al_map_rgb(0, 160, 0), TRIANGLE_UP);
	m_Em->addComponent<PhysicsComponent>(entity, 15, 0.5, 0.75);
	m_Em->addComponent<BoundryCheckComponent>(entity, BoundryCheckComponent::PUSH_ENTITY, true, true, true, true);
	m_Em->addComponent<CollisionComponent>(entity, 20.0, 20.0);
	m_Em->addComponent<PlayerControlComponent>(entity, ALLEGRO_KEY_LEFT, ALLEGRO_KEY_RIGHT, ALLEGRO_KEY_UP, ALLEGRO_KEY_DOWN, ALLEGRO_KEY_SPACE);
	m_Em->addComponent<DamageableComponent>(entity, PLAYER_TEAM, 500);

	m_Em->addComponent<ShootingComponent>(entity, PLAYER_TEAM)
		.addAttack(IAttack::instance<PlayerStandardAttack>());

	m_Em->addComponent<BuffableComponent>(entity, entity);

	return entity;
}

EntityHandle_t EntitySpawner::spawnEnemy(double x, double y)
{
	EntityHandle_t entity = m_Em->createEntity();
	m_Em->addComponent<EntityIdentifierComponent>(entity, ENTITY_ENEMY);
	m_Em->addComponent<PositionComponent>(entity, x, y);
	m_Em->addComponent<RenderComponent>(entity, 20, al_map_rgb(160, 0, 0));
	m_Em->addComponent<BoundryCheckComponent>(entity, BoundryCheckComponent::DESTROY_ENTITY, false, false, false, true);
	m_Em->addComponent<CollisionComponent>(entity, 20.0, 20.0);
	m_Em->addComponent<PhysicsComponent>(entity, 8, 8, 0).accelerateY(1);
	m_Em->addComponent<DamageDealingComponent>(entity, ENEMY_TEAM, 1000, true);
	m_Em->addComponent<DamageableComponent>(entity, ENEMY_TEAM, 500);

	m_Em->addComponent<ShootingComponent>(entity, ENEMY_TEAM)
		.addAttack(IAttack::instance<EnemyStandardAttack>());
	
	return entity;
}

EntityHandle_t EntitySpawner::spawnBuff(double x, double y, IBuff* buff)
{
	EntityHandle_t entity = m_Em->createEntity();
	m_Em->addComponent<PositionComponent>(entity, x, y);
	m_Em->addComponent<LifeTimeComponent>(entity, 200);
	m_Em->addComponent<PhysicsComponent>(entity, 2, 2, 0).accelerate(1 - rand() % 2, 1 - rand() % 2);
	m_Em->addComponent<RenderComponent>(entity, 6, al_map_rgb(120, 120, 0), CIRCLE);
	m_Em->addComponent<CollisionComponent>(entity, 7.0, 7.0);
	m_Em->addComponent<BuffHolderComponent>(entity, buff);

	return entity;

}
