//
//  LTexture.hpp
//  Pacman
//  Adapted from LazyFoo Productions Tutorial
//  Created by Quinn Ramsay on 2016-04-11.
//  Copyright © 2016 Quinn Ramsay. All rights reserved.
//

#ifndef LTexture_hpp
#define LTexture_hpp

#include <stdio.h>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>

//Texture wrapper class
class LTexture
{
public:
    //Initializes variables
    LTexture(SDL_Renderer* renderer);
    
    //Deallocates memory
    ~LTexture();
    
    void SetRenderer(SDL_Renderer* renderer);
    //Loads image at specified path
    bool loadFromFile( std::string path );
    
    //Creates image from font string
    bool loadFromRenderedText( std::string textureText, SDL_Color textColor,TTF_Font *gFont);
    
    //Deallocates texture
    void free();
    
    void render( int x, int y, int width, int height, SDL_Rect* clip = NULL);
    //Renders texture at given point
    void render( int x, int y, SDL_Rect* clip = NULL );
    
    //Gets image dimensions
    int getWidth();
    int getHeight();
    
private:
    //The actual hardware texture
    SDL_Texture* mTexture;
    //The window renderer
    SDL_Renderer* gRenderer;
    //Image dimensions
    int mWidth;
    int mHeight;
};
#endif /* LTexture_hpp */
