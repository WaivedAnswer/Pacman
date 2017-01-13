//
//  GameBody.hpp
//  Pacman
//
//  Created by Quinn Ramsay on 2016-04-09.
//  Copyright © 2016 Quinn Ramsay. All rights reserved.
//

#ifndef GameBody_hpp
#define GameBody_hpp

#include <stdio.h>
#include "PacmanCommon.h"

//class to holds physical aspects (extended bodies) of gamebodies
//gamebodies are used like in a tiled map
class GameBody
{
public:
    GameBody();
    GameBody(int objtype);
    GameBody(const float (&objdimensions)[DIMENSIONS], const int (&objcoordinates)[DIMENSIONS]);
    
    void GetDimensions(float (&objdimensions)[DIMENSIONS]);
    void SetDimensions(const float  (&objdimensions)[DIMENSIONS]);
    
    //x, y
    void GetCoordinates(int (&objcoordinates)[DIMENSIONS]);
    void SetCoordinates(const int (&objcoordinates)[DIMENSIONS]);
    
    bool DidBodiesCollide(GameBody &other);
    
    int GetType();
    void SetType(int bodytype);

    
    
private:
    //size of tiles
    float dimensions[DIMENSIONS];
    //map grid index
    int coordinates[DIMENSIONS];
    //object type
    int type;
};
//declares default gamebodies
extern GameBody FLOORBODY;
extern GameBody WALLBODY;
extern GameBody POINTBODY;
extern GameBody EATEMBODY;
extern GameBody GHOSTBODY;
extern GameBody PACBODY;
#endif /* GameBody_hpp */
