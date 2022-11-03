#include "longSnapshot.h"

void longSnapshot()
{
	printf("press any key to stop");
	while (kbhit() != 1) //the program will run as long as the user is not pressing a key on the keyboard
	{
		GetProcessesInfo();
		Sleep(1000); // 1sec pause between snapshots
	}
}