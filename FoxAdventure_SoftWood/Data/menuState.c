/*****************************************************************************/
/*  Автор         		: Дракончик				                             */
/*  Приставка     		: Sony PlayStation 2					             */
/*  ОС			  		: OSDSYS											 */
/*  Язык	      		: GNU C                                              */
/*                                                                           */
/*  Содержимое файла	: Стадия главного меню		                         */
/*  Атрибут файла		: SOURCE                                             */
/*  Имя файла     		: menuState.c	                                     */
/*                                                                           */
/*****************************************************************************/


#include "include/gameState.h"
#include "include/menuState.h"
#include "include/overState.h"
#include "include/introState.h"
#include "include/musicManager.h"
#include "include/textToGraphics.h"
#include "include/pad.h"


/****** User External Files ********/
#include "extern/menuState.ext"

/****** User Table Files ***********/


/****** User Define Files ***********/
#include "define/menuState.def"

GSTEXTURE TitleImage; 

GSTEXTURE ButtonStartImage; 
GSTEXTURE ButtonCloseImage; 
GSTEXTURE SelButtonStartImage; 
GSTEXTURE SelButtonCloseImage; 


BGM MenuMusicy;

int selectedOption; // 0 - New Game 1- ShutDown game

int idleTimer;

void MenuStart(GSGLOBAL* gsGlobal)
{
	idleTimer = 0; // Once the Idle timer reaches 6000 then restart the screen to prevent screen burn on CRT
	initMusicFormat();
	
	char temp[4096];
	strcpy(temp, relativePath);
	strcat(temp, PickMusic(1));
	MenuMusicy.fileName = temp;
	
	LoadMusic(&MenuMusicy);

	char tempy[4096];
	strcpy(tempy, relativePath);
	strcat(tempy, TITLEIMAGEPATH);
	gsKit_texture_png(gsGlobal, &TitleImage,tempy);
	
	strcpy(tempy, relativePath);
	strcat(tempy, BUTTONSTARTPATH);
	gsKit_texture_png(gsGlobal, &ButtonStartImage,tempy);
	
	strcpy(tempy, relativePath);
	strcat(tempy, BUTTONCLOSEPATH);
	gsKit_texture_png(gsGlobal, &ButtonCloseImage,tempy);

	strcpy(tempy, relativePath);
	strcat(tempy, SELBUTTONSTARTPATH);
	gsKit_texture_png(gsGlobal, &SelButtonStartImage,tempy);
	
	strcpy(tempy, relativePath);
	strcat(tempy, SELBUTTONCLOSEPATH);
	gsKit_texture_png(gsGlobal, &SelButtonCloseImage,tempy);
	
	selectedOption = 0;
}

void MenuUpdate(GSGLOBAL* gsGlobal)
{
	// This part here plays the music
	PlayMusic(&MenuMusicy);
	idleTimer++; // Once the Idle timer reaches 6000 then restart the screen to prevent screen burn on CRT
	printf("%d IdleTimer\n", idleTimer);
	// This is to prevent the screen burn. We force the game to reset
	if(idleTimer > 12000)
	{
		idleTimer = 0;
		StateMachineChange(&GameMachineState, &IntroState, gsGlobal);
	}
	
	// Change Menu
	if(PlaystationGamePad.UP_KEY_TAP && selectedOption != 0)
    {
    	selectedOption--;
    }
    else if(PlaystationGamePad.DOWN_KEY_TAP && selectedOption != 3)
    {
    	selectedOption++;
    }

	if(PlaystationGamePad.START_KEY_TAP)
    	{	
		switch(selectedOption)
		{
			// Start New Game
			case 0:
				StateMachineChange(&GameMachineState, &GameState, gsGlobal);
			break;

			case 1:
				// Shut Down
				GameRunning = 0;
				UnloadMusic(&MenuMusicy);
			break;
			
			default:
			
		}
	}

}

void MenuDraw(GSGLOBAL* gsGlobal, u64 colour)
{

	/*int i = (4096 - gsGlobal->CurrentPointer/1024);
	printf("VRAM: %d\n", i);*/
	
	gsKit_prim_sprite_texture(gsGlobal, &TitleImage,0,  // X1
						0,  // Y2
						0.0f,  // U1
						0.0f,  // V1
						TitleImage.Width * 2, // X2
						TitleImage.Height * 2, // Y2
						TitleImage.Width * 2, // U2
						TitleImage.Height * 2, // V2
						2,
						colour);				

	gsKit_prim_sprite_texture(gsGlobal, &ButtonStartImage,320-ButtonStartImage.Width/2,  // X1
						280,  // Y1
						0.0f,  // U1
						0.0f,  // V1
						320-ButtonStartImage.Width/2 + ButtonStartImage.Width, // X2
						280 + ButtonStartImage.Height, // Y2
						ButtonStartImage.Width, // U2
						ButtonStartImage.Height, // V2
						2,
						colour);	

	gsKit_prim_sprite_texture(gsGlobal, &ButtonCloseImage,320-ButtonCloseImage.Width/2 ,  // X1
						339,  // Y1
						0.0f,  // U1
						0.0f,  // V1
						320-ButtonCloseImage.Width/2  + ButtonCloseImage.Width, // X2
						339 + ButtonCloseImage.Height, // Y2
						ButtonCloseImage.Width, // U2
						ButtonCloseImage.Height, // V2
						2,
						colour);	

	switch(selectedOption)
	{
		// Start New Game
		case 0:
			gsKit_prim_sprite_texture(gsGlobal, &ButtonStartImage,320-SelButtonStartImage.Width/2,  // X1
						280,  // Y1
						0.0f,  // U1
						0.0f,  // V1
						320-SelButtonStartImage.Width/2 + SelButtonStartImage.Width, // X2
						280 + SelButtonStartImage.Height, // Y2
						SelButtonStartImage.Width, // U2
						SelButtonStartImage.Height, // V2
						2,
						colour);
		break;		
		case 1:
			gsKit_prim_sprite_texture(gsGlobal, &ButtonCloseImage,320-SelButtonCloseImage.Width/2 ,  // X1
						339,  // Y1
						0.0f,  // U1
						0.0f,  // V1
						320-SelButtonCloseImage.Width/2  + SelButtonCloseImage.Width, // X2
						339 + SelButtonCloseImage.Height, // Y2
						SelButtonCloseImage.Width, // U2
						SelButtonCloseImage.Height, // V2
						2,
						colour);
		break;
		default:
	}
	
	//gsKit_clear(gsGlobal, GS_SETREG_RGBAQ(0x00,0x00,0x00,0x00,0x00));
}

void MenuEnd(GSGLOBAL* gsGlobal)
{
	printf("This should Run when MenuState is Gone.\n");
	// Clear VRAM after the Menu is done~
	gsKit_vram_clear(gsGlobal);
	UnloadMusic(&MenuMusicy);
}

StateManager MenuState =
{
	MenuStart,
	MenuUpdate,
	MenuDraw,
	MenuEnd
};
