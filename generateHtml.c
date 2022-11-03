#include "generateHtml.h"



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
		while (curr != NULL)
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


DLL* dictionary(Snapshot* snpHead)
{
	DLL* dictionaryHead = NULL;
	Snapshot* snpIndex = snpHead;
	while (snpIndex != NULL)
	{
		Process* prcIndex = snpIndex->headprocess;
		while (prcIndex != NULL)
		{
			DLL* dllIndex = prcIndex->headDLL;
			while (dllIndex != NULL)
			{
				if ((searchByName(dllIndex->dllName, dllIndex)) != 0)
				{
					DLL* curr = (DLL*)malloc(sizeof(DLL));
					if (!curr) //allocation check
					{
						LogError(strerror(GetLastError()));   //log
						return;
					}
					strcpy(curr->dllName, dllIndex->dllName);
					curr->prev = NULL;
					curr->next = NULL;
					if (dictionaryHead == NULL)
					{
						dictionaryHead == curr;
					}
					else
					{
						DLL* dictionaryTail = dictionaryHead;
						while (dictionaryTail->next != NULL)
						{
							dictionaryTail = dictionaryTail->next;
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
						LogError(strerror(GetLastError()));   //log
						return;
					}
					curr->next = NULL;
					curr->prev = NULL;

					//copy values
					strcpy(curr->ProcessName, prcIndex->ProcessName);
					curr->ProcessId = prcIndex->ProcessId;
					curr->process_data.PageFaultCount = prcIndex->process_data.PageFaultCount;
					curr->process_data.WorkingSetSize = prcIndex->process_data.WorkingSetSize;
					curr->process_data.QuotaPagedPoolUsage = prcIndex->process_data.QuotaPagedPoolUsage;
					curr->process_data.QuotaPeakPagedPoolUsage = prcIndex->process_data.QuotaPeakPagedPoolUsage;
					curr->process_data.PagefileUsage = prcIndex->process_data.PagefileUsage;
					curr->headDLL = prcIndex->headDLL;
					curr->tailDLL = prcIndex->tailDLL;
					strcpy(curr->time, prcIndex->time);

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
		char start[800] ="<!DOCTYPE html><htmllang=\"en\"><head><meta charset=\"UTF-8\"\/><metahttp-equiv=\"X-UA-Compatible\"content=\"IE=edge\"/><meta name=\"viewport\"content=\"width=device-width,initial-scale=1.0\"\><title>Document<\/title><link rel=\"stylesheet\"href=\"project-style.css\"><\/head><body><nav class=\"homepage-navbar\"><ul>";
		fputs(start, f);
		Snapshot* SnapIndex = snapHead;
		int sumDll = 0;
		while (SnapIndex != NULL)
		{
			listDll = dictionary(SnapIndex);
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
		char navcounts[1000];
		sprintf(navcounts, " <li>dll count: %d</li>< li > process count : % d < / li>", sumDll, sumPrc);
		fputs(navcounts, f);
		char insert1[300]= "<li><a href=\"homepage.html\">home</a></li><li><a href=\"aboutMe.html\">about me</a></li></ul></nav><h1>snapshotslist</h1><tableclass=\"snapshots-table\"><th><td>snapshot</td><td>link</td><td>dll count</td><td>memory avg</td></th>";
		fputs(insert1, f);
		char snapNum[1000];
		char numDlls[1000];
		char memoryAvg[1000];
		SnapIndex = snapHead;
		while (SnapIndex != NULL)
		{
			sprintf(snapNum, "<tr><td>%d</td>", SnapIndex->position);
			fputs(snapNum, f);
			Process* prcIndex = SnapIndex->headprocess;
			int dllsum = 0;
			int memorysum = 0;
			while (prcIndex != NULL)
			{
				dllsum += prcIndex->tailDLL->position;
				memorysum = memorysum + prcIndex->process_data.WorkingSetSize;
				prcIndex = prcIndex->next;
			}
			sprintf(numDlls, "<td><a href="">snap page</a></td><td>%d</td>", dllsum);
			int memoryavg = memorysum / SnapIndex->tailprocess->position;
			sprintf(memoryAvg, "<td>%d</td></tr>", memoryavg);
			fputs(numDlls, f);
			fputs(memoryAvg, f);
			SnapIndex = SnapIndex->next;
		}
		char insert2[200]="</table><h1>dlls list</h1><table class=\"dlls-table\"><th><td>dll name</td><td>link</td></th>";
		fputs(insert2, f);
		SnapIndex = snapHead;
		while (SnapIndex != NULL)
		{
			listDll = dictionary(SnapIndex);
			while (listDll != NULL)
			{
				char DLLs[1000];
				sprintf(DLLs, "<tr><td>%s</td><td><a href=""></a></td></tr>", listDll->dllName);
				listDll = listDll->next;
			}
			SnapIndex = SnapIndex->next;
		}
		char end [50]="</table></body></html>";
		fputs(end, f);
		fclose(f);
	}
}


void generateSnapshotPage(Snapshot* snapHead)
{
	FILE* f = fopen("snapshot.html", "w");
	if (!f)
	{
		LogError("file not found");
		return;
	}
	else
	{
		char htmlStart[800]="<!DOCTYPE html><html lang=\"en\"><head><meta charset=\"UTF-8\"/><meta http-equiv=\"X-UA-Compatible\"content=\"IE=edge\"/><meta name=\"viewport\"content=\"width=device-width,initial-scale=1.0\"/><title>Document</title><link rel=\"stylesheet\"href=\"project-style.css\"></head><body><nav class=\"navbar\"><ul><li><a href=\"homepage.html\">home</a></li><li><a href=\"aboutMe.html\">about me</a></li></ul></nav>";
		fputs(htmlStart, f);
		char title[1000];
		sprintf(title, "<h1>snapshot number %d taken at %s</h1>", snapHead->position, snapHead->time);
		fputs("<h3>process list</h3><table class=\"snapshot-data\"><th><td>process name</td><td>page fault count</td><td>working set size</td><td>quota pagedpool usage</td><td>quota peaked paged pool usage</td><td>page file usage</td><td>process ID</td><td>dlls amount</td><td>dlls list</td></th>", f);
		Process* prcIndex = snapHead->headprocess;
		while (prcIndex != NULL)
		{
			char processData[1000];
			sprintf(processData, "<tr><td>%s</td><td>%lu</td><td>%zu</td><td>%zu</td><td>%zu</td><td>%zu</td><td>%lu</td><td>%d</td>", prcIndex->ProcessName, prcIndex->process_data.PageFaultCount, prcIndex->process_data.WorkingSetSize, prcIndex->process_data.QuotaPagedPoolUsage, prcIndex->process_data.QuotaPeakPagedPoolUsage, prcIndex->ProcessId);
			fputs("<td class=\"dropdown\"><div class=\"dropdown-content\">", f);
			DLL* dllIndex = prcIndex->headDLL;
			while (dllIndex != NULL)
			{
				char dlls[1000];
				sprintf(dlls, " <span>%s</span>", dllIndex->dllName);
				fputs(dlls, f);
				dllIndex = dllIndex->next;
			}
			prcIndex = prcIndex->next;

		}
		char htmlEnd[50] = "</div></td></tr></table></body></html>";

		fputs(htmlEnd, f);
	}
	fclose(f);

}



void generateDllPage(Snapshot* snapHead, char dllName[500])
{
	FILE* f = fopen("DLL.html", "w");
	if (!f)
	{
		LogError("file not found");
		return;
	}
	else
	{
		char htmlStart[800] = "<!DOCTYPE html><html lang=\"en\"><head><meta charset=\"UTF-8\"/><meta http-equiv=\"X-UA-Compatible\"content=\"IE=edge\"/><meta name=\"viewport\"content=\"width=device-width,initial-scale=1.0\"/><title>Document</title><link rel=\"stylesheet\"href=\"project-style.css\"></head><body><nav class=\"navbar\"><ul><li><a href=\"homepage.html\">home</a></li><li><a href=\"aboutMe.html\">about me</a></li></ul></nav>";
		fputs(htmlStart, f);
		Process* prcList = processListUsingDll(snapHead, dllName);
		int prcCount = 0;
		while (prcList != NULL)
		{
			prcCount++;
			prcList = prcList->next;
		}
		while (prcList != NULL)
		{
			prcList = prcList->prev;
		}
		char title[1000];
		sprintf(title, " <h1>%d processes used %s</h1>", prcCount, dllName);
		fputs(title, f);
		char insert1[100] = "<table><th><td>process ID<td><td>process name</td></th>";
		fputs(insert1,f);
		char prcData[1000];
		while (prcList != NULL)
		{
			sprintf(prcData, "<tr><td>%lu</td><td>%s</td></tr>", prcList->ProcessId, prcList->ProcessName);
			fputs(prcData, f);
			prcList = prcList->next;
		}
		char end[40] = "</table></body></html>";
		fputs(end, f);
		fclose(f);
	}
}


void generateHtmlReport(Snapshot* snp)
{
	generateHomePage(snp);
	Snapshot* indexSnap = snp;
	while (indexSnap != NULL)
	{
		generateSnapshotPage(indexSnap);
		DLL* dllList = dictionary(indexSnap);
		while (dllList != NULL)
		{
			generateDllPage(indexSnap, dllList->dllName);
			dllList = dllList->next;
		}
		indexSnap = indexSnap->next;
	}
	FILE* f = fopen("aboutMe.html", "w"); // generating "about me" page
	if (!f)
	{
		LogError("file not found");
		return;
	}
	else
	{
		char aboutMe [1000]= "<!DOCTYPE html>\n<html lang=\"en\">\n<head>\n<meta charset=\"UTF-8\"/>\n<meta http-equiv=\"X-UA-Compatible\"content=\"IE=edge\"/>\n<meta name=\"viewport\"content=\"width=device-width,initial-scale=1.0\"/>\n<title>Document</title>\n<link rel=\"stylesheet\"href=\"project-style.css\"/>\n</head>\n<body>\n<nav class=\"navbar\">\n<ul>\n<li><a href=\"homepage.html\">home</a></li>\n<li><a href=\"aboutMe.html\">about me</a></li>\n</ul>\n</nav>\n<div class=\"picture\"><img src=\"158839942_139041001891327_8709820587880628529_n.jpg\"alt=\"my picture\"/>\n</div>\n<div class =\"details\">\n<ul>\n<h2>avi abergel</h2>\n<li>24 years old</li>\n<li>\nborn in bet shemesh, israel.lives in zur hadassah israel. currentlystudying to be a full stack developer at\"level up\"course by zionet.\n</li><li><a href=\"https://github.com/avi-abergel\">my github</a></li><li>\n<a href=\"https://www.youtube.com/shorts/WCXI1KRgjck\">favourite youtube video</a></li>\n</ul>\n</div>\n</body>\n</html>";
		fputs(aboutMe, f);
		fclose(f);
	}
}
