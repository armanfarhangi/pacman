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
    Baddie(Texture* spritesheet, Boxman* boxman, int x_tile, int y_tile);
    
    //move baddie
    void move();
    
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
    
    //moving state
    int moving_state;
    
    //timer
    Timer first_timer;
    
    //vibration animation
    int vibration;
};


#endif