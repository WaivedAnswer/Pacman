//
//  Ghost.hpp
//  Pacman
//
//  Created by Quinn Ramsay on 2016-04-10.
//  Copyright © 2016 Quinn Ramsay. All rights reserved.
//

#ifndef Ghost_hpp
#define Ghost_hpp

#include <stdio.h>
#include "PacmanCommon.h"
#include "GameBody.hpp"
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include "LTexture.hpp"
#include "Map.hpp"

class Pac;
//ghost class chases pac when he is not in eatem state
//and runs away when he is
//ghost number used to retreive clipping information for sprite display
//entire sprite is 4 ghosts, chooses the proper ghost to use
class Ghost
{
public:
    Ghost();
    Ghost(float (&bodyDimensions)[DIMENSIONS], int (&bodyCoordinates)[DIMENSIONS], int nghostNum);
    void SetGhostNum(int num);
    //move ghost uses the dot product of the difference between the ghost and character
    //to rank and choose the optimal direction to travel
    //based on possible moves
    //with PERCENTGHOSTMOVE (in PacmanCommon.h) efficiency
    //1-PERCENTGHOSTMOVE they randomly choose a direction
    void MoveGhost(Map &map, Pac* character);
    //uses ghost number and gspriteclips information to draw correct ghost
    void DrawGhost(SDL_Renderer* renderer, const int (&offset)[DIMENSIONS]);
    
    //sends ghost back to start location with timer before it can move again
    void KillGhost(Map &map);
    GameBody* GetBody();
    //sets the time a ghost must stop for
    void SetGhostStopTime(int time);
    
    //changes the ghost state to run away from the character
    void SetRunAway(bool run);
    //counts down stop counter
    void Update();
    //resets upon restart of map
    void GhostReset(Map &map);
private:
    GameBody body;
    bool isRunning;
    int stopCounter;
    int lastDirection;
    LTexture* textures;
    SDL_Rect gSpriteClips[4];
    int ghostNum;
};
#endif /* Ghost_hpp */
