#include "myplugin.h"

IVEngineServer *vEngineServer = NULL;
IPlayerInfoManager *playerInfoManager = NULL;
IGameEventManager2 *gameEventManager2 = NULL;
IServerGameEnts *serverGameEnts = NULL;
CGlobalVars *globalVars = NULL;
IServerTools *serverTools = NULL;
IServerPluginHelpers *serverPluginHelpers = NULL;
IServerGameDLL *serverGameDLL = NULL;

PlayerDeathEvent *playerDeathEvent = NULL;
PlayerSayEvent *playerSayEvent = NULL;
PlayerConnectEvent *playerConnectEvent = NULL;
PlayerDisconnectEvent *playerDisconnectEvent = NULL;
RoundStartEvent *roundStartEvent = NULL;

bool MyPlugin::Load(CreateInterfaceFn interfaceFactory, CreateInterfaceFn gameServerFactory)
{
	serverGameDLL = (IServerGameDLL *)gameServerFactory(INTERFACEVERSION_SERVERGAMEDLL, NULL);
	if (!serverGameDLL)
	{
		Warning("Unable to load IServerGameDLL.\n");
		return false;
	}

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
	playerSayEvent = new PlayerSayEvent();
	playerConnectEvent = new PlayerConnectEvent();
	playerDisconnectEvent = new PlayerDisconnectEvent();
	roundStartEvent = new RoundStartEvent();

	return true;
}

void MyPlugin::Unload()
{
	gameEventManager2->RemoveListener(playerDeathEvent);
	delete playerDeathEvent;
	gameEventManager2->RemoveListener(playerSayEvent);
	delete playerSayEvent;
	gameEventManager2->RemoveListener(playerConnectEvent);
        delete playerConnectEvent;
	gameEventManager2->RemoveListener(playerDisconnectEvent);
        delete playerDisconnectEvent;
	gameEventManager2->RemoveListener(roundStartEvent);
        delete roundStartEvent;
}

void MyPlugin::Pause()
{
	
}

void MyPlugin::UnPause()
{
	
}

const char *MyPlugin::GetPluginDescription()
{
	return "MyPlugin version 1.0 by hungnmcoder";
}

void MyPlugin::LevelInit(char const *pMapName)
{
	gameEventManager2->AddListener(playerDeathEvent, "player_death", true);
	gameEventManager2->AddListener(playerSayEvent, "player_say", true);
	gameEventManager2->AddListener(playerConnectEvent, "player_connect", true);
	gameEventManager2->AddListener(playerDisconnectEvent, "player_disconnect", true);
	gameEventManager2->AddListener(roundStartEvent, "round_start", true);
}

void MyPlugin::ServerActivate(edict_t *pEdictList, int edictCount, int clientMax)
{
	ServerClass *serverClass = serverGameDLL->GetAllServerClasses();
	while (serverClass)
	{
		const char *className = serverClass->GetName();
		if (strcmp(className, "CBaseEntity") == 0)
		{
			SendTable *st = serverClass->m_pTable;
			for (int i = 0; i < st->m_nProps; i++)
			{
				SendProp *sp = st->GetProp(i);
				Msg("Prop name: %s. Prop Offset: %d.\n", sp->GetName(), sp->GetOffset());
			}
		}
		serverClass = serverClass->m_pNext;
	}	
}

void MyPlugin::GameFrame(bool simulating)
{
	
}

void MyPlugin::LevelShutdown()
{
	gameEventManager2->RemoveListener(playerDeathEvent);
	gameEventManager2->RemoveListener(playerSayEvent);
	gameEventManager2->RemoveListener(playerConnectEvent);
	gameEventManager2->RemoveListener(playerDisconnectEvent);
	gameEventManager2->RemoveListener(roundStartEvent);
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

}

void MyPlugin::ClientPutInServer(edict_t *entity, const char *playername)
{

}

void MyPlugin::ClientActive(edict_t *pEntity)
{

}

void MyPlugin::ClientDisconnect(edict_t *pEntity)
{

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
