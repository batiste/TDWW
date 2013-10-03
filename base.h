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
	CONFIG_LOAD_FAILED,
	
	NUM_ERRORS
};

static const char *ERROR_STRINGS[] = {
	"Error",
	"Window failed to initialize",
	"OpenGL rendering context failed to initialize",
	"GLEW failed to initialize",
	"Configuration file failed to load"
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

inline bool getFileContents( std::string path, std::string &fileContents ) {
	std::ifstream file( path );
	if( file.is_open() ) {
		std::string str( ( std::istreambuf_iterator< char >( file ) ), std::istreambuf_iterator< char >() );
		fileContents = str;
		return true;
	}
	return false;
}

inline bool stringToBool( std::string str ) {
	if( str == "true" ) {
		return true;
	}
	return false;
}

#endif //_BASE_H
