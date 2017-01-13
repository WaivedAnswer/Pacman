//
//  Map.cpp
//  Pacman
//
//  Created by Quinn Ramsay on 2016-04-10.
//  Copyright © 2016 Quinn Ramsay. All rights reserved.
//

#include "Map.hpp"

#include <string>
#include <fstream>
#include <sstream>
#include "LTexture.hpp"

Map::Map(std::string filename, int mapWidth, int mapHeight, float screenOffsetX, float screenOffsetY)
{
    std::ifstream map(filename);
    std::string line;
    offset[0] = screenOffsetX;
    offset[1] = screenOffsetY;
    if (map.is_open())
    {
        getline(map, line);
        std::istringstream firstss(line);
        
        for(int i=0; i<DIMENSIONS; i++)
        {
            firstss >> dimensions[i];
        }
        
        if(dimensions[0] != 0)
        {
            tileDimensions[0] = static_cast<double>(mapWidth)/static_cast<double>(dimensions[0]);
        }
        else
        {
            tileDimensions[0] = 0;
        }
        
        if(dimensions[1] != 0)
        {
            tileDimensions[1] = static_cast<double>(mapHeight)/static_cast<double>(dimensions[1]);
        }
        else
        {
            tileDimensions[1] = 0;
        }
        int ghostCount = 0;
        while (getline(map, line))
        {
            std::istringstream iss(line);
            
            std::vector<GameBody> row;
            do
            {
                int type = -1;
                iss >> type;
                
                switch (type)
                {
                    case FLOOR:
                        row.push_back(FLOORBODY);
                        break;
                    case WALL:
                        row.push_back(WALLBODY);
                        break;
                    case POINTS:
                        pointCount++;
                        row.push_back(POINTBODY);
                        break;
                    case EATEMS:
                        pointCount++;
                        row.push_back(EATEMBODY);
                        break;
                    case STARTLOCATION:
                        startLocation[0] = static_cast<int>(grid.size());
                        startLocation[1] = static_cast<int>(row.size());
                        row.push_back(FLOORBODY);
                        break;
                    case GHOSTSTART:
                        ghostStarts[ghostCount][0] = static_cast<int>(grid.size());
                        ghostStarts[ghostCount][1] = static_cast<int>(row.size());
                        ghostCount++;
                        row.push_back(FLOORBODY);
                        break;
                    default:
                        break;
                        
                }
            } while (iss);
            grid.push_back(row);
        }
    }
}

void Map::DrawMap(SDL_Renderer* renderer)
{
    int rowCount = 0, colCount = 0;
    
    for(auto it : grid)
    {
        colCount = 0;
        for(auto it2: it)
        {
            double dimensionDifference = tileDimensions[0] - tileDimensions[1];
            double wallAdjust = 0.5;
            
            //wall rects are entire tile dimension
            //need to multiple tile dimensions by grid count add offset to get screen coordinates
            SDL_Rect wallFillRect = { static_cast<int>(tileDimensions[0]*colCount + offset[0] + wallAdjust), static_cast<int>(tileDimensions[1]*rowCount + offset[1] + wallAdjust), static_cast<int>(tileDimensions[0] - wallAdjust), static_cast<int>(tileDimensions[1] - wallAdjust) };
            
            //point rects are half tile dimension
            //need to multiple tile dimensions by grid count add offset to get screen coordinates
            SDL_Rect pointFillRect = { static_cast<int>(tileDimensions[0]*colCount + tileDimensions[0]*0.25+ dimensionDifference/2.0  + offset[0]), static_cast<int>(tileDimensions[1]*rowCount + tileDimensions[1]*0.25 +  + offset[1]), static_cast<int>(0.5*tileDimensions[1]), static_cast<int>(0.5*tileDimensions[1]) };
            
            //eatem rects are entire tile dimension
            //need to multiple tile dimensions by grid count add offset to get screen coordinates
            SDL_Rect eatemFillRect = { static_cast<int>(tileDimensions[0]*colCount + tileDimensions[0]*0.125 + dimensionDifference/2.0  + offset[0]), static_cast<int>(tileDimensions[1]*rowCount + tileDimensions[1]*0.125  + offset[1]), static_cast<int>(0.75 * tileDimensions[1]), static_cast<int>(0.75 * tileDimensions[1]) };
            switch(it2.GetType())
            {
                //other types shouldnt be stored in map drawing
                case FLOOR:
                    break;
                case WALL:
                    SDL_SetRenderDrawColor( renderer, 0x00, 0x00, 0xFF, 0xFF );
                    SDL_RenderFillRect( renderer, &wallFillRect );
                    break;
                case POINTS:
                    SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
                    SDL_RenderFillRect( renderer, &pointFillRect );
                    break;
                case EATEMS:
                    SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
                    SDL_RenderFillRect( renderer, &eatemFillRect );
                    break;
                case GHOSTSTART:
                    break;
                default:
                    //do nothing
                    break;
            }
            colCount++;
        }
        rowCount++;
    }
}

bool Map::CanMove(int (&coordinates)[DIMENSIONS])
{
    int type = grid[coordinates[1]][coordinates[0]].GetType();
    for (int i = 0; i<DIMENSIONS; i++)
    {
        if(coordinates[i] < 0 || coordinates[i] > dimensions[i])
        {
            return false;
        }
    }
    return  type != WALL;
}



void Map::GetTileDimensions( float (&gtileDimensions)[DIMENSIONS])
{
    for(int i = 0; i<DIMENSIONS; i++)
    {
        gtileDimensions[i] = tileDimensions[i];
    }
}

//returns x, y
void Map::GetStartCoordinates( int (&gstartLocation)[DIMENSIONS])
{

    gstartLocation[0] = startLocation[1];
    gstartLocation[1] = startLocation[0];

}

void Map::GetGhostStartCoordinate(int (&gstartLocation)[DIMENSIONS], int ghostNum)
{
    gstartLocation[0] = ghostStarts[ghostNum][1];
    gstartLocation[1] = ghostStarts[ghostNum][0];
}

int Map::GetTileType(int (&coordinates)[DIMENSIONS])
{
    if(grid.empty())
    {
        return FLOOR;
    }
    if(!(coordinates[1] < grid.size() && coordinates[0] < grid[coordinates[1]].size()))
    {
        return FLOOR;
    }
    GameBody body = grid[coordinates[1]][coordinates[0]];
    return body.GetType();
}

bool Map::TakeObject(int (&coordinates)[DIMENSIONS])
{
    int type = grid[coordinates[1]][coordinates[0]].GetType();
    if(type == POINTS || type == EATEMS)
    {
        grid[coordinates[1]][coordinates[0]].SetType(FLOOR);
        pointCount--;
        return true;
    }
    return false;
}

int Map::GetPointCount()
{
    return pointCount;
}

//rereads map from file
void Map::MapReset(std::string filename,int mapWidth, int mapHeight)
{
    std::ifstream map(filename);
    std::string line;
    
    grid.clear();
    pointCount = 0;
    if (map.is_open())
    {
        getline(map, line);
        std::istringstream firstss(line);
        
        for(int i=0; i<DIMENSIONS; i++)
        {
            firstss >> dimensions[i];
        }
        
        if(dimensions[0] != 0)
        {
            tileDimensions[0] = static_cast<double>(mapWidth)/static_cast<double>(dimensions[0]);
        }
        else
        {
            tileDimensions[0] = 0;
        }
        
        if(dimensions[1] != 0)
        {
            tileDimensions[1] = static_cast<double>(mapHeight)/static_cast<double>(dimensions[1]);
        }
        else
        {
            tileDimensions[1] = 0;
        }
        int ghostCount = 0;
        while (getline(map, line))
        {
            std::istringstream iss(line);
            
            std::vector<GameBody> row;
            do
            {
                int type = -1;
                iss >> type;
                
                switch (type)
                {
                    case FLOOR:
                        row.push_back(FLOORBODY);
                        break;
                    case WALL:
                        row.push_back(WALLBODY);
                        break;
                    case POINTS:
                        pointCount++;
                        row.push_back(POINTBODY);
                        break;
                    case EATEMS:
                        pointCount++;
                        row.push_back(EATEMBODY);
                        break;
                    case STARTLOCATION:
                        startLocation[0] = static_cast<int>(grid.size());
                        startLocation[1] = static_cast<int>(row.size());
                        row.push_back(FLOORBODY);
                        break;
                    case GHOSTSTART:
                        ghostStarts[ghostCount][0] = static_cast<int>(grid.size());
                        ghostStarts[ghostCount][1] = static_cast<int>(row.size());
                        ghostCount++;
                        row.push_back(FLOORBODY);
                        break;
                    default:
                        break;
                        
                }
            } while (iss);
            grid.push_back(row);
        }
    }

}

