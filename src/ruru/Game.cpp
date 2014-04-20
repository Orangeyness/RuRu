#include "ruru/Game.h"
#include "ruru/services/ServiceLocator.h"
using namespace RuRu;

#include <iostream>

Game::Game(Config* config)
	: m_DataService(*this)
{
	m_Config = config;
	
	// State
	m_FrameCount = 0;
	m_FrameCountThisSecond = 0;
	m_LastFrameRate = 0;
	m_LastSecondTime = 0;

	m_GameActive = false;

	// Allegro Engine
	m_Display = NULL;
	m_EventQueue = NULL;
	m_RedrawTimer = NULL;

	//Register Services
	ServiceLocator::AddService<IDataService>(&m_DataService);
}

Game::~Game()
{
	// Cleanup allegro engine objects
	if (m_RedrawTimer) al_destroy_timer(m_RedrawTimer);
	if (m_Display) al_destroy_display(m_Display);
	if (m_EventQueue) al_destroy_event_queue(m_EventQueue);

	// Cleanup Scene stack
	while(!m_SceneStack.empty())
	{
		delete m_SceneStack.top();
		m_SceneStack.pop();
	}

	ServiceLocator::RemoveService<IDataService>(&m_DataService);
}

void Game::initialise()
{
	if (!al_init())
	{
		throw std::runtime_error("al_init failed");
	}	

	if (!al_init_font_addon())
	{
		throw std::runtime_error("al_init_font_addon failed");
	}

	if (!al_init_image_addon())
	{
		throw std::runtime_error("al_init_image_addon failed");
	}

	if (!al_install_keyboard())
	{
		throw std::runtime_error("al_install_keyboard failed");
	}

	if (!al_install_mouse())
	{
		throw std::runtime_error("al_install_mouse failed");
	}

	//Temporary Display Options
	al_set_new_display_flags(ALLEGRO_OPENGL);
	al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST);
	al_set_new_display_option(ALLEGRO_SAMPLES, 4, ALLEGRO_SUGGEST);
	al_set_new_display_option(ALLEGRO_RENDER_METHOD, 1, ALLEGRO_SUGGEST);
	al_set_new_display_option(ALLEGRO_VSYNC, 2, ALLEGRO_REQUIRE);
	al_set_new_display_option(ALLEGRO_CAN_DRAW_INTO_BITMAP, 1, ALLEGRO_SUGGEST);

	int originalDisplayFlags = al_get_new_display_flags();
	int displayFlags = 0;
	if (m_Config->getFullscreen())
	{
		displayFlags = displayFlags | ALLEGRO_FULLSCREEN_WINDOW | ALLEGRO_NOFRAME;
	}

	al_set_new_display_flags(displayFlags);
	al_set_new_bitmap_flags(ALLEGRO_MIN_LINEAR | ALLEGRO_MAG_LINEAR | ALLEGRO_VIDEO_BITMAP);

	if (m_Config->getResolutionWidth() < 0 || m_Config->getResolutionHeight() < 0)
	{
		ALLEGRO_DISPLAY_MODE largest_display_mode;
		al_get_display_mode(al_get_num_display_modes() - 1, &largest_display_mode);

		m_Config->setResolutionWidth(largest_display_mode.width);
		m_Config->setResolutionHeight(largest_display_mode.height);
	}

	m_Display = al_create_display(m_Config->getResolutionWidth(), m_Config->getResolutionHeight());
	if (!m_Display)
	{
		throw std::runtime_error("failed to create display");
	}
	al_set_new_display_flags(originalDisplayFlags);

	m_RedrawTimer = al_create_timer(ALLEGRO_BPS_TO_SECS(m_Config->getFrameSpeed()));
	if (!m_RedrawTimer)
	{
		throw std::runtime_error("failed to create timer");
	}

	m_EventQueue = al_create_event_queue();
	if (!m_EventQueue)
	{
		throw std::runtime_error("failed to create event queue");
	}

	al_register_event_source(m_EventQueue, al_get_display_event_source(m_Display));
	al_register_event_source(m_EventQueue, al_get_timer_event_source(m_RedrawTimer));
	al_register_event_source(m_EventQueue, al_get_keyboard_event_source());
}

void Game::run()
{
	al_start_timer(m_RedrawTimer);
	
	m_GameActive = true;
	m_LastSecondTime = al_current_time();
	bool redrawScene = true;

	while(m_GameActive)
	{
		ALLEGRO_EVENT event;
		al_wait_for_event(m_EventQueue, &event);

		switch(event.type)
		{
			case ALLEGRO_EVENT_DISPLAY_CLOSE:
				m_GameActive = false;
				break;

			case ALLEGRO_EVENT_KEY_DOWN:
				if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
					m_GameActive = false;
				break;

			case ALLEGRO_EVENT_TIMER:
				redrawScene = true;
				break;
		}
		
		if (redrawScene && al_is_event_queue_empty(m_EventQueue))
		{
			IScene* currentScene = getCurrentScene();
			currentScene->update(this);
			currentScene->draw(this);

			al_flip_display();

			calculateFrameRate();

			redrawScene = false;
		}
	}

}

void Game::pushScene(IScene* scene)
{
	if (!m_SceneStack.empty())
	{
		m_SceneStack.top()->pause();
	}
	
	m_SceneStack.push(scene);
}

void Game::popScene()
{
	if (m_SceneStack.empty())
		throw std::runtime_error("Unexpected empty scene stack");

	delete m_SceneStack.top();
	m_SceneStack.pop();

	if (!m_SceneStack.empty())
	{
		m_SceneStack.top()->resume();
	}
}

void Game::changeScene(IScene* scene)
{
	if (m_SceneStack.empty())
		throw std::runtime_error("Unexpected empty scene stack");

	delete m_SceneStack.top();
	m_SceneStack.pop();
	
	m_SceneStack.push(scene);
}

void Game::quit()
{
	m_GameActive = false;
}

ALLEGRO_BITMAP* Game::screen()
{
	return al_get_backbuffer(m_Display);
}

Game::DataService::DataService(Game& parent)
	: m_Parent(parent) { }

int Game::DataService::getScreenWidth()
{
	return al_get_display_width(m_Parent.m_Display);
}

int Game::DataService::getScreenHeight()
{
	return al_get_display_height(m_Parent.m_Display);
}

uint64_t Game::DataService::getGameFrameCount()
{
	return m_Parent.m_FrameCount;
}

// Helper Methods
IScene* Game::getCurrentScene()
{
	if (m_SceneStack.empty())
		throw std::runtime_error("Unexpected empty scene stack");
	
	return m_SceneStack.top();
}

void Game::calculateFrameRate()
{
	m_FrameCount += 1;
	m_FrameCountThisSecond += 1;

	double currentTime = al_current_time();
	if (currentTime - m_LastSecondTime >= 1.0)
	{
		m_LastFrameRate = m_FrameCountThisSecond / (currentTime - m_LastSecondTime);
		m_LastSecondTime = currentTime;
		m_FrameCountThisSecond = 0;

		std::cout << m_LastFrameRate << std::endl;
	}
}
