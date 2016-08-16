#include "hookfunctions.h"
#include "tier0/dbg.h"

bool Hook_Weapon_CanUse(CBaseCombatWeapon *pWeapon, void *instance, void *org)
{
	Msg("Hooked\n");
	return ((bool (*)(CBaseCombatWeapon *))org)(pWeapon);
}