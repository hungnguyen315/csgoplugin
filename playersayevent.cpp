#include "playersayevent.h"
/*#include "sys/mman.h"

extern CGlobalVars *globalVars;
extern IVEngineServer *vEngineServer;
extern IServerGameEnts *serverGameEnts;
//extern CCstrike15UsermessageHelpers *g_Cstrike15UsermessageHelpers;
extern int m_fEffects_off;

class CBaseCombatWeapon;

typedef bool (*fn_IsMoving)();
fn_IsMoving org_IsMoving;
bool Hook_IsMoving()
{
	Msg("Custom IsMoving fire.\n");
	return org_IsMoving();
}*/

void PlayerSayEvent::FireGameEvent(IGameEvent *event)
{
	/*const char *text = event->GetString("text");
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
						void **base = *(void ***)entity;
						//mprotect(&base[285], 4, PAGE_EXECUTE_READWRITE, &oldProtection);
						org_IsMoving = (fn_IsMoving)&base[80];
						
						mprotect(&entity, 640, PROT_READ | PROT_WRITE | PROT_EXEC);
						base[80] = (void *)&Hook_IsMoving;


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
	}*/
}

int PlayerSayEvent::GetEventDebugID()
{
	return EVENT_DEBUG_ID_INIT;
}
