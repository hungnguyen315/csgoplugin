#ifndef ANNOUNCEPHASEENDEVENT_H
#define ANNOUNCEPHASEENDEVENT_H

#include "igameevents.h"

class AnnouncePhaseEndEvent : public IGameEventListener2
{
	void FireGameEvent(IGameEvent *event);
	int GetEventDebugID();
};

#endif // ANNOUNCEPHASEENDEVENT_H