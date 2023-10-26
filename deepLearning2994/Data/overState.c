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
#include "include/pad.h"
#include "include/introState.h"
#include "extern/introState.ext"
#include "define/overState.def"
#include "include/textToGraphics.h"

extern StateMachine GameMachineState;
extern Controller PlaystationGamePad;
int selectOption;
GSTEXTURE GameOverImage;

void OverStart(GSGLOBAL* gsGlobal)
{
	initMusicFormat();

	char tempy[4096];
	strcpy(tempy, relativePath);
	strcat(tempy, GAMEOVERIMAGE);
	gsKit_texture_png(gsGlobal, &GameOverImage,tempy);

	selectOption = 0;
}

void OverUpdate(GSGLOBAL* gsGlobal)
{
	if(PlaystationGamePad.UP_KEY_TAP && selectOption != 0)
    {
    	selectOption--;
    }
    else if(PlaystationGamePad.DOWN_KEY_TAP && selectOption != 1)
    {
    	selectOption++;
    }

	if(PlaystationGamePad.START_KEY_TAP)
    	{	
		switch(selectOption)
		{
			case 0:
				StateMachineChange(&GameMachineState, &GameState, gsGlobal);
			break;

			case 1: 
				StateMachineChange(&GameMachineState, &MenuState, gsGlobal);
			break;

			default:
		}
	}

}

void OverDraw(GSGLOBAL* gsGlobal, u64 colour)
{
	gsKit_prim_sprite_texture(gsGlobal, &GameOverImage,0,  // X1
										0,  // Y1
										0,  // U1
										0.0f,  // V1
										GameOverImage.Width  * 2, // X2
										GameOverImage.Height * 2, // Y2
										GameOverImage.Width  * 2, // U2
										GameOverImage.Height * 2, // V2
										2,
										colour);	

	switch(selectOption)
	{
		case 0:
			DrawText(200, 320, "YFXFNM PFYJDJ",2, gsGlobal, &colour, 1);
			DrawText(200, 355, "GTHTQNB D VTY>",2, gsGlobal, &colour, 0);
		break;
		case 1: 
	  		DrawText(200, 320, "YFXFNM PFYJDJ",2, gsGlobal, &colour, 0);
			DrawText(200, 355, "GTHTQNB D VTY>",2, gsGlobal, &colour, 1);

		break;
		default:
	}
	
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
