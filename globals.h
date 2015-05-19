//Arman Farhangi
//May 11, 2015
//BOX-MAN Game
//C++ and SDL

#ifndef pacman_globals_h
#define pacman_globals_h

//libraries
#include <SDL2/SDL.h>
#include <SDL2_ttf/SDL_ttf.h>

/******* GLOBAL OBJECTS, CONSTANTS, ENUMERATIONS *******/

//window
extern SDL_Window* window;

//renderer
extern SDL_Renderer* renderer;

//tile dimensions
const int TILE_WIDTH = 30;
const int TILE_HEIGHT = 30;
//tile counts
const int X_TILES = 25;
const int Y_TILES = 25;
//window dimensions
const int WINDOW_WIDTH = X_TILES*TILE_WIDTH;
const int WINDOW_HEIGHT = Y_TILES*TILE_HEIGHT;

//fonts
extern TTF_Font* big_font;
extern TTF_Font* medium_font;
extern TTF_Font* small_font;
extern TTF_Font* smallest_font;

//level enumerations
enum Level { MENU, MAZE, INSTRUCTIONS, END };

//texture render enumerations
enum Texture_Centered_State { CENTERED, NOT_CENTERED };

//boxman animation state enumerations
enum Moving_State { MOVING_RIGHT, MOVING_LEFT, MOVING_UP, MOVING_DOWN, DYING, NONE };

//tile obstacle state
enum Obstacle_State { NON_OBSTACLE, OBSTACLE };

#endif


