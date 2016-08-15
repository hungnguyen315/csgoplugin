#include "playerspawnedevent.h"
#include "eiface.h"
#include "edict.h"
#include "const.h"
#include "cstrike15_usermessage_helpers.h"
#include "mrecipientfilter.h"

extern CGlobalVars *globalVars;
extern IVEngineServer *vEngineServer;
extern IServerGameEnts *serverGameEnts;

extern int m_fFlags_off;

void PlayerSpawnedEvent::FireGameEvent(IGameEvent *event)
{
	int userid = event->GetInt("userid");
	for (int i = 1; i <= globalVars->maxClients; i++)
	{
		edict_t *edict = globalVars->pEdicts + i;
		if (!edict || edict->IsFree())
			continue;
		
		CBaseEntity *entity = serverGameEnts->EdictToBaseEntity(edict);
		if (!entity)
			continue;
		
		if (vEngineServer->GetPlayerUserId(edict) != userid)
			continue;
		
		unsigned int *flags = (unsigned int *)((char *)entity + m_fFlags_off);
		if (*flags & FL_FAKECLIENT)
			continue;
		
		if (*flags & FL_CLIENT)
		{
			CCSUsrMsg_HudText *msg = (CCSUsrMsg_HudText *)g_Cstrike15UsermessageHelpers.GetPrototype(CS_UM_HudText)->New();
			msg->set_text("Welcome to my server. Hope you have a good day. Good luck and have fun!");
			MRecipientFilter filter;
			filter.AddRecipient(i);
			vEngineServer->SendUserMessage(static_cast<IRecipientFilter &>(filter), CS_UM_HudText, *msg);
			delete msg;
			break;
		}
	}
}

int PlayerSpawnedEvent::GetEventDebugID()
{
	return EVENT_DEBUG_ID_INIT;
}