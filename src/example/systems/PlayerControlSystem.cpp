#include "example/systems/PlayerControlSystem.h"

#include "example/components/PlayerControlComponent.h"
#include "example/components/PhysicsComponent.h"
#include "example/components/ShootingComponent.h"

#include <allegro5/allegro.h>

void PlayerControlSystem::ProcessInput(RuRu::Entity* entity)
{
	if (entity == nullptr) return;

	if (! entity->hasComponent<PhysicsComponent>()) return;
	if (! entity->hasComponent<PlayerControlComponent>()) return;

	ALLEGRO_KEYBOARD_STATE keyboardState;
	al_get_keyboard_state(&keyboardState);

	PhysicsComponent& movement = entity->getComponent<PhysicsComponent>();
	PlayerControlComponent& control = entity->getComponent<PlayerControlComponent>();

	if (al_key_down(&keyboardState, control.leftKey)) movement.accelerateX(-1);
	if (al_key_down(&keyboardState, control.rightKey)) movement.accelerateX(+1);
	if (al_key_down(&keyboardState, control.upKey)) movement.accelerateY(-1);
	if (al_key_down(&keyboardState, control.downKey)) movement.accelerateY(+1);

	if (! entity->hasComponent<ShootingComponent>()) return;
	ShootingComponent& shooting = entity->getComponent<ShootingComponent>();
	shooting.active = al_key_down(&keyboardState, control.spaceKey);
}
