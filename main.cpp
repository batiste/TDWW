#include "base.h"
#include "game.h"
#include "menu_state.h"

int main( int argc, char *argv[] ) {
	Game &g = Game::getInstance();
	g.init();
	g.switchState( new MenuState() );
	g.run();
	g.cleanup();
	return 0;
}
