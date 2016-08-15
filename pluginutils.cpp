#include "pluginutils.h"

extern CGlobalVars *globalVars;
extern IVEngineServer *vEngineServer;

// CBaseEntity
int m_iTeamNum_off;
int m_iPendingTeamNum_off;
int m_fFlags_off;
int m_nRenderMode_off;

// CBasePlayer
int m_iHealth_off;
int m_fEffects_off;

// CCSPlayerResource
int m_iCompetitiveRanking_off;

char botkickct[] = "bot_kick ct\n";
char botkickt[] = "bot_kick t\n";
char botaddct[] = "bot_add ct\n";
char botaddt[] = "bot_add t\n";

bool init_CCSPlayerResource_Props(SendTable *st)
{
	Msg("\n");
	Msg("###################################################\n");
	Msg("# CCSPlayerResource\n");
	Msg("###################################################\n");
	int num = 0;
	for (int i = 0; i < st->m_nProps; i++)
	{
		SendProp *sp = st->GetProp(i);
		const char *propName = sp->GetName();
		int propOffset = sp->GetOffset();
		Msg("Prop name: %s | Prop Offset: %d | Type: %d | IsSigned: %d\n", propName, propOffset, sp->GetType(), sp->IsSigned());
		if (strcmp(propName, "m_iCompetitiveRanking") == 0)
		{
			m_iCompetitiveRanking_off = propOffset;
			num++;
			continue;
		}
	}

	if (num == 1)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool init_CBaseEntity_Props(SendTable *st)
{
	Msg("\n");
	Msg("###################################################\n");
	Msg("# CBaseEntity\n");
	Msg("###################################################\n");
	int num = 0;
	for (int i = 0; i < st->m_nProps; i++)
	{
		SendProp *sp = st->GetProp(i);
		const char *propName = sp->GetName();
		int propOffset = sp->GetOffset();
		Msg("Prop name: %s | Prop Offset: %d | Type: %d | IsSigned: %d\n", propName, propOffset, sp->GetType(), sp->IsSigned());
		if (strcmp(propName, "m_iTeamNum") == 0)
		{
			m_iTeamNum_off = propOffset;
			num++;
			continue;
		}
		
		if (strcmp(propName, "m_iPendingTeamNum") == 0)
		{
			m_iPendingTeamNum_off = propOffset;
			num++;
			continue;
		}
		
		if (strcmp(propName, "m_fEffects") == 0)
		{
			m_fEffects_off = propOffset;
			num++;
			continue;
		}
		
		if (strcmp(propName, "m_nRenderMode") == 0)
		{
			m_nRenderMode_off = propOffset;
			num++;
			continue;
		}
	}

	if (num == 4)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool init_CBasePlayer_Props(SendTable *st)
{
	Msg("\n");
	Msg("###################################################\n");
	Msg("# CBasePlayer\n");
	Msg("###################################################\n");
	int num = 0;
	for (int i = 0; i < st->m_nProps; i++)
	{
		SendProp *sp = st->GetProp(i);
		const char *propName = sp->GetName();
		int propOffset = sp->GetOffset();
		Msg("Prop name: %s | Prop Offset: %d | Type: %d | IsSigned: %d\n", propName, propOffset, sp->GetType(), sp->IsSigned());
		if (strcmp(propName, "m_fFlags") == 0)
		{
			m_fFlags_off = propOffset;
			num++;
			continue;
		}
		
		if (strcmp(propName, "m_iHealth") == 0)
		{
			m_iHealth_off = propOffset;
			num++;
			continue;
		}
		
	}
	if (num == 2)
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
