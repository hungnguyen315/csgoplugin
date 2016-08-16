#include "hookfunctions.h"
#include "tier0/dbg.h"

bool HookFunctions::Hook_Weapon_CanUse(CBaseCombatWeapon *pWeapon)
{
	Msg("Hooked\n");
	return this->org_Weapon_CanUse(pWeapon);
}