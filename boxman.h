//Arman Farhangi
//May 14, 2015
//BOX-MAN Game
//C++ and SDL

#ifndef __pacman__boxman__
#define __pacman__boxman__

//libraries
#include <SDL2/SDL.h>
#include <vector>
//headers
#include "texture.h"
#include "tile.h"
#include "collider.h"

/****** BOXMAN CLASS DECLARES ********/
//player character
class Boxman : Collider
{
public:
    //constants
    const static int SPEED = 1;
    const static int WIDTH = TILE_WIDTH;
    const static int HEIGHT = TILE_HEIGHT;
    
    //constructor
    Boxman(Texture* spritesheet, std::vector<std::vector<Tile>>* tiles);
    
    //handle events
    void handle(SDL_Event e);
    
    //move boxman
    void move();
    
    //check if boxman moved into obstacle
    bool moved_into_surroundings();
    
    //render boxman
    void render();
    
private:
    //pointer to Game spritesheet
    Texture* spritesheet;
    
    //position on window
    int x_pos;
    int y_pos;
    
    //moving state
    int moving_state;
    
    //moving animation clips
    std::vector<SDL_Rect> moving_right;
    std::vector<SDL_Rect> moving_left;
    std::vector<SDL_Rect> moving_up;
    std::vector<SDL_Rect> moving_down;
    //animation counter
    int animation;
    
    //velocity
    int x_vel;
    int y_vel;
    
    //tile position on window
    int x_tile;
    int y_tile;
    
    //pointer to map tiles (to check for obstacles)
    std::vector<std::vector<Tile>>* tiles;
};

#endif
