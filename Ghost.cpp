//
//  Ghost.cpp
//  Pacman
//
//  Created by Quinn Ramsay on 2016-04-10.
//  Copyright © 2016 Quinn Ramsay. All rights reserved.
//

#include "Ghost.hpp"
#include "Pac.hpp"

Ghost::Ghost()
{
    isRunning = false;
    stopCounter = GHOSTINITIALSTOPCOUNT;
    textures = NULL;
    lastDirection = NONE;
}

Ghost::Ghost(float (&bodyDimensions)[DIMENSIONS], int (&bodyCoordinates)[DIMENSIONS], int nghostNum)
{
    isRunning = false;
    stopCounter = GHOSTINITIALSTOPCOUNT;
    textures = NULL;
    lastDirection = NONE;
    body.SetDimensions(bodyDimensions);
    body.SetCoordinates(bodyCoordinates);
    ghostNum = nghostNum;
}

void Ghost::SetGhostNum(int num)
{
    ghostNum = num;
}

//gets a vector of the optimal directions to travel based on dot product
std::vector<int> GetDirectionOrder(const int (&coordDiff)[DIMENSIONS])
{
    std::vector<int> DirectionOrder;
    std::vector<int> unOrderedDotProducts;
    std::vector<int> OrderedDotProducts;
    
    for (int i = 0; i<DIRECTIONTOTALS; i++)
    {
        unOrderedDotProducts.push_back(DotProduct(coordDiff, coordinateChanges[i]));
        OrderedDotProducts.push_back(DotProduct(coordDiff, coordinateChanges[i]));
    }
    
    std::sort(OrderedDotProducts.begin(),OrderedDotProducts.end());
    
    for (int i = 0; i<DIRECTIONTOTALS; i++)
    {
        for(int j = 0; j<DIRECTIONTOTALS;j++)
        {
            if(OrderedDotProducts[i] == unOrderedDotProducts[j])
            {
                DirectionOrder.push_back(j);
            }
        }
    }
    /*int dotNorth = DotProduct(coordDiff, coordinateChanges[NORTH]);
    int dotWest = DotProduct(coordDiff, coordinateChanges[WEST]);
    int dotSouth = DotProduct(coordDiff, coordinateChanges[SOUTH]);
    int dotEast = DotProduct(coordDiff, coordinateChanges[EAST]);
    int dotNone = DotProduct(coordDiff, coordinateChanges[NONE]);*/
    
    
    
    return DirectionOrder;
}

//tests optimal directions towards pac to see if valid choices, returns optimal valid choice
int GetDirectionTowardsPac(const int (&currentCoordinates)[DIMENSIONS], const int (&pacCoordinates)[DIMENSIONS], Map &map)
{
    int coordDiff[DIMENSIONS] = {0,0};
    int newCoordinates[DIMENSIONS] = {0,0};
    AddCoordinates(newCoordinates, currentCoordinates, newCoordinates);
    SubtractCoordinates(currentCoordinates, pacCoordinates, coordDiff);
    
    std::vector<int> DirectionOrder = GetDirectionOrder(coordDiff);
    
    for(auto it : DirectionOrder)
    {
        AddCoordinates(newCoordinates, coordinateChanges[it], newCoordinates);
        if (map.CanMove(newCoordinates) && it != NONE)
        {
            return it;
        }
        SubtractCoordinates(newCoordinates, coordinateChanges[it], newCoordinates);
    }

    return NONE;
}

//tests optimal directions away from pac to see if valid choices, returns optimal valid choice
int GetDirectionAwayFromPac(const int (&currentCoordinates)[DIMENSIONS], int (&pacCoordinates)[DIMENSIONS], Map &map)
{
    int coordDiff[DIMENSIONS] = {0,0};
    int newCoordinates[DIMENSIONS] = {0,0};
    AddCoordinates(newCoordinates, currentCoordinates, newCoordinates);
    SubtractCoordinates(currentCoordinates, pacCoordinates, coordDiff);
    
    std::vector<int> DirectionOrder = GetDirectionOrder(coordDiff);
    std::reverse(DirectionOrder.begin(), DirectionOrder.end());
    
    for(auto it : DirectionOrder)
    {
        AddCoordinates(newCoordinates, coordinateChanges[it], newCoordinates);
        if (map.CanMove(newCoordinates) && it != NONE)
        {
            return it;
        }
        SubtractCoordinates(newCoordinates, coordinateChanges[it], newCoordinates);
    }
    
    return NONE;
}

//moves ghost according to probability and best choice towards or away from Pac
//depending on isRunning state

void Ghost::MoveGhost(Map &map, Pac* character)
{
    if(stopCounter>0)
    {
        return;
    }
        
    int coordinates[DIMENSIONS] = {0,0};
    body.GetCoordinates(coordinates);
    int pacCoordinates[DIMENSIONS] = {0,0};
    character->GetBody()->GetCoordinates(pacCoordinates);
    
    int direction = NONE;
    if(!isRunning)
    {
        direction = GetDirectionTowardsPac(coordinates, pacCoordinates, map);
    }
    else
    {
        direction = GetDirectionAwayFromPac(coordinates, pacCoordinates, map);
    }
    
    int GhostMove = rand()%100;
    
    int randDirection = rand()%DIRECTIONTOTALS;
    
    if(GhostMove<PERCENTGHOSTMOVE)
    {
        lastDirection = direction;
        
    }
    else
    {
        lastDirection = randDirection;
    }
    
    switch (lastDirection)
    {
        case NONE:
            return;
        case NORTH:
            AddCoordinates(coordinates, coordinateChanges[NORTH], coordinates);
            break;
        case WEST:
            AddCoordinates(coordinates, coordinateChanges[WEST], coordinates);
            break;
        case SOUTH:
            AddCoordinates(coordinates, coordinateChanges[SOUTH], coordinates);
            break;
        case EAST:
            AddCoordinates(coordinates, coordinateChanges[EAST], coordinates);
            break;
    }
    
    if(!map.CanMove(coordinates))
    {
        return;
    }
    
    body.SetCoordinates(coordinates);
    
}

//draws ghosts according to position and clipping
void Ghost::DrawGhost(SDL_Renderer* renderer, const int (&offset)[DIMENSIONS])
{
    if(textures == NULL)
    {
        textures = new LTexture(renderer);
        textures->loadFromFile("2-ghosts-pac-man.jpg");
        //set top left sprite
        gSpriteClips[ 0 ].x =   0;
        gSpriteClips[ 0 ].y =   0;
        gSpriteClips[ 0 ].w = 161;
        gSpriteClips[ 0 ].h = 161;
        
        //Set top right sprite
        gSpriteClips[ 1 ].x = 161;
        gSpriteClips[ 1 ].y =   0;
        gSpriteClips[ 1 ].w = 161;
        gSpriteClips[ 1 ].h = 161;
        
        //Set bottom left sprite
        gSpriteClips[ 2 ].x =   0;
        gSpriteClips[ 2 ].y = 161;
        gSpriteClips[ 2 ].w = 161;
        gSpriteClips[ 2 ].h = 161;
        
        //Set bottom right sprite
        gSpriteClips[ 3 ].x = 161;
        gSpriteClips[ 3 ].y = 161;
        gSpriteClips[ 3 ].w = 161;
        gSpriteClips[ 3 ].h = 161;
    }
    
    int coordinates[DIMENSIONS];
    float dimensions[DIMENSIONS];
    
    body.GetCoordinates(coordinates);
    body.GetDimensions(dimensions);
    
    textures->render(coordinates[0]*dimensions[0] + offset[0], coordinates[1]*dimensions[1] + offset[1], static_cast<int>(dimensions[0]), static_cast<int>(dimensions[1]), &gSpriteClips[ghostNum]);

}

//send ghost back to start position sets stopCounter for GHOSTDEADCOUNT
void Ghost::KillGhost(Map &map)
{
    isRunning = false;
    stopCounter = GHOSTDEADCOUNT;
    int ghostCoordinates[DIMENSIONS] = {0,0};
    map.GetGhostStartCoordinate(ghostCoordinates, ghostNum);
    body.SetCoordinates(ghostCoordinates);
}

GameBody* Ghost::GetBody()
{
    return &body;
}

void Ghost::SetGhostStopTime(int time)
{
    stopCounter = time;
}

void Ghost::SetRunAway(bool run)
{
    isRunning = run;
}

void Ghost::Update()
{
    if(stopCounter>0)
    {
        stopCounter--;
    }
}
//resets ghost on map reset
void Ghost::GhostReset(Map &map)
{
    isRunning = false;
    stopCounter = GHOSTINITIALSTOPCOUNT;
    
    int ghostCoordinates[DIMENSIONS] = {0,0};
    map.GetGhostStartCoordinate(ghostCoordinates, ghostNum);
    body.SetCoordinates(ghostCoordinates);
    
    lastDirection = NONE;
    
}