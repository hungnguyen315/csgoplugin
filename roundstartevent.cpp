#include "roundstartevent.h"
#include "edict.h"
#include "eiface.h"
#include "const.h"
#include "pluginutils.h"

class CBaseEntity;

extern CGlobalVars *globalVars;
extern IVEngineServer *vEngineServer;
extern IServerGameEnts *serverGameEnts;

extern int m_iTeamNum_off;
extern int m_iPendingTeamNum_off;
extern int m_fFlags_off;

void RoundStartEvent::FireGameEvent(IGameEvent *event)
{
	unsigned short humansteamt = 0, botsteamt = 0, humansteamct = 0, botsteamct = 0;
	for (unsigned short i = 1; i < globalVars->maxClients; i++)
	{
		edict_t *edict = globalVars->pEdicts + i;
		if (!edict || edict->IsFree())
			continue;
		
		CBaseEntity *entity = serverGameEnts->EdictToBaseEntity(edict);
		if (!entity)
			continue;
		
		unsigned int *flags = (unsigned int *)((char *)entity + m_fFlags_off);
		int *pendingteam = (int *)((char *)entity + m_iPendingTeamNum_off);
		Msg("Player pending team is %d.\n", *pendingteam);
		if (*flags & FL_FAKECLIENT)
		{
			if (*pendingteam == COUNTER_TERRORIST)
				botsteamct++;
			else if (*pendingteam ==  TERRORIST)
				botsteamt++;
		}
		else if (*flags & FL_CLIENT)
		{
			if (*pendingteam == COUNTER_TERRORIST)
				humansteamct++;
			else if (*pendingteam == TERRORIST)
				humansteamt++;
		}
	}
	
	BalanceNumberOfBots(humansteamct, botsteamct, COUNTER_TERRORIST);
	BalanceNumberOfBots(humansteamt, botsteamt, TERRORIST);
}

int RoundStartEvent::GetEventDebugID()
{
	return EVENT_DEBUG_ID_INIT;
}
