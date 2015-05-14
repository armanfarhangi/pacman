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
    moving_up[0] = { TILE_WIDTH*0, TILE_HEIGHT*2, TILE_WIDTH, TILE_HEIGHT };
    moving_up[1] = { TILE_WIDTH*1, TILE_HEIGHT*2, TILE_WIDTH, TILE_HEIGHT };
    //setup moving down animation clips
    moving_down.resize(2);
    moving_down[0] = { TILE_WIDTH*0, TILE_HEIGHT*3, TILE_WIDTH, TILE_HEIGHT };
    moving_down[1] = { TILE_WIDTH*1, TILE_HEIGHT*3, TILE_WIDTH, TILE_HEIGHT };
    
    //initialize animation counter
    animation = 0;
    
    //default position
    x_pos = WINDOW_WIDTH/2;
    y_pos = (TILE_HEIGHT/2) + (TILE_HEIGHT*12) - 12; //-12; pacman tiles not fully aligned
    
    //default velocity
    x_vel = 0;
    y_vel = 0;
    
    //initialize hitbox (3/4 of tile)
    hitbox = { x_pos*2, y_pos*2, (TILE_WIDTH/4)*3, (TILE_HEIGHT/4)*3 };
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
        if (animation/10 == 2)
            animation = 0;
    }
    
    //if moving left
    if (animation_state == MOVING_LEFT)
    {
        //moving left animation
        spritesheet.render(x_pos, y_pos, &moving_left[animation/10]);
        ++animation;
        if (animation/10 == 2)
            animation = 0;
    }
    
    //if moving up
    if (animation_state == MOVING_UP)
    {
        //moving up animation
        spritesheet.render(x_pos, y_pos, &moving_up[animation/10]);
        ++animation;
        if (animation/10 == 2)
            animation = 0;
    }
    
    //if moving down
    if (animation_state == MOVING_DOWN)
    {
        //moving down animation
        spritesheet.render(x_pos, y_pos, &moving_down[animation/10]);
        ++animation;
        if (animation/10 == 2)
            animation = 0;
    }
}


//handle events for pacman velocity
void Pacman::handle(SDL_Event e)
{
    //if key press event that's not a repeat
    if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
    {
        //if right key
        if ( e.key.keysym.sym == SDLK_RIGHT )
        {
            //gear pacman right
            x_vel = PACMAN_SPEED;
            y_vel = 0;
            animation_state = MOVING_RIGHT;
        }
        //if left key
        else if ( e.key.keysym.sym == SDLK_LEFT )
        {
            //gear pacman left
            x_vel = -PACMAN_SPEED;
            y_vel = 0;
            animation_state = MOVING_LEFT;
        }
        //if up key
        else if ( e.key.keysym.sym == SDLK_UP )
        {
            //gear pacman up
            y_vel = -PACMAN_SPEED;
            x_vel = 0;
            animation_state = MOVING_UP;
        }
        //if down key
        else if ( e.key.keysym.sym == SDLK_DOWN )
        {
            //gear pacman down
            y_vel = PACMAN_SPEED;
            x_vel = 0;
            animation_state = MOVING_DOWN;
        }
    }
}


//move pacman after handling events
void Pacman::move()
{
    //change position based on velocity
    x_pos += x_vel;
    y_pos += y_vel;
}


