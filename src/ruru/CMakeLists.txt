set(ENGINE_FILES
	Game.cpp
	Config.cpp
	entity/EntityManager.cpp
	services/ServiceLocator.cpp
	events/EventService.cpp
	)

add_library(EngineCore OBJECT ${ENGINE_FILES})
