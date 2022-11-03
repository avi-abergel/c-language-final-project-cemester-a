#include "generateHtml.h"

#define seperator1 "dll&process"
#define seperator2 "snapData"
#define seperator3 "dlls"



int searchByName(char name[500], DLL* dllHead)
{
	DLL* curr = dllHead;
	if (curr == NULL)
	{
		LogError("list is empty");
		return;
	}
	else
	{
		while (curr != null)
		{
			if ((strcmp(curr->dllName, name)) == 0)
			{
				return 0;
			}
			curr = curr->next;
			return 1;
		}
	}
}


DLL* dictionary(Snapshot* snpIndex)
{
	DLL* dictionaryHead = NULL;
	snpIndex = Shead;
	while (snpHead != null)
	{
		Process* prcIndex= snpHead->headprocess;
		while (prcHead != null)
		{
			DLL* dllIndex = prcHead->headDLL;
			while (dllIndex != null)
			{
				if ((searchByName(dllIndex->dllName, dictionaryHead)) != 0)
				{
					DLL* curr = (DLL*)malloc(sizeof(dll));
					if (!curr) //allocation check
					{
						Log_Error(strerror(GetLastError()));   //log
						return;
					}
					strcpy(curr->dllName, dllIndex->dllName);
					curr->prev = NULL;
					curr->next = null;
					if (dictionaryHead == NULL)
					{
						dictionaryHead == curr;
					}
					else
					{
						DLL* dictionaryTail = dictionaryHead;
						while (dictionaryTail->next != null)
						{
							dictionaryTail = dictionaryTail->next
						}
						dictionaryTail->next = curr;
						curr->prev = dictionaryHead;
						dictionaryTail = curr;
					}
				}
				dllIndex = dllIndex->next;
			}
			prcIndex = prcIndex->next;
		}
		snpIndex = snpIndex->next;
	}
	return dictionaryHead;
}


Process* processListUsingDll(Snapshot* sList, char dllName[500])
{
	Snapshot* snapIndex = sList;
	Process* dictionaryHead = NULL;

	//Log_Event("Building proccess list based on dictionaty.\n");

	while (snapIndex != NULL)
	{
		Process* prcIndex = snapIndex->headprocess;
		//DLL'S LIST
		while (prcIndex != NULL)
		{
			DLL* dllIndex = prcIndex->headDLL;

			while (dllIndex != NULL)
			{
				//search if proccess item use this dll 
				if (strcmp(dllIndex->dllName, dllName) == 0)
				{
					Process* curr = (Process*)malloc(sizeof(Process)); //memory allocation
					if (!curr) //allocation check
					{
						Log_Error(strerror(GetLastError()));   //log
						return;
					}
					curr->next = NULL;
					curr->prev = NULL;

					//copy values
					strcpy(curr->processName, prcIndex->processName);
					curr->proccessId = prcIndex->proccessId;
					curr->PageFaultCount = prcIndex->PageFaultCount;
					curr->WorkingSetSize = prcIndex->WorkingSetSize;
					curr->QuotaPagedPoolUsage = prcIndex->QuotaPagedPoolUsage;
					curr->QuotaPeakPagedPoolUsage = prcIndex->QuotaPeakPagedPoolUsage;
					curr->PagefileUsage = prcIndex->PagefileUsage;
					curr->headDLL = prcIndex->headDLL;
					curr->tailDLL = prcIndex->tailDLL;
					curr->time = prcIndex->time;

					if (dictionaryHead == NULL) //if list is empty
					{
						dictionaryHead = curr;
					}
					else
					{//if not empty
						Process* dictionaryTail = dictionaryHead;

						while (dictionaryTail->next != NULL) //get pointer to tail of list
						{
							dictionaryTail = dictionaryTail->next;
						}

						dictionaryTail->next = curr;
						curr->prev = dictionaryTail;
						dictionaryTail = curr;
					}
				}
				dllIndex = dllIndex->next;
			}
			prcIndex = prcIndex->next;
		}
		snapIndex = snapIndex->next;
	}
	return dictionaryHead;
}




void generateHomePage(Snapshot* snapHead)
{
	DLL* listDll;
	FILE* f = fopen("homepage.html", "w");
	if (!f)
	{
		LogError("file not found");
		return;
	}
	else
	{
		fputs("<!DOCTYPE html><html lang= \"en\"><head><meta charset = \"UTF-8\" \/ ><meta http - equiv = \"X-UA-Compatible\" content = \"IE=edge\" / ><meta name = \"viewport\" content = \"width=device-width, initial-scale=1.0\" \/ ><title>Document< \/ title>< \/ head><body><nav class = \"homepage-navbar\">< ul>", f);
		Snapshot* SnapIndex = snapHead;
		int sumDll = 0;
		while (SnapIndex != null)
		{
			listDll = dictionary(snapIndex);
			int dllCount = 0;
			while (listDll != NULL)
			{
				dllCount++;
				listDll = listDll->next;
			}
			sumDll = +dllCount;
			SnapIndex = SnapIndex->next;
		}
		SnapIndex = snapHead;
		int sumPrc = 0;
		while (SnapIndex != NULL)
		{
			sumPrc += SnapIndex->tailprocess->position;
			SnapIndex = SnapIndex->next;
		}
		char* navcounts;
		sprintf(navcounts, " <li>dll count: %d</li>< li > process count : % d < / li>", sumDll, sumPrc);
		fputs(navcounts, f);
		fputs(" <li><a href="">homepage</a></li>< li > <a href = "">about< / a>< / li>< / ul>< / nav>	<h1>snapshots list< / h1>	<table class = \"snapshots-table\"><th><td>snapshot< / td><td>link< / td><td>dll count< / td>	<td>memory avg< / td>	< / th>");
		char* snapNum;
		char* numDlls;
		char* memoryAvg;
		SnapIndex = snapHead;
		while (SnapIndex != null)
		{
			sprintf(snapnum, " <tr><td> % d< / td>", SnapIndex->position);
			fputs(snapNum, f);
			Process* prcIndex = SnapIndex->headprocess;
			int dllsum = 0;
			int memorysum = 0;
			while (prcIndex != null)
			{
				dllsum += prcIndex->tailDLL->position;
				memorysum = memorysum + prcIndex->process_data.WorkingSetSize;
				prcIndex = prcIndex->next;
			}
			sprintf(numDlls, " <td><a href=""></a></td>< td > % d < / td>", dllsum);
			int memoryavg = memorysum / SnapIndex->tailprocess->position;
			sprintf(memoryAvg, "<td>%d</td>< / tr > ", memoryavg);
			fputs(numDlls, f);
			fputs(memoryAvg, f);
			SnapIndex = SnapIndex->next;
		}
		fputs("</table>< h1 > dlls list< / h1><table class = \"dlls-table\"><th><td>dll name< / td><td>link< / td>< / th>");
		SnapIndex = snapHead;
		while (SnapIndex != NULL)
		{
			listDll = dictionary(SnapIndex);
			while (listDll != null)
			{
				char* DLLs;
				sprintf(DLLs, "<tr>< td > % s< / td><td><a href = "">< / a>< / td>< / tr>", listDll->dllName);
				listDll = listDll->next;
			}
			SnapIndex = SnapIndex->next;
		}
		fputs("</table>< / body >< / html>", f);
		fclose(f);
	}
}

	
	void generateSnapshotPage(Snapshot * snapHead)
	{
		FILE* f = fopen("snapshot.html", "w");
		if (!f)
		{
			LogError("file not found");
			return;
		}
		else
		{
			fputs("<!DOCTYPE html>< html lang = \"en\" ><head><meta charset = \"UTF-8\" / ><meta http - equiv = \"X-UA-Compatible\" content = \"IE=edge\" / ><meta name = \"viewport\" content = \"width=device-width, initial-scale=1.0\" / ><title>Document< / title>	< / head><body><nav class = \"snapshot-navbar\"><ul><li><a href = "">home< / a>< / li><li><a href = "">about me< / a>< / li>< / ul>< / nav>",f);
			char* title;
			sprintf(title, "<h1>snapshot number %d taken at %s</h1>", snapHead->position, snapHead->time);
			fputs("<h3>process list</h3>< table class = \"snapshot-data\" ><th><td>process name< / td><td>page fault count< / td><td>working set size< / td><td>quota paged pool usage< / td><td>quota peaked paged pool usage< / td><td>page file usage< / td><td>process ID< / td><td>dlls amount< / td><td>dlls list< / td>< / th>", f);
			Process* prcIndex = snapHead->headprocess;
			while (prcIndex != null)
			{
				char* processData;
				sprintf(processData, "<tr>< td > % s< / td><td> % lu< / td><td> % zu< / td><td> % zu< / td><td> % zu< / td><td> % zu< / td><td> % lu< / td><td> % d < / td>", prcIndex->ProcessName, prcIndex->process_data.PageFaultCount, prcIndex->process_data.WorkingSetSize, prcIndex->process_data.QuotaPagedPoolUsage, prcIndex->process_data.QuotaPeakPagedPoolUsage, prcIndex->ProcessId);
				fputs("<td class=\"dropdown\"><div class=\"dropdown - content\">", f);
				DLL* dllIndex = prcIndex->headDLL;
				while (dllIndex != NULL)
				{
					char* dlls;
					sprintf(dlls, " <span>%s</span>", dllIndex->dllName);
					fputs(dlls, f);
					dllIndex = dllIndex->next;
				}
				prcIndex = prcIndex->next;

			}
			fputs(" </div></td>< / tr >< / table>< / body>< / html>", f);
		}
		fclose(f);

	}

	void generateDllPage(Snapshot* snapHead,char dllName[500])
	{
		FILE* f = fopen("DLL.html", "w");
		if (!f)
		{
			LogError("file not found");
			return;
		}
		else
		{
			fputs("<!DOCTYPE html>< html lang = \"en\" ><head>	<meta charset = \"UTF-8\" / ><meta http - equiv = \"X-UA-Compatible\" content = \"IE=edge\" / ><meta name = \"viewport\" content = \"width=device-width, initial-scale=1.0\" / ><title>Document< / title>< / head><body><nav class = \"snapshot-navbar\"><ul><li><a href = "">home< / a>< / li><li><a href = "">about me< / a>< / li>< / ul>< / nav>", f);
			Process* prcList=processListUsingDll(snapHead, dllName);
			int prcCount = 0;
			while (prcList != NULL)
			{
				prcCount++;
				prcList = prcList->next;
			}
			while (prcList != null)
			{
				prcList = prcList->prev;
			}
			char* title;
			sprintf(title, " <h1>%d processes used %s</h1>", prcCount, dllName);
			fputs(title, f);
			fputs("<table>< th ><td>process ID< / td><td>process name< / td>< / th>", f);
			char* prcData;
			while (prcList != null)
			{
				sprintf(prcData, "<tr>< td > % lu< / td><td> % s< / td>< / tr>", prcList->ProcessId, prcList->ProcessName);
				fputs(prcData, f);
				prcList = prcList->next;
			}
			fputs("</table>< / body >	< / html>", f);
			fclose(f);
		}
	}
