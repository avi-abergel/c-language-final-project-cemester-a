#include "log.h"


void LogError(char message[100])
{
	time_t t;
	time(&t);
	struct tm* timeinfo;
	timeinfo = localtime(&t);
	char finalMessage[100];
	sprintf(finalMessage, "%d%d%d:%d%d%d", timeinfo->tm_year + 1900, timeinfo->tm_mon + 1, timeinfo->tm_mday, timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);
	sprintf(finalMessage, "ERROR- %s\n", message);
	char FileName[100];
	sprintf(FileName, "myprog-%d%d%d.txt", timeinfo->tm_year + 1900, timeinfo->tm_mon + 1, timeinfo->tm_mday);
	FILE* f = fopen(FileName, "a");
	if (f==NULL)
	{
		printf("ERROR!- file not found");
		return 0;
	}
	else {
		fputs(finalMessage,f);
		fclose(f);
	}
}

void LogEvent(char message[100])
{
	time_t t;
	time(&t);
	struct tm* timeinfo;
	timeinfo = localtime(&t);
	char finalMessage[100];
	sprintf(finalMessage, "%d%d%d:%d%d%d", timeinfo->tm_year + 1900, timeinfo->tm_mon + 1, timeinfo->tm_mday, timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);
	sprintf(finalMessage, "EVENT- %s\n", message);
	char FileName[100];
	sprintf(FileName, "myprog-%d%d%d.txt", timeinfo->tm_year + 1900, timeinfo->tm_mon + 1, timeinfo->tm_mday);
	FILE* f = fopen(FileName, "a");
	if (!f)
	{
		printf("ERROR- file not found");
		return 0;
	}
	else {
		fputs(finalMessage, f);
		fclose(f);
	}
}

void LogWarning(char message[100])
{
	time_t t;
	time(&t);
	struct tm* timeinfo;
	timeinfo = localtime(&t);
	char finalMessage[100];
	sprintf(finalMessage, "%d%d%d:%d%d%d", timeinfo->tm_year + 1900, timeinfo->tm_mon + 1, timeinfo->tm_mday, timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);
	sprintf(finalMessage, "WARNING -%s\n", message);
	char FileName[100];
	sprintf(FileName, "myprog-%d%d%d.txt", timeinfo->tm_year + 1900, timeinfo->tm_mon + 1, timeinfo->tm_mday);
	FILE* f = fopen(FileName, "a");
	if (!f)
	{
		printf("ERROR- file not found");
		return 0;
	}
	else {
		fputs(finalMessage, f);
		fclose(f);
	}
}

