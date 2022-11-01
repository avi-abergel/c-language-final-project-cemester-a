#include "OneSnapshot.h"


Snapshot* GetProcessesInfo()
{
	// Get Processes
	DWORD aProcesses[1024], cbNeeded, cProcesses;
	unsigned int i;

	// * Receive all process ID and put in aProcesses Array
	if (!EnumProcesses(aProcesses, sizeof(aProcesses), &cbNeeded))
	{
		LogError("process opening failed");
		return 1;
	}

	// Calculate how many process identifiers were returned.
	cProcesses = cbNeeded / sizeof(DWORD);

	// *Loop of all processes
	for (i = 0; i < cProcesses; i++)
	{
		newProcess(aProcesses[i]);

	}
	sort();
	Snapshot snp;
	snp.headprocess = Phead;
	snp.tailprocess = Ptail;
	addSnapshot(snp);
	return &snp;

	// For each Process to get its Memory Information
}





void newProcess(DWORD processID)
{
	time_t t;
	time(&t);
	struct tm* timeinfo;
	timeinfo = localtime(&t);
	Process retProcess;
	HANDLE hProcess;
	PROCESS_MEMORY_COUNTERS pmc;

	// Open process in order to receive information
	hProcess = OpenProcess(PROCESS_QUERY_INFORMATION |
		PROCESS_VM_READ,
		FALSE, processID);
	if (NULL == hProcess)
	{
		LogWarning("systen has no access to process");
		return;
	}

	HMODULE hMods[1024];
	DWORD cbNeeded;
	TCHAR FoundProcessName[MAX_PATH];
	TCHAR wDllName[MAX_PATH];
	char regularCharArr[MAX_PATH];

	// Get Process Name
	if (!GetModuleFileNameEx(hProcess, 0, FoundProcessName, MAX_PATH))
	{
		int err = GetLastError();
		char Errormsg[50];
		sprintf(Errormsg, "error code:%d. %s", err, strerror(err));
		LogError(Errormsg);
	}
	else
	{
		if (GetProcessMemoryInfo(hProcess, &pmc, sizeof(pmc)))
		{
			char ProcessName[MAX_PATH];
			size_t numConverted;
			wcstombs_s(&numConverted, ProcessName, MAX_PATH, FoundProcessName, MAX_PATH); //converting process name to regular char string
			strcpy(retProcess.ProcessName, ProcessName);
			retProcess.ProcessId = processID;
			retProcess.process_data.PageFaultCount = pmc.PageFaultCount;
			retProcess.process_data.PeakWorkingSetSize = pmc.PeakWorkingSetSize;
			retProcess.process_data.QuotaPagedPoolUsage = pmc.QuotaPagedPoolUsage;
			retProcess.process_data.QuotaPeakPagedPoolUsage = pmc.QuotaPeakPagedPoolUsage;
			retProcess.process_data.PagefileUsage = pmc.PagefileUsage;
			sprintf(retProcess.time, "%d%d%d- %d:%d:%d", timeinfo->tm_year + 1900, timeinfo->tm_mon + 1, timeinfo->tm_mday, timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);
		}



		// Get Dlls List

		if (EnumProcessModules(hProcess, hMods, sizeof(hMods), &cbNeeded))
		{
			for (int i = 0; i < (cbNeeded / sizeof(HMODULE)); i++)
			{
				// Get the full path to the module's file.

				if (GetModuleFileNameEx(hProcess, hMods[i], wDllName, MAX_PATH))
				{
					// * Get the module name and handle value.
					// Convert wChar to regular char array (string)
					DLL retDll;
					char dllName[MAX_PATH];
					size_t numConverted;
					wcstombs_s(&numConverted, dllName, MAX_PATH, wDllName, MAX_PATH);
					strcpy(retDll.dllName, dllName);
					addDLL(retDll);
					retProcess.headDLL = Dhead;
					retProcess.tailDLL = Dtail;
				}
			}
			addProcess(retProcess);
		}

	}
	CloseHandle(hProcess);
}
