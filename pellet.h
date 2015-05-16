//Arman Farhangi
//May 15, 2015
//BOX-MAN Game
//C++ and SDL

#ifndef __pacman__pellet__
#define __pacman__pellet__

//headers
#include "collider.h"

/******* PELLET CLASS DECLARES *******/
//pellets that boxman eats
class Pellet : public Collider
{
public:
    //constructor sets window position
    Pellet(bool is_pellet, int x, int y);
    
    //render pellet
    void render();
    
private:
    //used to render
    SDL_Rect pellet_rect;
};

#endif
