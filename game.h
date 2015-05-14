//Arman Farhangi
//May 11, 2015
//PAC-MAN Game
//C++ and SDL

#ifndef pacman_Game_h
#define pacman_Game_h

//headers
#include "texture.h"


/******* GAME CLASS DECLARES *******/

//pac-man game
class Game
{
public:
    //constructor
    Game();
    
    //starts main game loop
    void start();
    
private:
    //determines level to loop
    int level;
    
    //spritesheet for boxman, ghosts, and tiles
    Texture spritesheet;
    
    //starts menu loop
    void menu();
    
    //starts instruction loop
    void instructions();
    
    //starts maze loop
    void maze();
};


#endif
