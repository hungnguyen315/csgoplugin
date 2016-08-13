#include "mrecipientfilter.h"
 
extern IVEngineServer		*engine;
extern CGlobalVars		*gpGlobals;
 
int MRecipientFilter::GetRecipientCount() const
{
	return m_Recipients.Count();
}
 
int MRecipientFilter::GetRecipientIndex(int slot) const
{
	if(slot < 0 || slot >= GetRecipientCount())
		return -1;
 
	return m_Recipients[slot];
}
 
void MRecipientFilter::AddAllPlayers()
{
	/*m_Recipients.RemoveAll();
 
	for(int i = 1; i <= gpGlobals->maxClients; i++)
	{
		edict_t *pPlayer = engine->PEntityOfEntIndex(i);
 
		if(!pPlayer || pPlayer->IsFree())
			continue;
 
		m_Recipients.AddToTail(i);
	}*/
} 
void MRecipientFilter::AddRecipient(int iPlayer)
{
	// Return if the recipient is already in the vector
	if(m_Recipients.Find(iPlayer) != m_Recipients.InvalidIndex())
		return;
 
	// Make sure the player is valid
	//edict_t* pPlayer = engine->PEntityOfEntIndex(iPlayer);
	//if(!pPlayer || pPlayer->IsFree())
	//	return;
 
	m_Recipients.AddToTail(iPlayer);
}
