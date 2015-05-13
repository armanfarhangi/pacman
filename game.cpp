//Arman Farhangi
//May 11, 2015
//PAC-MAN Game
//C++ and SDL

//libraries
#include <SDL2/SDL.h>
#include <vector>
//headers
#include "texture.h"
#include "game.h"
#include "globals.h"
#include "pacman.h"



/******* GAME CLASS DEFS *******/

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
        //instructions level
        else if (level == INSTRUCTIONS)
            instructions();
        //maze level
        else if (level == MAZE)
            maze(spritesheet);
    }
}

//starts menu loop
void Game::menu(Texture& spritesheet)
{
    //loop condition
    bool quit = false;
    //event storage
    SDL_Event event;
    
    //big pac-man animation clips
    std::vector<SDL_Rect> pacman_clips(2);
    pacman_clips[0] = { TILE_WIDTH*2, TILE_HEIGHT*1, TILE_WIDTH*2, TILE_HEIGHT*2 };
    pacman_clips[1] = { TILE_WIDTH*4, TILE_HEIGHT*1, TILE_WIDTH*2, TILE_HEIGHT*2 };
    //big pac-man animation counter
    int animation = 0;
    //big pac-man movement
    int movement = 0;
    //big pac-man flippability
    SDL_RendererFlip flip_type;
    //big pac-man x direction
    bool moving_right;
    if ( rand() % 2 == 0)
    {
        moving_right = true;
        flip_type = SDL_FLIP_NONE;
    }
    else
    {
        moving_right = false;
        flip_type = SDL_FLIP_HORIZONTAL;
    }

    
    //tile dimensions for clip rendering
    SDL_Rect clip;
    clip = { 0, 0, TILE_WIDTH, TILE_HEIGHT };
    
    //yellow title text
    Texture title;
    SDL_Color color = { 250, 218, 10, 255 };
    title.load_text(big_font, color, "PAC-MAN");
    //PLAY text
    Texture play;
    play.load_text(medium_font, color, "PLAY");
    //instructions text
    Texture instructions;
    instructions.load_text(medium_font, color, "INSTRUCTIONS");
    
    //window outline
    SDL_Rect window_outline = { 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT };
    //button outline
    SDL_Rect button_outline = { WINDOW_WIDTH/2 - play.get_width()/2 - 14, (WINDOW_HEIGHT*8)/10 - play.get_height()/2 - 10, play.get_width() + 22, play.get_height() + 14 };
    //button_select
    bool button_select = true;
    
    //menu loop
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
            
            //if event is a non-repeat key press
            else if ( event.type == SDL_KEYDOWN && event.key.repeat == 0 )
            {
                //if event is down or up key
                if ( event.key.keysym.sym == SDLK_DOWN || event.key.keysym.sym == SDLK_UP)
                {
                    //if top button, move button outline down
                    if (button_select == true)
                    {
                        button_outline.y += play.get_height() + 20;
                        button_outline.x -= 103;
                        button_outline.w += play.get_width() + 100;
                        button_select = false;
                    }
                    //if bottom button, move button outline up
                    else if (button_select == false)
                    {
                        button_outline.y -= play.get_height() + 20;
                        button_outline.x += 103;
                        button_outline.w -= play.get_width() + 100;
                        button_select = true;
                    }
                }
                
                //if event is enter key
                else if ( event.key.keysym.sym == SDLK_RETURN )
                {
                    //end menu loop
                    quit = true;
                    //if top button selected
                    if (button_select == true )
                        //change level to maze
                        level = MAZE;
                    //if bottom button is selected
                    if (button_select == false)
                        //change level to instructions
                        level = INSTRUCTIONS;
                }
            }
        }
        
            //clear screen black
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderClear(renderer);
            
            //render white window outline
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            SDL_RenderDrawRect(renderer, &window_outline);
            //render button outline
            SDL_RenderDrawRect(renderer, &button_outline);
        
            //render title
            title.render(WINDOW_WIDTH/2, WINDOW_HEIGHT/8);
        
            //render big pac-man
            clip = pacman_clips[animation/8];
            ++animation;
            if (animation/8 == 2) animation = 0;
            spritesheet.render(WINDOW_WIDTH/2 + movement, (WINDOW_HEIGHT/5)*2, &clip, 0.0, NULL, flip_type);
        
            //if pacman moves too far right
            if ( WINDOW_WIDTH/2 + movement > (WINDOW_WIDTH*7)/10)
            {
                //change x direction
                moving_right = !moving_right;
                flip_type = SDL_FLIP_HORIZONTAL;
            }
            //if pacman moves too far left
            else if ( WINDOW_WIDTH/2 + movement < (WINDOW_WIDTH*3)/10 )
            {
                //change x direction
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


//starts instructions loop
void Game::instructions()
{
    //yellow color for instructions text
    SDL_Color color = { 250, 218, 10, 255 };
    
    //create first instruction
    Texture instruction1;
    instruction1.load_text(smallest_font, color, "EAT ALL THE PELLETS");
    //create second instruction
    Texture instruction2;
    instruction2.load_text(smallest_font, color, "MOVE WITH UP/DOWN/LEFT/RIGHT KEYS");
    //create third instruction
    Texture instruction3;
    instruction3.load_text(smallest_font, color, "AVOID GHOSTS");
    //create fourth instruction
    Texture instruction4;
    instruction4.load_text(smallest_font, color, "BIG PELLETS LET YOU EAT GHOSTS");
    //create back button text
    Texture back;
    back.load_text(smallest_font, color, "BACK TO MENU");
    
    //window outline
    SDL_Rect window_outline = { 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT };
    //button outline
    SDL_Rect button_outline = { WINDOW_WIDTH/2 - back.get_width()/2 - 7, (WINDOW_HEIGHT*7)/10 - back.get_height()/2 - 10, back.get_width() + 14, back.get_height() + 14 };
    
    //game loop condition
    bool quit = false;
    //stores event information
    SDL_Event event;
    
    //game loop
    while (quit == false)
    {
        //event loop (while there are events in queue)
        while ( SDL_PollEvent(&event) != 0 )
        {
            //if quit event
            if (event.type == SDL_QUIT)
            {
                //end instructions loop
                quit = true;
                //end main loop
                level = END;
            }
            
            //if key press event that's not a repeat
            else if (event.type == SDL_KEYDOWN && event.key.repeat == 0)
                //if enter key
                if ( event.key.keysym.sym == SDLK_RETURN)
                {
                    //end instructions loop
                    quit = true;
                    //change level to title screen
                    level = MENU;
                }
        }
        
        //clear window black
        SDL_SetRenderDrawColor( renderer, 0, 0, 0, 255 );
        SDL_RenderClear(renderer);
        
        //set color to light pink
        SDL_SetRenderDrawColor( renderer, 219, 112, 147, 255 );
        
        //render instructions
        instruction1.render( WINDOW_WIDTH/2, (WINDOW_HEIGHT*2)/10);
        instruction2.render( WINDOW_WIDTH/2, (WINDOW_HEIGHT*3)/10);
        instruction3.render( WINDOW_WIDTH/2, (WINDOW_HEIGHT*4)/10);
        instruction4.render( WINDOW_WIDTH/2, (WINDOW_HEIGHT*5)/10);
        //render back button
        back.render( WINDOW_WIDTH/2, (WINDOW_HEIGHT*7)/10);
        
        //set color to white for outlines
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        //render back button outline
        SDL_RenderDrawRect(renderer, &button_outline);
        //render window outline
        SDL_RenderDrawRect(renderer, &window_outline);
        
        //update window with new renders
        SDL_RenderPresent( renderer );
    }
}

//starts maze loop
void Game::maze(Texture& spritesheet)
{
    //game loop condition
    bool quit = false;
    //stores event information
    SDL_Event event;
    
    //create pacman object
    Pacman pacman(spritesheet);
    
    //load maze image
    Texture maze;
    maze.load_image("maze.png");
    //bottom layer maze clip
    SDL_Rect bottom_maze = { WINDOW_WIDTH, 0 , WINDOW_WIDTH, WINDOW_HEIGHT };
    //top layer maze tiler
    std::vector<std::vector<SDL_Rect>> tiles(14);
    SDL_Rect clip;
    //14 by 16 2D vector
    for (int i = 0; i < tiles.size(); ++i)
    {
        for (int j = 0; j < 16; ++j)
        {
            //creating 14*16 32*31 clips for the maze image to render in tiles
            clip = { TILE_WIDTH*i, TILE_HEIGHT*j, TILE_WIDTH, TILE_HEIGHT };
            tiles[i].push_back(clip);
        }
    }
    
    //window outline
    SDL_Rect window_outline = { 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT };
    
    //game loop
    while (quit == false)
    {
        //event loop (while there are events in queue)
        while ( SDL_PollEvent(&event) != 0 )
        {
            //if quit event
            if (event.type == SDL_QUIT)
            {
                //end instructions loop
                quit = true;
                //end main loop
                level = END;
            }
        
            //handle event for pacman velocity
            pacman.handle(event);
        }
        
        
        //move pacman
        pacman.move();
        
        
        
        
        //clear window black
        SDL_SetRenderDrawColor( renderer, 0, 0, 0, 255 );
        SDL_RenderClear(renderer);
        
        //render bottom layer maze (empty)
        maze.render(WINDOW_WIDTH/2, WINDOW_HEIGHT/2, &bottom_maze);
        //render top layer maze tiles (filled with pellets)
        for (int i = 0; i < tiles.size(); ++i)
            for (int j = 0; j < 16; ++j)
                    maze.render( (TILE_WIDTH/2) + (TILE_WIDTH*i), (TILE_HEIGHT/2) + (TILE_HEIGHT*j), &tiles[i][j] );
        
        //render pacman
        pacman.render();
        
        //render white window outline
        SDL_SetRenderDrawColor( renderer, 255, 255, 255, 255 );
        SDL_RenderDrawRect( renderer, &window_outline );
        
        //update window with queued renders
        SDL_RenderPresent( renderer );
    }
}


