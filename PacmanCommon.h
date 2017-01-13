//
//  PacmanCommon.h
//  Pacman
//
//  Created by Quinn Ramsay on 2016-04-09.
//  Copyright © 2016 Quinn Ramsay. All rights reserved.
//

#ifndef PacmanCommon_h
#define PacmanCommon_h

#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <string>

const int DIMENSIONS = 2;

const int GHOSTNUM = 4;
const int PACLIVES = 3;

//percentage ghost take shortest path move /100
const int PERCENTGHOSTMOVE = 75;

//invincibility count
const int EATEMCOUNT = 60;

//ghost stop times
const int GHOSTDEADCOUNT = 30;
const int GHOSTINITIALSTOPCOUNT = 5;

//point scores
const int POINTSCORE = 10;
const int EATEMSCORE = 150;

const int SCREEN_WIDTH=640;
const int SCREEN_HEIGHT=480;

//MAP OFFSETS
const int OFFSET[2] = {SCREEN_WIDTH-SCREEN_HEIGHT, 0};
//TEXT OFFSETS
const int SCOREOFFSET[2] = {SCREEN_WIDTH/64, SCREEN_HEIGHT/8};
const int LIVESOFFSET[2] = {SCREEN_WIDTH/64, SCREEN_HEIGHT*7/8};

const int GAMEOVEROFFSET[2] = {SCREEN_WIDTH*2/5, SCREEN_HEIGHT/3};
const int WINOFFSET[2] = {SCREEN_WIDTH*3/7, SCREEN_HEIGHT/3};


enum ObjectTypes
{
    FLOOR,
    WALL,
    POINTS,
    EATEMS,
    STARTLOCATION,
    GHOSTSTART
};
enum Directions
{
    NONE,
    NORTH,
    WEST,
    SOUTH,
    EAST,
    DIRECTIONTOTALS
};

//coordinate change vectors for Directions
const int coordinateChanges[DIRECTIONTOTALS][DIMENSIONS] = {{0,0},{0,-1},{-1,0},{0,+1},{+1,0}};

//adds coordinates into results
void AddCoordinates(const int (&coordinate1)[DIMENSIONS], const int (&coordinate2)[DIMENSIONS], int (&result)[DIMENSIONS]);

//subtracts 2 from 1
void SubtractCoordinates(const int (&coordinate1)[DIMENSIONS], const int (&coordinate2)[DIMENSIONS], int (&result)[DIMENSIONS] );
int DotProduct(const int (&coordinate1)[DIMENSIONS], const int (&coordinate2)[DIMENSIONS]);



#endif /* PacmanCommon_h */
