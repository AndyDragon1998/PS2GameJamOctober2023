#ifndef PLAYER
#define PLAYER
#include <gsKit.h>
#include <dmaKit.h>
#include <gsToolkit.h>
#include "b2d_lite.h"

typedef struct
{
	int X;
	int Y;
    int X2;
	int Y2;
    int U;
    int isAlive;   
    int isMoving; 
    int mass;
}Player;

void InitializePlayer(Player* player, GSGLOBAL* gsGlobal,struct Body* playerBody);
void UpdatePlayer(Player* player, GSGLOBAL* gsGlobal, struct Body* playerBody);
void DrawPlayer(Player* player,GSGLOBAL* gsGlobal, u64 colour,struct Body* playerBody);


#endif