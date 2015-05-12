//Arman Farhangi
//May 11, 2015
//PAC-MAN Game
//C++ and SDL

#ifndef pacman_globals_h
#define pacman_globals_h

//libraries
#include <SDL2/SDL.h>
#include <SDL2_ttf/SDL_ttf.h>

//window
extern SDL_Window* window;
const int WINDOW_WIDTH = 453;
const int WINDOW_HEIGHT = 496;

//tile dimensions
const int TILE_WIDTH = 32;
const int TILE_HEIGHT = 31;

//renderer
extern SDL_Renderer* renderer;

//fonts
extern TTF_Font* big_font;
extern TTF_Font* medium_font;
extern TTF_Font* small_font;
extern TTF_Font* smallest_font;

//level enumerations
enum Level { MENU, MAZE, GAME_OVER, END };

#endif
