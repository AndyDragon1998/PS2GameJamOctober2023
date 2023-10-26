/*****************************************************************************/
/*  Автор         		: Дракончик				                             */
/*  Приставка     		: Sony PlayStation 2					             */
/*  ОС			  		: OSDSYS											 */
/*  Язык	      		: GNU C                                              */
/*                                                                           */
/*  Содержимое файла	: Стадия игровой детельности                         */
/*  Атрибут файла		: SOURCE                                             */
/*  Имя файла     		: gameState.c	                                     */
/*                                                                           */
/*****************************************************************************/

#include "include/gameState.h"
#include "include/menuState.h"
#include "include/b2d_lite.h"
#include "include/overState.h"
#include "include/introState.h"
#include "include/pad.h"
#include "include/musicManager.h"
#include "include/player.h"
// #include "include/b2d_lite.h"

extern StateMachine GameMachineState;

/****** User External Files ********/
#include "extern/gameState.ext"

/****** User Table Files ***********/


/****** User Define Files ***********/
#include "define/gameState.def"
extern StateMachine GameMachineState;
GSTEXTURE image[] = {};
int Timer;


BGM MikuSong;
int startX = 50;
int startX2 = 80;
int startY = 330;
int startY2 = 370;

Player player;
struct Body playerBody;
struct Body floor;

struct Vec2 PlayerWidth = {20.0f,6.0f};
struct Vec2 floorWidth = {64.0f,16.0f};


void GameStart(GSGLOBAL* gsGlobal)
{	
	Timer = 0;
	char temp[4096];
	strcpy(temp, relativePath);
	strcat(temp, PickMusic(2));
	MikuSong.fileName = temp;
	
	LoadMusic(&MikuSong);

	char tempy[4096];
	strcpy(tempy, relativePath);
	strcat(tempy, GIRLBGIMAGE);
	gsKit_texture_png(gsGlobal, &image[0],tempy);

	char tempi[4096];
	strcpy(tempi, relativePath);
	strcat(tempi, FLOORIMAGE);
	gsKit_texture_png(gsGlobal, &image[1],tempi);


	char tempur[4096];
	strcpy(tempur, relativePath);
	strcat(tempur, SQUARE);
	gsKit_texture_png(gsGlobal, &image[3],tempur);
	SetUpFont(gsGlobal);

	InitializePlayer(&player, gsGlobal,&playerBody);

}

void GameUpdate(GSGLOBAL* gsGlobal)
{
	Timer++;
	if(Timer > 12000)
	{
		Timer = 0;
		StateMachineChange(&GameMachineState, &OverState, gsGlobal);
	}
		UpdatePlayer(&player, gsGlobal, &playerBody);
		PlayMusic(&MikuSong);
}

void GameDraw(GSGLOBAL* gsGlobal, u64 colour)
{	
	gsKit_prim_sprite_texture(gsGlobal, &image[0],0,  // X1
						0,  // Y2
						0.0f,  // U1
						0.0f,  // V1
						image[0].Width * 2, // X2
						image[0].Height * 2, // Y2
						image[0].Width * 2, // U2
						image[0].Height * 2, // V2
						2,
						colour);



	DrawPlayer(&player, gsGlobal, colour,&playerBody);

}

void GameEnd(GSGLOBAL* gsGlobal)
{
	gsKit_vram_clear(gsGlobal);
}

StateManager GameState =
{
	GameStart,
	GameUpdate,
	GameDraw,
	GameEnd
};
