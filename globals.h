//Arman Farhangi
//May 11, 2015
//PAC-MAN Game
//C++ and SDL

#ifndef pacman_globals_h
#define pacman_globals_h

//libraries
#include <SDL2/SDL.h>
#include <SDL2_ttf/SDL_ttf.h>

/******* GLOBAL OBJECTS, CONSTANTS, ENUMERATIONS *******/

//window
extern SDL_Window* window;
const int WINDOW_WIDTH = 384;
const int WINDOW_HEIGHT = 512;

//renderer
extern SDL_Renderer* renderer;

//pacman clip dimensions
const int TILE_WIDTH = 16;
const int TILE_HEIGHT = 16;

//fonts
extern TTF_Font* big_font;
extern TTF_Font* medium_font;
extern TTF_Font* small_font;
extern TTF_Font* smallest_font;

//level enumerations
enum Level { MENU, MAZE, INSTRUCTIONS, END };

//boxman animation state enumerations
enum Animation_State { MOVING_RIGHT, MOVING_LEFT, MOVING_UP, MOVING_DOWN, DYING };

//texture render enumerations
enum Center_State { CENTERED, NOT_CENTERED };



#endif


