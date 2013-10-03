#ifndef _TEXTURE_H
#define _TEXTURE_H

#include "base.h"
#include "opengl.h"

class Texture {
public:
	Texture();
	~Texture();
	
	void loadFromFile( const std::string &path );
	void freeTexture();

	void render( FloatRect rect );
	
	GLuint getTextureID() { return textureID; }
private:
	GLuint textureID;
	GLuint textureWidth, textureHeight;
};

#endif //_TEXTURE_H
