#include "hookmanager.h"
#include "stdint.h"
#include "unistd.h"
#include "sys/mman.h"

int pagesize = sysconf(_SC_PAGE_SIZE);
int pagemask = ~(pagesize - 1);

void *AddHook(void *instance, void *hook, int offset)
{
	intptr_t vtable = *(intptr_t *)instance;
	intptr_t entry = vtable + sizeof(intptr_t) * offset;
	intptr_t original = *(intptr_t *)entry;
	mprotect((void *)(entry & pagemask), pagesize, PROT_READ|PROT_WRITE|PROT_EXEC);
	*entry = (intptr_t)hook;
	mprotect((void *)(entry & pagemask), pagesize, PROT_READ|PROT_EXEC);
	return original;
}