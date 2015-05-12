//Arman Farhangi
//May 11, 2015
//PAC-MAN Game
//C++ and SDL

//libraries
#include "functions.h"
#include "globals.h"
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <stdio.h>

//initialize global objects
SDL_Window* window = NULL;
SDL_Renderer* renderer;
TTF_Font* big_font;
TTF_Font* medium_font;
TTF_Font* small_font;
TTF_Font* smallest_font;


//setup SDL, window, renderer, SDL font, and SDL image
bool setup()
{
    //error report bool
    bool succeeded = true;
    
    //initialize SDL
    if ( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "SDL could not initialize.  Error: %s\n", SDL_GetError() );
        succeeded = false;
    }
    
    else
    {
        //create window titled PONG
        window = SDL_CreateWindow( "PONG", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
        
        //error check
        if (window == NULL)
        {
            printf( "Could not create window.  Error: %s\n", SDL_GetError() );
            succeeded = false;
        }
        
        else
        {
            //create hardware accelerated renderer
            renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
            
            //error check
            if (renderer == NULL)
            {
                printf( "Could not create renderer.  Error: %s\n", SDL_GetError() );
                succeeded = false;
            }
            
            else
            {
                //set render color to black
                SDL_SetRenderDrawColor( renderer, 0, 0, 0, 255 );
                
                //initialize PNG loading and error check
                int imgFlags = IMG_INIT_PNG;
                if( !( IMG_Init( imgFlags ) & imgFlags ) )
                {
                    printf( "SDL_image could not initialize. Error: %s\n", IMG_GetError() );
                    succeeded = false;
                }
                
                //initialize SDL Font and error check
                if( TTF_Init() == -1 )
                {
                    printf( "SDL_TTF could not initialize. Error: %s\n", TTF_GetError() );
                    succeeded = false;
                }
                
                else
                {
                    //open fonts
                    big_font = TTF_OpenFont( "PressStart2P.ttf", 60 );
                    medium_font = TTF_OpenFont( "PressStart2P.ttf", 28 );
                    small_font = TTF_OpenFont( "PressStart2P.ttf", 18 );
                    smallest_font = TTF_OpenFont( "PressStart2P.ttf", 12);
                    
                    //error check
                    if (big_font == NULL)
                    {
                        printf( "Could not open title font.  Error: %s\n", TTF_GetError() );
                        succeeded = false;
                    }
                    
                    //error check
                    if (medium_font == NULL)
                    {
                        printf( "Could not open button font.  Error: %s\n", TTF_GetError() );
                        succeeded = false;
                    }
                    
                    //error check
                    if (small_font == NULL)
                    {
                        printf( "Could not open button font.  Error: %s\n", TTF_GetError() );
                        succeeded = false;
                    }
                    
                    //error check
                    if (smallest_font == NULL)
                    {
                        printf( "Could not open button font.  Error: %s\n", TTF_GetError() );
                        succeeded = false;
                    }
                }
                
                
            }
        }
    }
    
    //return whether or not SDL is good to go
    return succeeded;
}


//destroy window, renderer, and quit SDL
void close()
{
    //free window
    SDL_DestroyWindow( window );
    window = NULL;
    //free renderer
    SDL_DestroyRenderer( renderer );
    renderer = NULL;
    
    //Free big font
    TTF_CloseFont( big_font );
    big_font = NULL;
    //free medium font
    TTF_CloseFont( medium_font );
    medium_font = NULL;
    //free small font
    TTF_CloseFont( small_font );
    small_font = NULL;
    //free smallest font
    TTF_CloseFont( smallest_font );
    smallest_font = NULL;
    
    //quit SDL systems
    TTF_Quit();
    SDL_Quit();
}
