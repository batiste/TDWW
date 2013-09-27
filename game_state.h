#ifndef _GAME_STATE_H
#define _GAME_STATE_H

#include "game.h"

class GameState {
public:
	virtual void init() = 0;
	virtual void cleanup() = 0;
	
	virtual void pause() = 0;
	virtual void resume() = 0;
	
	virtual void update() = 0;
	virtual void render() = 0;
private:
	
};

#endif //_GAME_STATE_H
