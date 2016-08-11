#ifndef PLUGINUTILS_H
#define PLUGINUTILS_H

#include "edict.h"
#include "eiface.h"

#define COUNTER_TERRORIST 3
#define TERRORIST 2

class CBaseEntity;

static const unsigned int m_iTeamNum_addr = 0x310;
static const unsigned int m_iPendingTeamNum_addr = 0x314;
static const unsigned int m_fFlags_addr = 0x0D8;

//edict_t *GetEdictByUserId(int userid);

#endif
