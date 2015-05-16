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
#include "globals.h"
#include "pellet.h"

/****** BOXMAN CLASS DECLARES ********/
//player character
class Boxman : Collider
{
public:
    //constants
    const static int SPEED = 2;
    const static int WIDTH = TILE_WIDTH;
    const static int HEIGHT = TILE_HEIGHT;
    
    //constructor
    Boxman(Texture* spritesheet, std::vector<std::vector<Tile>>* map_tiles, std::vector<std::vector<Pellet>>* pellets);
    
    //handle events
    void handle(SDL_Event e);
    
    //move boxman
    void move();
    
    //check if boxman can move a certain direction
    bool can_move_right();
    bool can_move_left();
    bool can_move_up();
    bool can_move_down();
    
    //check if boxman moved into obstacle
    bool moved_into_obstacle();
    
    //check if boxman collided with a pellet
    void check_pellet_collisions();
    
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
    
    //most recent direction desired by player
    int direction_queue;
    
    //tile position on window
    int x_tile;
    int y_tile;
    
    //pointer to map tiles (to check for obstacles)
    std::vector<std::vector<Tile>>* tiles;
    
    //pointer to pellet objects (to check for eating)
    std::vector<std::vector<Pellet>>* pellets;
    
    //pellets eaten
    int pellets_eaten;
};

#endif
