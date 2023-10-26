#ifndef CAMP_STATE
#define CAMP_STATE

#include "stateManager.h"
#include <stdbool.h>

void CampStart(GSGLOBAL* gsGlobal);
void CampUpdate(GSGLOBAL* gsGlobal);
void CampDraw(GSGLOBAL* gsGlobal, u64 colour);
void CampEnd(GSGLOBAL* gsGlobal);

extern StateManager CampState;

#endif
