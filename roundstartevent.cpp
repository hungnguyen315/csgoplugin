#include "roundstartevent.h"

extern CGlobalVars *globalVars;
extern IVEngineServer *vEngineServer;
extern IServerGameEnts *serverGameEnts;

struct User
{
	int userid = 0;
	int team = 0;
	bool isbot = false;	
};

void RoundStartEvent::FireGameEvent(IGameEvent *event)
{
	unsigned short humansTeamT = 0, botsTeamT = 0, humansTeamCT = 0, botsTeamCT = 0;
	//int botsTeamTUserId[globalVars->maxClients], botsTeamCTUserId[globalVars->maxClients]; 
	for (unsigned short i = 1; i <= globalVars->maxClients; i++)
	{
		edict_t *playerEdict = globalVars->pEdicts + i;
		if (playerEdict && !playerEdict->IsFree() && strcmp(playerEdict->GetClassName(), "player") == 0)
		{
			//int userid = vEngineServer->GetPlayerUserId(playerEdict);
			CBaseEntity *playerEntity = serverGameEnts->EdictToBaseEntity(playerEdict);
			if (playerEntity)
			{
				int team = *(int *)((char *)playerEntity + m_iTeamNum_addr);
				int flags = *(int *)((char *)playerEntity + m_fFlags_addr);
				if (flags & FL_FAKECLIENT)
				{
					if (team == COUNTER_TERRORIST)
					{
						//botsTeamCTUserId[botsTeamCT] = userid;
						botsTeamCT++;
					}
					else if (team == TERRORIST)
					{
						//botsTeamTUserId[botsTeamT] = userid;
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
	Msg("Number of Bots CT is %d.\n", botsTeamCT);
	Msg("Number of humans CT is %d.\n", humansTeamCT);
	Msg("Number of Bots T is %d.\n", botsTeamT);
	Msg("Number of humans T is %d.\n", humansTeamT);
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
		Msg("NumberBotsAllow %d. Team %d.\n", numberBotsAllow, team);
		if (bots <= numberBotsAllow)
		{
			for (unsigned short i = bots; i < numberBotsAllow; i++)
			{
				vEngineServer->ServerCommand(cmdBotAdd);
				//vEngineServer->CreateFakeClient("BOT");
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
