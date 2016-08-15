#include "playersayevent.h"

void PlayerSayEvent::FireGameEvent(IGameEvent *event)
{
	const char *text = event->GetString("text");
	if (strcmp(text, "!test") == 0)
	{
		
	}
}

int PlayerSayEvent::GetEventDebugID()
{
	return EVENT_DEBUG_ID_INIT;
}
