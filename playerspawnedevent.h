#ifndef PLAYERSPAWNEDEVENT_H
#define PLAYERSPAWNEDEVENT_H

#include "igameevents.h"

class PlayerSpawnedEvent : public IGameEventListener2
{
public:
	void FireGameEvent(IGameEvent *event);
	int GetEventDebugID();
};

#endif // PLAYERSPAWNEDEVENT_H