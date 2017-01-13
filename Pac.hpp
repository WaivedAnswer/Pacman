//
//  Pac.hpp
//  Pacman
//
//  Created by Quinn Ramsay on 2016-04-10.
//  Copyright © 2016 Quinn Ramsay. All rights reserved.
//

#ifndef Pac_hpp
#define Pac_hpp

#include <stdio.h>
#include "PacmanCommon.h"
#include "GameBody.hpp"
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>
#include "LTexture.hpp"
#include "Map.hpp"
#include "Ghost.hpp"
class Pac
{
public:
    Pac(float (&bodyDimensions)[DIMENSIONS], int (&bodyCoordinates)[DIMENSIONS]);
    ~Pac();
    //Moves pac in last direction traveled if valid
    bool MovePac(Map map);
    //moves pac according to user input
    bool MovePac(Map map, int direction);
    //picks up points and eatems from map if pac steps on that tile
    bool PickupObjects(Map &map);
    //drawing functions for pac, score, lives and endgame messages
    void DrawPac(SDL_Renderer* renderer, const int (&offset)[DIMENSIONS]);
    void DrawPacScore(SDL_Renderer* renderer, TTF_Font *gFont, const int (&offset)[DIMENSIONS]);
    void DrawPacLives(SDL_Renderer* renderer, TTF_Font *gFont, const int (&offset)[DIMENSIONS]);
    void DrawWin(SDL_Renderer* renderer, TTF_Font *gFont, const int (&offset)[DIMENSIONS]);
    void DrawGameOver(SDL_Renderer* renderer, TTF_Font *gFont, const int (&offset)[DIMENSIONS]);
    
    GameBody* GetBody();
    void SetBody(GameBody *gamebody);
    
    bool GetEatemState();
    void Update();
    //checks for collisions with ghosts, if pac is in eatemstate eats ghost, otherwise kills pac
    void InteractGhosts(Ghost (&ghosts)[GHOSTNUM], Map (&map));
    //reset ghost and pac positions, removes a life from pac
    void KillPac(Map (&map), Ghost (&ghosts)[GHOSTNUM]);
    
    int GetScore();
    int GetLives();
    //resets pac upon game reset
    void PacReset(Map &map);
private:
    int lives;
    bool eatemState;
    int score;
    int eatemCount;
    int lastDirection;
    GameBody body;
    LTexture* gameOverTexture;
    LTexture* scoreTexture;
    LTexture* liveTexture;
    LTexture* textures;
};
#endif /* Pac_hpp */
