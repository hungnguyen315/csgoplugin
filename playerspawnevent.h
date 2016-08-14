#ifndef PLAYERSPAWNEVENT_H
#define PLAYERSPAWNEVENT_H

#include "igameevents.h"

class PlayerSpawnEvent : public IGameEventListener2
{
public:
	void FireGameEvent(IGameEvent *event);
	int GetEventDebugID();
};

#endif // PLAYERSPAWNEVENT_H
