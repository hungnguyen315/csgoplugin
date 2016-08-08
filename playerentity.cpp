#include "playerentity.h"

PlayerEntity::PlayerEntity()
{
	this->Reset();
}

void PlayerEntity::Set(unsigned int userid, unsigned short entityIndex)
{
	this->userid = userid;
	this->entityIndex = entityIndex;
}

void PlayerEntity::Reset()
{
	this->userid = 0;
	this->entityIndex = 0;
}

unsigned int PlayerEntity::GetUserId()
{
	return this->userid;
}

unsigned short PlayerEntity::GetEntityIndex()
{
	return this->entityIndex;
}
