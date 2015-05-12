//Arman Farhangi
//May 11, 2015
//PAC-MAN Game
//C++ and SDL

#include "game.h"
#include "globals.h"
#include <SDL2/SDL.h>
#include "texture.h"
#include <vector>

//constructor starts level at menu
Game::Game()
{
    level = MENU;
}

//starts main game loop
void Game::start()
{
    //load spritesheet
    Texture spritesheet;
    spritesheet.load_image("pacman_sheet.png");
    
    //while game hasn't ended
    while (level != END)
    {
        //menu level
        if (level == MENU)
            menu(spritesheet);
    }
}

//starts menu loop
void Game::menu(Texture& spritesheet)
{
    //loop condition
    bool quit = false;
    //event storage
    SDL_Event event;
    
    //window outline
    SDL_Rect window_outline = { 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT };
    
    //big pac-man clips
    std::vector<SDL_Rect> pacman_clips(2);
    pacman_clips[0].x = TILE_WIDTH*2;
    pacman_clips[0].y = TILE_HEIGHT*1;
    pacman_clips[0].w = TILE_WIDTH*2;
    pacman_clips[0].h = TILE_HEIGHT*2;
    pacman_clips[1].x = TILE_WIDTH*4;
    pacman_clips[1].y = TILE_HEIGHT*1;
    pacman_clips[1].w = TILE_WIDTH*2;
    pacman_clips[1].h = TILE_HEIGHT*2;
    //pac-man flippability
    SDL_RendererFlip flip_type = SDL_FLIP_NONE;
    //big pac-man animation counter
    int animation = 0;
    //big pac-man movement
    int movement = 1;
    bool moving_right = true;
    
    //tile dimensions for clip rendering
    SDL_Rect clip;
    clip = { 0, 0, TILE_WIDTH, TILE_HEIGHT };
    
    //title text
    Texture title;
    SDL_Color color = { 250, 218, 10, 255 };
    title.load_text(big_font, color, "PAC-MAN");
    //PLAY text
    Texture play;
    play.load_text(medium_font, color, "PLAY");
    //instructions text
    Texture instructions;
    instructions.load_text(medium_font, color, "INSTRUCTIONS");
    
    //while menu is looping
    while ( quit == false )
    {
        //while there are events in queue
        while ( SDL_PollEvent( &event) != 0 )
        {
            //if event is quit
            if ( event.type == SDL_QUIT )
            {
                //end menu loop
                quit = true;
                //end game loop
                level = END;
            }
        }
        
            //clear screen black
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderClear(renderer);
            
            //white window outline
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            SDL_RenderDrawRect(renderer, &window_outline);
            
            //render title
            title.render(WINDOW_WIDTH/2, WINDOW_HEIGHT/8);
        
            //render big pac-man
            clip = pacman_clips[animation/8];
            ++animation;
            if (animation/8 == 2) animation = 0;
            spritesheet.render(WINDOW_WIDTH/2 + movement, (WINDOW_HEIGHT/5)*2, &clip, 0.0, NULL, flip_type);
        
            //change direction if pacman reaches certain x coors
            if ( WINDOW_WIDTH/2 + movement > (WINDOW_WIDTH*4)/5)
            {
                moving_right = !moving_right;
                flip_type = SDL_FLIP_HORIZONTAL;
            }
            else if ( WINDOW_WIDTH/2 + movement < (WINDOW_WIDTH*1)/5 )
            {
                moving_right = !moving_right;
                flip_type = SDL_FLIP_NONE;
            }
        
            //if bound right, move right
            if ( moving_right == true )
                ++movement;
            //if bound left, move left
            else if ( moving_right == false)
                --movement;
        
            //render PLAY
            play.render(WINDOW_WIDTH/2, (WINDOW_HEIGHT*8)/10);
            //render INSTRUCTIONS
            instructions.render(WINDOW_WIDTH/2, (WINDOW_HEIGHT*9)/10);
        

        
            //update screen
            SDL_RenderPresent( renderer );
    }
}