#ifndef GAME_STATE
#define GAME_STATE

#include "stateManager.h"
#include <stdbool.h>

struct RenderSprite
{
        int x;
        int y;
        int x2;
        int y2;	
        float u1;
        float v1;
        float u2;
        float v2;	
};

void GameStart(GSGLOBAL* gsGlobal);
void GameUpdate(GSGLOBAL* gsGlobal);
void GameDraw(GSGLOBAL* gsGlobal, u64 colour);
void GameEnd(GSGLOBAL* gsGlobal);
void UpdateRender(struct RenderSprite* spriteData, int new_x, int new_y);

extern StateManager GameState;

#endif
