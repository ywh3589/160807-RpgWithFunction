
#pragma once

#include "value.h"

extern PMONSTER	g_pMonsterPrototype[MAP_BACK - 1];

bool InitMap();
void RunMap();
void ReleaseMap();