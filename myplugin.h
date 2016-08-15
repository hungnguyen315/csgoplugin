#ifndef MYPLUGIN_H
#define MYPLUGIN_H

#include "engine/iserverplugin.h"
#include "igameevents.h"
#include "eiface.h"
#include "iplayerinfo.h"
#include "toolframework/itoolentity.h"

class MyPlugin : public IServerPluginCallbacks
{
public:
	// Plugin state
	bool Load(CreateInterfaceFn interfaceFactory, CreateInterfaceFn gameServerFactory);
	void Unload();
	void Pause();
	void UnPause();
	const char *GetPluginDescription();
	
	// Server Events
	void LevelInit(char const *pMapName);
	void ServerActivate(edict_t *pEdictList, int edictCount, int clientMax);
	void GameFrame(bool simulating);
	void LevelShutdown();
	void OnQueryCvarValueFinished(QueryCvarCookie_t iCookie, edict_t *pPlayerEntity, EQueryCvarValueStatus eStatus, const char *pCvarName, const char *pCvarValue);
	void OnEdictAllocated(edict_t *edict);
	void OnEdictFreed(const edict_t *edict);
	
	// Clients
	PLUGIN_RESULT ClientConnect(bool *bAllowConnect, edict_t *pEntity, const char *pszName, const char *pszAddress, char *reject, int maxrejectlen);
	void ClientFullyConnect(edict_t *pEntity);
	void ClientPutInServer(edict_t *entity, const char *playername);
	void ClientActive(edict_t *pEntity);
	void ClientDisconnect(edict_t *pEntity);
	void SetCommandClient(int index);
	void ClientSettingsChanged(edict_t *pEdict);
	PLUGIN_RESULT ClientCommand(edict_t *pEntity, const CCommand &args);
	PLUGIN_RESULT NetworkIDValidated(const char *pszUserName, const char *pszNetworkID);
};

MyPlugin g_MyPlugin;
EXPOSE_SINGLE_INTERFACE_GLOBALVAR(MyPlugin, IServerPluginCallbacks, INTERFACEVERSION_ISERVERPLUGINCALLBACKS, g_MyPlugin);

#endif // MYPLUGIN_H
