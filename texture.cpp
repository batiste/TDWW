#include "texture.h"

Texture::Texture() {
	textureID = 0;
	textureWidth = 0;
	textureHeight = 0;
}

Texture::~Texture() {
	freeTexture();
}

void Texture::loadFromFile( const std::string &path ) {
	//Free texture in case it was already created
	freeTexture();
	
	glGenTextures( 1, &textureID );
	glBindTexture( GL_TEXTURE_2D, textureID );

	SDL_Surface *surface = IMG_Load( path.c_str() );
	if( !surface ) {
		//Image failed to load
		error( IMG_LOAD_FAILED, "File missing or corrupted: " + path, false );
		return;
	}
	textureWidth = surface->w;
	textureHeight = surface->h;
	
	glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, surface->w, surface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, surface->pixels );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
	
	glBindTexture( GL_TEXTURE_2D, 0 );
}

void Texture::freeTexture() {
	if( textureID != 0 ) {
		glDeleteTextures( 1, &textureID );
		textureID = 0;
	}
	
	textureWidth = 0;
	textureHeight = 0;
}

void Texture::render( FloatRect rect ) {
	if( textureID != 0 ) {
		glLoadIdentity();
		glTranslatef( rect.x, rect.y, 0.0f );
		glBindTexture( GL_TEXTURE_2D, textureID );
		
		glBegin( GL_QUADS );
			glTexCoord2f( 0.0f, 0.0f ); glVertex2f( 0.0f, 0.0f );
			glTexCoord2f( 1.0f, 0.0f ); glVertex2f( textureWidth, 0.0f );
			glTexCoord2f( 1.0f, 1.0f ); glVertex2f( textureWidth, textureHeight );
			glTexCoord2f( 0.0f, 1.0f ); glVertex2f( 0.0f, textureHeight );
		glEnd();
	}
}
