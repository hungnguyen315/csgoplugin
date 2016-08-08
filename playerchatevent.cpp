#include "playerchatevent.h"

void PlayerChatEvent::FireGameEvent(IGameEvent *event)
{
	short userid = event->GetInt("userid");
	const char *text = event->GetString("text");
	Msg("Player id %d say %s\n", userid, text);
}

int PlayerChatEvent::GetEventDebugID()
{
	return EVENT_DEBUG_ID_INIT;
}
