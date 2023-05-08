#pragma once

#ifndef BUTTON_H
#define BUTTON_H

#include "GlobalData.h"
#include "LTexture.h"

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <string>



class Button
{
public:
    //Initializes internal variables
    Button();
    ~Button();

    //Sets top left position
    void setPosition(int x, int y);

    //Sets Button Width , Height
    void setWidthHeight(int w, int h);

    //Handles mouse event
    bool isInside(SDL_Event* e);
    bool isInside(SDL_Event* e, int x, int y);

    void free();

    //Shows button sprite
    void render (LTexture icon,  SDL_Renderer*& render) ;

private:
    //Top left position
    SDL_Rect* mPosition;

    //Currently used global sprite
    LButtonSprite mCurrentSprite;

    int BUTTON_WIDTH ;
    int BUTTON_HEIGHT ;
};










#endif // !BUTTON_H

