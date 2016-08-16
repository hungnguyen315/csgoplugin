#ifndef HOOKFUNCTIONS_H
#define HOOKFUNCTIONS_H

class CBaseCombatWeapon;

typedef bool (*fn_Weapon_CanUse)(CBaseCombatWeapon *);

class HookFunctions
{
public:
	fn_Weapon_CanUse org_Weapon_CanUse;
	bool Hook_Weapon_CanUse(CBaseCombatWeapon *pWeapon);
};

#endif // HOOKFUNCTIONS_H