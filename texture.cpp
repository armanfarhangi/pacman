//Arman Farhangi
//May 11, 2015
//PAC-MAN Game
//C++ and SDL

//libraries
#include "texture.h"
#include <SDL2/SDL.h>
#include <SDL2_ttf/SDL_ttf.h>
#include "globals.h"
#include <stdio.h>
#include <SDL2_image/SDL_image.h>

//constructor
Texture::Texture()
{
    texture = NULL;
    width = 0;
    height = 0;
}

//load image texture
void Texture::load_image(std::string path)
{
    //load image into surface
    SDL_Surface* surface = IMG_Load( path.c_str() );
    
    //error check
    if (surface == NULL)
        printf( "Couldn't load text surface.  Error: %s\n", IMG_GetError() );
    else
    {
        //grab dimensions from surface
        width = surface->w;
        height = surface->h;
        
        //create texture from surface
        texture = SDL_CreateTextureFromSurface( renderer, surface);
        
        //error check
        if ( texture == NULL )
            printf( "Couldn't create texture from surface. Error: %s\n", IMG_GetError() );
    }
    
    //free unneeded surface
    SDL_FreeSurface(surface);
}

//load text texture
void Texture::load_text(TTF_Font* font, SDL_Color color, std::string text)
{
    //load text into a surface
    SDL_Surface* surface = TTF_RenderText_Solid( font, text.c_str(), color );
    
    //error check
    if (surface == NULL)
        printf( "Couldn't load text surface. Error: %s\n", TTF_GetError() );
    
    else
    {
        //grab dimensions from surface
        width = surface->w;
        height = surface->h;
        
        //create texture from surface
        texture = SDL_CreateTextureFromSurface( renderer, surface );
        
        //error check
        if ( texture == NULL )
            printf( "Couldn't create texture out of surface. Error: %s\n", SDL_GetError() );
    }
    
    //free unneeded surface
    SDL_FreeSurface( surface );
}

//render texture or texture clip to window
void Texture::render(int x, int y, SDL_Rect* clip)
{
    //point and dimensions for full texture to be rendered
    SDL_Rect render_rect = { x - width/2, y - height/2, width, height };
    
    //if clipping, adjust render rectangle
    if (clip != NULL)
    {
        render_rect.x = x - clip->w/2;
        render_rect.y = y - clip->h/2;
        render_rect.w = clip->w;
        render_rect.h = clip->h;
    }
    
    //render full texture or texture clip
    SDL_RenderCopy( renderer, texture, clip, &render_rect);
}

//free texture
Texture::~Texture()
{
    SDL_DestroyTexture(texture);
}
