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

#include "include/campState.h"
#include "include/gameState.h"
#include "include/menuState.h"
#include "include/overState.h"
#include "include/introState.h"
#include "include/pad.h"
#include "include/musicManager.h"

extern StateMachine GameMachineState;

/****** User External Files ********/
#include "extern/campState.ext"

/****** User Table Files ***********/


/****** User Define Files ***********/
#include "define/campState.def"

GSTEXTURE GameBG_in_camp;
GSTEXTURE PlayerBG_in_camp;
GSTEXTURE BulletBG_in_camp;
GSTEXTURE TargBG_in_camp;
GSTEXTURE DialogBG_in_camp;

BGM CampMusicStateWT;

//player

float playerX_in_camp = 246.0f;
float playerY_in_camp = 62.0f;
float playerV_in_camp = 0.0f;

float playerX2_in_camp = 294.0f;
float playerY2_in_camp = 110.0f;
float playerV2_in_camp = 32.0f;

//bullet

float bulletX_in_camp = 1110.0f;
float bulletY_in_camp = 0.0f;
float bulletV_in_camp = 0.0f;

float bulletX2_in_camp = 0.0f;
float bulletY2_in_camp = 0.0f;
float bulletV2_in_camp = 0.0f;

float bulletScale = 8.0f;

// speed

float step_in_camp = 2.0f;
float bullet_step = 6.0f; 

// vector

float bullet_vector = 1;

// bool logic

bool isActiveBulletShtorm = false;
bool isDeathFirstEnemy = true;
bool isDeathSecondEnemy = true;
bool isDeathThirdEnemy = true;
bool isDeathFourthEnemy = true;
bool isCanFire = false;

//Bool and Int for dialog

int countMSG = 0;

bool isEndDialogSlepa = true;
bool isZoneSlepa = false;

// enemy first position

float x1_enemy_first = 396;
float x2_enemy_first = 444;

float x1_enemy_second = 396 + 50;
float x2_enemy_second = 444 + 50;

float x1_enemy_third = 396 + 50 + 50;
float x2_enemy_third = 444 + 50 + 50;

float x1_enemy_fourth = 396 + 50 + 50 + 50;
float x2_enemy_fourth = 444 + 50 + 50 + 50;

void MovePlayerUp_in_camp()
{
	if(playerX2_in_camp < 260 || (playerX2_in_camp > 260 && playerY_in_camp > 116)){
		playerY_in_camp -= step_in_camp;
    	playerY2_in_camp -= step_in_camp;
	} 
}

void MovePlayerDown_in_camp()
{
    playerY_in_camp += step_in_camp; 
    playerY2_in_camp += step_in_camp;
	
}

void MovePlayerLeft_in_camp()
{
	if(playerX_in_camp > 218){
    	playerX_in_camp -= step_in_camp;
    	playerX2_in_camp -= step_in_camp; 
    }
}

void MovePlayerRight_in_camp()
{
	if(playerY_in_camp > 116 || (playerX_in_camp < 260 && playerY_in_camp < 116)){
    	playerX_in_camp += step_in_camp;
    	playerX2_in_camp += step_in_camp;
    }
}

void BulletShtorm(float vector)
{
	if(vector == 1)
	{
		bulletY_in_camp -= bullet_step;
		bulletY2_in_camp -= bullet_step;					
	}
	if(vector == 2)
	{
		bulletX_in_camp += bullet_step;	
		bulletX2_in_camp += bullet_step;					
	}
	if(vector == 3)
	{
		bulletY_in_camp += bullet_step;		
		bulletY2_in_camp += bullet_step;			
	}
	if(vector == 4)
	{
		bulletX_in_camp -= bullet_step;	
		bulletX2_in_camp -= bullet_step;					
	}
}

void CampStart(GSGLOBAL* gsGlobal)
{
	initMusicFormat();
	char temp[4096];
	strcpy(temp, relativePath);
	strcat(temp, PickMusic(2));
	CampMusicStateWT.fileName = temp;
	
	LoadMusic(&CampMusicStateWT);

	char tempy[4096];
	strcpy(tempy, relativePath);
	strcat(tempy, GIRLBGIMAGE);
	gsKit_texture_png(gsGlobal, &GameBG_in_camp,tempy);
	
	char tempys[4096];
	strcpy(tempys, relativePath);
	strcat(tempys, PLAYERIMAGE);
	gsKit_texture_png(gsGlobal, &PlayerBG_in_camp,tempys);
	
	char tempys2[4096];
	strcpy(tempys2, relativePath);
	strcat(tempys2, BULLETIMAGE);
	gsKit_texture_png(gsGlobal, &BulletBG_in_camp,tempys2);
	
	char tempys21[4096];
	strcpy(tempys21, relativePath);
	strcat(tempys21, TARG);
	gsKit_texture_png(gsGlobal, &TargBG_in_camp,tempys21);
	
	char dino[4096];
	strcpy(dino, relativePath);
	strcat(dino, DIALOG);
	gsKit_texture_png(gsGlobal, &DialogBG_in_camp,dino);
	
	SetUpFont(gsGlobal);

}

void CampUpdate(GSGLOBAL* gsGlobal)
{
	PlayMusic(&CampMusicStateWT);
	
	if(PlaystationGamePad.SELECT_KEY_TAP && isZoneSlepa)
	{
		countMSG = countMSG + 1;
			
		if(countMSG == 2)
		{
			isZoneSlepa = false;
			step_in_camp = 2.0f;
			isEndDialogSlepa = false;
			isCanFire = true;
		}
		
	}

	if(PlaystationGamePad.RIGHT_KEY_DOWN && playerX2_in_camp <= 640)
	{
		MovePlayerRight_in_camp();
		
		
		if((bulletX_in_camp > 640 || bulletX_in_camp < 0 || bulletY_in_camp > 512 || bulletY2_in_camp < 0) && isActiveBulletShtorm == false  )
		{
			playerV_in_camp = 98.0f;
			playerV2_in_camp = 128.0f;
			bullet_vector = 2;
		}
	}
	if(PlaystationGamePad.UP_KEY_DOWN && playerY_in_camp >= 0)
	{
		MovePlayerUp_in_camp();
		
		
		
		if((bulletX_in_camp > 640 || bulletX_in_camp < 0 || bulletY_in_camp > 512 || bulletY2_in_camp < 0) && isActiveBulletShtorm == false)
		{
			playerV_in_camp = 0.0f;
			playerV2_in_camp = 32.0f;
			bullet_vector = 1;
		}
		
	}
	if(PlaystationGamePad.DOWN_KEY_DOWN && playerY2_in_camp <= 512)
	{
		MovePlayerDown_in_camp();
		
		
		if((bulletX_in_camp > 640 || bulletX_in_camp < 0 || bulletY_in_camp > 512 || bulletY2_in_camp < 0) && isActiveBulletShtorm == false)
		{
			playerV_in_camp = 64.0f;
			playerV2_in_camp = 96.0f;
			bullet_vector = 3;
		}
	}
	if(PlaystationGamePad.LEFT_KEY_DOWN && playerX_in_camp >= 0)
	{
		MovePlayerLeft_in_camp();
		
		
		if((bulletX_in_camp > 640 || bulletX_in_camp < 0 || bulletY_in_camp > 512 || bulletY2_in_camp < 0) && isActiveBulletShtorm == false)
		{
			playerV_in_camp = 32.0f;
			playerV2_in_camp = 64.0f;
			bullet_vector = 4;
		}
	}
	
	if((PlaystationGamePad.START_KEY_TAP && (bulletX_in_camp > 640 || bulletX_in_camp < 0 || bulletY_in_camp > 512 || bulletY2_in_camp < 0)) && isCanFire)
	{
		bulletX_in_camp = playerX_in_camp + bulletScale;
		bulletY_in_camp = playerY_in_camp + bulletScale;
		bulletX2_in_camp = playerX2_in_camp - bulletScale*4;
		bulletY2_in_camp = playerY2_in_camp - bulletScale*3;
		
		
		isActiveBulletShtorm = true;
	}
	
	if((bulletX_in_camp > 640 || bulletX_in_camp < 0 || bulletY_in_camp > 512 || bulletY2_in_camp < 0))
	{
		bulletX_in_camp = 11111;
		bulletY_in_camp = 111111;
		bulletX2_in_camp = 11111;
		bulletY2_in_camp = 11111;
		isActiveBulletShtorm = false;
	}
	
	if(	(bulletX_in_camp >= 246+150 && bulletX_in_camp <= 266+150+30 &&
		bulletY_in_camp >= 62+150 && bulletY_in_camp <= 82+150+30 ||
		bulletX2_in_camp >= 294+150 && bulletX2_in_camp <= 274+150+30 &&
		bulletY2_in_camp <= 110+150 && bulletY2_in_camp >= 90+150+30
		)&& isDeathFirstEnemy)
	{
			
			isDeathFirstEnemy = false;
			if(isDeathFirstEnemy)
			{
				x1_enemy_first = 1000;
				x2_enemy_first = 1000;
			}
			else
			{
				bulletX_in_camp = 1000;
				bulletX2_in_camp = 1000;
				x1_enemy_first = 1000;
				x2_enemy_first = 1000;
			}
			//MovePlayerLeft_in_camp();
			
	} // first enemy
	
	if(	(bulletX_in_camp >= 246+150+50 && bulletX_in_camp <= 266+150+30+50 &&
		bulletY_in_camp >= 62+150 && bulletY_in_camp <= 82+150+30 ||
		bulletX2_in_camp >= 294+150+50 && bulletX2_in_camp <= 274+150+30+50 &&
		bulletY2_in_camp <= 110+150 && bulletY2_in_camp >= 90+150+30
		)&& isDeathSecondEnemy)
	{
			
			isDeathSecondEnemy = false;
			if(isDeathSecondEnemy)
			{
				x1_enemy_second = 1000;
				x2_enemy_second = 1000;
			}
			else
			{
				bulletX_in_camp = 1000;
				bulletX2_in_camp = 1000;
				x1_enemy_second = 1000;
				x2_enemy_second = 1000;
			}
			//MovePlayerLeft_in_camp();
			
	} // second enemy
	
	if(	(bulletX_in_camp >= 246+150+50+50 && bulletX_in_camp <= 266+150+30+50+50 &&
		bulletY_in_camp >= 62+150 && bulletY_in_camp <= 82+150+30 ||
		bulletX2_in_camp >= 294+150+50+50 && bulletX2_in_camp <= 274+150+30+50+50 &&
		bulletY2_in_camp <= 110+150 && bulletY2_in_camp >= 90+150+30
		)&& isDeathThirdEnemy)
	{
			
			isDeathThirdEnemy = false;
			if(isDeathThirdEnemy)
			{
				x1_enemy_third = 1000;
				x2_enemy_third = 1000;
			}
			else
			{
				bulletX_in_camp = 1000;
				bulletX2_in_camp = 1000;
				x1_enemy_third = 1000;
				x2_enemy_third = 1000;
			}
			//MovePlayerLeft_in_camp();
			
	} // third enemy
	
	if(	(bulletX_in_camp >= 246+150+50+50+50 && bulletX_in_camp <= 266+150+30+50+50+50 &&
		bulletY_in_camp >= 62+150 && bulletY_in_camp <= 82+150+30 ||
		bulletX2_in_camp >= 294+150+50+50+50 && bulletX2_in_camp <= 274+150+30+50+50+50 &&
		bulletY2_in_camp <= 110+150 && bulletY2_in_camp >= 90+150+30
		)&& isDeathFourthEnemy)
	{
			
			isDeathFourthEnemy = false;
			if(isDeathFourthEnemy)
			{
				x1_enemy_fourth = 1000;
				x2_enemy_fourth = 1000;
			}
			else
			{
				bulletX_in_camp = 1000;
				bulletX2_in_camp = 1000;
				x1_enemy_fourth = 1000;
				x2_enemy_fourth = 1000;
			}
			//MovePlayerLeft_in_camp();
			
	} // fourth enemy
	
	BulletShtorm(bullet_vector);
}

void CampDraw(GSGLOBAL* gsGlobal, u64 colour)
{
		gsKit_prim_sprite_texture(gsGlobal, 
		&GameBG_in_camp, 
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
		&PlayerBG_in_camp, 
		playerX_in_camp, 
		playerY_in_camp, 
		playerV_in_camp, 
		0.0f,  
		playerX2_in_camp, 
		playerY2_in_camp, 
		playerV2_in_camp, 
		PlayerBG_in_camp.Height * 2,
		2, 
		colour); // player
		
		gsKit_prim_sprite_texture(gsGlobal,
		&TargBG_in_camp, 
		x1_enemy_first, 	//x1
		62+150, 	//y1
		0.0f, 
		0.0f,  
		x2_enemy_first,	//x2 
		110+150, 	//y2
		32.0f, 
		PlayerBG_in_camp.Height * 2,
		2, 
		colour);//first enemy!!! 
		
		gsKit_prim_sprite_texture(gsGlobal,
		&TargBG_in_camp, 
		x1_enemy_second, 	//x1
		62+150, 	//y1
		32.0f, 
		0.0f,  
		x2_enemy_second,	//x2 
		110+150, 	//y2
		64.0f, 
		PlayerBG_in_camp.Height * 2,
		2, 
		colour);//second enemy!!! 
		
		gsKit_prim_sprite_texture(gsGlobal,
		&TargBG_in_camp, 
		x1_enemy_third, 	//x1
		62+150, 	//y1
		64.0f, 
		0.0f,  
		x2_enemy_third,	//x2 
		110+150, 	//y2
		96.0f, 
		PlayerBG_in_camp.Height * 2,
		2, 
		colour);//third enemy!!! 
		
		gsKit_prim_sprite_texture(gsGlobal,
		&TargBG_in_camp, 
		x1_enemy_fourth, 	//x1
		62+150, 	//y1
		96.0f, 
		0.0f,  
		x2_enemy_fourth,	//x2 
		110+150, 	//y2
		128.0f, 
		PlayerBG_in_camp.Height * 2,
		2, 
		colour);//fourth enemy!!! 
		
		gsKit_prim_sprite_texture(gsGlobal,
		&BulletBG_in_camp, 
		bulletX_in_camp, 
		bulletY_in_camp, 
		bulletV_in_camp, 
		0.0f,  
		bulletX2_in_camp, 
		bulletY2_in_camp, 
		bulletV2_in_camp, 
		BulletBG_in_camp.Height * 2,
		2, 
		colour);
		
		
		if (playerX_in_camp >= 450 && playerY_in_camp >= 100 && playerX2_in_camp <= 640 && playerY2_in_camp <= 200 && PlaystationGamePad.START_KEY_TAP && isEndDialogSlepa) {
		    
		    isZoneSlepa = true;
		    step_in_camp = 0.0f;
		    
		} // dialog menu
		
		if(isZoneSlepa){
		    	gsKit_prim_sprite_texture(gsGlobal,
		    	&DialogBG_in_camp,
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
			
			switch(countMSG){
				case 0:
					DrawText(20, 390, "GHBDTN YJDTYMRBQ",2, gsGlobal, &colour,1);
					DrawText(20, 420, "LFQ EUFLF.",2, gsGlobal, &colour,1);
					DrawText(20, 450, "NS GHBITK JNNJXBNM YFDSRB",2, gsGlobal, &colour,1);
					DrawText(20, 480, "GHJQLB DYBP R VBITYZV)",2, gsGlobal, &colour,1);
					break;
				case 1:
					DrawText(20, 390, "RYJGRF LKZ CNHTKZKRB",2, gsGlobal, &colour,3);
					DrawText(20, 420, "TYNTH",2, gsGlobal, &colour,3);
					DrawText(20, 450, "DGTHTL DJBY",2, gsGlobal, &colour,3);
					DrawText(20, 480, "CKFDF BVGTHBB",2, gsGlobal, &colour,3);
					break;
			}
		}
		
}


void CampEnd(GSGLOBAL* gsGlobal)
{
	gsKit_vram_clear(gsGlobal);
	UnloadMusic(&CampMusicStateWT);
}

StateManager CampState =
{
	CampStart,
	CampUpdate,
	CampDraw,
	CampEnd
};
