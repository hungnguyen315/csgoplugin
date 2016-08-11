#include "pluginutils.h"

extern CGlobalVars *globalVars;
extern IVEngineServer *vEngineServer;

void BalanceNumberOfBots(unsigned short humans, unsigned short bots, int team)
{
	Msg("Number of bots team %d is %d.\n", team, bots);
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
