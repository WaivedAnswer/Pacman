//
//  PacmanCommon.cpp
//  Pacman
//
//  Created by Quinn Ramsay on 2016-04-11.
//  Copyright © 2016 Quinn Ramsay. All rights reserved.
//

#include <stdio.h>
#include "PacmanCommon.h"


void AddCoordinates(const int (&coordinate1)[DIMENSIONS], const int (&coordinate2)[DIMENSIONS], int (&result)[DIMENSIONS])
{
    for(int i =0; i<DIMENSIONS; i++)
    {
        result[i] = coordinate1[i] + coordinate2[i];
    }
}

void SubtractCoordinates(const int (&coordinate1)[DIMENSIONS], const int (&coordinate2)[DIMENSIONS], int (&result)[DIMENSIONS])
{
    for(int i =0; i<DIMENSIONS; i++)
    {
        result[i] = coordinate1[i] - coordinate2[i];
    }
}

int DotProduct(const int (&coordinate1)[DIMENSIONS], const int (&coordinate2)[DIMENSIONS])
{
    int total = 0;
    
    for (int i = 0; i<DIMENSIONS; i++)
    {
        total += coordinate1[i]*coordinate2[i];
    }
    
    return total;
}