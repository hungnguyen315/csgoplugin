#ifndef PRECIPIENTFILTER_H
#define PRECIPIENTFILTER_H

#include "irecipientfilter.h"
#include "edict.h"

class PRecipientFilter : public IRecipientFilter
{
public:
	PRecipientFilter();
	~PRecipientFilter() {}
public:
	bool IsReliable() const;
	bool IsInitMessage() const;
	int GetRecipientCount() const;
	int GetRecipientIndex(int slot) const;
public:
	void AddPlayer(const int iPlayer);
	void SetToReliable(bool isreliable);
	void SetToInit(bool isinitmsg);
	void Reset();
private:
	bool m_IsReliable;
	bool m_IsInitMessage;
	int m_Size;
	int *m_Players;
};

#endif // PRECIPIENTFILTER_H
