#include "game.h"
#include "game_state.h"

Game &Game::getInstance() {
	static Game instance;
	return instance;
}

void Game::init() {
	running = false;
	
	SDL_Init( SDL_INIT_EVERYTHING );
	
	window = SDL_CreateWindow( "The Dead Will Walk", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL );
	
	glContext = SDL_GL_CreateContext( window );
}

void Game::cleanup() {
	while( !states.empty() ) {
		states.back()->cleanup();
		states.pop_back();
	}
	
	states.clear();
	
	SDL_GL_DeleteContext( glContext );
	SDL_DestroyWindow( window );
}

void Game::run() {
	running = true;
	while( running ) {
		SDL_Event event;
		while( SDL_PollEvent( &event ) ) {
			switch( event.type ) {
			case SDL_QUIT:
				running = false;	
				break;
			}
		}
		if( !states.empty() ) {
			states.back()->update();
			states.back()->render();
		}
	}
}

void Game::switchState( GameState *state ) {
	if( !states.empty() ) {
		states.back()->cleanup();
		states.pop_back();
	}
	
	states.push_back( state );
	states.back()->init();
}

void Game::pushState( GameState *state ) {
	if( !states.empty() ) {
		states.back()->pause();
	}

	states.push_back( state );
	states.back()->init();
}

void Game::popState() {
	if( !states.empty() ) {
		states.back()->cleanup();
		states.pop_back();
	}
	
	if( !states.empty() ) {
		states.back()->resume();
	}
}
