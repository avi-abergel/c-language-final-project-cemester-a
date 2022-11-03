#include "addProcess.h"



int Pcounter = 1;

Process* Ptail = NULL;
Process* Phead = NULL;

void addProcess(Process prc) //adding new process struct to a linked list
{
	Process* curr = (Process*)malloc(sizeof(Process));
	curr->ProcessId = prc.ProcessId;
	strcpy(curr->ProcessName, prc.ProcessName);
	strcpy(curr->time, prc.time);
	curr->process_data = prc.process_data;
	curr->headDLL = prc.headDLL;
	curr->tailDLL = prc.tailDLL;
	strcpy(curr->time, prc.time);
	curr->next = NULL;;
	curr->prev = NULL;
	if (Phead == NULL)
	{
		Phead = curr;
		Ptail = curr;
		curr->position = Pcounter;
	}
	else
	{
		curr->prev = Ptail;
		Ptail->next = curr;
		Ptail = curr;
		Pcounter++;
		curr->position = Pcounter;
	}
}

void swapPrc(Process* prc)  //swaping items in list
{
	int positionSwap = 0;
	if (prc == NULL)
	{
		return;
	}
	else if (prc->next == NULL)
	{
		return;
	}
	else if (prc == Phead && prc->next == Ptail)
	{
		prc->position = positionSwap;
		prc->position = prc->next->position;
		prc->next->position = positionSwap;
		prc->next = NULL;
		prc->prev = Ptail;
		Ptail->prev = NULL;
		Ptail->next = prc;
		Ptail = prc;
		Phead = prc->prev;
	}
	else if (prc == Phead && prc->next != NULL)
	{
		prc->position = positionSwap;
		prc->position = prc->next->position;
		prc->next->position = positionSwap;
		prc->next = prc->next->next;
		prc->next->prev->next = prc;
		prc->next->prev->prev = NULL;
		prc->prev = prc->next->prev;
		prc->next->prev = prc;
	}
	else if (prc->next == Ptail)
	{
		prc->position = positionSwap;
		prc->position = prc->next->position;
		prc->next->position = positionSwap;
		prc->prev->next = prc->next;
		prc->next->prev = prc->prev;
		prc->next->next = prc;
		prc->prev = prc->next;
		prc->next = NULL;
		Ptail = prc;
	}
	else
	{
		//regular swap
		prc->position = positionSwap;
		prc->position = prc->next->position;
		prc->next->position = positionSwap;
		prc->prev->next = prc->next;
		prc->next->prev = prc->prev;
		prc->next->next->prev = prc;
		prc->prev = prc->next;
		prc->next = prc->next->next;
		prc->prev->next = prc;
	}
}

void sort() //bubble sort 
{
	Process* curr = Phead;
	if (!curr)
	{
		return;
	}
	char change = 1;
	while (change != 0)
	{
		change = 0;
		while (curr != NULL)
		{
			if (curr->next != NULL && curr->tailDLL->position > curr->next->tailDLL->position)
			{

				swapPrc(curr);
				change++;
			}
			curr = curr->next;
		}
		curr = Phead;
	}
}

