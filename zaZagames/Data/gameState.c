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

/*#include "include/gameState.h"
#include "include/menuState.h"
#include "include/overState.h"
#include "include/introState.h"
#include "include/pad.h"
#include "include/musicManager.h"*/
#include "include/gameState.h"
#include "include/menuState.h"
#include "include/overState.h"
#include "include/introState.h"
#include "include/musicManager.h"
#include "include/textToGraphics.h"
#include "include/soundEffects.h"
#include "include/pad.h"
#include <math.h>

#include <stdbool.h>


extern StateMachine GameMachineState;

/****** User External Files ********/
#include "extern/gameState.ext"

/****** User Table Files ***********/


/****** User Define Files ***********/
#include "define/gameState.def"


const int BULLET_START_X = 21;
const int BULLET_START_Y = 15;
int BULLET_SOST = 2;

GSTEXTURE GameBG;
BGM MikuSong;
BGM BulletSound;

// HERO
GSTEXTURE HeroTexture;
int Y_CONSTRAINT = 350;
int X_SOLDIER = 50;
int Y_SOLDIER = 100;
float PowOfSpriteHero = 0.0f;
float PowOfAnimationSpriteHero = 0.0f;

// ZOMBIE
typedef struct
{
	GSTEXTURE ZombieTexture;
	int x;
	int y;
	int speed;
} Zombie;



int ZombieCount = 0;
Zombie ZombieList[3];
char ZOMBIEtempy[1026];
int KadrRespawn = 0;

// BULLETS
typedef struct
{
	GSTEXTURE BulletTexture;
	int x;
	int y;
	float sost_hero;
	int life;
} Bullet;

int BulletCount = 0;
//Bullet BulletList[30];
char BULLtempy[1026];

/*Bullet b;
b.life = 0;
b.x = X_SOLDIER + 21;
b.y = Y_CONSTRAINT + 15;
b.sost_hero = PowOfSpriteHero;*/

int bullet_life = 0;
GSTEXTURE BulletTexture;
int X_BULLET = 0; int Y_BULLET = 0; bool BULLET_LIVE = false;
int X_BULLET_LIVE = 0; int Y_BULLET_LIVE = 0;
int con = 0;




int Kadr = 0;

void GameStart(GSGLOBAL* gsGlobal)
{
	X_BULLET = X_SOLDIER + 21;
	Y_BULLET = Y_CONSTRAINT + 15;

	char tempMus[4096];
	strcpy(tempMus, relativePath);
	strcat(tempMus, PickMusic(2));
	MikuSong.fileName = tempMus;
	LoadMusic(&MikuSong);

	char tempy[4096];
	strcpy(tempy, relativePath);
	strcat(tempy, GIRLBGIMAGE);
	gsKit_texture_png(gsGlobal, &GameBG, tempy);

	strcpy(tempy, relativePath);
	strcat(tempy, SOLDIER);
	gsKit_texture_png(gsGlobal, &HeroTexture, tempy);

	

	SetUpFont(gsGlobal);

}



void GameUpdate(GSGLOBAL* gsGlobal)
{
	// This part here plays the music
	PlayMusic(&MikuSong);

	// HERO MOVE LOGIC

	bool isMoving = false;
	KadrRespawn += 1;

	if (PlaystationGamePad.RIGHT_KEY_DOWN && PlaystationGamePad.LEFT_KEY_DOWN) {
		PowOfAnimationSpriteHero = 0;
	}
	else if(PlaystationGamePad.RIGHT_KEY_DOWN)
    {
		isMoving = true;

		Kadr += 1;
		if (Kadr == 5) { PowOfAnimationSpriteHero += 1; Kadr = 0; }
		if (PowOfAnimationSpriteHero == 6) { PowOfAnimationSpriteHero = 0; }
		if (X_SOLDIER+28 < 600) { PowOfSpriteHero = 0; X_SOLDIER += 4; X_BULLET += 4;}
    }
	else if(PlaystationGamePad.LEFT_KEY_DOWN)
    {
		isMoving = true;

		Kadr += 1;
		if (Kadr == 5) { PowOfAnimationSpriteHero += 1; Kadr = 0; }
		if (PowOfAnimationSpriteHero == 6) { PowOfAnimationSpriteHero = 0; }
		if (X_SOLDIER > 12) { PowOfSpriteHero = 1; X_SOLDIER -= 4; X_BULLET -= 4; }
    }

	if (PlaystationGamePad.UP_KEY_DOWN && PlaystationGamePad.DOWN_KEY_DOWN) {
		PowOfAnimationSpriteHero = 0;
	}
	else if(PlaystationGamePad.UP_KEY_DOWN)
    {
		isMoving = true;

		Kadr += 1;
		if (Kadr == 5) { PowOfAnimationSpriteHero += 1; Kadr = 0; }
		if (PowOfAnimationSpriteHero == 6) { PowOfAnimationSpriteHero = 0; }
		if (Y_CONSTRAINT >= 320) {
			Y_CONSTRAINT -= 4; Y_BULLET -= 4;
		}
    }
	else if(PlaystationGamePad.DOWN_KEY_DOWN)
    {
		isMoving = true;

		Kadr += 1;
		if (Kadr == 5) { PowOfAnimationSpriteHero += 1; Kadr = 0; }
		if (PowOfAnimationSpriteHero == 6) { PowOfAnimationSpriteHero = 0; }
		if (Y_CONSTRAINT <= 444) {
			Y_CONSTRAINT += 4; Y_BULLET += 4;
		}
    }

	// ZOMBIE LOGIC
	/*
	int ZombieCount = 0;
	Zombie ZombieList[30];
	char ZOMBIEtempy[2048];
	int KadrRespawn = 0;
	*/
	if (KadrRespawn == 50 && ZombieCount < 3) {
		
		ZombieCount += 1;
		Zombie z; z.x = 300; z.y = 300; z.speed = 2;

		strcpy(ZOMBIEtempy, relativePath);
		strcat(ZOMBIEtempy, ZOMBIE);
		gsKit_texture_png(gsGlobal, &z.ZombieTexture, ZOMBIEtempy);

		ZombieList[ZombieCount-1] = z;
	}
	

	
	
	if(isMoving == false){ PowOfAnimationSpriteHero = 0; }


	// BULLET MOVE LOGIC
	if (BULLET_LIVE == false) {
		con = 0;
	}
	
	if (PlaystationGamePad.BUTTON_X_KEY_TAP) {
		if (BULLET_LIVE == false) {
			BULLET_LIVE = true;

			X_BULLET_LIVE = X_BULLET;
			Y_BULLET_LIVE = Y_BULLET;

			strcpy(BULLtempy, relativePath);
			strcat(BULLtempy, BULLET);
			gsKit_texture_png(gsGlobal, &BulletTexture, BULLtempy);

			if (PowOfSpriteHero == 0) {
				con = 8;
			}
			else if (PowOfSpriteHero == 1) {
				con = -8;
			}
		}
	}
	if (X_BULLET_LIVE > 640 || X_BULLET_LIVE < -10) {
		BULLET_LIVE = false;
		con = 0;
	} else {
		X_BULLET_LIVE += con;
	}
	int sost_b = con / 8;

	/*for (int i = 0; i < 3; i++) {
		if ( X_BULLET_LIVE == ZombieList[i].x ) {
			ZombieCount -= 1;
		}
	}*/

	for (int i = 0; i < ZombieCount; i++) {
		int vy = Y_CONSTRAINT - ZombieList[i].y;
		int vx = X_SOLDIER - ZombieList[i].x;
		int len = sqrt(pow(vx, 2) + pow(vy, 2));
		//int len = abs(dd);

		ZombieList[i].x += vx * ZombieList[i].speed / len;
		ZombieList[i].y += vy * ZombieList[i].speed / len;
	}
	KadrRespawn = 0;
}

void GameDraw(GSGLOBAL* gsGlobal, u64 colour)
{
	
	gsKit_prim_sprite_texture(gsGlobal, &GameBG,
		0,  // X1
		0,  // Y1
		0.0f,  // U1
		0.0f,  // V1
		GameBG.Width * 2, // X2
		GameBG.Height * 2, // Y2
		GameBG.Width * 2, // U2
		GameBG.Height * 2, // V2
		2,
		colour
	);

	gsKit_prim_sprite_texture(gsGlobal, &BulletTexture,
			X_BULLET_LIVE+3,  // X1 /////
			Y_BULLET_LIVE+12,  // Y1 /////s
			0.0f,  // U1
			0.0f,  // V1
			X_BULLET_LIVE+14, // X2
			Y_BULLET_LIVE+19, // Y2
			9.0f, // U2
			5.0f, // V2
			2,
			colour
		);
	

	gsKit_prim_sprite_texture(gsGlobal, &HeroTexture,
		X_SOLDIER,  // X1
		Y_CONSTRAINT,  // Y1
		28.0f * PowOfSpriteHero,  // U1
		35.0f * PowOfAnimationSpriteHero,  // V1
		X_SOLDIER + 28 * 2, // X2
		Y_CONSTRAINT + 35 * 2, // Y2
		28.0f * (PowOfSpriteHero + 1), // U2
		35.0f * (PowOfAnimationSpriteHero + 1), // V2
		2,
		colour
	);

	for (int i = 0; i < ZombieCount; i++) {
		gsKit_prim_sprite_texture(gsGlobal, &ZombieList[i].ZombieTexture,
			ZombieList[i].x,  // X1 /////
			ZombieList[i].y,  // Y1 /////s
			0.0f,  // U1
			0.0f,  // V1
			ZombieList[i].x+21, // X2
			ZombieList[i].y+32, // Y2
			21.0f, // U2
			32.0f, // V2
			2,
			colour
		);
	}
}

void GameEnd(GSGLOBAL* gsGlobal)
{

}

StateManager GameState =
{
	GameStart,
	GameUpdate,
	GameDraw,
	GameEnd
};
