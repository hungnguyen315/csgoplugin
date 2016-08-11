#include "pluginutils.h"

extern CGlobalVars *globalVars;
extern IVEngineServer *vEngineServer;

bool init_CBaseEntity_Props(SendTable *st)
{
	int num = 0;
	for (int i = 0; i < st->m_nProps; i++)
	{
		SendProp *sp = st->GetProp(i);
		const char *propName = sp->GetName();
		Msg("Prop name: %s. Prop Offset: %d.\n. Type: ", propName, sp->GetOffset());
		if (strcmp(propName, "m_iTeamNum") == 0)
		{
			m_iTeamNum_off = sp->GetOffset();
			num++;
			continue;
		}
		
		if (strcmp(propName, "m_iPendingTeamNum") == 0)
		{
			m_iPendingTeamNum_off = sp->GetOffset();
			num++;
			continue;
		}
		
		if (strcmp(propName, "m_fFlags") == 0)
		{
			m_fFlags_off = sp->GetOffset();
			num++;
			continue;
		}
	}
	if (num == 3)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void BalanceNumberOfBots(unsigned short humans, unsigned short bots, int team)
{
	if (humans <= 5)
	{
		unsigned short numberBotsAllow = 5 - humans;
		if (bots <= numberBotsAllow)
		{
			for (unsigned short i = bots; i < numberBotsAllow; i++)
			{
				if (team == COUNTER_TERRORIST)
				{
					vEngineServer->ServerCommand("bot_add ct\n");
				}
				else if (team == TERRORIST)
				{
					vEngineServer->ServerCommand("bot_add t\n");
				}
				else
				{
					return;
				}
			}
		}
		else
		{
			while (bots > numberBotsAllow)
			{
				if (team == COUNTER_TERRORIST)
				{
					vEngineServer->ServerCommand("bot_kick ct\n");
				}
				else if (team == TERRORIST)
				{
					vEngineServer->ServerCommand("bot_kick t\n");
				}
				else
				{
					return;
				}
				bots--;
			}
		}
	}
	else
	{
		for (unsigned short i = 0; i < bots; i++)
		{
			if (team == COUNTER_TERRORIST)
			{
				vEngineServer->ServerCommand("bot_kick ct\n");
			}
			else if (team == TERRORIST)
			{
				vEngineServer->ServerCommand("bot_kick t\n");
			}
			else
			{
				return;
			}
		}
	}
}
