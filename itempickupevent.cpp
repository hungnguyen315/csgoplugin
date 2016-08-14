#include "itempickupevent.h"

void ItemPickupEvent::FireGameEvent(IGameEvent *event)
{
	//const char *weapon = event->GetString("item");
	//Msg("%s\n", weapon);
}

int ItemPickupEvent::GetEventDebugID()
{
	return EVENT_DEBUG_ID_INIT;
}
