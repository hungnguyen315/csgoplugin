#ifndef PLAYERDISCONNECTEVENT_H
#define PLAYERDISCONNECTEVENT_H

#include "igameevents.h"
#include "edict.h"

class PlayerDisconnectEvent : public IGameEventListener2
{
public:
	void FireGameEvent(IGameEvent *event);
	int GetEventDebugID();
};

#endif // PLAYERDISCONNECTEVENT_H
