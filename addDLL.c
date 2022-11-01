#include "addDLL.h"


int Dcounter = 1;
DLL* Dhead = NULL;
DLL* Dtail = NULL;

void addDLL(DLL dll) //adding new dll struct to a linked list
{
	DLL* curr = (DLL*)malloc(sizeof(DLL));
	strcpy(curr->dllName, dll.dllName);
	curr->next = NULL;
	curr->prev = NULL;
	if (Dhead == NULL)
	{
		Dhead = curr;
		Dtail = curr;
		curr->position = Dcounter;
	}
	else
	{
		curr->prev = Dtail;
		Dtail->next = curr;
		Dtail = curr;
		Dcounter++;
		curr->position = Dcounter;
	}
}