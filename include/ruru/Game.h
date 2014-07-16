#ifndef H_GAME
#define H_GAME

#include "ruru/RuRu.h"
#include "ruru/Config.h"
#include "ruru/IScene.h"
#include "ruru/services/IDataService.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <stack>

NS_RURU_BEGIN

class Game
{
	private:
		// Global data handler
		class DataService : public IDataService
		{
			friend ServiceLocator;

			private:
				Game& m_Parent;

			public:
				DataService(Game& parent);
				virtual int getScreenWidth();
				virtual int getScreenHeight();
				virtual uint64_t getGameFrameCount();
		} m_DataService;


		// Settings
		Config* m_Config;

		// State
		uint64_t m_FrameCount;
		int m_FrameCountThisSecond;
		double m_LastFrameRate;
		double m_LastSecondTime;
		bool m_GameActive;
		std::stack<IScene*> m_SceneStack;
		ServiceLocator m_ServiceLocator;

		// Allegro controls
		ALLEGRO_DISPLAY* 		m_Display;
		ALLEGRO_EVENT_QUEUE* 	m_EventQueue;
		ALLEGRO_TIMER* 			m_RedrawTimer;		

		// Helper Methods
		IScene* getCurrentScene();
		void calculateFrameRate();


	public:
		Game(Config* config);
		~Game();

		void initialise();
		void run();

		void pushScene(IScene* state);
		void popScene();
		void changeScene(IScene* state);
		void quit();
	
		ServiceLocator* getServices();

		ALLEGRO_BITMAP* screen();
};

NS_RURU_END
#endif
