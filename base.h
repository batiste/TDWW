#ifndef _BASE_H
#define _BASE_H

#include <iostream>
#include <vector>
#include <string>

#if defined __WINDOWS__
#include <SDL.h>
#elif defined __gnu_linux__
#include <SDL2/SDL.h>
#endif

//Typedefs
typedef unsigned int uint;

//Global functions
inline void println( std::string str ) {
	std::cout << str << std::endl;
}

enum ERROR {
	TEST_ERROR,
	WINDOW_INIT_FAILED,
	CONTEXT_INIT_FAILED,
	GLEW_INIT_FAILED,
	
	NUM_ERRORS
};

static const char *ERROR_STRINGS[] = {
	"Error",
	"Window failed to initialize",
	"OpenGL rendering context failed to initialize",
	"GLEW failed to initialize"
};

inline std::string getErrorString( ERROR err ) {
	if( err >= NUM_ERRORS ) {
		return "Unknown error";
	}
	return ERROR_STRINGS[ err ];
}

inline void error( ERROR err ) {
	std::string errStr = "ERROR " + std::to_string( err ) + ": " + getErrorString( err ) + ".";
	println( errStr );
	
	std::cin.get();
	exit( err );
}

#endif //_BASE_H
