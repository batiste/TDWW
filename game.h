#ifndef _GAME_H
#define _GAME_H

#include "base.h"
#include "opengl.h"

class GameState;

class Game {
public:
	static Game &getInstance();

	void init();
	void cleanup();
	void run();
	
	void switchState( GameState *state );
	void pushState( GameState *state );
	void popState();
private:
	Game() {}
	Game( Game const& );
	void operator=( Game const& );
	
	bool running;
	std::vector< GameState* > states;
	SDL_Window *window;
	SDL_GLContext glContext;
};

#endif
