//Arman Farhangi
//May 14, 2015
//BOX-MAN Game
//C++ and SDL

//headers
#include "boxman.h"
#include "globals.h"

/******* BOXMAN CLASS DEFS *******/
//set boxman animation clips
Boxman::Boxman(Texture* spritesheet, std::vector<std::vector<Tile>>* tiles)
{
    //set Game spritesheet reference
    Boxman::spritesheet = spritesheet;
    
    //set default position
    x_tile = 11;
    y_tile = 19;
    x_pos = TILE_WIDTH * x_tile;
    y_pos = TILE_HEIGHT * y_tile;
    //set hitbox
    hitbox = {x_pos, y_pos, WIDTH, HEIGHT};
    
    //set default moving state
    moving_state = MOVING_RIGHT;
    
    //set moving right clips
    SDL_Rect clip = { TILE_WIDTH*0, TILE_HEIGHT*1, TILE_WIDTH, TILE_HEIGHT };
    moving_right.push_back(clip);
    clip.x = TILE_WIDTH*1;
    clip.y = TILE_HEIGHT*1;
    moving_right.push_back(clip);
    //set moving left clips
    clip.x = TILE_WIDTH*0;
    clip.y = TILE_HEIGHT*2;
    moving_left.push_back(clip);
    clip.x = TILE_WIDTH*1;
    clip.y = TILE_HEIGHT*2;
    moving_left.push_back(clip);
    //set moving up clips
    clip.x = TILE_WIDTH*0;
    clip.y = TILE_HEIGHT*3;
    moving_up.push_back(clip);
    clip.x = TILE_WIDTH*1;
    clip.y = TILE_HEIGHT*3;
    moving_up.push_back(clip);
    //set moving down clips
    clip.x = TILE_WIDTH*0;
    clip.y = TILE_HEIGHT*4;
    moving_down.push_back(clip);
    clip.x = TILE_WIDTH*1;
    clip.y = TILE_HEIGHT*4;
    moving_down.push_back(clip);
    //initialize animation counter
    animation = 0;
    
    //set default velocities
    x_vel = 0;
    y_vel = 0;
    
    //set tiles pointer
    Boxman::tiles = tiles;
}


//handle events for movement (only move one direction at a time)
void Boxman::handle(SDL_Event e)
{
    //if event is a non-repeat key press
    if ( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
    {
        //if event is right key
        if ( e.key.keysym.sym == SDLK_RIGHT )
            {
                y_vel = 0;
                x_vel = SPEED;
                moving_state = MOVING_RIGHT;
            }
        //if event is left key
        else if ( e.key.keysym.sym == SDLK_LEFT )
            {
                y_vel = 0;
                x_vel = -SPEED;
                moving_state = MOVING_LEFT;
            }
        //if event is up key
        if (e.key.keysym.sym == SDLK_UP)
        {
            x_vel = 0;
            y_vel = -SPEED;
            moving_state = MOVING_UP;
        }
        //if event is down key
        if (e.key.keysym.sym == SDLK_DOWN)
        {
            x_vel = 0;
            y_vel = SPEED;
            moving_state = MOVING_DOWN;
        }
    }
}


//move boxman
void Boxman::move()
{
    //change position based on velocity
    x_pos += x_vel;
    y_pos += y_vel;
    //move hitbox too
    hitbox.x += x_vel;
    hitbox.y += y_vel;
    //keep track of tile for map collisions
    x_tile = x_pos/TILE_WIDTH;
    y_tile = y_pos/TILE_HEIGHT;
    
    //if boxman collided with an obstacle
    if ( collided((*tiles)[x_tile+1][y_tile])
        || collided((*tiles)[x_tile-1][y_tile])
        || collided((*tiles)[x_tile][y_tile-1])
        || collided((*tiles)[x_tile][y_tile+1]) )
    {
        //negate movement
        x_pos -= x_vel;
        y_pos -= y_vel;
        hitbox.x -= x_vel;
        hitbox.y -= y_vel;
    }
}

//render current boxman clip
void Boxman::render()
{
    //if moving right
    if ( moving_state == MOVING_RIGHT )
    {
        //render moving right clips
        spritesheet->render(x_pos, y_pos, &moving_right[animation/10]);
        ++animation;
        if (animation/10 == 2)
            animation = 0;
    }
    //if moving left
    else if ( moving_state == MOVING_LEFT )
    {
        //render moving left clips
        spritesheet->render(x_pos, y_pos, &moving_left[animation/10]);
        ++animation;
        if (animation/10 == 2)
            animation = 0;
    }
    //if moving up
    else if ( moving_state == MOVING_UP )
    {
        //render moving up clips
        spritesheet->render(x_pos, y_pos, &moving_up[animation/10]);
        ++animation;
        if (animation/10 == 2)
            animation = 0;
    }
    //if moving down
    else if ( moving_state == MOVING_DOWN )
    {
        //render moving down clips
        spritesheet->render(x_pos, y_pos, &moving_down[animation/10]);
        ++animation;
        if (animation/10 == 2)
            animation = 0;
    }
}