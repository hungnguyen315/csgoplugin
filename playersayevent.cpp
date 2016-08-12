#include "playersayevent.h"

extern CGlobalVars *globalVars;
extern IVEngineServer *vEngineServer;
extern IServerGameEnts *serverGameEnts;
extern int m_fEffects_off;

void PlayerSayEvent::FireGameEvent(IGameEvent *event)
{
	const char *text = event->GetString("text");
	if (strcmp(text, "!bc") == 0)
	{
		for (unsigned short i = 1; i <= globalVars->maxClients; i++)
		{
			edict_t *edict = globalVars->pEdicts + i;
			if (edict && !edict->IsFree() && (strcmp(edict->GetClassName(), "player") == 0))
			{
				CBaseEntity *entity = serverGameEnts->EdictToBaseEntity(edict);
				if (entity)
				{
					*(int *)((char *)entity + m_fEffects_off) |= EF_MAX_BITS;
				}
			}
		}
	}
}

int PlayerSayEvent::GetEventDebugID()
{
	return EVENT_DEBUG_ID_INIT;
}
