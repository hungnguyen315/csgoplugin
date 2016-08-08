#include "playerdeathevent.h"

void PlayerDeathEvent::FireGameEvent(IGameEvent *event)
{
	Msg("Player dead\n");
}

int PlayerDeathEvent::GetEventDebugID()
{
	return EVENT_DEBUG_ID_INIT;
}
