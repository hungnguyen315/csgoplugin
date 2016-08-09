#include "playerbet.h"

PlayerBet::PlayerBet()
{
	this->Reset();
}

void PlayerBet::Reset()
{
	this->status = false;
	this->amount = 0;
}
