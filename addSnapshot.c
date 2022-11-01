#include "addSnapshot.h"

int Scounter = 1;

Snapshot* Shead;
Snapshot* Stail;


Snapshot* addSnapshot(Snapshot snp) //adding new anpshot struct to a linked list
{
	Snapshot* curr = (Snapshot*)malloc(sizeof(Snapshot));
	curr->headprocess = snp.headprocess;
	curr->tailprocess = snp.tailprocess;
	time_t t;
	time(&t);
	struct tm* timeinfo;
	timeinfo = localtime(&t);
	sprintf(curr->time, "%d%d%d- %d:%d:%d", timeinfo->tm_year + 1900, timeinfo->tm_mon + 1, timeinfo->tm_mday, timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);

	curr->next = NULL;
	curr->prev = NULL;
	if (Shead == NULL)
	{
		Shead = curr;
		Stail = curr;
		curr->position = Scounter;
	}
	else
	{
		curr->prev = Stail;
		Stail->next = curr;
		Stail = curr;
		Scounter++;
		curr->position = Scounter;
	}
	return curr;
}
