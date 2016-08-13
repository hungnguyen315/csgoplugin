#include "pluginutils.h"

extern CGlobalVars *globalVars;
extern IVEngineServer *vEngineServer;

// CBaseEntity
int m_iTeamNum_off;
int m_iPendingTeamNum_off;
int m_fFlags_off;

// CBasePlayer
int m_iHealth_off;
int m_fEffects_off;

// CCSPlayerResource
int m_iCompetitiveRanking_off;

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

void CreateMenu(bf_write* pBuffer, const char* szMessage, int nOptions, int iSecondsToStayOpen)
{
	//Assert(pBuffer);
 
	// Add option to bits
	int optionBits = 0;
	for(int i = 0; i < nOptions; i++)
		optionBits |= (1<<i);
 
	pBuffer->WriteShort(optionBits); // Write options
	pBuffer->WriteChar(iSecondsToStayOpen); // Seconds to stay open
	pBuffer->WriteByte(false); // We don't need to receive any more of this menu
	pBuffer->WriteString(szMessage); // Write the menu message
}
