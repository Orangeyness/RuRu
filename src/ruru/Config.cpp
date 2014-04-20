#include "ruru/Config.h"

#include <cstdlib>
#include <stdexcept>

using namespace RuRu;

Config::Config()
{
	m_Config = NULL;
	
	m_ResolutionWidth = CONFIG_DEFAULT_RESOLUTION_WIDTH;
	m_ResolutionHeight = CONFIG_DEFAULT_RESOLUTION_HEIGHT;
	m_Fullscreen = CONFIG_DEFAULT_FULLSCREEN;
	m_FrameSpeed = CONFIG_DEFAULT_FRAME_SPEED;
}

void Config::load(std::string filename)
{
	if (m_Config != NULL)
	{
		al_destroy_config(m_Config);
	}

	m_Config = al_load_config_file(filename.c_str());

	if (m_Config == NULL)
	{
		throw std::runtime_error("Config file is missing");
	}

	loadResolutionWidth();
	loadResolutionHeight();
	loadFullscreen();
	loadFrameSpeed();
}

Config::~Config()
{
	if (m_Config != NULL)
	{
		al_destroy_config(m_Config);
	}
}

void Config::saveResolutionWidth()
{
	al_set_config_value(m_Config, "Display", "ResolutionWidth", std::to_string(m_ResolutionWidth).c_str());
}

void Config::saveResolutionHeight()
{
	al_set_config_value(m_Config, "Display", "ResolutionHeight", std::to_string(m_ResolutionHeight).c_str());
}

void Config::saveFullscreen()
{
	al_set_config_value(m_Config, "Display", "Fullscreen", std::to_string((m_Fullscreen ? 1 : 0)).c_str());
}

void Config::saveFrameSpeed()
{
	al_set_config_value(m_Config, "Game", "FrameSpeed", std::to_string(m_FrameSpeed).c_str());
}

void Config::loadResolutionWidth()
{
	const char* val = al_get_config_value(m_Config, "Display", "ResolutionWidth");

	if (val == NULL) return;

	m_ResolutionWidth = strtol(val, NULL, 10);
}

void Config::loadResolutionHeight()
{
	const char* val = al_get_config_value(m_Config, "Display", "ResolutionHeight");

	if (val == NULL) return;

	m_ResolutionHeight = strtol(val, NULL, 10);
}

void Config::loadFullscreen()
{
	const char* val = al_get_config_value(m_Config, "Display", "Fullscreen");

	if (val == NULL) return;

	m_Fullscreen = (strtol(val, NULL, 10) == 1);
}

void Config::loadFrameSpeed()
{
	const char* val = al_get_config_value(m_Config, "Game", "FrameSpeed");

	if (val == NULL) return;

	m_FrameSpeed = strtol(val, NULL, 10);
}

int Config::getResolutionWidth() const { return m_ResolutionWidth; }
int Config::getResolutionHeight() const { return m_ResolutionHeight; }
bool Config::getFullscreen() const { return m_Fullscreen; }
int Config::getFrameSpeed() const { return m_FrameSpeed; }

void Config::setResolutionWidth(int width) { m_ResolutionWidth = width; }
void Config::setResolutionHeight(int height) { m_ResolutionHeight = height; }
void Config::setFullscreen(bool fullscreen) { m_Fullscreen = fullscreen; }
void Config::setFrameSpeed(int frameSpeed) { m_FrameSpeed = frameSpeed; }

void Config::save(std::string filename)
{
	if (m_Config == NULL)
	{
		m_Config = al_create_config();
	}

	saveResolutionWidth();
	saveResolutionHeight();
	saveFullscreen();
	saveFrameSpeed();	

	al_save_config_file(filename.c_str(), m_Config);
}
