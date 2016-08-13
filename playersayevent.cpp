#include "playersayevent.h"

extern CGlobalVars *globalVars;
extern IVEngineServer *vEngineServer;
extern IServerGameEnts *serverGameEnts;
//extern CCstrike15UsermessageHelpers *g_Cstrike15UsermessageHelpers;
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
				const int userid = event->GetInt("userid");
				if (vEngineServer->GetPlayerUserId(edict) == userid)
				{
					CBaseEntity *entity = serverGameEnts->EdictToBaseEntity(edict);
					if (entity)
					{
						int optionBits = 0;
						for(int i = 0; i < 3; i++)
						{
							optionBits |= (1<<i);
						}

						CCSUsrMsg_ShowMenu *msg = (CCSUsrMsg_ShowMenu *)g_Cstrike15UsermessageHelpers.GetPrototype(CS_UM_ShowMenu)->New();
						msg->set_bits_valid_slots(optionBits);
						msg->set_display_time(10);
						//msg->set_flags(false);
						msg->set_menu_string("->1. Say hello\n->2. Say bye\n->3. Exit");
						MRecipientFilter filter;
						filter.AddRecipient(i);
						vEngineServer->SendUserMessage(static_cast<IRecipientFilter &>(filter), CS_UM_ShowMenu, *msg);
						delete msg;
					
					}
					break;
				}
			}
		}
	}
}

int PlayerSayEvent::GetEventDebugID()
{
	return EVENT_DEBUG_ID_INIT;
}
