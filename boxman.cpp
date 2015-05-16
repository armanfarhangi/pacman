//Arman Farhangi
//May 14, 2015
//BOX-MAN Game
//C++ and SDL

//headers
#include "boxman.h"
#include "globals.h"

/******* BOXMAN CLASS DEFS *******/
//set boxman animation clips
Boxman::Boxman(Texture* spritesheet, std::vector<std::vector<Tile>>* map_tiles, std::vector<std::vector<Pellet>>* map_pellets)
{
    //set Game spritesheet reference
    Boxman::spritesheet = spritesheet;
    
    //set default position
    x_tile = 12;
    y_tile = 20;
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
    
    //initialize direction queue
    direction_queue = MOVING_RIGHT;
    
    //set tiles pointer
    tiles = map_tiles;
    
    //set pellets pointer
    pellets = map_pellets;
    
    //initialize pellets eaten
    pellets_eaten = 0;
}


//handle events for movement (only move one direction at a time)
void Boxman::handle(SDL_Event e)
{
    //if event is a non-repeat key press and boxman is in the center of a tile
    if ( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
    {
        //if event is right key
        if ( e.key.keysym.sym == SDLK_RIGHT )
                direction_queue = MOVING_RIGHT;
        //if event is left key
        else if ( e.key.keysym.sym == SDLK_LEFT )
                direction_queue = MOVING_LEFT;
        //if event is up key
        if (e.key.keysym.sym == SDLK_UP)
            direction_queue = MOVING_UP;
        //if event is down key
        if (e.key.keysym.sym == SDLK_DOWN)
            direction_queue = MOVING_DOWN;
    }
}


//move boxman
void Boxman::move()
{
    //if queued right and can move right
    if ( direction_queue == MOVING_RIGHT && can_move_right() )
    {
        //gear boxman right
        y_vel = 0;
        x_vel = SPEED;
        moving_state = MOVING_RIGHT;
    }
    //if queued left and can move left
    else if ( direction_queue == MOVING_LEFT && can_move_left() )
    {
        //gear boxman left
        y_vel = 0;
        x_vel = -SPEED;
        moving_state = MOVING_LEFT;
    }
    //if queued up and can move up
    else if ( direction_queue == MOVING_UP && can_move_up() )
    {
        //gear boxman up
        x_vel = 0;
        y_vel = -SPEED;
        moving_state = MOVING_UP;
    }
    //if queued down and can move down
    else if ( direction_queue == MOVING_DOWN && can_move_down() )
    {
        //gear boxman down
        x_vel = 0;
        y_vel = SPEED;
        moving_state = MOVING_DOWN;
    }

    
    //change position based on velocity
    x_pos += x_vel;
    y_pos += y_vel;
    //move hitbox too
    hitbox.x += x_vel;
    hitbox.y += y_vel;
    //keep track of tile for map collisions (determine tile position by center of boxman)
    x_tile = (x_pos + TILE_WIDTH/2)/TILE_WIDTH;
    y_tile = (y_pos + TILE_WIDTH/2)/TILE_HEIGHT;
        
    
    //if boxman moved into an obstacle tile
    if ( moved_into_obstacle() )
    {
        //negate movement
        x_pos -= x_vel;
        y_pos -= y_vel;
        hitbox.x -= x_vel;
        hitbox.y -= y_vel;
    }
    
    //check for pellet collisions
    check_pellet_collisions();
}


//check if pacman has an aligned non-obstacle tile to the right
bool Boxman::can_move_right()
{
   return ((*tiles)[y_tile][x_tile + 1].get_state() == NON_OBSTACLE && y_pos % 30 == 0 );
}


//check if pacman has an aligned non-obstacle tile to the left
bool Boxman::can_move_left()
{
    return ( (*tiles)[y_tile][x_tile - 1].get_state() == NON_OBSTACLE  && y_pos % 30 == 0 );
}


//check if pacman has an aligned non-obstacle tile above
bool Boxman::can_move_up()
{
    return ( (*tiles)[y_tile - 1][x_tile].get_state() == NON_OBSTACLE && x_pos % 30 == 0 );
}


//check if pacman has an aligned non-obstacle tile below
bool Boxman::can_move_down()
{
    return ( (*tiles)[y_tile + 1][x_tile].get_state() == NON_OBSTACLE && x_pos % 30 == 0 );
}

//check if boxman collided into obstacles in surrounding 8 tiles
bool Boxman::moved_into_obstacle()
{
    //if boxman collided with above tile
    if ( collided( (*tiles)[y_tile - 1][x_tile ]) )
        return true;
    //if boxman collided with below tile
    else if ( collided( (*tiles)[y_tile + 1][x_tile] ) )
        return true;
    //if boxman collided with right tile
    else if ( collided( (*tiles)[y_tile][x_tile + 1] ) )
        return true;
    //if boxman collided with left tile
    else if ( collided( (*tiles)[y_tile][x_tile - 1] ) )
        return true;
    //if boxman collided with above-right tile
    else if ( collided( (*tiles)[y_tile - 1][x_tile + 1] ) )
        return true;
    //if boxman collided with below-right tile
    else if ( collided( (*tiles)[y_tile + 1][x_tile + 1] ) )
        return true;
    //if boxman collided with below-left tile
    else if ( collided( (*tiles)[y_tile + 1][x_tile - 1] ) )
        return true;
    //if boxman collided with above-left tile
    else if ( collided( (*tiles)[y_tile - 1][x_tile - 1] ) )
        return true;
    
    return false;
}

//check if boxman collided with pellets
void Boxman::check_pellet_collisions()
{
    //if boxman collided with pellet
    if ( collided( (*pellets)[y_tile][x_tile]) )
    {
        //destroy pellet and raise count
        (*pellets)[y_tile][x_tile].destroy();
        ++pellets_eaten;
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