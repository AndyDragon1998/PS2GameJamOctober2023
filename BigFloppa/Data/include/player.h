#ifndef PLAYER_STATE
#define PLAYER_STATE

#include "stateManager.h"
#include <stdbool.h>

void PlayerStart(GSGLOBAL* gsGlobal);
void PlayerUpdate(GSGLOBAL* gsGlobal);
void PlayerDraw(GSGLOBAL* gsGlobal, u64 colour);
void PlayerEnd(GSGLOBAL* gsGlobal);

extern StateManager GameState;

#endif
