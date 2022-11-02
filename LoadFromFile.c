#include "LoadFromFile.h"

typedef struct FileHeader_ { // struct of header
	int version;
	int numSnaps;
	char reserve[100];
}FileHeader;

void LoadFromfile() // saving snpshot information un a file
{
	FILE* f = fopen("snapshots.bin", "rb"); // opening file
	if (f == NULL)
	{
		LogError("file not opened");
		return;
	}
	else
	{
		FileHeader* HeaderBuffer = (FileHeader*)malloc(sizeof(FileHeader));
		fread(HeaderBuffer, sizeof(FileHeader), 1, f);  //reading header file
		
		for (int i = 0; i < HeaderBuffer->numSnaps; i++) // reading all the snapshots in the list in the file
		{
		    Snapshot* Sbuffer = (Snapshot*)malloc(sizeof(Snapshot));
			fread(Sbuffer, sizeof(Snapshot), 1, f);
			addSnapshot(*Sbuffer);
			
			for (int i = 0; i < Sbuffer->tailprocess->position; i++)  // reading the list of all processes in the file
			{
				Process* Pbuffer = (Process*)malloc(sizeof(Process));
				fread(Pbuffer, sizeof(Process), 1, f);
				addProcess(*Pbuffer);
				
				for (int i = 0; i < Pbuffer->tailDLL->position; i++) // reading the list of process's dlls
				{
					DLL* Dbuffer = (DLL*)malloc(sizeof(DLL));
					fread(Dbuffer, sizeof(DLL), 1, f);
					addDLL(*Dbuffer);
				}
			}
			
		}
	}
	fclose(f);
}