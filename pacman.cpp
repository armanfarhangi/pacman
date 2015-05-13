//Arman Farhangi
//May 13, 2015
//PAC-MAN Game
//C++ and SDL

//headers
#include "pacman.h"

/******* PACMAN CLASS DEFS *******/

//constructor
Pacman::Pacman(Texture& spritesheet)
{
    //allow pacman object to use spritesheet
    Pacman::spritesheet = spritesheet;
    
    //default animation state is moving right
    animation_state = MOVING_RIGHT;
    
    //setup moving_right animation clips
    moving_right.resize(2);
    moving_right[0] = { TILE_WIDTH*0, TILE_HEIGHT*0, TILE_WIDTH, TILE_HEIGHT };
    moving_right[1] = { TILE_WIDTH*1, TILE_HEIGHT*0, TILE_WIDTH, TILE_HEIGHT };

    
    //initialize animation counter
    animation = 0;
    
    //default position
    x_pos = WINDOW_WIDTH/2;
    y_pos = (TILE_HEIGHT/2) + (TILE_HEIGHT*12) - 12; //-12; pacman tiles not fully aligned -_-
}

//render pacman depending on animation state
void Pacman::render()
{
    //if moving right
    if (animation_state == MOVING_RIGHT)
    {
        spritesheet.render(x_pos, y_pos, &moving_right[animation/10]);
        ++animation;
        if (animation/10 == 2) animation = 0;
    }
}