#include "twentySnaps.h"

void twentySnaps()
{
	Snapshot* mainSnap = GetProcessesInfo(); //creating the main snapshot
	Process* mainPrcListIndex = mainSnap->headprocess;
	Sleep(1000); //1 sec pause
	for (int i = 0; i < 19; i++)
	{
		Snapshot* secondarySnap = GetProcessesInfo(); //creating second snapshot
		Process* secPrcListIndex = secondarySnap->headprocess;
		while (secPrcListIndex != NULL) // going through the list of processes in both snapshots and comparing the data 
		{
			if (secPrcListIndex->ProcessId == mainPrcListIndex->ProcessId)
			{
				if (secPrcListIndex->process_data.PageFaultCount != mainPrcListIndex->process_data.PageFaultCount) //if the data is different, it adds up to the data of the main snapshot
				{
					mainPrcListIndex->process_data.PageFaultCount = mainPrcListIndex->process_data.PageFaultCount + secPrcListIndex->process_data.PageFaultCount;
				}
				if (secPrcListIndex->process_data.PagefileUsage != mainPrcListIndex->process_data.PagefileUsage)
				{
					mainPrcListIndex->process_data.PagefileUsage = mainPrcListIndex->process_data.PagefileUsage + secPrcListIndex->process_data.PagefileUsage;
				}
				if (secPrcListIndex->process_data.WorkingSetSize != mainPrcListIndex->process_data.WorkingSetSize)
				{
					mainPrcListIndex->process_data.WorkingSetSize = mainPrcListIndex->process_data.WorkingSetSize + secPrcListIndex->process_data.WorkingSetSize;
				}
				if (secPrcListIndex->process_data.QuotaPagedPoolUsage != mainPrcListIndex->process_data.QuotaPagedPoolUsage)
				{
					mainPrcListIndex->process_data.QuotaPagedPoolUsage = mainPrcListIndex->process_data.QuotaPagedPoolUsage + secPrcListIndex->process_data.QuotaPagedPoolUsage;
				}
				if (secPrcListIndex->process_data.QuotaPeakPagedPoolUsage != mainPrcListIndex->process_data.QuotaPeakPagedPoolUsage)
				{
					mainPrcListIndex->process_data.QuotaPeakPagedPoolUsage = mainPrcListIndex->process_data.QuotaPeakPagedPoolUsage + secPrcListIndex->process_data.QuotaPagedPoolUsage;
				}
				mainPrcListIndex= mainPrcListIndex->next;
				secPrcListIndex= secPrcListIndex->next;
			}
		}
		mainPrcListIndex= mainSnap->headprocess;
		Sleep(1000); // 1 sec pause
	}
}