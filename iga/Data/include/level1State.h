#ifndef LEVEL1_STATE
#define LEVEL1_STATE

#include "stateManager.h"
#include <stdbool.h>

void level1Start(GSGLOBAL* gsGlobal);
void level1Update(GSGLOBAL* gsGlobal);
void level1Draw(GSGLOBAL* gsGlobal, u64 colour);
void level1End(GSGLOBAL* gsGlobal);

extern StateManager level1State;

#endif
