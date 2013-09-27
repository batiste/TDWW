#include "base.h"
#include "game.h"

int main( int argc, char *argv[] ) {
	Game &g = Game::getInstance();
	g.init();
	g.run();
	g.cleanup();
	return 0;
}
