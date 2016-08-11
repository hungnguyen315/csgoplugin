#ifndef ROUNDSTARTEVENT_H
#define ROUNDSTARTEVENT_H

#include "igameevents.h"
#include "edict.h"
#include "eiface.h"
#include "const.h"
#include "pluginutils.h"

class CBaseEntity;
class RoundStartEvent : public IGameEventListener2
{
public:
	void FireGameEvent(IGameEvent *event);
	int GetEventDebugID();
};

#endif // ROUNDSTARTEVENT_H
