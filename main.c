#include "LoadFromFile.h"
#pragma warning(disable:4996)


main()
{
	int userResponse;
	printf("Hello! please choose an option:\n1-take one snapshot\n2-take 20 snapshots\n3-start a long snapshot\n4-generate HTML report\n5-reset collection\n6-save in file\n7-load from file\n8-QUIT\n");
	scanf("%d", &userResponse);
	while (userResponse != 8)
	{
		switch (userResponse)
		{
		default:printf("option doesnt exist. please choose one of the option 1-8");
			break;
		case 1:GetProcessesInfo();
			break;
		case 2:twentySnaps();
			break;
		case 3:longSnapshot();
			break;
		case 4:printf("4");
			break;
		case 5:freeMemory();
			break;
		case 6:saveInfile();
			break;
		case 7:LoadFromfile();
			break;
		case 8:
			break;
		}
		printf("Hello! please choose an option:\n1-take one snapshot\n2-take 20 snapshots\n3-start a long snapshot\n4-generate HTML report\n5-reset collection\n6-save in file\n7-load from file\n8-QUIT\n");
		scanf("%d", &userResponse);
	}

	 
	printf("GOODBYE!");
	return 0;
}