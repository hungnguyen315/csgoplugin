#include "pluginutils.h"

extern CGlobalVars *globalVars;
extern IVEngineServer *vEngineServer;

void BalanceNumberOfBots(unsigned short humans, unsigned short bots, int team)
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
				Msg(cmdBotAdd);
			}
		}
		else
		{
			while (bots > numberBotsAllow)
			{
				vEngineServer->ServerCommand(cmdBotKick);
				Msg(cmdBotKick);
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
