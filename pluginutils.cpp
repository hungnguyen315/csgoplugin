#include "pluginutils.h"

extern CGlobalVars *globalVars;
extern IVEngineServer *vEngineServer;

edict_t *GetEdictByUserId(int userid)
{
	for (int i = 1; i <= globalVars->maxClients; i++)
	{
		edict_t *edict = globalVars->pEdicts + i;
		if (vEngineServer->GetPlayerUserId(edict) == userid)
		{
			return edict;
		}
		/*if (edict && !edict->IsFree() && strcmp(edict->GetClassName(), "player") == 0)
		{
			if (vEngineServer->GetPlayerUserId(edict) == userid)
			{
				return edict;
			}
		}*/
	}
}
