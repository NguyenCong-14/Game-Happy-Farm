
#include "Button.h"
#include "GlobalData.h"

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <string>

Button::Button()
{
    mPosition = new SDL_Rect;
    mPosition->x = 0;
    mPosition->y = 0;

    mCurrentSprite = BUTTON_MOUSE_OUT;
}

Button::~Button()
{
    delete mPosition;
    mPosition = nullptr;
}

void Button::free()
{
    mPosition->x = 1800;
    mPosition->y = 1800;
}
void Button::setPosition(int x, int y)
{
    mPosition->x = x;
    mPosition->y = y;
}

void Button::setWidthHeight(int w, int h)
{
    BUTTON_HEIGHT = h;
    BUTTON_WIDTH = w;
}

bool Button::isInside(SDL_Event* e)
{
        //Get mouse position
        int x, y;
        SDL_GetMouseState(&x, &y);

        //Check if mouse is in button
        bool inside = true;

        //Mouse is left of the button
        if (x < mPosition->x)
        {
            inside = false;
        }
        //Mouse is right of the button
        else if (x > mPosition->x + BUTTON_WIDTH)
        {
            inside = false;
        }
        //Mouse above the button
        else if (y < mPosition->y)
        {
            inside = false;
        }
        //Mouse below the button
        else if (y > mPosition->y + BUTTON_HEIGHT)
        {
            inside = false;
        }


    return inside;
}

bool Button::isInside(SDL_Event* e ,int x , int y)
{
    //Get mouse position
    int xa, ya;
    SDL_GetMouseState(&xa, &ya);

    //Check if mouse is in button
    bool inside = true;

    //Mouse is left of the button
    if (xa < x)
    {
        inside = false;
    }
    //Mouse is right of the button
    else if (xa > x + BUTTON_WIDTH)
    {
        inside = false;
    }
    //Mouse above the button
    else if (ya < y)
    {
        inside = false;
    }
    //Mouse below the button
    else if (ya > y + BUTTON_HEIGHT)
    {
        inside = false;
    }


    return inside;
}


void Button::render(LTexture icon, SDL_Renderer* &render)
{
    icon.render(mPosition->x ,mPosition->y, render);
}

