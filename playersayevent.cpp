#include "playersayevent.h"

extern IVEngineServer *vEngineServer;

void PlayerSayEvent::FireGameEvent(IGameEvent *event)
{

}

int PlayerSayEvent::GetEventDebugID()
{
	return EVENT_DEBUG_ID_INIT;
}
