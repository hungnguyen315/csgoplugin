#ifndef PLAYERCONNECTEVENT_H
#define PLAYERCONNECTEVENT_H

#include "igameevents.h"

class PlayerConnectEvent : public IGameEventListener2
{
public:
	void FireGameEvent(IGameEvent *event);
	int GetEventDebugID();
};

#endif // PLAYERCONNECTEVENT_H
