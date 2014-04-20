#ifndef H_ISCENE
#define H_ISCENE

#include "ruru/RuRu.h"
NS_RURU_BEGIN

class Game;

class IScene
{
	public:
		virtual void pause() = 0;
		virtual void resume() = 0;
		
		virtual void update(Game* game) = 0;
		virtual void draw(Game* game) = 0;
		virtual ~IScene() {}
};

NS_RURU_END
#endif
