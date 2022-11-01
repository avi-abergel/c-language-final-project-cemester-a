#include "SaveInFile.h"

typedef struct FileHeader_ { // struct of header
	int version;
	int numSnaps;
	char reserve[100];
}FileHeader;

void saveInfile() // saving snapshot information in a file
{
	int numsnaps=0;
	Snapshot* sindex = Shead;
	while (sindex != NULL)
	{
		numsnaps++;
		sindex = sindex->next;
	}
	FileHeader HeaderOfFile = { numsnaps,Stail->position };
	FILE* f = fopen("snapshots.bin", "wb"); // opening file
	if (f == NULL)
	{
		LogError("file not opened");
		return;
	}
	else
	{
		fwrite(&HeaderOfFile, sizeof(FileHeader), 1, f); //writing header file 
		while (sindex != NULL) // writing all the snapshots in the list in the file
		{
			fwrite(sindex,sizeof(Snapshot),1,f);
			Process* pindex = sindex->headprocess;
			while (pindex != NULL) // writing the list of all processes in the file
			{
				fwrite(pindex, sizeof(Process), 1, f);
				DLL* dindex = pindex->headDLL;
				while (dindex != NULL) // writing the list of process's dlls
				{
					fwrite(dindex, sizeof(DLL), 1, f);
					dindex=dindex->next;
				}
				pindex=pindex->next;
			}
			sindex=sindex->next;
		}
	}
}