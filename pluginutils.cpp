#include "pluginutils.h"
#include "eiface.h"

extern IVEngineServer *vEngineServer;

char botkickct[] = "bot_kick ct\n";
char botkickt[] = "bot_kick t\n";
char botaddct[] = "bot_add ct\n";
char botaddt[] = "bot_add t\n";

void BalanceNumberOfBots(unsigned short humans, unsigned short bots, int team)
{
	char *botkick, *botadd;

	if (team == COUNTER_TERRORIST)
	{
		botkick = botkickct;
		botadd = botaddct;
	}
	else if (team == TERRORIST)
	{
		botkick = botkickt;
		botadd = botaddt;
	}
	else
	{
		return;
	}

	if (humans < 5)
	{
		unsigned short numberbotsallow = 5 - humans;
		if (bots < numberbotsallow)
		{
			for (unsigned short i = bots; i < numberbotsallow; i++)
			{
				vEngineServer->ServerCommand(botadd);
			}
		}
		else
		{
			while (bots > numberbotsallow)
			{
				vEngineServer->ServerCommand(botkick);
				bots--;
			}
		}
	}
	else
	{
		for (unsigned short i = 0; i < bots; i++)
		{
			vEngineServer->ServerCommand(botkick);
		}
	}
}
