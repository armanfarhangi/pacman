//Arman Farhangi
//May 11, 2015
//PAC-MAN Game
//C++ and SDL

#ifndef __pacman__texture__
#define __pacman__texture__

//libraries
#include <SDL2/SDL.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <string>

//contains a texture and its dimensions
class Texture
{
public:
    //constructor
    Texture();
    
    //loads image texture
    void load_image(std::string path);
    
    //loads text texture
    void load_text(TTF_Font* font, SDL_Color color, std::string text);
    
    //renders to window
    void render(int x, int y, SDL_Rect* clip = NULL);
    
    //frees texture
    ~Texture();
    
    //gets width
    int get_width() { return width; };
    //gets height
    int get_height() { return height; };
    
private:
    //loaded texture
    SDL_Texture* texture;
    
    //texture width
    int width;
    //height
    int height;
};

#endif
