#ifndef H_CONFIG
#define H_CONFIG

#define CONFIG_DEFAULT_RESOLUTION_WIDTH 800
#define CONFIG_DEFAULT_RESOLUTION_HEIGHT 600
#define CONFIG_DEFAULT_FULLSCREEN 0
#define CONFIG_DEFAULT_FRAME_SPEED 60

#include <allegro5/allegro5.h>
#include <string>

#include "ruru/RuRu.h"

NS_RURU_BEGIN

class Config
{
	private:
		ALLEGRO_CONFIG* m_Config;
	
		int 	m_ResolutionWidth;
		int 	m_ResolutionHeight;
		bool 	m_Fullscreen;
		int 	m_FrameSpeed;

		void 	saveResolutionWidth();
		void 	saveResolutionHeight();
		void 	saveFullscreen();
		void 	saveFrameSpeed();
				
		void 	loadResolutionWidth();
		void 	loadResolutionHeight();
		void	loadFullscreen();
		void 	loadFrameSpeed();

	public:
		Config();
		~Config();

		int getResolutionWidth() const;
		int getResolutionHeight() const;
		bool getFullscreen() const;
		int getFrameSpeed() const;
	
		void setResolutionWidth(int width);
		void setResolutionHeight(int height);
		void setFullscreen(bool fullscreen);
		void setFrameSpeed(int frameSpeed);

		void load(std::string filename);
		void save(std::string filename);
};

NS_RURU_END
#endif
