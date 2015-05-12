//Arman Farhangi
//May 11, 2015
//PAC-MAN Game
//C++ and SDL

#ifndef pacman_Game_h
#define pacman_Game_h

#include "texture.h"

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
    
    //starts menu loop
    void menu(Texture& spritesheet);
    
    //starts instruction loop
    void instructions();
    
    //starts maze loop
    void maze(Texture& texture);
};


#endif
