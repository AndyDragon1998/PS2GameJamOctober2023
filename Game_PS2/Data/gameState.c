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


extern StateMachine GameMachineState;

/****** User External Files ********/
#include "extern/gameState.ext"

/****** User Table Files ***********/


/****** User Define Files ***********/
#include "define/gameState.def"

GSTEXTURE GameBG;
GSTEXTURE User;
GSTEXTURE User_left;
GSTEXTURE User_right;
GSTEXTURE Box;
BGM MikuSong;

// int

int x1, x2, y1, y2, z1, z2;
int countChests = 0;
//bool

bool t = false, t1 = false, t2 = false, t3 = false;
bool user = false, user_left = false, user_right = false;

void GameStart(GSGLOBAL* gsGlobal)
{
	char temp[4096];
	strcpy(temp, relativePath);
	strcat(temp, PickMusic(2));
	MikuSong.fileName = temp;
	
	LoadMusic(&MikuSong);
	
	x1 = -34;
	x2 = 0;
	y1 = -34;
	y2 = 0;
	z1 = 1;
	z2 = 1;

	char tempy[4096];
	strcpy(tempy, relativePath);
	strcat(tempy, GIRLBGIMAGE);
	gsKit_texture_png(gsGlobal, &GameBG, tempy);
	
	char tempy_user[4096];
	strcpy(tempy_user, relativePath);
	strcat(tempy_user, GIRLBGIMAGE_USER);
	gsKit_texture_png(gsGlobal, &User, tempy_user);
	
	char tempy_user_left[4096];
	strcpy(tempy_user_left, relativePath);
	strcat(tempy_user_left, GIRLBGIMAGE_USER_LEFT);
	gsKit_texture_png(gsGlobal, &User_left, tempy_user_left);
	
	char tempy_user_right[4096];
	strcpy(tempy_user_right, relativePath);
	strcat(tempy_user_right, GIRLBGIMAGE_USER_RIGHT);
	gsKit_texture_png(gsGlobal, &User_right, tempy_user_right);
	
	char tempy_box_1[4096];
	strcpy(tempy_box_1, relativePath);
	strcat(tempy_box_1, GIRLBGIMAGE_BOX);
	gsKit_texture_png(gsGlobal, &Box, tempy_box_1);
	
	char tempy_box_2[4096];
	strcpy(tempy_box_2, relativePath);
	strcat(tempy_box_2, GIRLBGIMAGE_BOX);
	gsKit_texture_png(gsGlobal, &Box, tempy_box_2);
	
	char tempy_box_3[4096];
	strcpy(tempy_box_3, relativePath);
	strcat(tempy_box_3, GIRLBGIMAGE_BOX);
	gsKit_texture_png(gsGlobal, &Box, tempy_box_3);
	
	char tempy_box_4[4096];
	strcpy(tempy_box_4, relativePath);
	strcat(tempy_box_4, GIRLBGIMAGE_BOX);
	gsKit_texture_png(gsGlobal, &Box, tempy_box_4);
	
	SetUpFont(gsGlobal);
}

void GameUpdate(GSGLOBAL* gsGlobal)
{
	

    // This part here plays the music
    PlayMusic(&MikuSong);
    
    if (PlaystationGamePad.LEFT_KEY_DOWN)
    {
    	user_left = true;
    	
        x1 -= z1;
        x2 -= z2;
    }
    else if (PlaystationGamePad.RIGHT_KEY_DOWN)
    {
    	user_right = true;
    
        x1 += z1;
        x2 += z2;
    }
    else if (PlaystationGamePad.UP_KEY_DOWN)
    {
    	user = true;
    
        y1 -= z1;
        y2 -= z2;
    }
    else if (PlaystationGamePad.DOWN_KEY_DOWN)
    {
    	user = true;
    
        y1 += z1;
        y2 += z2;
    }
}

/*void Move (char move) {
	gsKit_prim_sprite_texture(gsGlobal, &move,
						x1 ,  // X1
						y1,  // Y2
						0.0f,  // U1
						0.0f,  // V1
						x2, // X2
						y2, // Y2
						move.Width, // U2
						move.Height, // V2
						2,
						colour);
}*/

void GameDraw(GSGLOBAL* gsGlobal, u64 colour)
{
	/*if(countChests == 3)
	{
		DrawText(120, 360, "BUHF JRJYXTYF",2, gsGlobal, &colour,1);
		z1 = 0;
		z2 = 0;
	}*/

	gsKit_prim_sprite_texture(gsGlobal, &GameBG,
						0,  // X1
						0,  // Y2
						0.0f,  // U1
						0.0f,  // V1
						GameBG.Width * 2, // X2
						GameBG.Height * 2, // Y2
						GameBG.Width * 2, // U2
						GameBG.Height * 2, // V2
						2,
						colour);

	//if (user_left == true) {
		/*char User_left = "User_left";
		Move (User_left);*/
		/*gsKit_prim_sprite_texture(gsGlobal, &User_left,
						x1 ,  // X1
						y1,  // Y2
						0.0f,  // U1
						0.0f,  // V1
						x2, // X2
						y2, // Y2
						User_left.Width, // U2
						User_left.Height, // V2
						2,
						colour);
	}
	else if (user_right == true) {*/
		/*char User_right = "User_right";
		Move (User_right);*/
		/*gsKit_prim_sprite_texture(gsGlobal, &User_right,
						x1 ,  // X1
						y1,  // Y2
						0.0f,  // U1
						0.0f,  // V1
						x2, // X2
						y2, // Y2
						User_right.Width, // U2
						User_right.Height, // V2
						2,
						colour);
	}
	else if (user == true) {*/
		/*char User = "User";
		Move (User);*/
		/*gsKit_prim_sprite_texture(gsGlobal, &User,
						x1 ,  // X1
						y1,  // Y2
						0.0f,  // U1
						0.0f,  // V1
						x2, // X2
						y2, // Y2
						User.Width, // U2
						User.Height, // V2
						2,
						colour);
	}*/
						
	gsKit_prim_sprite_texture(gsGlobal, &User,
						x1 ,  // X1
						y1,  // Y2
						0.0f,  // U1
						0.0f,  // V1
						x2, // X2
						y2, // Y2
						User.Width, // U2
						User.Height, // V2
						2,
						colour);
	
	if (t == false) {
		gsKit_prim_sprite_texture(gsGlobal, &Box,
						350,  // X1
						170,  // Y2
						0.0f,  // U1
						0.0f,  // V1
						371, // X2
						191, // Y2
						Box.Width, // U2
						Box.Height, // V2
						2,
						colour);
	}
	
	if (t1 == false) {
		gsKit_prim_sprite_texture(gsGlobal, &Box,
						185,  // X1
						345,  // Y2
						0.0f,  // U1
						0.0f,  // V1
						206, // X2
						366, // Y2
						Box.Width, // U2
						Box.Height, // V2
						2,
						colour);
	}
	
	if (t2 == false) {
		gsKit_prim_sprite_texture(gsGlobal, &Box,
						85,  // X1
						230,  // Y2
						0.0f,  // U1
						0.0f,  // V1
						106, // X2
						251, // Y2
						Box.Width, // U2
						Box.Height, // V2
						2,
						colour);
	}
	
	if (t3 == false) {
		gsKit_prim_sprite_texture(gsGlobal, &Box,
						90,  // X1
						70,  // Y2
						0.0f,  // U1
						0.0f,  // V1
						111, // X2
						91, // Y2
						Box.Width, // U2
						Box.Height, // V2
						2,
						colour);
	}
					
	if (x2 >= 350 && y2 >= 170 && x1 <= 371 && y1 <= 191)
	{
		t = true;
		
		gsKit_prim_sprite_texture(gsGlobal, &Box,
						10,  // X1
						485,  // Y2
						0.0f,  // U1
						0.0f,  // V1
						31, // X2
						506, // Y2
						Box.Width, // U2
						Box.Height, // V2
						2,
						colour);
	}
	else if (t == true) {
		gsKit_prim_sprite_texture(gsGlobal, &Box,
						10,  // X1
						485,  // Y2
						0.0f,  // U1
						0.0f,  // V1
						31, // X2
						506, // Y2
						Box.Width, // U2
						Box.Height, // V2
						2,
						colour);
						
		DrawText(120, 360, "BUHF JRJYXTYF",2, gsGlobal, &colour,1);
		z1 = 0;
		z2 = 0;
	}
	
	if (x2 >= 185 && y2 >= 345 && x1 <= 206 && y1 <= 366) {
		t1 = true;
		
		gsKit_prim_sprite_texture(gsGlobal, &Box,
						40,  // X1
						485,  // Y2
						0.0f,  // U1
						0.0f,  // V1
						61, // X2
						506, // Y2
						Box.Width, // U2
						Box.Height, // V2
						2,
						colour);
	}
	else if (t1 == true) {
		gsKit_prim_sprite_texture(gsGlobal, &Box,
						40,  // X1
						485,  // Y2
						0.0f,  // U1
						0.0f,  // V1
						61, // X2
						506, // Y2
						Box.Width, // U2
						Box.Height, // V2
						2,
						colour);
	}
	
	if (x2 >= 85 && y2 >= 230 && x1 <= 106 && y1 <= 251)
	{
		t2 = true;
		
		gsKit_prim_sprite_texture(gsGlobal, &Box,
						70,  // X1
						485,  // Y2
						0.0f,  // U1
						0.0f,  // V1
						91, // X2
						506, // Y2
						Box.Width, // U2
						Box.Height, // V2
						2,
						colour);
	}
	else if (t2 == true) {
		gsKit_prim_sprite_texture(gsGlobal, &Box,
						70,  // X1
						485,  // Y2
						0.0f,  // U1
						0.0f,  // V1
						91, // X2
						506, // Y2
						Box.Width, // U2
						Box.Height, // V2
						2,
						colour);
	}
	
	if (x2 >= 90 && y2 >= 70 && x1 <= 111 && y1 <= 91)
	{
		t3 = true;
		
		gsKit_prim_sprite_texture(gsGlobal, &Box,
						100,  // X1
						485,  // Y2
						0.0f,  // U1
						0.0f,  // V1
						121, // X2
						506, // Y2
						Box.Width, // U2
						Box.Height, // V2
						2,
						colour);
	}
	else if (t3 == true) {
		gsKit_prim_sprite_texture(gsGlobal, &Box,
						100,  // X1
						485,  // Y2
						0.0f,  // U1
						0.0f,  // V1
						121, // X2
						506, // Y2
						Box.Width, // U2
						Box.Height, // V2
						2,
						colour);
	}
}

void GameEnd(GSGLOBAL* gsGlobal)
{
	/*if (PlaystationGamePad.START_KEY_TUP)
    	{
        	GameRunning = 0;
		UnloadMusic(&MenuMusicy);
    	}*/
}

StateManager GameState =
{
	GameStart,
	GameUpdate,
	GameDraw,
	GameEnd
};
