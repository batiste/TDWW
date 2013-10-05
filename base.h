#ifndef _BASE_H
#define _BASE_H

#include <iostream>
#include <fstream>
#include <streambuf>
#include <sstream>
#include <vector>
#include <string>

#if defined __WINDOWS__
#include <SDL.h>
#include <SDL_image.h>
#elif defined __gnu_linux__
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#endif

//Basic classes
template< typename T >
class Vec2 {
public:
	Vec2() {
		Vec2( 0, 0, 0, 0 );
	}
	Vec2( T x, T y ) {
		this->x = x;
		this->y = y;
	}
	
	T x, y;
};

template< typename T >
class Rect {
public:
	Rect() {
		Rect( 0, 0, 0, 0 );
	}
	Rect( T x, T y, T w, T h ) {
		this->x = x;
		this->y = y;
		this->w = w;
		this->h = h;
	}
	
	T x, y, w, h;
};

//Typedefs
typedef unsigned int uint;

typedef Vec2< int > Vec2i;
typedef Vec2< float > Vec2f;

typedef Rect< int > IntRect;
typedef Rect< float > FloatRect;

//Global functions
inline void println( const std::string &str ) {
	std::cout << str << std::endl;
}

enum ERROR {
	TEST_ERROR,
	WINDOW_INIT_FAILED,
	CONTEXT_INIT_FAILED,
	GLEW_INIT_FAILED,
	CONFIG_LOAD_FAILED,
	OPENGL_ERROR,
	IMG_LOAD_FAILED,
	
	NUM_ERRORS
};

static const char *ERROR_STRINGS[] = {
	"< Insert error here >",
	"Window failed to initialize",
	"OpenGL rendering context failed to initialize",
	"GLEW failed to initialize",
	"Configuration file failed to load",
	"OpenGL error",
	"Image failed to load"
};

inline std::string getErrorString( ERROR err ) {
	if( err >= NUM_ERRORS ) {
		return "Unknown error";
	}
	return ERROR_STRINGS[ err ];
}

inline void error( ERROR err, const std::string &details = "", bool fatal = true ) {
	std::string errStr = "ERROR " + std::to_string( err ) + ": " + getErrorString( err ) + ".";
	if( details.length() > 0 ) {
		errStr += " Details: " + details + ".";
	}
	println( errStr );
	
	if( fatal ) {
		println( "Press ENTER to exit..." );
		std::cin.get();
		exit( err );
	}
}

inline bool getFileContents( const std::string &path, std::string &fileContents ) {
	std::ifstream file( path );
	if( file.is_open() ) {
		std::string str( ( std::istreambuf_iterator< char >( file ) ), std::istreambuf_iterator< char >() );
		fileContents = str;
		return true;
	}
	return false;
}

inline bool stringToBool( const std::string &str ) {
	if( str == "true" || str == "t" ) {
		return true;
	} else if( str == "false" || str == "f" ) {
		return false;
	}
	return false;
}

#endif //_BASE_H
