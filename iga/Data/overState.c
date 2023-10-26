/*****************************************************************************/
/*  Автор         		: Дракончик				                             */
/*  Приставка     		: Sony PlayStation 2					             */
/*  ОС			  		: OSDSYS											 */
/*  Язык	      		: GNU C                                              */
/*                                                                           */
/*  Содержимое файла	: Стадия завершение Игри	                         */
/*  Атрибут файла		: SOURCE                                             */
/*  Имя файла     		: overState.c	                                     */
/*                                                                           */
/*****************************************************************************/
#include "include/level1State.h"
#include "include/gameState.h"
#include "include/menuState.h"
#include "include/overState.h"
#include "include/introState.h"
#include "include/musicManager.h"
#include "include/textToGraphics.h"
#include "include/pad.h"

#include "extern/menuState.ext"

/****** User Table Files ***********/


/****** User Define Files ***********/
#include "define/menuState.def"

extern StateMachine GameMachineState;

GSTEXTURE OverImage; 

void OverStart(GSGLOBAL* gsGlobal)
{
	char tempover[4096];
	strcpy(tempover, relativePath);
	strcat(tempover, OVERIMAGEPATH);
	gsKit_texture_png(gsGlobal, &OverImage,tempover);
	
	
	SetUpFont(gsGlobal);
}

void OverUpdate(GSGLOBAL* gsGlobal)
{
	if(PlaystationGamePad.START_KEY_TAP)
    	{	
		StateMachineChange(&GameMachineState, &MenuState, gsGlobal);
	}
}

void OverDraw(GSGLOBAL* gsGlobal, u64 colour)
{
	gsKit_prim_sprite_texture(gsGlobal, &OverImage,0,  // X1
						0,  // Y2
						0.0f,  // U1
						0.0f,  // V1
						OverImage.Width * 2, // X2
						OverImage.Height * 2, // Y2
						OverImage.Width * 2, // U2
						OverImage.Height * 2, // V2
						2,
						colour);
}

void OverEnd(GSGLOBAL* gsGlobal)
{
	gsKit_vram_clear(gsGlobal);
}

StateManager OverState =
{
	OverStart,
	OverUpdate,
	OverDraw,
	OverEnd
};
