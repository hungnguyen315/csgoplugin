#include "roundstartevent.h"

extern CGlobalVars *globalVars;
extern IVEngineServer *vEngineServer;
extern IServerGameEnts *serverGameEnts;

void RoundStartEvent::FireGameEvent(IGameEvent *event)
{
	unsigned short humansTeamT = 0, botsTeamT = 0, humansTeamCT = 0, botsTeamCT = 0;
	for (unsigned short i = 1; i <= globalVars->maxClients; i++)
	{
		edict_t *playerEdict = globalVars->pEdicts + i;
		if (playerEdict && !playerEdict->IsFree() && strcmp(playerEdict->GetClassName(), "player") == 0)
		{
			CBaseEntity *playerEntity = serverGameEnts->EdictToBaseEntity(playerEdict);
			if (playerEntity)
			{
				int team = *(int *)((char *)playerEntity + m_iTeamNum_addr);
				int flags = *(int *)((char *)playerEntity + m_fFlags_addr);
				if (flags & FL_FAKECLIENT)
				{
					if (team == COUNTER_TERRORIST)
					{
						botsTeamCT++;
					}
					else if (team == TERRORIST)
					{
						botsTeamT++;
					}
				}
				else if (flags & FL_CLIENT)
				{
					if (team == COUNTER_TERRORIST)
					{
						humansTeamCT++;
					}
					else if (team == TERRORIST)
					{
						humansTeamT++;
					}
				}
			}
		}
	}

	BalanceNumberOfBots(humansTeamCT, botsTeamCT, COUNTER_TERRORIST);
	BalanceNumberOfBots(humansTeamT, botsTeamT, TERRORIST);
}

int RoundStartEvent::GetEventDebugID()
{
	return EVENT_DEBUG_ID_INIT;
}
