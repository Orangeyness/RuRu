set (GAME_FILES
	main.cpp
	GamePlayScene.cpp
	EntitySpawner.cpp
	components/PhysicsComponent.cpp
	components/BoundryCheckComponent.cpp
	systems/PlayerControlSystem.cpp
	systems/MovementSystem.cpp
	systems/RenderSystem.cpp
	systems/ShootingSystem.cpp
	systems/CollisionSystem.cpp
	particles/ExplosionParticle.cpp
	)

add_library(GameComponents OBJECT ${GAME_FILES})
