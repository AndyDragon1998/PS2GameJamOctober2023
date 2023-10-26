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
#include "include/campState.h"
#include "include/pad.h"
#include "include/musicManager.h"


extern StateMachine GameMachineState;

/****** User External Files ********/
#include "extern/gameState.ext"

/****** User Table Files ***********/


/****** User Define Files ***********/
#include "define/gameState.def"

GSTEXTURE GameBG;
GSTEXTURE PlayerBG;
GSTEXTURE DialogBG;
GSTEXTURE NewBarmen;

u64 ImageColourInBar;
u64 AlphaChannelInBar;
u64 oldalphaInBar;

BGM MikuSong;

float playerX = 296.0f;
float playerY = 462.0f;
float playerV = 0.0f;

float playerX2 = 344.0f ;
float playerY2 = 510.0f;
float playerV2 = 32.0f;

float angle = 90.0f;
float step = 2.0f;

float BarmenV1 = 0.0f;
float BarmenV2 = 18.0f;
int AnimTimer = 0; 

int countMessages = 0;

bool isDialogZone = false;
bool isChangeStateToCamp = false;
bool isEndDialogMenu = true;

void MovePlayerUp()
{
    playerY -= step;
    playerY2 -= step; 
}

void MovePlayerDown()
{
    playerY += step; 
    playerY2 += step;
}

void MovePlayerLeft()
{
    playerX -= step;
    playerX2 -= step; 
}

void MovePlayerRight()
{
    playerX += step;
    playerX2 += step;
    
}

void GameStart(GSGLOBAL* gsGlobal)
{
	AlphaChannelInBar = 0;

	initMusicFormat();
	char temp[4096];
	strcpy(temp, relativePath);
	strcat(temp, PickMusic(4));
	MikuSong.fileName = temp;
	
	LoadMusic(&MikuSong);

	char tempy[4096];
	strcpy(tempy, relativePath);
	strcat(tempy, GIRLBGIMAGE);
	gsKit_texture_png(gsGlobal, &GameBG,tempy);
	
	char tempys[4096];
	strcpy(tempys, relativePath);
	strcat(tempys, PLAYERIMAGE);
	gsKit_texture_png(gsGlobal, &PlayerBG,tempys);
	
	char dino[4096];
	strcpy(dino, relativePath);
	strcat(dino, DIALOG);
	gsKit_texture_png(gsGlobal, &DialogBG,dino);
	
	char dino2[4096];
	strcpy(dino2, relativePath);
	strcat(dino2, NEWBARMEN);
	gsKit_texture_png(gsGlobal, &NewBarmen,dino2);
	
	
	
	SetUpFont(gsGlobal);

}

void GameUpdate(GSGLOBAL* gsGlobal)
{

	PlayMusic(&MikuSong);
	if(AnimTimer == 6){
		if(BarmenV2 == 306){
			BarmenV1 = 0.0f;
			BarmenV2 = 18.0f;
		}	
		BarmenV1 += 18;
		BarmenV2 += 18;
		AnimTimer = 0;
	}
	AnimTimer += 1;

	if(PlaystationGamePad.RIGHT_KEY_DOWN && playerX2 <= 492)
	{
		MovePlayerRight();
		playerV = 98.0f;
		playerV2 = 128.0f;
	}
	if(PlaystationGamePad.UP_KEY_DOWN && playerY >= 124)
	{
		MovePlayerUp();
		playerV = 0.0f;
		playerV2 = 32.0f;
	}
	if(PlaystationGamePad.DOWN_KEY_DOWN && playerY2 <= 510)
	{
		MovePlayerDown();
		playerV = 64.0f;
		playerV2 = 96.0f;
	}
	if(PlaystationGamePad.LEFT_KEY_DOWN && playerX >= 122)
	{
		MovePlayerLeft();
		playerV = 32.0f;
		playerV2 = 64.0f;
	}
	
	if(playerX >= 250 &&  playerY >= 450 && playerX2 <= 380 && playerY2 <= 515 && PlaystationGamePad.START_KEY_TAP && isChangeStateToCamp){
		StateMachineChange(&GameMachineState, &CampState, gsGlobal);
	} // change machineState
	
	
	if(PlaystationGamePad.SELECT_KEY_TAP && isDialogZone)
	{
		countMessages = countMessages + 1;
			
		if(countMessages == 5)
		{
			isDialogZone = false;
			step = 2.0f;
			isChangeStateToCamp = true;
			isEndDialogMenu = false;
		}
		
	}
	
	
}

void GameDraw(GSGLOBAL* gsGlobal, u64 colour)
{
		gsKit_prim_sprite_texture(gsGlobal, 
		&GameBG, 
		0, 
		0, 
		0.0f, 
		0.0f, 
		640, 
		512, 
		640, 
		512,
		2,
		colour);

		gsKit_prim_sprite_texture(gsGlobal,
		&PlayerBG, 
		playerX, 
		playerY, 
		playerV, 
		0.0f,  
		playerX2, 
		playerY2, 
		playerV2, 
		PlayerBG.Height * 2,
		2, 
		colour);
		
		gsKit_prim_sprite_texture(gsGlobal,
		&NewBarmen, 
		250+30, 
		100-70, 
		BarmenV1, 
		0.0f,  
		314+30, 
		164-70, 
		BarmenV2, 
		PlayerBG.Height * 2,
		2, 
		colour);
		
		
		
		
		if (playerX >= 200 && playerY >= 100 && playerX2 <= 420 && playerY2 <= 200 && PlaystationGamePad.START_KEY_TAP && isEndDialogMenu) {
		    
		    isDialogZone = true;
		    MovePlayerDown();
		    step = 0.0f;
		    
		} // dialog menu
		
//isZoneSlepa
//isEndDialogSlepa
		
		if(isDialogZone){
		    	gsKit_prim_sprite_texture(gsGlobal, 
		    	&DialogBG,
			0,  // X1
			380,  // Y2
			0.0f,  // U1
			0.0f,  // V1
			640, // X2
			512, // Y2
			0.0f,  // U2
			0.0f,  // V2
			2,
			colour);
			
			switch(countMessages){
				case 0:
					DrawText(20, 390, "PYFTIM DFHU TNF PFLFXF GJ",2, gsGlobal, &colour,1);
					DrawText(20, 420, "RJKJYBPFWBB GKFYTNS PDEXBN YT NFR",2, gsGlobal, &colour,1);
					DrawText(20, 450, "EP B GKJCJ YJDST VBHS ",2, gsGlobal, &colour,1);
					DrawText(20, 480, "B YJDST HTCEHCS DTCMVF RHENFF)",2, gsGlobal, &colour,1);
					break;
				case 1:
					DrawText(20, 390, "LF GTHEY Z CKSIFK XNJ YF TNJQ",2, gsGlobal, &colour,2);
					DrawText(20, 420, "GKFYTNT PBDEN LBRBT VENFYNS",2, gsGlobal, &colour,2);
					DrawText(20, 450, "B XELJDBOF YFV GHBLTNCZ",2, gsGlobal, &colour,2);
					DrawText(20, 480, "CNJKRYENMCZ C PBCNJRBV DHFUJV",2, gsGlobal, &colour,2);
					break;
				case 2:
					DrawText(20, 390, "VS PT BP PFDJTDFNTKMYJUJ",2, gsGlobal, &colour,1);
					DrawText(20, 420, "JNHZLF F TOT VS CJGBHFTV",2, gsGlobal, &colour,1);
					DrawText(20, 450, "YJDJGHFYWTD B YFTVYBRJD",2, gsGlobal, &colour,1);
					DrawText(20, 480, "TNJ DCBJ D KFUTHT DTLM",2, gsGlobal, &colour,1);
					break;
				case 3:
					DrawText(20, 390, "CKBCFK JG TNJV NFV JGTOFEN",2, gsGlobal, &colour,2);
					DrawText(20, 420, "YFCNJZOTT BCGSNFYBT YFLJ GELTN",2, gsGlobal, &colour,2);
					DrawText(20, 450, "GHJQNB XTHTP JUJYM B DJLE",2, gsGlobal, &colour,2);
					DrawText(20, 480, "GHTPLT XTV YFC GHBUKFCZN",2, gsGlobal, &colour,2);
					break;
				case 4:
					DrawText(20, 390, "NS R TNJVE UJNJD DTLM",2, gsGlobal, &colour,1);
					DrawText(20, 420, "DGTHTL PFDJTDBDFNM",2, gsGlobal, &colour,1);
					DrawText(20, 450, "B CJPLFDFNM LKZ YFIBD",2, gsGlobal, &colour,1);
					DrawText(20, 480, "GHFNMTD PLFYBZ",2, gsGlobal, &colour,1);
					break;
			}
			
		}
		
		
		 	
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
