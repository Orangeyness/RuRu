set(ENGINE_FILES
	Game.cpp
	Config.cpp
	services/ServiceLocator.cpp
	services/ServiceMixin.cpp
	events/EventService.cpp
	particles/ParticleManager.cpp
	)

add_library(EngineCore OBJECT ${ENGINE_FILES})
