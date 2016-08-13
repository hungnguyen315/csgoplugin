#ifndef PLUGINUTILS_H
#define PLUGINUTILS_H

#include "edict.h"
#include "eiface.h"
#include "dt_send.h"

#define COUNTER_TERRORIST 3
#define TERRORIST 2

class CBaseEntity;

bool init_CBaseEntity_Props(SendTable* st);
bool init_CBasePlayer_Props(SendTable* st);
bool init_CCSPlayerResource_Props(SendTable *st);
void BalanceNumberOfBots(unsigned short humans, unsigned short bots, int team);
void CreateMenu(bf_write* pBuffer, const char* szMessage, int nOptions, int iSecondsToStayOpen);

#endif
