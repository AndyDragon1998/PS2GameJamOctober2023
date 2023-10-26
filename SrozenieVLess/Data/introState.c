/*****************************************************************************/
/*  Автор         		: Дракончик				                             */
/*  Приставка     		: Sony PlayStation 2					             */
/*  ОС			  		: OSDSYS											 */
/*  Язык	      		: GNU C                                              */
/*                                                                           */
/*  Содержимое файла	: Стадия логотипов			                         */
/*  Атрибут файла		: SOURCE                                             */
/*  Имя файла     		: introState.c	                                     */
/*                                                                           */
/*****************************************************************************/

#include "include/gameState.h"
#include "include/menuState.h"
#include "include/overState.h"
#include "include/introState.h"
#include <stdlib.h>
#include <string.h>
#include <pwd.h>

/****** User External Files ********/
#include "extern/introState.ext"

/****** User Table Files ***********/


/****** User Define Files ***********/
#include "define/introState.def"

GSTEXTURE IntroImage;

u64 IntroImageColour;
u64 AlphaChannel;

int introTimer;

u64 oldalpha;

void IntroStart(GSGLOBAL* gsGlobal)
{
 	char tempy[4096];
	strcpy(tempy, relativePath);
	strcat(tempy, INTROIMAGEPATH);
	gsKit_texture_png(gsGlobal, &IntroImage, tempy);
}

void IntroUpdate(GSGLOBAL* gsGlobal)
{
	introTimer++;

	if(introTimer > 488)
	{
		introTimer = 0;
		StateMachineChange(&GameMachineState, &MenuState, gsGlobal);
	}
	
}

void IntroDraw(GSGLOBAL* gsGlobal, u64 colour)
{	
	gsKit_prim_sprite_texture(gsGlobal, &IntroImage, 0, 0, 0.0f, 0.0f, IntroImage.Width * 2, IntroImage.Height * 2, IntroImage.Width * 2, IntroImage.Height * 2, 2, colour);						
    	
}

void IntroEnd(GSGLOBAL* gsGlobal)
{

	printf("This should Run when MenuState is Gone.\n");
	// Clear VRAM after the Menu is done~
	gsKit_vram_clear(gsGlobal);
}

StateManager IntroState =
{
	IntroStart,
	IntroUpdate,
	IntroDraw,
	IntroEnd
};
