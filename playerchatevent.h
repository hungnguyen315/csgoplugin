#ifndef PLAYERCHATEVENT_H
#define PLAYERCHATEVENT_H

#include "igameevents.h"

class PlayerChatEvent : public IGameEventListener2
{
public:
	void FireGameEvent(IGameEvent *event);
	int GetEventDebugID();
};

#endif // PLAYERCHATEVENT_H
