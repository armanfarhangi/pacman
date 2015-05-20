//Arman Farhangi
//May 11, 2015
//BOX-MAN Game
//C++ and SDL

//libraries
#include <SDL2/SDL.h>
#include <vector>
#include <fstream>
//headers
#include "texture.h"
#include "game.h"
#include "globals.h"
#include "tile.h"
#include "boxman.h"
#include "pellet.h"
#include "baddie.h"


/******* GAME CLASS DEFS *******/

//constructor starts level at menu
Game::Game()
{
    level = MENU;
    spritesheet.load_image("boxman_sheet.jpg");
}




//starts main game loop
void Game::start()
{
    //while game hasn't ended
    while (level != END)
    {
        //menu level
        if (level == MENU)
            menu();
        //instructions level
        else if (level == INSTRUCTIONS)
            instructions();
        //maze level
        else if (level == MAZE)
            maze();
    }
}





//starts menu loop
void Game::menu()
{
    //loop condition
    bool quit = false;
    //event storage
    SDL_Event event;
    
    //boxman animation clips
    std::vector<SDL_Rect> boxman_clips(2);
    boxman_clips[0] = { 0, TILE_HEIGHT*1, TILE_WIDTH, TILE_HEIGHT };
    boxman_clips[1] = { TILE_WIDTH*1, TILE_HEIGHT*1, TILE_WIDTH, TILE_HEIGHT };
    //boxman animation counter
    int animation = 0;
    //boxman movement
    int movement = 0;
    //boxman flippability
    SDL_RendererFlip flip_type;
    //boxman x direction
    bool moving_right;
    //50% chance starts off moving right
    if ( rand() % 2 == 0)
    {
        moving_right = true;
        flip_type = SDL_FLIP_NONE;
    }
    //50% chance starts off moving left
    else
    {
        moving_right = false;
        flip_type = SDL_FLIP_HORIZONTAL;
    }
    
    
    //yellow title text
    Texture title;
    SDL_Color color = { 250, 218, 10, 255 };
    title.load_text(big_font, color, "BOX-MAN");
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
                        button_outline.y += play.get_height() + 47;
                        button_outline.x -= 103;
                        button_outline.w += play.get_width() + 100;
                        button_select = false;
                    }
                    //if bottom button, move button outline up
                    else if (button_select == false)
                    {
                        button_outline.y -= play.get_height() + 47;
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
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
            SDL_RenderClear(renderer);
            
            //render white window outline
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            SDL_RenderDrawRect(renderer, &window_outline);
            //render button outline
            SDL_RenderDrawRect(renderer, &button_outline);
        
            //render title
            title.render(WINDOW_WIDTH/2, WINDOW_HEIGHT/8, NULL, CENTERED);
        
            //if boxman moves too far right
            if ( (WINDOW_WIDTH/2 - 2*TILE_WIDTH) + movement > (WINDOW_WIDTH*6)/10)
            {
                //change x direction
                moving_right = !moving_right;
                flip_type = SDL_FLIP_HORIZONTAL;
            }
            //if boxman moves too far left
            else if ( (WINDOW_WIDTH/2 - 2*TILE_WIDTH) + movement < (WINDOW_WIDTH*2)/10 )
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
        
            //render boxman
            spritesheet.render( (WINDOW_WIDTH/2 - 2*TILE_WIDTH) + movement, (WINDOW_HEIGHT/5)*2, &boxman_clips[animation/8], NOT_CENTERED, 5, 0.0, NULL, flip_type);
            ++animation;
            if (animation/8 == 2)
                animation = 0;
        
            //render PLAY
            play.render(WINDOW_WIDTH/2, (WINDOW_HEIGHT*8)/10, NULL, CENTERED);
            //render INSTRUCTIONS
            instructions.render(WINDOW_WIDTH/2, (WINDOW_HEIGHT*9)/10, NULL, CENTERED);
    
        
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
    instruction1.load_text(small_font, color, "EAT ALL THE PELLETS");
    //create second instruction
    Texture instruction2;
    instruction2.load_text(small_font, color, "MOVE WITH UP/DOWN/LEFT/RIGHT KEYS");
    //create third instruction
    Texture instruction3;
    instruction3.load_text(small_font, color, "AVOID GHOSTS");
    //create fourth instruction
    Texture instruction4;
    instruction4.load_text(small_font, color, "BIG PELLETS LET YOU EAT GHOSTS");
    //create back button text
    Texture back;
    back.load_text(small_font, color, "BACK TO MENU");
    
    //window outline
    SDL_Rect window_outline = { 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT };
    //button outline
    SDL_Rect button_outline = { WINDOW_WIDTH/2 - back.get_width()/2 - 10, (WINDOW_HEIGHT*7)/10 - back.get_height()/2 - 10, back.get_width() + 20, back.get_height() + 20 };
    
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
        instruction1.render( WINDOW_WIDTH/2, (WINDOW_HEIGHT*2)/10, NULL, CENTERED);
        instruction2.render( WINDOW_WIDTH/2, (WINDOW_HEIGHT*3)/10, NULL, CENTERED);
        instruction3.render( WINDOW_WIDTH/2, (WINDOW_HEIGHT*4)/10, NULL, CENTERED);
        instruction4.render( WINDOW_WIDTH/2, (WINDOW_HEIGHT*5)/10, NULL, CENTERED);
        //render back button
        back.render( WINDOW_WIDTH/2, (WINDOW_HEIGHT*7)/10, NULL, CENTERED);
        
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
void Game::maze()
{
    //game loop condition
    bool quit = false;
    //stores event information
    SDL_Event event;
    
    //window outline
    SDL_Rect window_outline = { 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT };
    
    //create map with 25 x 25 tiles
    std::vector<std::vector<Tile>> tiles(Y_TILES);
    //open map file to determine what kind of tile
    std::ifstream read_tiles;
    read_tiles.open("tile_layout.txt");
    bool obstacle_state;
    //for the amount of y tiles by the amount of x tiles
    for (int i = 0; i < Y_TILES; ++i)
        for (int j = 0; j < X_TILES; ++j)
        {
            //read in tile state from txt file
            read_tiles >> obstacle_state;
            tiles[i].push_back( Tile( obstacle_state, j, i) );
        }
    //close stream when done
    read_tiles.close();
    
    //create pellets
    std::vector<std::vector<Pellet>> pellets(Y_TILES);
    //open file to determine if pellets on each tile
    std::ifstream read_pellets;
    read_pellets.open("pellet_locations.txt");
    int pellet_on_tile;
    //for y_tiles * x_tiles
    for (int i = 0; i < Y_TILES; ++i)
        for (int j = 0; j < X_TILES; ++j)
        {
            //read in pellet state from txt file
            read_pellets >> pellet_on_tile;
            pellets[i].push_back( Pellet( pellet_on_tile, TILE_WIDTH*j, TILE_HEIGHT*i ) );
        }
    
    //boxman
    Boxman boxman(&spritesheet, &tiles, &pellets);
    
    //baddies
    std::vector<Baddie> baddies;
    baddies.push_back( Baddie(&spritesheet, &boxman, 11, 12, 1, &tiles) );
    baddies.push_back( Baddie(&spritesheet, &boxman, 12, 13, 2, &tiles) );
    baddies.push_back( Baddie(&spritesheet, &boxman, 13, 12, 3, &tiles) );
    
    
    //winning text
    Texture you_win;
    SDL_Color color = {250, 218, 10, 255};
    you_win.load_text(big_font, color, "YOU WIN!");
    
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
            
            //handle boxman velocity
            boxman.handle(event);
        }
        
        
        //move boxman
        boxman.move();
        
        //move baddies
        for (int i = 0; i < baddies.size(); ++i)
            baddies[i].move();
        
        //render tiles
        for (int i = 0; i < Y_TILES; ++i)
           for (int j = 0; j < X_TILES; ++j)
                spritesheet.render(TILE_WIDTH*j, TILE_HEIGHT*i, &tiles[i][j].get_clip());
        
        //render white window outline
        SDL_SetRenderDrawColor( renderer, 255, 255, 255, 255 );
        SDL_RenderDrawRect( renderer, &window_outline );
        
        //render pellets
        for (int i = 0; i < Y_TILES; ++i)
            for (int j = 0; j < X_TILES; ++j)
                pellets[i][j].render();
        
        //render baddies
        for (int i = 0; i < baddies.size(); ++i)
            baddies[i].render();
        
        //render boxman
        boxman.render();
        
        //upon eating all the pellets
        if (boxman.get_count() == 202)
        {
            you_win.render(WINDOW_WIDTH/2, WINDOW_HEIGHT/4, NULL, CENTERED);
            boxman.stop();
        }
        
        //update window with queued renders
        SDL_RenderPresent( renderer );
    }
}


