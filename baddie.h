//Arman Farhangi
//May 18, 2015
//BOX-MAN Game
//C++ and SDL

#ifndef __pacman__baddie__
#define __pacman__baddie__

//headers
#include "collider.h"
#include "boxman.h"
#include "timer.h"

/******* BADDIE CLASS DECLARES *******/
//boxman's enemies
class Baddie : public Collider
{
public:
    //constants
    const static int SPEED = 3;
    const static int WIDTH = TILE_WIDTH;
    const static int HEIGHT = TILE_HEIGHT;
    
    //constructor
    Baddie(Texture* spritesheet, Boxman* boxman, int x_tile, int y_tile, int type, std::vector<std::vector<Tile>>* tiles);
    
    //move baddie
    void move();
    
    //check if baddie can move a certain direction
    bool can_move_right();
    bool can_move_left();
    bool can_move_up();
    bool can_move_down();
    
    //render baddie
    void render();
    
private:
    //pointer to Game spritesheet
    Texture* spritesheet;
    
    //clip to render
    SDL_Rect clip;
    
    //pointer to boxman
    Boxman* boxman;
    
    //position in pixels
    int x_pos;
    int y_pos;
    //position in tiles
    int x_tile;
    int y_tile;
    
    //type of baddie (determines movement behavior)
    int type;
    
    //moving state
    int moving_state;
    
    //timers
    Timer first_timer;
    Timer second_timer;
    
    //vibration animation
    int vibration;
    
    //pointer to map tiles (to check for obstacles)
    std::vector<std::vector<Tile>>* tiles;
};


#endif