#include "game.h"
#include "game_state.h"

Game &Game::getInstance() {
	static Game instance;
	return instance;
}

void Game::init() {
	running = false;
	winWidth = 640;
	winHeight = 480;
	fullscreen = false;
	
	//Load config
	if( !loadConfig( "settings.cfg" ) ) {
		error( CONFIG_LOAD_FAILED );
	}
	
	//Create SDL window and OpenGL rendering context
	SDL_Init( SDL_INIT_EVERYTHING );
	Uint32 winFlags = SDL_WINDOW_OPENGL;
	if( fullscreen ) {
		winFlags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
	}
	window = SDL_CreateWindow( "The Dead Will Walk", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, winWidth, winHeight, winFlags );
	if( !window ) {
		error( WINDOW_INIT_FAILED );
	}
	glContext = SDL_GL_CreateContext( window );
	if( !glContext ) {
		error( CONTEXT_INIT_FAILED );
	}
	
	//Initialize SDL_image
	IMG_Init( IMG_INIT_PNG );
	
	//Initialize GLEW
	glewExperimental = true;
	GLenum glewError = glewInit();
	if( glewError != GLEW_OK ) {
		error( GLEW_INIT_FAILED );
	}
	
	//OpenGL init
	glViewport( 0.0f, 0.0f, (float)winWidth, (float)winHeight );
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	glOrtho( 0.0, winWidth, winHeight, 0.0, 1.0, -1.0 );
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();	
	glEnable( GL_TEXTURE_2D );
	glEnable( GL_BLEND );
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
	glClearColor( 1.0f, 0.0f, 1.0f, 0.0f );
	GLenum err = glGetError();
	if( err != GL_NO_ERROR ) {
		error( OPENGL_ERROR );
	}
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
		//Handle events --TEMPORARY--
		SDL_Event event;
		while( SDL_PollEvent( &event ) ) {
			switch( event.type ) {
			case SDL_QUIT:
				running = false;	
				break;
			}
		}
		if( !states.empty() ) {
			//Update gamestate
			states.back()->update();
			
			//Clear screen and render gamestate
			glClear( GL_COLOR_BUFFER_BIT );
			states.back()->render();
			SDL_GL_SwapWindow( window );
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

bool Game::loadConfig( const std::string &path ) {
	//This function is kind of hackish and prone to error, it should eventually be replaced
	std::string cfg;
	if( getFileContents( path, cfg ) ) {
		std::istringstream cfgStream( cfg );
		std::string line;
		while( !cfgStream.eof() ) {
			std::getline( cfgStream, line );
			if( !line.empty() ) {
				if( line.substr( 0, line.find_first_of( '=' ) ) == "width" ) {
					winWidth = atoi( line.substr( line.find_first_of( '=' ) + 1 ).c_str() );
				}
				if( line.substr( 0, line.find_first_of( '=' ) ) == "height" ) {
					winHeight = atoi( line.substr( line.find_first_of( '=' ) + 1 ).c_str() );
				}
				if( line.substr( 0, line.find_first_of( '=' ) ) == "fullscreen" ) {
					fullscreen = stringToBool( line.substr( line.find_first_of( '=' ) + 1 ).c_str() );
				}
			}
		}
		return true;
	}
	return false;
}
