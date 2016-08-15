#include "playerspawnevent.h"
/*#include "eiface.h"
#include "edict.h"

class CBaseEntity;

extern CGlobalVars *globalVars;
extern IVEngineServer *vEngineServer;
extern IServerGameEnts *serverGameEnts;

extern int m_nRenderMode_off;
extern int m_fEffects_off;*/

void PlayerSpawnEvent::FireGameEvent(IGameEvent *event)
{
	/*int userid = event->GetInt("userid");
	for (int i = 1; i < globalVars->maxClients; i++)
	{
		edict_t *edict = globalVars->pEdicts + i;
		if (!edict || edict->IsFree())
		{
			continue;
		}

		CBaseEntity *entity = serverGameEnts->EdictToBaseEntity(edict);
		if (!entity)
		{
			continue;
		}
		
		if (vEngineServer->GetPlayerUserId(edict) != userid)
		{
			continue;
		}
		unsigned int *effect = (unsigned int *)((char *)entity + m_fEffects_off);
		//unsigned int *renderMode = (unsigned int *)((char *)entity + m_nRenderMode_off);
		//Msg("Render mode is %d.\n", *renderMode);
		//*effect |= EF_NODRAW;
		//*renderMode &= ~kRenderNormal;
		//*renderMode |= kRenderNone;
		break;
	}*/
}

int PlayerSpawnEvent::GetEventDebugID()
{
	return EVENT_DEBUG_ID_INIT;
}
