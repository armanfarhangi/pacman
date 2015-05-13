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
    
    //setup moving right animation clips
    moving_right.resize(2);
    moving_right[0] = { TILE_WIDTH*0, TILE_HEIGHT*0, TILE_WIDTH, TILE_HEIGHT };
    moving_right[1] = { TILE_WIDTH*1, TILE_HEIGHT*0, TILE_WIDTH, TILE_HEIGHT };
    //setup moving left animation clips
    moving_left.resize(2);
    moving_left[0] = { TILE_WIDTH*0, TILE_HEIGHT*1, TILE_WIDTH, TILE_HEIGHT };
    moving_left[1] = { TILE_WIDTH*1, TILE_HEIGHT*1, TILE_WIDTH, TILE_HEIGHT };
    //setup moving up animation clips
    moving_up.resize(2);
    moving_up[0] = { TILE_WIDTH*0, TILE_HEIGHT*1, TILE_WIDTH, TILE_HEIGHT };
    moving_up[1] = { TILE_WIDTH*2, TILE_HEIGHT*2, TILE_WIDTH, TILE_HEIGHT };
    //setup moving down animation clips
    moving_up.resize(2);
    moving_up[0] = { TILE_WIDTH*0, TILE_HEIGHT*1, TILE_WIDTH, TILE_HEIGHT };
    moving_up[1] = { TILE_WIDTH*3, TILE_HEIGHT*3, TILE_WIDTH, TILE_HEIGHT };
    
    //initialize animation counter
    animation = 0;
    
    //default position
    x_pos = WINDOW_WIDTH/2;
    y_pos = (TILE_HEIGHT/2) + (TILE_HEIGHT*12) - 12; //-12; pacman tiles not fully aligned
    
    //default velocity
    x_vel = 0;
    y_vel = 0;
}

//render pacman depending on animation state
void Pacman::render()
{
    //if moving right
    if (animation_state == MOVING_RIGHT)
    {
        //moving right animation
        spritesheet.render(x_pos, y_pos, &moving_right[animation/10]);
        ++animation;
        if (animation/10 == 2) animation = 0;
    }
    
    //if moving left
    if (animation_state == MOVING_LEFT)
    {
        //moving left animation
        spritesheet.render(x_pos, y_pos, &moving_left[animation/10]);
        ++animation;
        if (animation/10 == 2) animation = 0;
    }
    
    //if moving up
    if (animation_state == MOVING_UP)
    {
        //moving up animation
        spritesheet.render(x_pos, y_pos, &moving_up[animation/10]);
        ++animation;
        if (animation/10 == 2) animation = 0;
    }
    
    //if moving down
    if (animation_state == MOVING_DOWN)
    {
        //moving down animation
        spritesheet.render(x_pos, y_pos, &moving_down[animation/10]);
        ++animation;
        if (animation/10 == 2) animation = 0;
    }
}