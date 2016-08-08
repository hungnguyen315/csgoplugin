#include "myplugin.h"

IVEngineServer *vEngineServer = NULL;
IPlayerInfoManager *playerInfoManager = NULL;
IGameEventManager2 *gameEventManager2 = NULL;
IServerGameEnts *serverGameEnts = NULL;
CGlobalVars *globalVars = NULL;
IServerTools *serverTools = NULL;
IServerPluginHelpers *serverPluginHelpers = NULL;

PlayerDeathEvent *playerDeathEvent = NULL;
PlayerChatEvent *playerChatEvent = NULL;

bool MyPlugin::Load(CreateInterfaceFn interfaceFactory, CreateInterfaceFn gameServerFactory)
{
	serverGameEnts = (IServerGameEnts *)gameServerFactory(INTERFACEVERSION_SERVERGAMEENTS, NULL);
	if (!serverGameEnts)
	{
		Warning("Unable to load IServerGameEnts.\n");
		return false;
	}

	playerInfoManager = (IPlayerInfoManager *)gameServerFactory(INTERFACEVERSION_PLAYERINFOMANAGER, NULL);
	if (playerInfoManager)
	{
		globalVars = playerInfoManager->GetGlobalVars();
	}
	else
	{
		Warning("Unable to load IPlayerInfoManager.\n");
		return false;
	}

	gameEventManager2 = (IGameEventManager2 *)interfaceFactory(INTERFACEVERSION_GAMEEVENTSMANAGER2, NULL);
	if (!gameEventManager2)
	{
		Warning("Unable to load IGameEventManager2.\n");
		return false;
	}

	vEngineServer = (IVEngineServer *)interfaceFactory(INTERFACEVERSION_VENGINESERVER, NULL);
	if (!vEngineServer)
	{
		Warning("Unable to load IVEngineServer.\n");
		return false;
	}

	serverTools = (IServerTools *)gameServerFactory(VSERVERTOOLS_INTERFACE_VERSION, NULL);
	if (!serverTools)
	{
		Warning("Unable to load IServerTools.\n");
		return false;
	}

	serverPluginHelpers = (IServerPluginHelpers *)interfaceFactory(INTERFACEVERSION_ISERVERPLUGINHELPERS, NULL);
	if (!serverPluginHelpers)
	{
		Warning("Unable to load IServerPluginHelpers.\n");
		return false;
	}

	playerDeathEvent = new PlayerDeathEvent();
	playerChatEvent = new PlayerChatEvent();

	return true;
}

void MyPlugin::Unload()
{
	gameEventManager2->RemoveListener(playerDeathEvent);
	delete playerDeathEvent;
	gameEventManager2->RemoveListener(playerChatEvent);
	delete playerChatEvent;
}

void MyPlugin::Pause()
{
	
}

void MyPlugin::UnPause()
{
	
}

const char *MyPlugin::GetPluginDescription()
{
	return "MyPlugin version 1.0 by Hung Nguyen";
}

void MyPlugin::LevelInit(char const *pMapName)
{
	gameEventManager2->AddListener(playerDeathEvent, "player_death", true);
	gameEventManager2->AddListener(playerChatEvent, "player_chat", true);
}

void MyPlugin::ServerActivate(edict_t *pEdictList, int edictCount, int clientMax)
{
	
}

void MyPlugin::GameFrame(bool simulating)
{
	
}

void MyPlugin::LevelShutdown()
{
	gameEventManager2->RemoveListener(playerDeathEvent);
	gameEventManager2->RemoveListener(playerChatEvent);
}

void MyPlugin::OnQueryCvarValueFinished(QueryCvarCookie_t iCookie, edict_t *pPlayerEntity, EQueryCvarValueStatus eStatus, const char *pCvarName, const char *pCvarValue)
{
	
}

void MyPlugin::OnEdictAllocated(edict_t *edict)
{
	
}

void MyPlugin::OnEdictFreed(const edict_t *edict)
{
	
}


PLUGIN_RESULT MyPlugin::ClientConnect(bool *bAllowConnect, edict_t *pEntity, const char *pszName, const char *pszAddress, char *reject, int maxrejectlen)
{
	return PLUGIN_CONTINUE;
}

void MyPlugin::ClientFullyConnect(edict_t *pEntity)
{
	Msg("ClientFullyConnect\n");
	Msg("%s\n\n", pEntity->GetClassName());
}

void MyPlugin::ClientPutInServer(edict_t *entity, const char *playername)
{
	Msg("ClientPutInServer\n");
	Msg("%s\n\n", entity->GetClassName());
}

void MyPlugin::ClientActive(edict_t *pEntity)
{
	Msg("ClientActive\n");
	Msg("%s\n\n", pEntity->GetClassName());	
}

void MyPlugin::ClientDisconnect(edict_t *pEntity)
{
	Msg("ClientDisconnect\n");
	Msg("%s\n\n", pEntity->GetClassName());
}

void MyPlugin::SetCommandClient(int index)
{
	
}

void MyPlugin::ClientSettingsChanged(edict_t *pEdict)
{
	
}

PLUGIN_RESULT MyPlugin::ClientCommand(edict_t *pEntity, const CCommand &args)
{
	return PLUGIN_CONTINUE;
}

PLUGIN_RESULT MyPlugin::NetworkIDValidated(const char *pszUserName, const char *pszNetworkID)
{
	return PLUGIN_CONTINUE;
}
