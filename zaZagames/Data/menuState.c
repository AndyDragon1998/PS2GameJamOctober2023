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

BGM MenuMusicy;

int selectedOption; // 0 - New Game 1 - Load Game 2- ShutDown game

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
	
	
	SetUpFont(gsGlobal);
	
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
	   			// Open Load screen
			break;

			case 2:
	   			// settings
			break;
			
			case 3:
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



	switch(selectedOption)
	{
		// Start New Game
		case 0:
			DrawText(120, 360, "YJDFZ BUHF",2, gsGlobal, &colour,1);
			DrawText(120, 385, "GHJLJK:BNM",2, gsGlobal, &colour,0);
			DrawText(120, 410, "YFCNHJQRB",2, gsGlobal, &colour,0);
			DrawText(120, 435, "PFDTHIBNM BUHE",2, gsGlobal, &colour,0);
		break;
		case 1: 
	  		DrawText(120, 360, "YJDFZ BUHF",2, gsGlobal, &colour,0);
			DrawText(120, 385, "GHJLJK:BNM",2, gsGlobal, &colour,1);
			DrawText(120, 410, "YFCNHJQRB",2, gsGlobal, &colour,0);
			DrawText(120, 435, "PFDTHIBNM BUHE",2, gsGlobal, &colour,0);
		break;
		case 2:
	   		DrawText(120, 360, "YJDFZ BUHF",2, gsGlobal, &colour,0);
			DrawText(120, 385, "GHJLJK:BNM",2, gsGlobal, &colour,0);
			DrawText(120, 410, "YFCNHJQRB",2, gsGlobal, &colour,1);
			DrawText(120, 435, "PFDTHIBNM BUHE",2, gsGlobal, &colour,0);
		break;
		case 3:
			DrawText(120, 360, "YJDFZ BUHF",2, gsGlobal, &colour,0);
			DrawText(120, 385, "GHJLJK:BNM",2, gsGlobal, &colour,0);
			DrawText(120, 410, "YFCNHJQRB",2, gsGlobal, &colour,0);
			DrawText(120, 435, "PFDTHIBNM BUHE",2, gsGlobal, &colour,1);
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
