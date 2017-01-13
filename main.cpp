//
//  main.cpp
//  Pacman
//
//  Created by Quinn Ramsay on 2016-04-09.
//  Copyright © 2016 Quinn Ramsay. All rights reserved.
//

#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <SDL2_mixer/SDL_mixer.h>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <math.h>
#include "Map.hpp"
#include "Pac.hpp"

//const int TILE_TYPES=3;



TTF_Font *gFont = NULL;
TTF_Font *largeFont = NULL;

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The surface contained by the window
 SDL_Surface* gScreenSurface = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

bool init()
{
    //Initialization flag
    bool success = true;
 
    //Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
        return false;
    }
    
    //Create window
    gWindow = SDL_CreateWindow( "PacMan", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
    if( gWindow == NULL )
    {
        printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
        return false;
    }
    //Create renderer for window
    
    gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED );
    if( gRenderer == NULL )
    {
        printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
        success = false;
    }
    else
    {
        //Initialize renderer color
        SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0x00, 0xFF );
        
        //Initialize PNG loading
        int imgFlags = IMG_INIT_PNG;
        if( !( IMG_Init( imgFlags ) & imgFlags ) )
        {
            printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
            success = false;
        }
        
        //Initialize SDL_ttf
        if( TTF_Init() == -1 )
        {
            printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
            success = false;
        }
    }
 
    return success;
 }

SDL_Surface* loadSurface( std::string path )
{
    //Load image at specified path
    SDL_Surface* optimizedSurface = NULL;
    SDL_Surface* loadedSurface = IMG_Load( path.c_str());
    if( loadedSurface == NULL )
    {
        printf( "Unable to load image %s! SDL_Image Error: %s\n", path.c_str(), IMG_GetError() );
    }
    else
    {
        //Convert surface to screen format
        optimizedSurface = SDL_ConvertSurface( loadedSurface, gScreenSurface->format, NULL );
        if( optimizedSurface == NULL )
        {
            printf( "Unable to optimize image %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
        }
        
        //Get rid of old loaded surface
        SDL_FreeSurface( loadedSurface );
    }
    
    return optimizedSurface;
}


bool loadMedia()
{
    //Loading success flag
    bool success = true;
    gFont = TTF_OpenFont( "OpenSansBold.ttf", 28 );
    if( gFont == NULL )
    {
        printf( "Unable to load font %s! SDL Error: %s\n", "OpenSansBold.ttf", SDL_GetError() );
        success = false;
    }
    largeFont = TTF_OpenFont( "OpenSansBold.ttf", 48);
    if( largeFont == NULL )
    {
        printf( "Unable to load font %s! SDL Error: %s\n", "OpenSansBold.ttf", SDL_GetError() );
        success = false;
    }
    
    return success;
}



void close()
{
    
    
    //Destroy window
    SDL_DestroyRenderer( gRenderer );
    SDL_DestroyWindow( gWindow );
    gWindow = NULL;
    gRenderer = NULL;
    
    //Quit SDL subsystems
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

void ResetLevel(Map &map, Ghost (&GhostList)[GHOSTNUM], Pac &pac)
{
    map.MapReset("LevelTest.txt", SCREEN_HEIGHT, SCREEN_HEIGHT);
    for (int i = 0; i<GHOSTNUM; i++)
    {
        GhostList[i].GhostReset(map);
    }
    pac.PacReset(map);
    
}

int main(int argc, char* args[])
{
    //main loop flag
    Map testMap = Map("LevelTest.txt", SCREEN_HEIGHT, SCREEN_HEIGHT, OFFSET[0], OFFSET[1]);
    float tileDimensions[DIMENSIONS];
    testMap.GetTileDimensions(tileDimensions);
    int PacCoordinates[DIMENSIONS] = {0,0};
    testMap.GetStartCoordinates(PacCoordinates);
    Pac character = Pac(tileDimensions, PacCoordinates);
    Ghost GhostList[GHOSTNUM];
    for (int i = 0; i<GHOSTNUM; i++)
    {
        GhostList[i].SetGhostNum(i);
        GameBody* ghostBody = GhostList[i].GetBody();
        int ghostCoordinates[DIMENSIONS] = {0,0};
        testMap.GetGhostStartCoordinate(ghostCoordinates, i);
        ghostBody->SetCoordinates(ghostCoordinates);
        ghostBody->SetDimensions(tileDimensions);
        
    }
    bool quit = false;
    bool isPaused = false;
    //Event handler
    SDL_Event event;
    //Initialize SDL
    
    // if initialization doesnt work
    if (init()==false)
    {
        return 1;
    }
    
    //if the files dont load
    if( loadMedia()==false)
    {
        return 2;
    }
    
    while (!quit)
    {
        bool hasMoved = false;
        while (SDL_PollEvent(&event) != 0)
        {
            
            //If the user has Xed out the window
            if( event.type == SDL_QUIT )
            {
                //Quit the program
                quit = true;
            }
            //checks key presses
            else if(event.type == SDL_KEYDOWN)
            {
                switch (event.key.keysym.sym)
                {
                        //directional keypresses
                    case SDLK_UP:
                        if(!isPaused)
                            character.MovePac(testMap, NORTH);
                        hasMoved = true;
                        break;
                
                    case SDLK_DOWN:
                        if(!isPaused)
                            character.MovePac(testMap, SOUTH);
                        hasMoved = true;
                        break;
                    case SDLK_RIGHT:
                        if(!isPaused)
                            character.MovePac(testMap, EAST);
                        hasMoved = true;
                        break;
                        
                    case SDLK_LEFT:
                        if(!isPaused)
                            character.MovePac(testMap, WEST);
                        hasMoved = true;
                        break;
                        //'P' pauses the game
                    case SDLK_p:
                        isPaused = !isPaused;
                        break;
                    case SDLK_r:
                        //'R' restarts level
                        isPaused = false;
                        ResetLevel(testMap, GhostList, character);
                        break;
                }
            }
        }
        //disables movement and interaction when game is paused or gameover
        if(!isPaused)
        {
            for (int i = 0; i<GHOSTNUM; i++)
            {
                GhostList[i].MoveGhost(testMap, &character);
            }
        
            character.InteractGhosts(GhostList, testMap);
        
            if(!hasMoved)
            {
                character.MovePac(testMap);
            }
        
            character.InteractGhosts(GhostList, testMap);
        
            for (int i = 0; i<GHOSTNUM; i++)
            {
                GhostList[i].Update();
            }
        
            character.Update();
        
            character.PickupObjects(testMap);
        }
        
        SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0x00, 0xFF );
        //Clear screen
        SDL_RenderClear( gRenderer );
        
        //Draws map ghosts pacman score and lives
        testMap.DrawMap(gRenderer);
        
        for (int i = 0; i<GHOSTNUM; i++)
        {
            GhostList[i].DrawGhost(gRenderer, OFFSET);
        }
        
        character.DrawPac(gRenderer, OFFSET);
        character.DrawPacScore(gRenderer, gFont, SCOREOFFSET);
        character.DrawPacLives(gRenderer, gFont, LIVESOFFSET);
        
        if(testMap.GetPointCount()<=0)
        {
            isPaused = true;
            character.DrawWin(gRenderer, largeFont, WINOFFSET);
        }
        if(character.GetLives()<=0)
        {
            isPaused = true;
            character.DrawGameOver(gRenderer, largeFont, GAMEOVEROFFSET);
        }
        
        //Update screen
        SDL_RenderPresent( gRenderer );
        
        SDL_Delay(200);
    }
    
    close();
    
    return 0;
}


