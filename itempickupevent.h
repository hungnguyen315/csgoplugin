#ifndef ITEMPICKUPEVENT_H
#define ITEMPICKUPEVENT_H

#include "igameevents.h"

class ItemPickupEvent : public IGameEventListener2
{
public:
	void FireGameEvent(IGameEvent *event);
	int GetEventDebugID();
};

#endif // ITEMPICKUPEVENT_H
