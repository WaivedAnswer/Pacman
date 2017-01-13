//
//  GameBody.cpp
//  Pacman
//
//  Created by Quinn Ramsay on 2016-04-09.
//  Copyright © 2016 Quinn Ramsay. All rights reserved.
//

#include "GameBody.hpp"

GameBody::GameBody()
{
    for (int i = 0; i<DIMENSIONS; i++)
    {
        dimensions[i] = 0.0;
        coordinates[i] = 0.0;
    }
}

GameBody::GameBody(int objtype)
{
    for (int i = 0; i<DIMENSIONS; i++)
    {
        dimensions[i] = 0.0;
        coordinates[i] = 0.0;
    }
    type = objtype;
}

GameBody::GameBody(const float (&objdimensions)[DIMENSIONS], const int (&objcoordinates)[DIMENSIONS])
{
    for (int i = 0; i<DIMENSIONS; i++)
    {
        dimensions[i] = objdimensions[i];
        coordinates[i] = objcoordinates[i];
    }
}

void GameBody::GetDimensions(float (&objdimensions)[DIMENSIONS])
{
    for (int i = 0; i<DIMENSIONS; i++)
    {
        objdimensions[i] = dimensions[i];
    }
}

void GameBody::SetDimensions(const float (&objdimensions)[DIMENSIONS])
{
    for (int i = 0; i<DIMENSIONS; i++)
    {
        dimensions[i] = objdimensions[i];
    }
}

void GameBody::GetCoordinates(int (&objcoordinates)[DIMENSIONS])
{
    for (int i = 0; i<DIMENSIONS; i++)
    {
        objcoordinates[i] = coordinates[i];
    }
}

void GameBody::SetCoordinates(const int (&objcoordinates)[DIMENSIONS])
{
    for (int i = 0; i<DIMENSIONS; i++)
    {
        coordinates[i] = objcoordinates[i];
    }
}

bool GameBody::DidBodiesCollide(GameBody &other)
{
    int otherCoordinates[DIMENSIONS] = {0,0};
    float otherDimensions[DIMENSIONS] = {0.0,0.0};
    other.GetDimensions(otherDimensions);
    other.GetCoordinates(otherCoordinates);
    
    float leftSide = coordinates[0]*dimensions[0];
    float rightSide = coordinates[0]*dimensions[0] + dimensions[0];
    float leftOtherSide = otherCoordinates[0]*otherDimensions[0];
    float rightOtherSide = otherCoordinates[0]*otherDimensions[0] + otherDimensions[0];
    
    float topSide = coordinates[1]*dimensions[1];
    float bottomSide = coordinates[1]*dimensions[1] + dimensions[1];
    float topOtherSide = otherCoordinates[1]*otherDimensions[1];
    float bottomOtherSide = otherCoordinates[1]*otherDimensions[1] + otherDimensions[1];
    
    if(leftSide<rightOtherSide &&
       rightSide>leftOtherSide &&
       topSide < bottomOtherSide &&
       bottomSide > topOtherSide)
    {
        return true;
    }
    
    return false;
}

int GameBody::GetType()
{
    return type;
}


void GameBody::SetType(int bodytype)
{
    type = bodytype;
}


GameBody FLOORBODY = GameBody(FLOOR);
GameBody WALLBODY = GameBody(WALL);
GameBody POINTBODY = GameBody(POINTS);
GameBody EATEMBODY = GameBody(EATEMS);
GameBody GHOSTBODY = GameBody();
GameBody PACBODY = GameBody();