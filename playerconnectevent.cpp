#include "playerconnectevent.h"
#include "sys/mman.h"
#include "eiface.h"
#include "edict.h"
#include "stdint.h"

class CBasePlayer;
class CBaseCombatWeapon;

extern CGlobalVars *globalVars;
extern IVEngineServer *vEngineServer;
extern IServerGameEnts *serverGameEnts;
extern int pagesize;

void *pageof(void *p)
{
	return (void *)((intptr_t)p & ~(pagesize - 1));
}
bool Hook_Weapon_CanSwitchTo(CBaseCombatWeapon *weapon)
{
	Msg("Hooked\n");
	return false;
}

void PlayerConnectEvent::FireGameEvent(IGameEvent *event)
{
	int userid = event->GetInt("userid");
	for (int i = 1; i <= globalVars->maxClients; i++)
	{
		edict_t *edict = globalVars->pEdicts + i;
		if (!edict || edict->IsFree())
			continue;
		
		CBasePlayer *player = (CBasePlayer *)serverGameEnts->EdictToBaseEntity(edict);
		if (!player)
			continue;
		
		if (vEngineServer->GetPlayerUserId(edict) != userid)
			continue;
		
		intptr_t vtable = *(intptr_t *)player;
		intptr_t entry = vtable + sizeof(intptr_t) * 287;
		intptr_t original = *(intptr_t *)entry;
		mprotect(pageof((void *)entry), pagesize, PROT_READ|PROT_WRITE|PROT_EXEC);
		*((intptr_t*)entry) = (intptr_t)Hook_Weapon_CanSwitchTo;
		mprotect(pageof((void *)entry), pagesize, PROT_READ|PROT_EXEC);
		
		/*void **base = *(void ***)player;
		uint32_t addressofcall = (uint32_t)base[287];
		uint32_t addressofnextinstruction = addressofcall + 5;
		uint32_t calloffset = (uint32_t)Hook_Weapon_CanSwitchTo - addressofnextinstruction;
		mprotect(pageof((void *)(addressofcall + 1)), pagesize, PROT_WRITE|PROT_EXEC|PROT_READ);
		memcpy((void*)(addressofcall + 1), (void *)&calloffset, 4);*/
	}
}

int PlayerConnectEvent::GetEventDebugID()
{
	return EVENT_DEBUG_ID_INIT;
}
