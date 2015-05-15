//Arman Farhangi
//May 11, 2015
//BOX-MAN Game
//C++ and SDL

//libraries
#include <stdio.h>
#include <ctime>
//headers
#include "functions.h"
#include "game.h"

/******* MAIN FUNCTION *******/
int main( int arg, char* args[] )
{
    //allow for fresh random generation
    srand(static_cast<unsigned int>(time(NULL)));
    
    //setup required systems
    if ( setup() == false)
        printf( "FAILURE!" );
    else
    {
        //create and start game
        Game game;
        game.start();
    }
    
    //close systems and cleanup
    shutdown();
    
    return 0;
}