#ifndef _MENU_STATE_H
#define _MENU_STATE_H

#include "game_state.h"
#include "texture.h"

class MenuState : public GameState {
public:
	void init();
	void cleanup();
	
	void pause();
	void resume();
	
	void update();
	void render();
private:
	Texture tex;
};

#endif
