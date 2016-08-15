#include "announcephaseendevent.h"
#include "eiface.h"
#include "edict.h"
#include "cstrike15_usermessage_helpers.h"
#include "mrecipientfilter.h"

extern CGlobalVars *globalVars;
extern IVEngineServer *vEngineServer;
extern IServerGameEnts *serverGameEnts;

extern int m_fFlags_off;

class CBasePlayer;

void AnnouncePhaseEndEvent::FireGameEvent(IGameEvent *event)
{
	MRecipientFilter filter;
	for (int i = 1; i <= globalVars->maxClients; i++)
	{
		edict_t *edict = globalVars->pEdicts + i;
		if (!edict || edict->IsFree())
			continue;
		
		CBasePlayer *player = (CBasePlayer *)serverGameEnts->EdictToBaseEntity(edict);
		if (!player)
			continue;
		
		unsigned int *flags = (unsigned int *)((char *)player + m_fFlags_off);
		if (*flags & FL_FAKECLIENT)
			continue;
		
		if (*flags & FL_CLIENT)
			filter.AddRecipient(i);
	}
	
	CCSUsrMsg_ServerRankRevealAll *msg = (CCSUsrMsg_ServerRankRevealAll *)g_Cstrike15UsermessageHelpers.GetPrototype(CS_UM_ServerRankRevealAll)->New();
	vEngineServer->SendUserMessage(static_cast<IRecipientFilter &>(filter), CS_UM_ServerRankRevealAll, *msg);
	delete msg;
}

int AnnouncePhaseEndEvent::GetEventDebugID()
{
	return EVENT_DEBUG_ID_INIT;
}