#include "example/attacks/PlayerStandardAttack.h"

#include "example/components/PositionComponent.h"
#include "example/components/RenderComponent.h"
#include "example/components/BoundryCheckComponent.h"
#include "example/components/CollisionComponent.h"
#include "example/components/PhysicsComponent.h"
#include "example/components/DamageDealingComponent.h"

#include "example/EntitySpawner.h"

PlayerStandardAttack::PlayerStandardAttack() { }

int PlayerStandardAttack::getReloadTime() const 
{
	return 10;
}

int PlayerStandardAttack::getAttackType() const
{
	return 0;
}

void PlayerStandardAttack::cast(double x, double y, RuRu::EntityManager& em) const
{
	RuRu::EntityHandle_t entity = em.createEntity();
	em.addComponent<PositionComponent>(entity, x, y);
	em.addComponent<RenderComponent>(entity, 5, al_map_rgb(200, 160, 0));
	em.addComponent<BoundryCheckComponent>(entity, BoundryCheckComponent::DESTROY_ENTITY, true, true, true, true);
	em.addComponent<CollisionComponent>(entity, em.getComponentAccessor<PositionComponent>(entity), 5.0, 5.0);
	em.addComponent<PhysicsComponent>(entity, 17, 17, 0)->accelerateY(-1);
	em.addComponent<DamageDealingComponent>(entity, PLAYER_TEAM, 250, false);
}
