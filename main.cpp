

//Using SDL, SDL_image, standard IO, and strings
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <string>

#include "LTexture.h"
#include "GlobalData.h"
#include "Button.h"
#include "Animals.h"


// define Animal_Count
LTexture text_gCowCount;	LTexture img_gCowtable;		static string Cow_count = "0";
LTexture text_gPigCount;	LTexture img_gPigtable;		static string Pig_count = "0";
LTexture text_gChickCount;	LTexture img_gChicktable;	static string Chick_count = "0";
LTexture text_gSheepCount;	LTexture img_gSheeptable;	static string Sheep_count = "0";

LTexture img_checklist;		Button bt_checklist;
LTexture img_pick;			Button bt_pick;
LTexture img_exit;			Button bt_exit;


LTexture img_iconTime;
LTexture text_minute;
LTexture text_second;
static int minute = 0 ;
static int second = 0 ;
static Uint32 startime = 0;

// define Animal_Add
LTexture img_gAddCow;		Button bt_gAddCow;
LTexture img_gAddSheep;		Button bt_gAddSheep;
LTexture img_gAddChick;		Button bt_gAddChick;
LTexture img_gAddPig;		Button bt_gAddPig;

// define Food
LTexture img_gFood;			Button bt_gFood;
LTexture img_gFood0_1kg;	Button bt_gFood0_1kg;
LTexture img_gFood0_5kg;	Button bt_gFood0_5kg;
LTexture img_gFood1kg;		Button bt_gFood1kg;
LTexture img_gFood_all;		Button bt_gFood_all;

LTexture img_bt_01kg;
LTexture img_bt_05kg;
LTexture img_bt_1kg;

LTexture img_neadfood;
// define Data Table
LTexture img_DataTable_Cow;
LTexture img_DataTable_Sheep;
LTexture img_DataTable_Pig;
LTexture img_DataTable_Chick;

LTexture text_Cow_tuoi;
LTexture text_Cow_TuoiDoi;
LTexture text_Cow_TrongLuong;
LTexture text_Cow_DoNo;

LTexture text_Sheep_tuoi;
LTexture text_Sheep_TuoiDoi;
LTexture text_Sheep_TrongLuong;
LTexture text_Sheep_DoNo;

LTexture text_Pig_tuoi;
LTexture text_Pig_TuoiDoi;
LTexture text_Pig_TrongLuong;
LTexture text_Pig_DoNo;

LTexture text_Chick_tuoi;
LTexture text_Chick_TuoiDoi;
LTexture text_Chick_TrongLuong;
LTexture text_Chick_DoNo;

// define Image Animal
LTexture img_Cow[10];
LTexture img_Sheep[10];
LTexture img_Chick[10];
LTexture img_Pig[10];

Button bt_Cow[10];
Button bt_Sheep[10];
Button bt_Chick[10];
Button bt_Pig[10];

Mix_Music* sound_Cow = NULL ;
Mix_Music* sound_Pig = NULL ;
Mix_Music* sound_Sheep = NULL ;
Mix_Music* sound_Chick = NULL;

Animal** data_A = new Animal * [10];
static int i_A_Cow = 0;
static int i_A_Sheep = 0;
static int i_A_Pig = 0;
static int i_A_Chick = 0;

static int i_A = -1;
static SDL_Rect pos[10];

static int x_cow = 0, y_cow = 0;

static int i_A_Current = -1;




//Scene textures
LTexture img_gBackground; Button bt_gBackground;

//Mouse mode
static LMouseMode MouseMode = MOUSE_MODE_NULL;

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();


bool init()
{
	//Initialization flag
	bool success = true;


	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
	{
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			printf("Warning: Linear texture filtering not enabled!");
		}

		//Create window
		gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			//Create renderer for window
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
			if (gRenderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					success = false;
				}
				//Initialize SDL_ttf
				if (TTF_Init() == -1)
				{
					printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
					success = false;
				}
				if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
				{
					printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
					success = false;
				}
			}
		}
	}
	return success;
}

bool loadMedia()
{
	//Loading success flag
	bool success = true;

	//Load count table IMG
	if (!img_gCowtable.loadFromFile("Pictures/Number Table/Cow_table.png",gRenderer))
	{
		success = false;
	}
	if (!img_gSheeptable.loadFromFile("Pictures/Number Table/Sheep_table.png", gRenderer))
	{
		success = false;
	}
	if (!img_gPigtable.loadFromFile("Pictures/Number Table/Pig_table.png", gRenderer))
	{
		success = false;
	}
	if (!img_gChicktable.loadFromFile("Pictures/Number Table/Chick_table.png", gRenderer))
	{
		success = false;
	}

	//Load Add IMG
	if (!img_gAddCow.loadFromFile("Pictures/Number Table/add.png", gRenderer))
	{
		success = false;
	}
	if (!img_gAddSheep.loadFromFile("Pictures/Number Table/add.png", gRenderer))
	{
		success = false;
	}
	if (!img_gAddChick.loadFromFile("Pictures/Number Table/add.png", gRenderer))
	{
		success = false;
	}
	if (!img_gAddPig.loadFromFile("Pictures/Number Table/add.png", gRenderer))
	{
		success = false;
	}

	//Load Food' IMG
	if (!img_gFood.loadFromFile("Pictures/Food/Food.png", gRenderer))
	{
		success = false;
	}
	if (!img_gFood0_1kg.loadFromFile("Pictures/Food/01kg.png", gRenderer))
	{
		success = false;
	}
	if (!img_gFood0_5kg.loadFromFile("Pictures/Food/05kg.png", gRenderer))
	{
		success = false;
	}
	if (!img_gFood1kg.loadFromFile("Pictures/Food/1kg.png", gRenderer))
	{
		success = false;
	}
	if (!img_gFood_all.loadFromFile("Pictures/Food/Food all.png", gRenderer))
	{
		success = false;
	}

	if (!img_bt_01kg.loadFromFile("Pictures/Food/bt_01kg.png", gRenderer))
	{
		success = false;
	}
	if (!img_bt_05kg.loadFromFile("Pictures/Food/bt_05kg.png", gRenderer))
	{
		success = false;
	}
	if (!img_bt_1kg.loadFromFile("Pictures/Food/bt_1kg.png", gRenderer))
	{
		success = false;
	}

	if (!img_neadfood.loadFromFile("Pictures/needfood.png", gRenderer))
	{
		success = false;
	}


	// Load Data table img
	if (!img_DataTable_Cow.loadFromFile("Pictures/Data Table/Data_Cow.png", gRenderer))
	{
		success = false;
	}
	if (!img_DataTable_Sheep.loadFromFile("Pictures/Data Table/Data_Sheep.png", gRenderer))
	{
		success = false;
	}
	if (!img_DataTable_Pig.loadFromFile("Pictures/Data Table/Data_Pig.png", gRenderer))
	{
		success = false;
	}
	if (!img_DataTable_Chick.loadFromFile("Pictures/Data Table/Data_Chick.png", gRenderer))
	{
		success = false;
	}

	// Load Animal img
	for (int i = 0; i < 10; i++)
	{
		if (!img_Cow[i].loadFromFile("Pictures/Cow.png", gRenderer))
			success = false;
		if (!img_Chick[i].loadFromFile("Pictures/Chick.png", gRenderer))
			success = false;
		if (!img_Sheep[i].loadFromFile("Pictures/Sheep.png", gRenderer))
			success = false;
		if (!img_Pig[i].loadFromFile("Pictures/Pig.png", gRenderer))
			success = false;
	}


	//Load background texture
	if (!img_gBackground.loadFromFile("Pictures/Background.png",gRenderer))
	{
		success = false;
	}
	if (!img_iconTime.loadFromFile("Pictures/iconTime.png",gRenderer))
	{
		success = false;
	}
	if (!img_checklist.loadFromFile("Pictures/checklist.png", gRenderer))
	{
		success = false;
	}
	if (!img_pick.loadFromFile("Pictures/pick.png", gRenderer))
	{
		success = false;
	}
	if (!img_exit.loadFromFile("Pictures/exit.png", gRenderer))
	{
		success = false;
	}

	//Open the font
	gFont = TTF_OpenFont("Font/ARIALNB.ttf", 30);

	sound_Chick = Mix_LoadMUS("Sound/Chick.mp3");
	sound_Cow = Mix_LoadMUS("Sound/Cow.mp3");
	sound_Sheep = Mix_LoadMUS("Sound/Sheep.mp3");
	sound_Pig = Mix_LoadMUS("Sound/Pig.mp3");

	if (sound_Chick == NULL || sound_Cow == NULL || sound_Pig == NULL || sound_Sheep == NULL)
		success = false;
	// Button define
	for (int i = 0; i < 10; i++)
	{
		bt_Cow[i].setWidthHeight(img_Cow[i].getWidth(), img_Cow[i].getHeight());
		bt_Sheep[i].setWidthHeight(img_Sheep[i].getWidth(), img_Sheep[i].getHeight());
		bt_Chick[i].setWidthHeight(img_Chick[i].getWidth(), img_Chick[i].getHeight());
		bt_Pig[i].setWidthHeight(img_Pig[i].getWidth(), img_Pig[i].getHeight());

	}

	bt_gBackground.setPosition(0, 284);
	bt_gBackground.setWidthHeight(1200, 390);

	bt_checklist.setWidthHeight(img_checklist.getWidth(), img_checklist.getHeight());
	bt_checklist.setPosition(490, 710);

	bt_pick.setWidthHeight(img_pick.getWidth(), img_pick.getHeight());
	bt_pick.setPosition(420, 710);

	bt_gAddCow.setWidthHeight(img_gAddCow.getWidth(), img_gAddCow.getHeight());
	bt_gAddCow.setPosition(585, 695);

	bt_gAddPig.setWidthHeight(img_gAddPig.getWidth(), img_gAddPig.getHeight());
	bt_gAddPig.setPosition(730, 695);

	bt_gAddSheep.setWidthHeight(img_gAddSheep.getWidth(), img_gAddSheep.getHeight());
	bt_gAddSheep.setPosition(880, 695);

	bt_gAddChick.setWidthHeight(img_gAddChick.getWidth(), img_gAddChick.getHeight());
	bt_gAddChick.setPosition(1030, 695);

	bt_gFood.setWidthHeight(img_gFood.getWidth(), img_gFood.getHeight());
	bt_gFood.setPosition(15, 670);

	bt_gFood0_1kg.setWidthHeight(img_gFood0_1kg.getWidth(), img_gFood0_1kg.getHeight());
	bt_gFood0_1kg.setPosition(320, 695);

	bt_gFood0_5kg.setWidthHeight(img_gFood0_5kg.getWidth(), img_gFood0_5kg.getHeight());
	bt_gFood0_5kg.setPosition(230, 695);

	bt_gFood1kg.setWidthHeight(img_gFood1kg.getWidth(), img_gFood1kg.getHeight());
	bt_gFood1kg.setPosition(140, 710);

	bt_gFood_all.setWidthHeight(img_gFood.getWidth(), img_gFood.getHeight());
	bt_gFood_all.setPosition(20, 550);

	
	img_pick.render(420, 710, gRenderer);

	bt_exit.setPosition(1120, 5);
	bt_exit.setWidthHeight(img_exit.getWidth(),img_exit.getHeight());

	return success;
}


void close()
{
	//Free loaded images

	//Free global font
	TTF_CloseFont(gFont);
	gFont = NULL;

	//Free music
	Mix_FreeMusic(sound_Chick);	sound_Chick = NULL;
	Mix_FreeMusic(sound_Cow);	sound_Cow = NULL;
	Mix_FreeMusic(sound_Sheep);	sound_Sheep = NULL;
	Mix_FreeMusic(sound_Pig);	sound_Pig = NULL;


	//Destroy window	
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

int main(int argc, char* args[])
{
	static string m;
	static string s;
	//Start up SDL and create window
	if (!init())
	{
		printf("Failed to initialize!\n");
	}
	else
	{
		//Load media
		if (!loadMedia())
		{
			printf("Failed to load media!\n");
		}
		else
		{
			//Main loop flag
			bool quit = false;

			//Event handler
			SDL_Event e;
			startime = SDL_GetTicks();
			//While application is running
			while (!quit)
			{

				SDL_RenderClear(gRenderer);
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

				//Render background texture to screen
				img_gBackground.render(0, 0, gRenderer);

				img_checklist.render(490, 710, gRenderer);
				img_pick.render(420, 710, gRenderer);
				img_exit.render(1120, 5, gRenderer);

				//Render Table to the screen
				img_gCowtable.render(585, 700, gRenderer);
				img_gPigtable.render(735, 700, gRenderer);
				img_gSheeptable.render(885, 700, gRenderer);
				img_gChicktable.render(1035, 700, gRenderer);

				//Render and Set Add Animal Button
				img_gAddCow.render(585, 695, gRenderer);
				img_gAddPig.render(730, 695, gRenderer);
				img_gAddSheep.render(880, 695, gRenderer);
				img_gAddChick.render(1030, 695, gRenderer);

				//Render and Set Add Food Button
				img_gFood.render(15, 670, gRenderer);




				bool quit_event = false;
				static bool flag_move = false;
				while (SDL_PollEvent(&e) != 0 && !quit_event)
				{
					if (bt_gFood.isInside(&e) && e.button.clicks == 1)
					{
						MouseMode = MOUSE_MODE_FOOD_FOOD;
					}
					if (MouseMode == MOUSE_MODE_FOOD_FOOD)
					{

						if (bt_gFood0_1kg.isInside(&e) && e.type == SDL_MOUSEBUTTONDOWN)
						{
							MouseMode = MOUSE_MODE_FOOD_0_1KG;
							quit_event = true;
						}
						if (bt_gFood0_5kg.isInside(&e) && e.type == SDL_MOUSEBUTTONDOWN)
						{
							MouseMode = MOUSE_MODE_FOOD_0_5KG;
							quit_event = true;
						}
						if (bt_gFood1kg.isInside(&e) && e.type == SDL_MOUSEBUTTONDOWN)
						{
							MouseMode = MOUSE_MODE_FOOD_1KG;
							quit_event = true;
						}
					}
					if (MouseMode == MOUSE_MODE_FOOD_0_1KG )
					{
						if (bt_gFood_all.isInside(&e) && e.button.clicks == 1)
						{
							MouseMode = MOUSE_MODE_FOOD_ALL_0_1KG;
							quit_event = true;
						}
					}
					if (MouseMode == MOUSE_MODE_FOOD_0_5KG)
					{
						if (bt_gFood_all.isInside(&e) && e.button.clicks == 1)
						{
							MouseMode = MOUSE_MODE_FOOD_ALL_0_5KG;
							quit_event = true;
						}
					}
					if (MouseMode == MOUSE_MODE_FOOD_1KG)
					{
						if (bt_gFood_all.isInside(&e) && e.button.clicks == 1)
						{
							MouseMode = MOUSE_MODE_FOOD_ALL_1KG;
							quit_event = true;
						}
					}

					if (bt_gAddCow.isInside(&e) && e.type == SDL_MOUSEBUTTONDOWN)
					{
						MouseMode = MOUSE_MODE_ADD_COW;
						i_A++; i_A_Cow++;
						Cow_count.empty();
						Cow_count = to_string(i_A_Cow);
						data_A[i_A] = new Cow;
						quit_event = true;

					}
					if (bt_gAddChick.isInside(&e) && e.type == SDL_MOUSEBUTTONDOWN)
					{
						MouseMode = MOUSE_MODE_ADD_CHICK;
						i_A++; i_A_Chick++;
						Chick_count = to_string(i_A_Chick);
						data_A[i_A] = new Chicken;
						quit_event = true;
					}
					if (bt_gAddPig.isInside(&e) && e.type == SDL_MOUSEBUTTONDOWN)
					{
						MouseMode = MOUSE_MODE_ADD_PIG;
						i_A++; i_A_Pig++;
						Pig_count = to_string(i_A_Pig);
						data_A[i_A] = new Pig;
						quit_event = true;
					}
					if (bt_gAddSheep.isInside(&e) && e.type == SDL_MOUSEBUTTONDOWN)
					{
						MouseMode = MOUSE_MODE_ADD_SHEEP;
						i_A++; i_A_Sheep++;
						Sheep_count = to_string(i_A_Sheep);
						data_A[i_A] = new Sheep;
						quit_event = true;
					}

					if  (bt_checklist.isInside(&e) && e.type == SDL_MOUSEBUTTONDOWN)
					{
							MouseMode = MOUSE_MODE_DATA_LIST;
					}

					if (bt_pick.isInside(&e) && e.type == SDL_MOUSEBUTTONDOWN)
					{
						MouseMode = MOUSE_MODE_MOVE_PICK;
					}

					if (i_A > -1 && (MouseMode == MOUSE_MODE_FOOD_0_1KG || MouseMode == MOUSE_MODE_FOOD_0_5KG || MouseMode == MOUSE_MODE_FOOD_1KG))
					{
						for (int i = 0; i <= i_A; i++)
						{
							if (data_A[i]->Code() == 1 && bt_Cow[i].isInside(&e) && e.type == SDL_MOUSEBUTTONDOWN)
							{
								data_A[i]->An(MouseMode);
							}
							if (data_A[i]->Code() == 2 && bt_Sheep[i].isInside(&e) && e.type == SDL_MOUSEBUTTONDOWN)
							{
								data_A[i]->An(MouseMode);
							}
							if (data_A[i]->Code() == 3 && bt_Pig[i].isInside(&e) && e.type == SDL_MOUSEBUTTONDOWN)
							{
								data_A[i]->An(MouseMode);
							}
							if (data_A[i]->Code() == 4 && bt_Chick[i].isInside(&e) && e.type == SDL_MOUSEBUTTONDOWN)
							{
								data_A[i]->An(MouseMode);
							}
						}
					}

					if (i_A > -1 && MouseMode == MOUSE_MODE_DATA_LIST)
					{
						for (int i = 0; i <= i_A; i++)
						{
							if (data_A[i]->Code() == 1 && bt_Cow[i].isInside(&e) && e.button.clicks == 1  )
							{
								MouseMode = MOUSE_MODE_DATA_COW;
								i_A_Current = i;
								quit_event = true;
							}
							if (data_A[i]->Code() == 2 && bt_Sheep[i].isInside(&e) && e.button.clicks == 1)
							{
								MouseMode = MOUSE_MODE_DATA_SHEEP;
								i_A_Current = i;
								quit_event = true;
							}
							if (data_A[i]->Code() == 3 && bt_Pig[i].isInside(&e) && e.button.clicks == 1)
							{
								MouseMode = MOUSE_MODE_DATA_PIG;
								i_A_Current = i;
								quit_event = true;
							}
							if (data_A[i]->Code() == 4 && bt_Chick[i].isInside(&e) && e.button.clicks == 1)
							{
								MouseMode = MOUSE_MODE_DATA_CHICK;
								i_A_Current = i;
								quit_event = true;
							}
						}

					}

					if (i_A > -1 && MouseMode == MOUSE_MODE_MOVE_PICK)
					{
						flag_move = true;
						for (int i = 0; i <= i_A; i++)
						{
							if (data_A[i]->Code() == 1 && bt_Cow[i].isInside(&e) && e.button.clicks == 1)
							{
								MouseMode = MOUSE_MODE_MOVE_COW;
								i_A_Current = i;
								quit_event = true;
							}
							if (data_A[i]->Code() == 2 && bt_Sheep[i].isInside(&e) && e.button.clicks == 1)
							{
								MouseMode = MOUSE_MODE_MOVE_SHEEP;
								i_A_Current = i;
								quit_event = true;
							}
							if (data_A[i]->Code() == 3 && bt_Pig[i].isInside(&e) && e.button.clicks == 1)
							{
								MouseMode = MOUSE_MODE_MOVE_PIG;
								i_A_Current = i;
								quit_event = true;
							}
							if (data_A[i]->Code() == 4 && bt_Chick[i].isInside(&e) && e.button.clicks == 1)
							{
								MouseMode = MOUSE_MODE_MOVE_CHICK;
								i_A_Current = i;
								quit_event = true;
							}
						}
					}

					if (i_A > -1 )
						for (int i = 0; i <= i_A; i++)
						{
							if (data_A[i]->Code() == 1 && bt_Cow[i].isInside(&e) && e.button.clicks == 1)
							{
								Mix_PlayMusic(sound_Cow, 1);
							}
							if (data_A[i]->Code() == 2 && bt_Sheep[i].isInside(&e) && e.button.clicks == 1)
							{
								Mix_PlayMusic(sound_Sheep, 1);
							}
							if (data_A[i]->Code() == 3 && bt_Pig[i].isInside(&e) && e.button.clicks == 1)
							{
								Mix_PlayMusic(sound_Pig, 1);
							}
							if (data_A[i]->Code() == 4 && bt_Chick[i].isInside(&e) && e.button.clicks == 1)
							{
								Mix_PlayMusic(sound_Chick, 1);
							}
						}
					
					if (bt_gBackground.isInside(&e) &&  e.button.clicks > 1)
					{
						MouseMode = MOUSE_MODE_NULL;
						quit_event = true;
					}

					if (bt_exit.isInside(&e) && e.type == SDL_MOUSEBUTTONDOWN)
					{
						quit = true;
					}

				}



				// handle Mouse event
				if (MouseMode == MOUSE_MODE_FOOD_FOOD)
				{
					img_gFood0_1kg.render(320, 695, gRenderer);
					img_gFood0_5kg.render(230, 695, gRenderer);
					img_gFood1kg.render(140, 695, gRenderer);

				}
				if (i_A > -1 && (MouseMode == MOUSE_MODE_FOOD_0_1KG || MouseMode == MOUSE_MODE_FOOD_0_5KG || MouseMode == MOUSE_MODE_FOOD_1KG))
				{
					img_gFood_all.render(20,550, gRenderer);
				}
				if (i_A > -1 && (MouseMode == MOUSE_MODE_FOOD_ALL_0_1KG || MouseMode == MOUSE_MODE_FOOD_ALL_0_5KG || MouseMode == MOUSE_MODE_FOOD_ALL_1KG))
				{
					for (int i = 0; i <= i_A; i++)
					{
						data_A[i]->An(MouseMode);
					}
				}
				if (MouseMode == MOUSE_MODE_ADD_COW )
				{
					int x, y;
					SDL_GetMouseState(&x, &y);

					pos[i_A].x = x-100;
					pos[i_A].y = y-60;	

					img_Cow[i_A].render(pos[i_A].x, pos[i_A].y, gRenderer);
					data_A[i_A]->SetPos(pos[i_A].x, pos[i_A].y);
					bt_Cow[i_A].setPosition(pos[i_A].x, pos[i_A].y);
				}

				if (MouseMode == MOUSE_MODE_ADD_SHEEP)
				{
					int x, y;
					SDL_GetMouseState(&x, &y);

					pos[i_A].x = x-80;
					pos[i_A].y = y-60;
					
					img_Sheep[i_A].render(pos[i_A].x, pos[i_A].y, gRenderer);
					data_A[i_A]->SetPos(pos[i_A].x, pos[i_A].y);
					bt_Sheep[i_A].setPosition(pos[i_A].x,pos[i_A].y);
				}

				if (MouseMode == MOUSE_MODE_ADD_CHICK)
				{
					int x, y;
					SDL_GetMouseState(&x, &y);

					pos[i_A].x = x-40;
					pos[i_A].y = y-50;

					img_Chick[i_A].render(pos[i_A].x, pos[i_A].y, gRenderer);
					data_A[i_A]->SetPos(pos[i_A].x, pos[i_A].y);
					bt_Chick[i_A].setPosition(pos[i_A].x, pos[i_A].y);

				}

				if (MouseMode == MOUSE_MODE_ADD_PIG)
				{
					int x, y;
					SDL_GetMouseState(&x, &y);
				
					pos[i_A].x = x-80;
					pos[i_A].y = y-60;

					img_Pig[i_A].render(pos[i_A].x, pos[i_A].y, gRenderer);
					data_A[i_A]->SetPos(pos[i_A].x, pos[i_A].y);
					bt_Pig[i_A].setPosition(pos[i_A].x, pos[i_A].y);
				}
				
				for (int i = 0; i <= i_A; i++)
				{
					data_A[i]->ThayDoiDoNo(minute);
					if (data_A[i]->Code() == 1)
					{
						img_Cow[i].render(pos[i].x, pos[i].y, gRenderer);
						if (data_A[i]->isDie())
						{
							if (!img_Cow[i].loadFromFile("Pictures/DeadCow.png", gRenderer))
								quit = true;
							bt_Cow[i].free();
						}
						if (data_A[i]->isCry() && !data_A[i]->isDie())
							img_neadfood.render(pos[i].x - 50, pos[i].y - 30, gRenderer);
					}
					if (data_A[i]->Code() == 2)
					{
						img_Sheep[i].render(pos[i].x, pos[i].y, gRenderer);
						if (data_A[i]->isDie())
						{
							if (!img_Sheep[i].loadFromFile("Pictures/DeadSheep.png", gRenderer))
								quit = true;
							bt_Sheep[i].free();
						}
						if (data_A[i]->isCry() && !data_A[i]->isDie())
							img_neadfood.render(pos[i].x - 40, pos[i].y - 30, gRenderer);
					}
					if (data_A[i]->Code() == 3)
					{
						img_Pig[i].render(pos[i].x, pos[i].y, gRenderer);
						if (data_A[i]->isDie())
						{
							if (!img_Pig[i].loadFromFile("Pictures/DeadPig.png", gRenderer))
								quit = true;
							bt_Pig[i].free();
						}
						if (data_A[i]->isCry() && !data_A[i]->isDie())
							img_neadfood.render(pos[i].x - 40, pos[i].y - 30, gRenderer);
					}
					if (data_A[i]->Code() == 4)
					{
						img_Chick[i].render(pos[i].x, pos[i].y, gRenderer);
						if (data_A[i]->isDie())
						{
							if (!img_Chick[i].loadFromFile("Pictures/DeadChick.png", gRenderer))
								quit = true;
							bt_Chick[i].free();
						}
						if (data_A[i]->isCry() && !data_A[i]->isDie())
							img_neadfood.render(pos[i].x - 45 , pos[i].y - 30 , gRenderer);
					}

				}

				if (i_A > -1)
				{
					if (MouseMode == MOUSE_MODE_DATA_COW)
					{
						img_DataTable_Cow.render(400, 200, gRenderer);
						if (text_Cow_tuoi.loadFromRenderedText("Tuoi  :    " + data_A[i_A_Current]->get_tuoi(), textColor, gRenderer, gFont))
						{
							text_Cow_tuoi.render(490, 340, gRenderer);
						}
						if (text_Cow_TuoiDoi.loadFromRenderedText("Tuoi Doi  :  " + data_A[i_A_Current]->get_TuoiDoi(), textColor, gRenderer, gFont))
						{
							text_Cow_TuoiDoi.render(480, 380, gRenderer);
						}
						if (text_Cow_DoNo.loadFromRenderedText("Do No  :  " + data_A[i_A_Current]->get_DoNo() + " % ", textColor, gRenderer, gFont))
						{
							text_Cow_DoNo.render(490, 420, gRenderer);
						}
						if (text_Cow_DoNo.loadFromRenderedText("Trong Luong  :  " + data_A[i_A_Current]->get_TrongLuong() + " kg ", textColor, gRenderer, gFont))
						{
							text_Cow_DoNo.render(430, 460, gRenderer);
						}
						
					}
					if (MouseMode == MOUSE_MODE_DATA_SHEEP)
					{
						img_DataTable_Sheep.render(400, 200, gRenderer);
						if (text_Sheep_tuoi.loadFromRenderedText("Tuoi  :    " + data_A[i_A_Current]->get_tuoi(), textColor, gRenderer, gFont))
						{
							text_Sheep_tuoi.render(490, 340, gRenderer);
						}
						if (text_Sheep_TuoiDoi.loadFromRenderedText("Tuoi Doi  :  " + data_A[i_A_Current]->get_TuoiDoi(), textColor, gRenderer, gFont))
						{
							text_Sheep_TuoiDoi.render(480, 380, gRenderer);
						}
						if (text_Sheep_DoNo.loadFromRenderedText("Do No  :  " + data_A[i_A_Current]->get_DoNo() + " % ", textColor, gRenderer, gFont))
						{
							text_Sheep_DoNo.render(490, 420, gRenderer);
						}
						if (text_Sheep_DoNo.loadFromRenderedText("Trong Luong  :  " + data_A[i_A_Current]->get_TrongLuong() + " kg ", textColor, gRenderer, gFont))
						{
							text_Sheep_DoNo.render(430, 460, gRenderer);
						}
						
					}
					if (MouseMode == MOUSE_MODE_DATA_PIG)
					{
						img_DataTable_Pig.render(400, 200, gRenderer);
						if (text_Pig_tuoi.loadFromRenderedText("Tuoi  :    " + data_A[i_A_Current]->get_tuoi(), textColor, gRenderer, gFont))
						{
							text_Pig_tuoi.render(490, 340, gRenderer);
						}
						if (text_Pig_TuoiDoi.loadFromRenderedText("Tuoi Doi  :  " + data_A[i_A_Current]->get_TuoiDoi(), textColor, gRenderer, gFont))
						{
							text_Pig_TuoiDoi.render(480, 380, gRenderer);
						}
						if (text_Pig_DoNo.loadFromRenderedText("Do No  :  " + data_A[i_A_Current]->get_DoNo() + " % ", textColor, gRenderer, gFont))
						{
							text_Pig_DoNo.render(490, 420, gRenderer);
						}
						if (text_Pig_DoNo.loadFromRenderedText("Trong Luong  :  " + data_A[i_A_Current]->get_TrongLuong() + " kg ", textColor, gRenderer, gFont))
						{
							text_Pig_DoNo.render(430, 460, gRenderer);
						}
					}
					if (MouseMode == MOUSE_MODE_DATA_CHICK)
					{
						img_DataTable_Chick.render(400, 200, gRenderer);
						if (text_Chick_tuoi.loadFromRenderedText("Tuoi  :    " + data_A[i_A_Current]->get_tuoi(), textColor, gRenderer, gFont))
						{
							text_Chick_tuoi.render(490, 340, gRenderer);
						}
						if (text_Chick_TuoiDoi.loadFromRenderedText("Tuoi Doi  :  " + data_A[i_A_Current]->get_TuoiDoi(), textColor, gRenderer, gFont))
						{
							text_Chick_TuoiDoi.render(480, 380, gRenderer);
						}
						if (text_Chick_DoNo.loadFromRenderedText("Do No  :  " + data_A[i_A_Current]->get_DoNo() + " % ", textColor, gRenderer, gFont))
						{
							text_Chick_DoNo.render(490, 420, gRenderer);
						}
						if (text_Chick_DoNo.loadFromRenderedText("Trong Luong  :  " + data_A[i_A_Current]->get_TrongLuong() + " kg ", textColor, gRenderer, gFont))
						{
							text_Chick_DoNo.render(430, 460, gRenderer);
						}

					}


					if ( MouseMode == MOUSE_MODE_MOVE_COW)
					{
						int x, y;
						SDL_GetMouseState(&x, &y);

						pos[i_A_Current].x = x - 100;
						pos[i_A_Current].y = y - 60;
						img_Cow[i_A_Current].render(pos[i_A_Current].x, pos[i_A_Current].y , gRenderer);
					}
					if (MouseMode == MOUSE_MODE_MOVE_SHEEP)
					{
						int x, y;
						SDL_GetMouseState(&x, &y);

						pos[i_A_Current].x = x - 80;
						pos[i_A_Current].y = y - 60;
						img_Sheep[i_A_Current].render(pos[i_A_Current].x, pos[i_A_Current].y, gRenderer);
					}
					if (MouseMode == MOUSE_MODE_MOVE_PIG)
					{
						int x, y;
						SDL_GetMouseState(&x, &y);

						pos[i_A_Current].x = x - 40;
						pos[i_A_Current].y = y - 60;
						img_Pig[i_A_Current].render(pos[i_A_Current].x, pos[i_A_Current].y, gRenderer);
					}
					if (MouseMode == MOUSE_MODE_MOVE_CHICK)
					{
						int x, y;
						SDL_GetMouseState(&x, &y);

						pos[i_A_Current].x = x - 40;
						pos[i_A_Current].y = y - 50;
						img_Chick[i_A_Current].render(pos[i_A_Current].x, pos[i_A_Current].y, gRenderer);
					}

					if (MouseMode == MOUSE_MODE_NULL && flag_move == true && i_A_Current != -1 )
					{
						data_A[i_A_Current]->ThayDoiViTri(pos[i_A_Current].x, pos[i_A_Current].y);
						if (data_A[i_A_Current]->Code() == 1)
							bt_Cow[i_A_Current].setPosition(pos[i_A_Current].x, pos[i_A_Current].y);
						if (data_A[i_A_Current]->Code() == 2)
							bt_Sheep[i_A_Current].setPosition(pos[i_A_Current].x, pos[i_A_Current].y);
						if (data_A[i_A_Current]->Code() == 3)
							bt_Pig[i_A_Current].setPosition(pos[i_A_Current].x, pos[i_A_Current].y);
						if (data_A[i_A_Current]->Code() == 4)
							bt_Chick[i_A_Current].setPosition(pos[i_A_Current].x, pos[i_A_Current].y);

						i_A_Current = -1;
						flag_move = false;

					}


				}


				// Button render
				if (MouseMode == MOUSE_MODE_FOOD_0_1KG)
				{
					int x, y;
					SDL_GetMouseState(&x, &y);
					img_bt_01kg.render(x-60, y-60, gRenderer);
				}
				if (MouseMode == MOUSE_MODE_FOOD_0_5KG)
				{
					int x, y;
					SDL_GetMouseState(&x, &y);
					img_bt_05kg.render(x-60, y-60, gRenderer);
				}
				if (MouseMode == MOUSE_MODE_FOOD_1KG)
				{
					int x, y;
					SDL_GetMouseState(&x, &y);
					img_bt_1kg.render(x-60, y-60, gRenderer);
				}

				if (MouseMode == MOUSE_MODE_DATA_LIST)
				{
					int x, y;
					SDL_GetMouseState(&x, &y);
					img_checklist.render(x-25, y-40, gRenderer);
				}
				if (MouseMode == MOUSE_MODE_MOVE_PICK)
				{
					int x, y;
					SDL_GetMouseState(&x, &y);
					img_pick.render(x-25, y-40, gRenderer);
				}

				if (text_gCowCount.loadFromRenderedText(Cow_count, textColor, gRenderer, gFont))
				{
					text_gCowCount.render(685, 725, gRenderer);
				}
				if (text_gSheepCount.loadFromRenderedText(Sheep_count, textColor, gRenderer, gFont))
				{
					text_gPigCount.render(835, 725, gRenderer);
				}
				if (text_gPigCount.loadFromRenderedText(Pig_count, textColor, gRenderer, gFont))
				{
					text_gSheepCount.render(985, 725, gRenderer);
				}
				if (text_gChickCount.loadFromRenderedText(Chick_count, textColor, gRenderer, gFont))
				{
					text_gChickCount.render(1135, 725, gRenderer);
				}
				
				int time_current = SDL_GetTicks();
				if ((time_current - startime)/1000 >= 1)
				{
					second++;
					startime = SDL_GetTicks();
				}
				if (second == 60)
				{
					second = 0;
					minute++;
				}
				m = to_string(minute);
				s = to_string(second);
				text_minute.loadFromRenderedText(m + " : ", textColor, gRenderer, gFont);
				text_second.loadFromRenderedText(s, textColor, gRenderer, gFont);

				img_iconTime.render(10, 10, gRenderer);
				text_minute.render(60, 15, gRenderer);
				text_second.render(100, 15, gRenderer);

				SDL_RenderPresent(gRenderer);

			}

		}

		//Free resources and close SDL
		close();
		return 0;
	}
}