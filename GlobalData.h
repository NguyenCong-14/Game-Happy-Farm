#pragma once

#ifndef GLOBALDATA_H
#define GLOBALDATA_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "LTexture.h"



//Screen dimension constants
const int SCREEN_WIDTH = 1200;
const int SCREEN_HEIGHT = 800;

//The window we'll be rendering to
static SDL_Window* gWindow = NULL;

//The window renderer
static SDL_Renderer* gRenderer = NULL;

//Globally used font
static TTF_Font* gFont ;

//Globally text colour
static SDL_Color textColor = { 0, 0, 0 , 0xFF };




//Globally Button sprite
enum LButtonSprite
{
    BUTTON_MOUSE_OUT = 0,
    BUTTON_MOUSE_IN = 1,
    BUTTON_MOUSE_DOWN = 2,
    BUTTON_MOUSE_UP = 3,
    BUTTON_TOTAL = 4
};

enum LMouseMode
{
    MOUSE_MODE_NULL = 0,

    MOUSE_MODE_MOVE_PICK = 1,
    MOUSE_MODE_MOVE_COW = 2,
    MOUSE_MODE_MOVE_SHEEP = 3,
    MOUSE_MODE_MOVE_PIG = 4,
    MOUSE_MODE_MOVE_CHICK = 5,

    MOUSE_MODE_ADD_COW = 6,
    MOUSE_MODE_ADD_SHEEP = 7,
    MOUSE_MODE_ADD_PIG = 8,
    MOUSE_MODE_ADD_CHICK = 9,

    MOUSE_MODE_DATA_LIST = 10,
    MOUSE_MODE_DATA_COW = 11,
    MOUSE_MODE_DATA_SHEEP = 12,
    MOUSE_MODE_DATA_PIG = 13,
    MOUSE_MODE_DATA_CHICK = 14,

    MOUSE_MODE_FOOD_FOOD = 15,
    MOUSE_MODE_FOOD_0_1KG = 16,
    MOUSE_MODE_FOOD_0_5KG = 17,
    MOUSE_MODE_FOOD_1KG = 18,

    MOUSE_MODE_FOOD_ALL_0_1KG = 19,
    MOUSE_MODE_FOOD_ALL_0_5KG = 20,
    MOUSE_MODE_FOOD_ALL_1KG = 21

};




#endif // !GLOBALDATA_H