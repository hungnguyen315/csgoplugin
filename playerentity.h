#ifndef PLAYERENTITY_H
#define PLAYERENTITY_H

class PlayerEntity
{
private:
	unsigned int userid;
	unsigned short entityIndex;

public:
	PlayerEntity();
	void Set(unsigned int userid, unsigned short entityIndex);
	void Reset();
	unsigned int GetUserId();
	unsigned short GetEntityIndex();
};

#endif // PLAYERENTITY_H
