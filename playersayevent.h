#ifndef PLAYERSAYEVENT_H
#define PLAYERSAYEVENT_H

#include "igameevents.h"
#include "edict.h"
#include "eiface.h"
#include "pluginutils.h"

class PlayerSayEvent : public IGameEventListener2
{
public:
	void FireGameEvent(IGameEvent *event);
	int GetEventDebugID();
};

#endif // PLAYERSAYEVENT_H
