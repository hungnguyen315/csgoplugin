#include "playersayevent.h"

extern IVEngineServer *vEngineServer;

void PlayerSayEvent::FireGameEvent(IGameEvent *event)
{
	short userid = event->GetInt("userid");
	if (userid > 0)
	{
		const char *text = event->GetString("text");
		if (strncmp(text, "bet", 3) == 0)
		{

			edict_t *playerEdict = GetEdictByUserId(userid);
			if (strncmp(text + 4, "ct", 2) == 0)
			{
				Msg("Bet team ct\n");
			}
			else if (strncmp(text + 4, "t", 1) == 0)
			{
				Msg("Bet team t\n");
			}
			else
			{
				vEngineServer->ClientPrintf(playerEdict, "Wrong bet.");
			}
		}	
	}
}

int PlayerSayEvent::GetEventDebugID()
{
	return EVENT_DEBUG_ID_INIT;
}
