//Arman Farhangi
//May 18, 2015
//BOX-MAN Game
//C++ and SDL

//headers
#include "baddie.h"

/******* BADDIE CLASS DEFS *******/

//constructor
Baddie::Baddie(Texture* spritesheet, Boxman* boxman, int x_tile, int y_tile)
{
    //set spritesheet reference
    Baddie::spritesheet = spritesheet;
    
    //set boxman reference
    Baddie::boxman = boxman;
    
    //set position
    x_pos = x_tile * TILE_WIDTH;
    y_pos = y_tile * TILE_HEIGHT;
    
    //set hitbox values
    hitbox = { x_pos, y_pos, TILE_WIDTH, TILE_HEIGHT};
    
    //clip to render from spritesheet
    clip = { 0, TILE_HEIGHT * 5, TILE_WIDTH, TILE_HEIGHT};
    
    //set moving state
    moving_state = MOVING_DOWN;
    
    //start timer
    first_timer.start();
}

//move baddie
void Baddie::move()
{
    //if it hasn't been  been 5 seconds from beginning
    if ( first_timer.check() < 5000)
    {
        if (y_pos <= TILE_HEIGHT * 12)
            moving_state = MOVING_DOWN;
        else if (y_pos >= TILE_HEIGHT* 13)
            moving_state = MOVING_UP;
        
        if (moving_state == MOVING_DOWN)
            y_pos += SPEED - 2;
        else if (moving_state == MOVING_UP)
            y_pos += -(SPEED - 2);
    }
}


//render baddie
void Baddie::render()
{
    spritesheet->render(x_pos, y_pos, &clip);
}

