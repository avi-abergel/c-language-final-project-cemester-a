//#include <stdio.h>
//#include <stdlib.h> 
//#include <string.h>
//#include <time.h>
//#include <windows.h>
//#include <psapi.h>
#include "log.h"


typedef struct DLL_ {
	int position;
	char dllName[MAX_PATH];
	struct DLL_* prev;
	struct DLL_* next;

}DLL;

extern DLL* Dhead;
extern DLL* Dtail;


typedef struct Process_ {
	int position;
	DWORD ProcessId;
	char ProcessName[MAX_PATH];
	char time[50];
	PROCESS_MEMORY_COUNTERS process_data;
	DLL* headDLL;
	DLL* tailDLL;
	struct Process_* prev;
	struct Process_* next;
}Process;

extern Process* Phead;
extern Process* Ptail;


typedef struct Snapshot_ {
	int position;
	Process* headprocess;
	Process* tailprocess;
	char time[50];
	struct Snapshot_* prev;
	struct Snapshot_* next;
}Snapshot;

extern Snapshot* Shead;
extern Snapshot* Stail;

