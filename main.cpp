//Arman Farhangi
//May 11, 2015
//PAC-MAN Game
//C++ and SDL

//libraries
#include "functions.h"
#include <stdio.h>
#include "game.h"

//main function
int main( int arg, char* args[] )
{
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
    close();
    
    return 0;
}