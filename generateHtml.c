#include "generateHtml.h"

#define seperator1 "[[[line1]]]"
#define seperator2 "[[[line2]]]"
#define seperator3 "[[[line3]]]"



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



char* ReadAllFile(char* fileName)
{
	FILE* f = fopen(fileName, "r");
	if (!f)
	{
		LogError("file not found");
		return;
	}
	else
	{
		char* buff = (char*)malloc(1000);
		char* read;
		int FileSize = 0;
		while (read = fgets(buff, 1000, f));
		{
			FileSize += strlen(buff);
		}
		free(buff);
		fclose(f);
		FileSize++;
		
		buff = malloc(sizeof(FileSize));
		f = fopen(fileName, "r");
		if (!f)
		{
			LogError("file not found");
			return;
		}
		else
		{
			int position = 0;
			char charToRead;
			while (charToRead = fgetc(f) != EOF)
			{
				buff(position) = charToRead;
				position++;
			}
			buff(position) = NULL;
			fclose(f);
			return buff;
		}
	}
}




void generateHomePage(char* seperator)
{
	char* replaceHtml = seperator;
	char* template = ReadAllFile("C:\\Users\\97252\\source\\repos\\project_2_Final\\project_2_Final\\project-homepage.html");
	char* findToken = strstr(template, seperator);
	int len = findToken - template;
	char* newFile=(char*)malloc()
}