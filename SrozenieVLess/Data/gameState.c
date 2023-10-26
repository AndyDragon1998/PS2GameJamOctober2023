#include "include/gameState.h"
#include "include/menuState.h"
#include "include/overState.h"
#include "include/introState.h"
#include "include/pad.h"
#include "include/musicManager.h"
#include "include/b2d_lite.h"
#include "include/collide.h"

extern StateMachine GameMachineState;

/****** User External Files ********/
#include "extern/gameState.ext"

/****** User Table Files ***********/

/****** User Define Files ***********/
#include "define/gameState.def"

GSTEXTURE GameBG;
GSTEXTURE greenpudge;
GSTEXTURE purplepudge;
GSTEXTURE plate;
//GSTEXTURE HOOKARROW;



int moveSpeedGreen, fallSpeedGreen, moveSpeedPurple, fallSpeedPurple;

int rXGreen1, rXGreen2, rXPurple1, rXPurple2;

int X1, X2, Y1, Y2;

int WinsGreen, WinsPurple = 0;

#define GRAVITY 1.0f
#define JUMP_STRENGTH 20.0f

void GameStart(GSGLOBAL* gsGlobal)
{
    char tempy[4096];
    strcpy(tempy, relativePath);
    strcat(tempy, GIRLBGIMAGE);
    gsKit_texture_png(gsGlobal, &GameBG, tempy);

    strcpy(tempy, relativePath);
    strcat(tempy, GREENPUDGE);
    gsKit_texture_png(gsGlobal, &greenpudge, tempy);

    strcpy(tempy, relativePath);
    strcat(tempy, PURPLEPUDGE);
    gsKit_texture_png(gsGlobal, &purplepudge, tempy);

    strcpy(tempy, relativePath);
    strcat(tempy, TESTPLATE);
    gsKit_texture_png(gsGlobal, &plate, tempy);

    SetUpFont(gsGlobal);

    // Инициализация начальных значений
    moveSpeedGreen = 5;
    fallSpeedGreen = 0;
    
    moveSpeedPurple = 5;
    fallSpeedPurple = 0;
    X1 = 10;
    Y1 = 100;
    X2 = 300;
    Y2 = 50;
    
    rXGreen1 = X1;
    rXGreen2 = X1 + greenpudge.Width;
    rXPurple1 = X2;
    rXPurple2 = X2 + purplepudge.Width;
}

void GameUpdate(GSGLOBAL* gsGlobal)
{

    // Управление персонажем
    if (PlaystationGamePad.LEFT_KEY_DOWN) {
        X1 -= moveSpeedGreen;
        
        rXGreen1 = X1 + greenpudge.Width;
    	rXGreen2 = X1;
    	
    	rXPurple1 = X2 + purplepudge.Width;
    	rXPurple2 = X2;
        
    } else if (PlaystationGamePad.RIGHT_KEY_DOWN) {
        X1 += moveSpeedGreen;
        
        rXGreen1 = X1;
    	rXGreen2 = X1 + greenpudge.Width;
        
        rXPurple1 = X2;
    	rXPurple2 = X2 + purplepudge.Width;
    }
    
    //if (PlaystationGamePad.LEFT_KEY_DOWN) {
    //    X2 -= moveSpeedPurple;
    //} else if (PlaystationGamePad.RIGHT_KEY_DOWN) {
    //    X2 += moveSpeedPurple;
    //}

    // Применение гравитации
    //if ((Y1 < 236 || X1< -44 || X1 >212 || Y1 > 240) || (Y1 < 236 || X1< 320-64 || X1 >320+192 || Y1 > 240)) {
    if ((Y1 < 236 || X1< -44 || X1 >212 || Y1 > 240) && (Y1 < 236 || X1< 320-64 || X1 >320+192 || Y1 > 240)) {
        fallSpeedGreen += GRAVITY;
    } else {
        Y1 = 236;  // Остановка на платформе
        fallSpeedGreen = 0;
    }
    
    if ((Y2 < 236 || X2< -44 || X2 >212 || Y2 > 240) && (Y2 < 236 || X2< 320-64 || X2 >320+192 || Y2 > 240)) {
        fallSpeedPurple += GRAVITY;
    } else {
        Y2 = 236;  // Остановка на платформе
        fallSpeedPurple = 0;
    }
    
    

    // Обработка прыжка
    if (PlaystationGamePad.BUTTON_X_KEY_TAP && Y1 == 236) {
        fallSpeedGreen = -JUMP_STRENGTH;
    }
    
    if (PlaystationGamePad.BUTTON_X_KEY_TAP && Y2 == 236) {
        fallSpeedPurple = -JUMP_STRENGTH;
    }

    Y1 += fallSpeedGreen;
    Y2 += fallSpeedPurple;
   
    
    if (Y1>320) {
    	WinsPurple += 1;
    	X1 = 10;
    	Y1 = 100;
    	X2 = 300;
    	Y2 = 50;
    	
    	rXGreen1 = X1;
    	rXGreen2 = X1 + greenpudge.Width;
    	rXPurple1 = X2;
    	rXPurple2 = X2 + purplepudge.Width;
    }
    
    if (Y2>320) {
    	WinsGreen += 1;
    	X1 = 10;
    	Y1 = 100;
    	X2 = 300;
    	Y2 = 50;
    	
    	rXGreen1 = X1;
    	rXGreen2 = X1 + greenpudge.Width;
    	rXPurple1 = X2;
    	rXPurple2 = X2 + purplepudge.Width;
    }
    
    if(WinsGreen > 9 || WinsPurple > 9){
    	WinsGreen = 0;
    	WinsPurple = 0;
    	StateMachineChange(&GameMachineState, &MenuState, gsGlobal);
    }
    
    
    
}

void GameDraw(GSGLOBAL* gsGlobal, u64 colour)
{
    gsKit_prim_sprite_texture(gsGlobal, &GameBG, 0, 0, 0.0f, 0.0f, GameBG.Width * 2, GameBG.Height * 2, GameBG.Width * 2, GameBG.Height * 2, 2, colour);

    //gsKit_prim_sprite_texture(gsGlobal, &purplepudge, X2, Y2, 0.0f, 0.0f, X2 + purplepudge.Width, Y2 + purplepudge.Height, purplepudge.Width, purplepudge.Height, 2, colour);
    gsKit_prim_sprite_texture(gsGlobal, &purplepudge, rXPurple1, Y2, 0.0f, 0.0f, rXPurple2, Y2 + purplepudge.Height, purplepudge.Width, purplepudge.Height, 2, colour);

    gsKit_prim_sprite_texture(gsGlobal, &greenpudge, rXGreen1, Y1, 0.0f, 0.0f, rXGreen2, Y1 + greenpudge.Height, greenpudge.Width, greenpudge.Height, 2, colour);

    gsKit_prim_sprite_texture(gsGlobal, &plate, 20, 300, 0.0f, 0.0f, 20 + plate.Width, 300 + plate.Height, plate.Width, plate.Height, 2, colour);
    gsKit_prim_sprite_texture(gsGlobal, &plate, 320, 300, 0.0f, 0.0f, 320 + plate.Width, 300 + plate.Height, plate.Width, plate.Height, 2, colour);
    
    	switch(WinsGreen)
	{
		// Start New Game
		case 0:
			DrawText(20, 30, "0",3, gsGlobal, &colour,1);
		break;
		case 1: 

			DrawText(20, 30, "1",3, gsGlobal, &colour,1);
		break;
		case 2: 

			DrawText(20, 30, "2",3, gsGlobal, &colour,1);
		break;
		case 3: 

			DrawText(20, 30, "3",3, gsGlobal, &colour,1);
		break;
		case 4: 

			DrawText(20, 30, "4",3, gsGlobal, &colour,1);
		break;
		case 5: 

			DrawText(20, 30, "5",3, gsGlobal, &colour,1);
		break;
		case 6: 

			DrawText(20, 30, "6",3, gsGlobal, &colour,1);
		break;
		case 7: 

			DrawText(20, 30, "7",3, gsGlobal, &colour,1);
		break;
		case 8: 

			DrawText(20, 30, "8",3, gsGlobal, &colour,1);
		break;
		case 9: 

			DrawText(20, 30, "9",3, gsGlobal, &colour,1);
		break;
		
	}
	
	switch(WinsPurple)
	{
		case 0:
			DrawText(580, 30, "0",3, gsGlobal, &colour,0);
		break;
		case 1: 

			DrawText(580, 30, "1",3, gsGlobal, &colour,0);
		break;
		case 2: 

			DrawText(580, 30, "2",3, gsGlobal, &colour,0);
		break;
		case 3: 

			DrawText(580, 30, "3",3, gsGlobal, &colour,0);
		break;
		case 4: 

			DrawText(580, 30, "4",3, gsGlobal, &colour,0);
		break;
		case 5: 

			DrawText(580, 30, "5",3, gsGlobal, &colour,0);
		break;
		case 6: 

			DrawText(580, 30, "6",3, gsGlobal, &colour,0);
		break;
		case 7: 

			DrawText(580, 30, "7",3, gsGlobal, &colour,0);
		break;
		case 8: 

			DrawText(580, 30, "8",3, gsGlobal, &colour,0);
		break;
		case 9: 

			DrawText(580, 30, "9",3, gsGlobal, &colour,0);
		break;
	}
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

