//Arman Farhangi
//May 12, 2015
//PAC-MAN Game
//C++ and SDL

#ifndef pacman_tile_h
#define pacman_tile_h

//headers
#include "collider.h"
#include "texture.h"


/******* TILE CLASS DECLARES *******/

//map tiles
class Tile : public Collider
{
public:
    //constructor
    Tile( int obstace_state );
    
    //accessors
    bool get_obstacle_state();
    
private:
    //holds graphic
    Texture graphic;
    
    //obstacle state
    bool is_obstacle;
};

#endif
