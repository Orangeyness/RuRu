set (GAME_FILES
	main.cpp
	GamePlayScene.cpp
	EntitySpawner.cpp
	components/PhysicsComponent.cpp
	components/BoundryCheckComponent.cpp
	components/ShootingComponent.cpp
	systems/PlayerControlSystem.cpp
	systems/MovementSystem.cpp
	systems/RenderSystem.cpp
	systems/ShootingSystem.cpp
	systems/CollisionSystem.cpp
	particles/ExplosionParticle.cpp
	attacks/PlayerStandardAttack.cpp
	attacks/PlayerSplitAttack.cpp
	attacks/EnemyStandardAttack.cpp
	)

add_library(GameComponents OBJECT ${GAME_FILES})
