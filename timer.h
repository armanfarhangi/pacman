//Arman Farhangi
//May 18, 2015
//BOX-MAN Game
//Standard C++ and SDL Libraries

#ifndef pong_timer_h
#define pong_timer_h

//libraries
#include <SDL2/SDL.h>

/******* TIMER CLASS DECLARES *******/

//stopwatch timer
class Timer
{
public:
    //constructor
    Timer();
    
    //create arbitrary starting point
    void start();
    
    //check time passed since the last start
    int check();
    
private:
    //stores starting time
    Uint32 start_time;
};




/******* CLASS TIMER DEFS *******/

#endif
