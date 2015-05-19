//Arman Farhangi
//May 18, 2015
//BOX-MAN Game
//Standard C++ and SDL Libraries

//headers
#include "timer.h"


/******* TIMER CLASS DEFS *******/

//constructor
Timer::Timer()
{
    start_time = 0;
}

//take arbitrary starting point
void Timer::start()
{
    start_time = SDL_GetTicks();
}

//get ms passed since timer was started
int Timer::check()
{
    return SDL_GetTicks() - start_time;
}