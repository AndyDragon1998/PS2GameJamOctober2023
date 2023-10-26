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

#include "include/gameState.h"
#include "include/menuState.h"
#include "include/overState.h"
#include "include/introState.h"
#include "include/pad.h"

extern StateMachine GameMachineState;

extern Controller PlaystationGamePad;

extern char relativePath[];

#include "define/overState.def"
#include "extern/overState.ext"
//#define GI "/Graphics/Images/img.png"

GSTEXTURE fre;
int idleTimer1;

extern StateMachine GameMachineState;

void OverStart(GSGLOBAL* gsGlobal)
{
	char tempy[4096];
	strcpy(tempy, relativePath);
	strcat(tempy, "/Graphics/Images/fred.png");
	gsKit_texture_png(gsGlobal, &fre,tempy);
	SetUpFont(gsGlobal);
}

void OverUpdate(GSGLOBAL* gsGlobal)
{
	if(PlaystationGamePad.LEFT_KEY_TAP)
    	{	
    		StateMachineChange(&GameMachineState, &MenuState, gsGlobal);
    	 	
	}
}

void OverDraw(GSGLOBAL* gsGlobal, u64 colour)
{
	gsKit_prim_sprite_texture(gsGlobal, &fre,0,  // X1
						0,  // Y2
						0.0f,  // U1
						0.0f,  // V1
						fre.Width * 2, // X2
						fre.Height * 2, // Y2
						fre.Width * 2, // U2
						fre.Height * 2, // V2
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
