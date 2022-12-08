#include "twentySnaps.h"

void twentySnaps()
{
	Snapshot* mainSnap = GetProcessesInfo(); //creating the main snapshot
	Process* mainPrcListIndex = mainSnap->headprocess;
	DLL* mainDllListIndex = mainSnap->headprocess->headDLL;
	Sleep(1000); //1 sec pause
	for (int i = 0; i < 19; i++)
	{
		Snapshot* secondarySnap = GetProcessesInfo(); //creating second snapshot
		Process* secPrcListIndex = secondarySnap->headprocess;
		DLL* secDllListIndex = secondarySnap->headprocess->headDLL;
		while (secPrcListIndex != NULL) // going through the list of processes in both snapshots and comparing the names and id of the processes, if true adds the the process data to the main process. 
		{
			while(mainPrcListIndex!=NULL)
			{ 
				if (secPrcListIndex->ProcessId == mainPrcListIndex->ProcessId && strcmp(secPrcListIndex->ProcessName, mainPrcListIndex->ProcessName) == 0)
				{
					mainPrcListIndex->process_data.PageFaultCount += secPrcListIndex->process_data.PageFaultCount;
					mainPrcListIndex->process_data.PagefileUsage += secPrcListIndex->process_data.PagefileUsage;
					mainPrcListIndex->process_data.WorkingSetSize += secPrcListIndex->process_data.WorkingSetSize;
					mainPrcListIndex->process_data.QuotaPagedPoolUsage += secPrcListIndex->process_data.QuotaPagedPoolUsage;
					mainPrcListIndex->process_data.QuotaPeakPagedPoolUsage += secPrcListIndex->process_data.QuotaPagedPoolUsage;
					while (secDllListIndex != NULL)
					{
						while (mainDllListIndex != NULL) //checking if the dlls in the new snapshot exists in the main snapshot
						{
							if (strcmp(secDllListIndex->dllName, mainDllListIndex->dllName) == 0)
							{
								mainDllListIndex = mainDllListIndex->next;
							}
							else if (strcmp(secDllListIndex->dllName,mainDllListIndex->dllName)!=0) // if they do not exist, add a new dll structure with the data of the new dll to the main snapshots dlls list.
							{
								if (mainDllListIndex->next == NULL)
								{
									DLL* curr = (DLL*)malloc(sizeof(DLL));
									strcpy(curr->dllName, secDllListIndex->dllName);
									curr->position = secDllListIndex->position;
									curr->next = NULL;
									curr->prev = mainPrcListIndex->tailDLL;
									mainPrcListIndex->tailDLL->next = curr;
								}
								mainDllListIndex = mainDllListIndex->next;
							}
							
						}
						secDllListIndex = secDllListIndex->next;
					}
				}
				mainPrcListIndex = mainPrcListIndex->next;
			}
			secPrcListIndex = secPrcListIndex->next;
			mainPrcListIndex = mainSnap->headprocess;
		}
		free(secondarySnap); //freeing the secondary snapshot
		Sleep(1000); // 1 sec pause
	}
}