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
    //if event is a non-repeat key press and pacman is in the center of a tile
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
    //keep track of tile for map collisions (base tile position on center of boxman)
    x_tile = (x_pos + TILE_WIDTH/2)/TILE_WIDTH;
    y_tile = (y_pos + TILE_WIDTH/2)/TILE_HEIGHT;
        
    
    //if boxman moved into an obstacle tile
    if ( moved_into_surroundings() )
    {
        //negate movement
        x_pos -= x_vel;
        y_pos -= y_vel;
        hitbox.x -= x_vel;
        hitbox.y -= y_vel;
    }
}


//check if boxman collided with top, right, bottom, and left surroundings
bool Boxman::moved_into_surroundings()
{
    //if pacman collided with above tile
    if ( collided( (*tiles)[y_tile - 1][x_tile]) )
        return true;
    //if pacman collided with below tile
    else if ( collided( (*tiles)[y_tile + 1][x_tile]) )
        return true;
    //if pacman collided with right tile
    else if ( collided( (*tiles)[y_tile][x_tile + 1]) )
        return true;
    //if pacman collided with left tile
    else if ( collided( (*tiles)[y_tile][x_tile - 1]) )
        return true;
    return false;
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