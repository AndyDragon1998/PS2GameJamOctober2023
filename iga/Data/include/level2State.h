#ifndef LEVEL2_STATE
#define LEVEL2_STATE

#include "stateManager.h"
#include <stdbool.h>

void level2Start(GSGLOBAL* gsGlobal);
void level2Update(GSGLOBAL* gsGlobal);
void level2Draw(GSGLOBAL* gsGlobal, u64 colour);
void level2End(GSGLOBAL* gsGlobal);

extern StateManager level2State;

#endif
