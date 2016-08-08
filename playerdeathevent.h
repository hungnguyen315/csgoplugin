#ifndef PLAYERDEATHEVENT_H
#define PLAYERDEATHEVENT_H

#include "igameevents.h"

class PlayerDeathEvent : public IGameEventListener2
{
public:
	void FireGameEvent(IGameEvent *event);
	int GetEventDebugID();
};

#endif // PLAYERDEATHEVENT_H
