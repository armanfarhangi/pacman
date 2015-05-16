//Arman Farhangi
//May 15, 2015
//BOX-MAN Game
//C++ and SDL


#include <SDL2/SDL.h>
//headers
#include "pellet.h"
#include "globals.h"


/******* PELLET CLASS DEFS *******/
//constructor sets clip in relation to bool
Pellet::Pellet(bool is_pellet, int x, int y)
{
    if (is_pellet == true)
    {
        pellet_rect = { (x + TILE_WIDTH/2 - 2), (y + TILE_HEIGHT/2 - 2), 4, 4 };
    }
    else if (is_pellet == false)
    {
        pellet_rect = { 0, 0, 0, 0};
    }
}


//render pellet
void Pellet::render()
{
    SDL_RenderFillRect(renderer, &pellet_rect);
}