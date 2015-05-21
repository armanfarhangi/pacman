//Arman Farhangi
//May 18, 2015
//BOX-MAN Game
//C++ and SDL

//headers
#include "baddie.h"
#include <iostream>

/******* BADDIE CLASS DEFS *******/

//constructor
Baddie::Baddie(Texture* spritesheet, Boxman* boxman, int x_tile, int y_tile, int type, std::vector<std::vector<Tile>>* tiles)
{
    //set spritesheet reference
    Baddie::spritesheet = spritesheet;
    
    //set boxman reference
    Baddie::boxman = boxman;
    
    //set position
    x_pos = x_tile * TILE_WIDTH;
    y_pos = y_tile * TILE_HEIGHT;
    Baddie::x_tile = x_tile;
    Baddie::y_tile = y_tile;
    
    //set type
    Baddie::type = type;
    
    //set hitbox values
    hitbox = { x_pos, y_pos, TILE_WIDTH, TILE_HEIGHT};
    
    //clip to render from spritesheet
    clip = { 0, TILE_HEIGHT * 5, TILE_WIDTH, TILE_HEIGHT};
    
    //set moving state
    moving_state = MOVING_DOWN;
    
    //start timer
    first_timer.start();
    
    //set vibration to zero
    vibration = 0;
    
    //set tiles pointer
    Baddie::tiles = tiles;
}

//move baddie
void Baddie::move()
{
    //if it hasn't been  been 7 seconds from beginning of game
    if ( first_timer.check() <= 7000)
    {
        if (first_timer.check() <= 4000)
        {
            // gear down if at top of center square
            if (y_pos <= TILE_HEIGHT * 12)
                moving_state = MOVING_DOWN;
            //gear up if at bottom of center square
            else if (y_pos >= TILE_HEIGHT* 13)
                moving_state = MOVING_UP;
        }
        
        //if it has been past four seconds from the beginning of game
        else if (first_timer.check() > 4000)
        {
            //if they're not on the 11th tile row
            if (y_pos != TILE_HEIGHT * 10)
                //gear up
                moving_state = MOVING_UP;
            //otherwise
            else
                //don't move
                moving_state = NONE;
        }
        
        //move (slowly) depending on moving state
        if (moving_state == MOVING_DOWN)
            y_pos += SPEED - 2;
        else if (moving_state == MOVING_UP)
            y_pos += -(SPEED - 2);
    }
    
    //if it has been 7 seconds from the beginning of the game
    else if (first_timer.check() > 7000)
    {
        

        
        //set tile position
        x_tile = (x_pos + TILE_WIDTH/2) / TILE_WIDTH;
        y_tile = (y_pos + TILE_HEIGHT/2) / TILE_HEIGHT;
    }
}


//render baddie
void Baddie::render()
{
    //create vibrating animation by rendering slightly offset for each frame
    if (vibration == 0)
        spritesheet->render(x_pos, y_pos, &clip);
    else if (vibration == 1)
        spritesheet->render(x_pos + vibration, y_pos, &clip);
    else if (vibration == 2)
        spritesheet->render(x_pos, y_pos, &clip);
    else if (vibration == 3)
        spritesheet->render(x_pos - vibration, y_pos, &clip);
    else if (vibration == 4)
        spritesheet->render(x_pos, y_pos, &clip);
    else if (vibration == 5)
        spritesheet->render(x_pos, y_pos + vibration, &clip);
    else if (vibration == 6)
        spritesheet->render(x_pos, y_pos, &clip);
    else if (vibration == 7)
        spritesheet->render(x_pos, y_pos - vibration, &clip);
    ++vibration;
    if (vibration == 8)
        vibration = 0;

}


//check if baddie has an aligned non-obstacle tile to the right
bool Baddie::can_move_right()
{
    return ((*tiles)[y_tile][x_tile + 1].get_state() == NON_OBSTACLE && y_pos % 30 == 0 );
}


//check if baddie has an aligned non-obstacle tile to the left
bool Baddie::can_move_left()
{
    return ( (*tiles)[y_tile][x_tile - 1].get_state() == NON_OBSTACLE  && y_pos % 30 == 0 );
}


//check if baddie has an aligned non-obstacle tile above
bool Baddie::can_move_up()
{
    return ( (*tiles)[y_tile - 1][x_tile].get_state() == NON_OBSTACLE && x_pos % 30 == 0 );
}


//check if baddie has an aligned non-obstacle tile below
bool Baddie::can_move_down()
{
    return ( (*tiles)[y_tile + 1][x_tile].get_state() == NON_OBSTACLE && x_pos % 30 == 0 );
}

