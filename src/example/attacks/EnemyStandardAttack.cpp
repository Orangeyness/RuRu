#include "example/attacks/EnemyStandardAttack.h"

#include "example/components/PositionComponent.h"
#include "example/components/RenderComponent.h"
#include "example/components/BoundryCheckComponent.h"
#include "example/components/CollisionComponent.h"
#include "example/components/PhysicsComponent.h"
#include "example/components/DamageDealingComponent.h"

#include "example/EntitySpawner.h"

EnemyStandardAttack::EnemyStandardAttack() { }

int EnemyStandardAttack::getReloadTime() const 
{
	return 30;
}

int EnemyStandardAttack::getAttackType() const
{
	return 0;
}

void EnemyStandardAttack::cast(double x, double y, RuRu::EntityManager& em) const
{
	RuRu::EntityHandle_t entity = em.createEntity();
	em.addComponent<PositionComponent>(entity, x, y);
	em.addComponent<RenderComponent>(entity, 5, al_map_rgb(255, 0, 0));
	em.addComponent<BoundryCheckComponent>(entity, BoundryCheckComponent::DESTROY_ENTITY, true, true, true, true);
	em.addComponent<CollisionComponent>(entity, em.getComponentAccessor<PositionComponent>(entity), 5.0, 5.0);
	em.addComponent<PhysicsComponent>(entity, 15, 15, 0)->accelerateY(1);
	em.addComponent<DamageDealingComponent>(entity, ENEMY_TEAM, 250, false);
}
