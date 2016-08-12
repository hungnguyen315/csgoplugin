#include "roundstartevent.h"

extern CGlobalVars *globalVars;
extern IVEngineServer *vEngineServer;
extern IServerGameEnts *serverGameEnts;

extern int m_iTeamNum_off;
extern int m_iPendingTeamNum_off;
extern int m_fFlags_off;

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
				int *team = (int *)((char *)playerEntity + m_iTeamNum_off);
				int *pendingTeam = (int *)((char *)playerEntity + m_iPendingTeamNum_off);
				unsigned int *flags = (unsigned int *)((char *)playerEntity + m_fFlags_off);
				if (*flags & FL_FAKECLIENT)
				{
					if (*pendingTeam == COUNTER_TERRORIST)
					{
						botsTeamCT++;
					}
					else if (*pendingTeam == TERRORIST)
					{
						botsTeamT++;
					}
				}
				else if (*flags & FL_CLIENT)
				{
					if (*pendingTeam == COUNTER_TERRORIST)
					{
						humansTeamCT++;
					}
					else if (*pendingTeam == TERRORIST)
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
