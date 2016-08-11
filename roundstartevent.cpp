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

	this->HandleNumberOfBot(humansTeamCT, botsTeamCT, COUNTER_TERRORIST);
	this->HandleNumberOfBot(humansTeamT, botsTeamT, TERRORIST);
}

void RoundStartEvent::HandleNumberOfBot(unsigned short humans, unsigned short bots, int team)
{
	char cmdBotAdd[11];
	char cmdBotKick[12];
	if (team == COUNTER_TERRORIST)
	{
		strcpy(cmdBotAdd, "bot_add ct\n");
		strcpy(cmdBotKick, "bot_kick ct\n");
	}
	else if (team == TERRORIST)
	{
		strcpy(cmdBotAdd, "bot_add t\n");
		strcpy(cmdBotKick, "bot_kick t\n");
	}
	else
	{
		return;
	}

	if (humans <= 5)
	{
		unsigned short numberBotsAllow = 5 - humans;
		if (bots <= numberBotsAllow)
		{
			for (unsigned short i = bots; i < numberBotsAllow; i++)
			{
				vEngineServer->ServerCommand(cmdBotAdd);
				Msg("ADDDDDD.\n");
			}
		}
		else
		{
			while (bots > numberBotsAllow)
			{
				vEngineServer->ServerCommand(cmdBotKick);
				bots--;
			}
		}
	}
	else
	{
		for (unsigned short i = 0; i < bots; i++)
		{
			vEngineServer->ServerCommand(cmdBotKick);
		}
	}
}

int RoundStartEvent::GetEventDebugID()
{
	return EVENT_DEBUG_ID_INIT;
}
