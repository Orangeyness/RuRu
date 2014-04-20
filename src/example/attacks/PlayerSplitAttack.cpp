#include "example/attacks/PlayerSplitAttack.h"

#include "example/components/PositionComponent.h"
#include "example/components/RenderComponent.h"
#include "example/components/BoundryCheckComponent.h"
#include "example/components/CollisionComponent.h"
#include "example/components/PhysicsComponent.h"
#include "example/components/DamageDealingComponent.h"

#include "example/EntitySpawner.h"

PlayerSplitAttack::PlayerSplitAttack() { }

int PlayerSplitAttack::getReloadTime() const 
{
	return 10;
}

int PlayerSplitAttack::getAttackType() const
{
	return 1;
}

void PlayerSplitAttack::cast(double x, double y, RuRu::EntityManager& em) const
{
	RuRu::EntityHandle_t entity;

	entity = em.createEntity();
	em.addComponent<PositionComponent>(entity, x, y);
	em.addComponent<RenderComponent>(entity, 3, al_map_rgb(200, 160, 0));
	em.addComponent<BoundryCheckComponent>(entity, BoundryCheckComponent::DESTROY_ENTITY, true, true, true, true);
	em.addComponent<CollisionComponent>(entity, em.getComponentAccessor<PositionComponent>(entity), 3.0, 3.0);
	em.addComponent<PhysicsComponent>(entity, 17, 17, 0)
		->accelerate(-0.1, -1);
	em.addComponent<DamageDealingComponent>(entity, PLAYER_TEAM, 250, false);

	entity = em.createEntity();
	em.addComponent<PositionComponent>(entity, x, y);
	em.addComponent<RenderComponent>(entity, 3, al_map_rgb(200, 160, 0));
	em.addComponent<BoundryCheckComponent>(entity, BoundryCheckComponent::DESTROY_ENTITY, true, true, true, true);
	em.addComponent<CollisionComponent>(entity, em.getComponentAccessor<PositionComponent>(entity), 3.0, 3.0);
	em.addComponent<PhysicsComponent>(entity, 17, 17, 0)
		->accelerate(0, -1);
	em.addComponent<DamageDealingComponent>(entity, PLAYER_TEAM, 250, false);

	entity = em.createEntity();
	em.addComponent<PositionComponent>(entity, x, y);
	em.addComponent<RenderComponent>(entity, 3, al_map_rgb(200, 160, 0));
	em.addComponent<BoundryCheckComponent>(entity, BoundryCheckComponent::DESTROY_ENTITY, true, true, true, true);
	em.addComponent<CollisionComponent>(entity, em.getComponentAccessor<PositionComponent>(entity), 3.0, 3.0);
	em.addComponent<PhysicsComponent>(entity, 17, 17, 0)
		->accelerate(0.1, -1);
	em.addComponent<DamageDealingComponent>(entity, PLAYER_TEAM, 250, false);
}
