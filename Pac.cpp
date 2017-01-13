//
//  Pac.cpp
//  Pacman
//
//  Created by Quinn Ramsay on 2016-04-10.
//  Copyright © 2016 Quinn Ramsay. All rights reserved.
//

#include "Pac.hpp"
#include <SDL2_ttf/SDL_ttf.h>

Pac::Pac(float (&bodyDimensions)[DIMENSIONS], int (&bodyCoordinates)[DIMENSIONS])
{
    //body = new GameBody(bodyDimensions, bodyCoordinates);
    body.SetDimensions(bodyDimensions);
    body.SetCoordinates(bodyCoordinates);
    eatemState = false;
    lives = PACLIVES;
    textures = NULL;
    liveTexture = NULL;
    scoreTexture = NULL;
    gameOverTexture = NULL;
    lastDirection = NONE;
}

Pac::~Pac()
{
    if(textures != NULL)
    {
        delete textures;
        textures = NULL;
    }
    
    if(liveTexture != NULL)
    {
        delete liveTexture;
        liveTexture = NULL;
    }
    
    if(scoreTexture != NULL)
    {
        delete scoreTexture;
        scoreTexture = NULL;
    }
    
    if(gameOverTexture != NULL)
    {
        delete gameOverTexture;
        gameOverTexture = NULL;
    }
    
    //TODO remove
    /*if(body != NULL)
    {
        delete body;
        body = NULL;
    }*/
}

bool Pac::MovePac(Map map)
{
    //TODO change this later to not work off frames
    int coordinates[DIMENSIONS];
    body.GetCoordinates(coordinates);
    switch (lastDirection)
    {
        case NONE:
            return false;
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
        return false;
    }
    
    body.SetCoordinates(coordinates);
    
    return true;
}

bool Pac::MovePac(Map map, int direction)
{
    int coordinates[DIMENSIONS];
    body.GetCoordinates(coordinates);
    lastDirection = direction;
    switch (lastDirection)
    {
        case NONE:
            return false;
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
        return false;
    }
    
    body.SetCoordinates(coordinates);
    
    return true;

}

bool Pac::PickupObjects(Map &map)
{
    int coordinates[DIMENSIONS];
    body.GetCoordinates(coordinates);
    int type = map.GetTileType(coordinates);
    if(type == POINTS)
    {
        score += POINTSCORE;
        map.TakeObject(coordinates);
        //map.SetPointCount(map.GetPointCount()-1);
        return true;
    }
    else if(type == EATEMS)
    {
        score += EATEMSCORE;
        map.TakeObject(coordinates);
        //map.SetPointCount(map.GetPointCount()-1);
        eatemState = true;
        eatemCount = EATEMCOUNT;
        return true;
    }
    return false;
}


void Pac::DrawPac(SDL_Renderer* renderer, const int (&offset)[DIMENSIONS])
{
    if(textures == NULL)
    {
        textures = new LTexture(renderer);
        textures->loadFromFile("Yellow.png");
    }
    
    int coordinates[DIMENSIONS];
    float dimensions[DIMENSIONS];
    
    body.GetCoordinates(coordinates);
    body.GetDimensions(dimensions);
    
    textures->render(coordinates[0]*dimensions[0] + offset[0], coordinates[1]*dimensions[1] + offset[1], static_cast<int>(dimensions[0]), static_cast<int>(dimensions[1]));
}

void Pac::DrawPacScore(SDL_Renderer* renderer, TTF_Font *gFont, const int (&offset)[DIMENSIONS])
{
    if(scoreTexture == NULL)
    {
        scoreTexture = new LTexture(renderer);
        //scoreTexture->loadFromFile("Yellow.png");
    }
    std::string stringscore = "SCORE:" + std::to_string(score);
    SDL_Color color = {0xFF, 0xFF, 0x00, 0xFF};
    scoreTexture->loadFromRenderedText(stringscore, color, gFont);
    
    scoreTexture->render(offset[0], offset[1]);
}

void Pac::DrawPacLives(SDL_Renderer* renderer, TTF_Font *gFont, const int (&offset)[DIMENSIONS])
{
    if(liveTexture == NULL)
    {
        liveTexture = new LTexture(renderer);
        //liveTexture->loadFromFile("Yellow.png");
    }
    std::string stringlives = "LIVES: " + std::to_string(lives);
    SDL_Color color = {0xFF, 0xFF, 0x00, 0xFF};
    liveTexture->loadFromRenderedText(stringlives, color, gFont);
    
    liveTexture->render(offset[0], offset[1]);
}

void Pac::DrawWin(SDL_Renderer* renderer, TTF_Font *gFont, const int (&offset)[DIMENSIONS])
{
    if(gameOverTexture == NULL)
    {
        gameOverTexture = new LTexture(renderer);
    }

    std::string stringwin;
    if(lives ==3)
    {
        stringwin = "PERFECT WIN";
    }
    else
    {
       stringwin = "YOU WIN!";
    }
    SDL_Color color = {0xFF, 0xFF, 0x00, 0xFF};
    gameOverTexture->loadFromRenderedText(stringwin, color, gFont);
    
    gameOverTexture->render(offset[0], offset[1]);
}

void Pac::DrawGameOver(SDL_Renderer* renderer, TTF_Font *gFont, const int (&offset)[DIMENSIONS])
{
    if(gameOverTexture == NULL)
    {
        gameOverTexture = new LTexture(renderer);
        //liveTexture->loadFromFile("Yellow.png");
    }
    std::string stringGameOver = "GAME OVER";
    SDL_Color color = {0xFF, 0xFF, 0x00, 0xFF};
    gameOverTexture->loadFromRenderedText(stringGameOver, color, gFont);
    
    gameOverTexture->render(offset[0], offset[1]);
}

void Pac::Update()
{
    if (eatemState)
    {
        eatemCount--;
        if(eatemCount == 0)
        {
            eatemState = false;
        }
    }
    
}

GameBody* Pac::GetBody()
{
    return &body;
}
void Pac::SetBody(GameBody *gamebody)
{
    body = *gamebody;
}

bool Pac::GetEatemState()
{
    return eatemState;
}

void Pac::InteractGhosts(Ghost (&ghosts)[GHOSTNUM], Map (&map))
{

    for (int i = 0; i<GHOSTNUM; i++)
    {
        GameBody ghostBody = *(ghosts[i].GetBody());
        if(body.DidBodiesCollide(ghostBody))
        {
            if(!eatemState)
            {
                KillPac(map, ghosts);
                return;
            }
            else
            {
                ghosts[i].KillGhost(map);
            }
        }
        ghosts[i].SetRunAway(eatemState);
        
    }

}

void Pac::KillPac(Map (&map), Ghost (&ghosts)[GHOSTNUM])
{
    lastDirection = NONE;
    int PacCoordinates[DIMENSIONS] = {0,0};
    map.GetStartCoordinates(PacCoordinates);
    body.SetCoordinates(PacCoordinates);
    
    for (int i = 0; i<GHOSTNUM; i++)
    {
        GameBody* ghostBody = ghosts[i].GetBody();
        int ghostCoordinates[DIMENSIONS] = {0,0};
        map.GetGhostStartCoordinate(ghostCoordinates, i);
        ghostBody->SetCoordinates(ghostCoordinates);
        ghosts[i].SetGhostStopTime(GHOSTINITIALSTOPCOUNT);
    }
    lives--;
    
}

int Pac::GetScore()
{
    return score;
}

int Pac::GetLives()
{
    return lives;
}

void Pac::PacReset(Map &map)
{
    lastDirection = NONE;
    //body = new GameBody(bodyDimensions, bodyCoordinates);
    int PacCoordinates[DIMENSIONS] = {0,0};
    map.GetStartCoordinates(PacCoordinates);
    body.SetCoordinates(PacCoordinates);
    eatemState = false;
    eatemCount = 0;
    lives = PACLIVES;
    score = 0;
    
}