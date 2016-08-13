#include "precipientfilter.h"

extern CGlobalVars *globalVars;

PRecipientFilter::PRecipientFilter()
{
	this->m_IsReliable = false;
	this->m_IsInitMessage = false;
	this->m_Size = 0;
	this->m_Players[globalVars->maxClients];
}

bool PRecipientFilter::IsReliable() const
{
	return this->m_IsReliable;
}

bool PRecipientFilter::IsInitMessage() const
{
	return this->m_IsInitMessage;
}

int PRecipientFilter::GetRecipientCount() const
{
	return this->m_Size;
}

int PRecipientFilter::GetRecipientIndex(int slot) const
{
	if (slot >= 0 && slot < this->m_Size)
	{
		return this->m_Players[slot];
	}
	return -1;
}

void PRecipientFilter::SetToInit(bool isinitmsg)
{
	this->m_IsInitMessage = isinitmsg;
}

void PRecipientFilter::SetToReliable(bool isreliable)
{
	this->m_IsReliable = isreliable;
}

void PRecipientFilter::AddPlayer(const int iPlayer)
{
	this->m_Players[this->m_Size++] = iPlayer;
}

void PRecipientFilter::Reset()
{
	this->m_IsReliable = false;
	this->m_IsInitMessage = false;
	this->m_Size = 0;
}
