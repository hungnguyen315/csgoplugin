#ifndef PLUGINUTILS_H
#define PLUGINUTILS_H

#include "edict.h"
#include "eiface.h"
#include "dt_send.h"

#define COUNTER_TERRORIST 3
#define TERRORIST 2

class CBaseEntity;

static int m_iTeamNum_off = 0;
static int m_iPendingTeamNum_off = 0;
static int m_fFlags_off = 0;

bool init_CBaseEntity_Props(SendTable* st);
bool init_CBasePlayer_Props(SendTable* st);
void BalanceNumberOfBots(unsigned short humans, unsigned short bots, int team);


#endif
