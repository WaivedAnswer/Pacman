//
//  Map.hpp
//  Pacman
//
//  Created by Quinn Ramsay on 2016-04-10.
//  Copyright © 2016 Quinn Ramsay. All rights reserved.
//

#ifndef Map_hpp
#define Map_hpp

#include <stdio.h>
#include <vector>
#include <string>
#include "GameBody.hpp"
#include "PacmanCommon.h"
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>

//map class holds grid of gamebodies and allows interaction with each
//also stores tile dimensions and offset, start location of pacman and start locations
//of ghosts
class Map
{
public:
    //reads Map from text file
    Map(std::string filename, int mapWidth, int mapHeight, float screenOffsetX, float screenOffsetY);
    
    void DrawMap(SDL_Renderer* renderer);
    //checks if one can move to this coordinate
    //if !WALL
    bool CanMove(int (&coordinates)[DIMENSIONS]);
    
    void GetTileDimensions( float (&gtileDimensions)[DIMENSIONS]);
    //returns x,y
    void GetStartCoordinates( int (&gstartLocation)[DIMENSIONS]);
    void GetGhostStartCoordinate(int (&gstartLocation)[DIMENSIONS], int ghostNum);
    
    int GetTileType(int (&coordinates)[DIMENSIONS]);
    
    //used for replacing object with floor type
    //picking up points and eatems
    bool TakeObject(int (&coordinates)[DIMENSIONS]);
    
    //get total point count remaining on map
    int GetPointCount();
    //resets map on game reset
    //reloads map from file
    void MapReset(std::string filename,int mapWidth, int mapHeight);
private:
    int pointCount;
    int dimensions[DIMENSIONS];
    float tileDimensions[DIMENSIONS];
    //holds start location as index (y,x)
    int startLocation[DIMENSIONS];
    int ghostStarts[GHOSTNUM][DIMENSIONS];
    float offset[DIMENSIONS];
    std::vector<std::vector<GameBody>> grid;
    
};
#endif /* Map_hpp */
