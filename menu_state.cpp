#include "menu_state.h"

void MenuState::init() {
	glClearColor( 0.0f, 1.0f, 1.0f, 0.0f );
	tex.loadFromFile( "res/img/tex.png" );
}

void MenuState::cleanup() {

}

void MenuState::pause() {

}

void MenuState::resume() {

}

void MenuState::update() {

}

void MenuState::render() {
	tex.render( FloatRect( 0, 0, 128, 128 ) );
}
