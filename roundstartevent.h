#ifndef ROUNDSTARTEVENT_H
#define ROUNDSTARTEVENT_H

#include "igameevents.h"

class CBaseEntity;
class RoundStartEvent : public IGameEventListener2
{
public:
	void FireGameEvent(IGameEvent *event);
	int GetEventDebugID();
};

#endif // ROUNDSTARTEVENT_H
