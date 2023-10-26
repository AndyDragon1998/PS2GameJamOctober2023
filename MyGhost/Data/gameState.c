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
#include "include/overState.h"
#include "include/introState.h"
#include "include/pad.h"
#include "include/musicManager.h"
#include <stdlib.h>


extern StateMachine GameMachineState;

/****** User External Files ********/
#include "extern/gameState.ext"

/****** User Table Files ***********/


/****** User Define Files ***********/
#include "define/gameState.def"

GSTEXTURE GameBG;
GSTEXTURE GameBG2;
GSTEXTURE Hero;
GSTEXTURE Rip;
GSTEXTURE Rip2;
GSTEXTURE Pum;

GSTEXTURE Entity;

/*int introTimer2;
u64 AlphaChannel;
u64 oldalpha;*/

BGM MikuSong;
int textPosX;
int textPosY;
int speed_x;
int speed_y;
int speed_x2;
int speed_y2;

int textSpeed;
int jumpi;
int downi;
int idleTimer2;

int prT;
int pod;

int speed_xRip;
int speed_xRip2;
int speed_xPum;
int game_over;

void GameStart(GSGLOBAL* gsGlobal)
{
	/*AlphaChannel = 0;
	introTimer2 = 0;*/
	idleTimer2 = 0; // Once the Idle timer reaches 6000 then restart the screen to prevent screen burn on CRT
	
	char temp[4096];
	strcpy(temp, relativePath);
	strcat(temp, PickMusic(2));
	MikuSong.fileName = temp;
	
	LoadMusic(&MikuSong);

	char tempy[4096];
	strcpy(tempy, relativePath);
	strcat(tempy, GIRLBGIMAGE);
	gsKit_texture_png(gsGlobal, &GameBG,tempy);
	
	char tempy2[4096];
	strcpy(tempy2, relativePath);
	strcat(tempy2, GIRLBGIMAGE);
	gsKit_texture_png(gsGlobal, &GameBG2,tempy2);
	
	char tem[4096];
	strcpy(tem, relativePath);
	strcat(tem, HEROIS);
	gsKit_texture_png(gsGlobal, &Hero,tem);
	
	/*char tem2[4096];
	strcpy(tem2, relativePath);
	strcat(tem2, "/Graphics/Enemies/1.png");
	gsKit_texture_png(gsGlobal, &Rip,tem2);
	
	char tem3[4096];
	strcpy(tem3, relativePath);
	strcat(tem3, RIP2);
	gsKit_texture_png(gsGlobal, &Rip2,tem3);
	
	char tem4[4096];
	strcpy(tem4, relativePath);
	strcat(tem4, PUM);
	gsKit_texture_png(gsGlobal, &Pum,tem4);*/
	
	SetUpFont(gsGlobal);
	
	textPosX = 130;
    	textPosY = 360;
    	textSpeed = 2;
    	jumpi=0;
    	downi=40;
    	speed_x = 0;
    	speed_y = 0;
	speed_x2 = 800;
	speed_y2 = 0;
	prT=75;
	pod=0;
	speed_xRip = 600;
	speed_xRip2 = 800;
	speed_xPum = 1200;
	game_over = 0;
	
}

void GameUpdate(GSGLOBAL* gsGlobal)
{
	// This part here plays the music
		PlayMusic(&MikuSong);
	const char* massiv[] = {"/Graphics/Enemies/1.png", "/Graphics/Enemies/2.png", "/Graphics/Enemies/3.png"};
	
	if(PlaystationGamePad.UP_KEY_TAP)
    	{	
    		pod = 0;
    	 	//textPosY -= 5;
    	 	//textPosY += 5
    	 	while (jumpi<=40){
    	 		textPosY -= 2;
    	 		jumpi+=1;
    	 	}
    	 	pod = 40;
    	 	downi = 0;
    	 	
	}
	if(pod==40){
		prT--;
	}
	if(prT <=0 && pod == 40){
		pod = 0;
    	 	while (downi<=40){
    	 		textPosY += 2;
    	 		downi+=1;
    	 	}
    	 	jumpi = 0;
    	 	prT=50;
			}
	
	speed_x--;
	speed_x2--;
	
	if(speed_x <= -1200)
	{
		speed_x = 0;
	}
	
	if(speed_x2 >= 0)
	{
		speed_x2 = 1200;
	}	
	
	speed_xRip--;
	if (speed_xRip <=0)
	{
		int ran = 0 + rand()%(2-0+1);
		char tem2[4096];
		strcpy(tem2, relativePath);
		strcat(tem2, massiv[ran]);
		gsKit_texture_png(gsGlobal, &Rip,tem2);
		speed_xRip=600;
	}
	
	if(PlaystationGamePad.LEFT_KEY_TAP)
    	{	
    		StateMachineChange(&GameMachineState, &MenuState, gsGlobal);
    	 	
	}
	
	if (speed_xRip == textPosX && textPosY == 360) {
		game_over++;
	}
	
	if (game_over >= 2) {
		StateMachineChange(&GameMachineState, &OverState, gsGlobal);
	}
	
	
}

void GameDraw(GSGLOBAL* gsGlobal, u64 colour)
{
	gsKit_prim_sprite_texture(gsGlobal, &GameBG,speed_x,  // X1
						speed_y,  // Y1
						0.0f,  // U1
						0.0f,  // V1
						speed_x+1200, // X2
						GameBG.Height * 2, // Y2
						GameBG.Width * 2, // U2
						GameBG.Height * 2, // V2
						2,
						colour);
						
	gsKit_prim_sprite_texture(gsGlobal, &GameBG2,speed_x2,  // X1
						speed_y,  // Y1
						0.0f,  // U1
						0.0f,  // V1
						speed_x+1200, // X2
						GameBG2.Height * 2, // Y2
						GameBG2.Width * 2, // U2
						GameBG2.Height * 2, // V2
						2,
						colour);
			/////////////////////////////////////////////////////////////			
	gsKit_prim_sprite_texture(gsGlobal, &Hero,textPosX,  // X1
						textPosY,  // Y1
						0.0f,  // U1
						0.0f,  // V1
						textPosX+32, // X2 +32
						textPosY +32, // Y2+32
						Hero.Width * 2, // U2
						Hero.Height * 2, // V2
						2,
						colour);
							
	gsKit_prim_sprite_texture(gsGlobal, &Rip,speed_xRip,  // X1
						360,  // Y1
						0.0f,  // U1
						0.0f,  // V1
						speed_xRip+35, // X2 +32
						360+35, // Y2+32
						Rip.Width * 2, // U2
						Rip.Height * 2, // V2
						2,
						colour);					
						
}

void GameEnd(GSGLOBAL* gsGlobal)
{
	gsKit_vram_clear(gsGlobal);
	UnloadMusic(&MikuSong);
}

StateManager GameState =
{
	GameStart,
	GameUpdate,
	GameDraw,
	GameEnd
};
