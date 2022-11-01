#include "freeMemory.h"

void freeMemory()
{
	Snapshot* Sindex = Shead;
	Process* Pindex = Phead;
	DLL* Dindex = Dhead;
	while (Sindex != NULL) //freeing snapshots list
	{
		free(Sindex);
		Sindex = Sindex++;
	}
	while (Pindex != NULL) //freeing processes list
	{
		free(Pindex);
		Pindex = Pindex++;
	}
	while (Dindex != NULL) //freeing dlls list
	{
		free(Dindex);
		Dindex = Dindex++;
	}
}