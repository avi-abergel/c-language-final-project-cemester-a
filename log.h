#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <time.h>
#include <windows.h>
#include <psapi.h>
#include <conio.h>
#pragma warning(disable:4996)

void LogError(char message[100]);
void LogEvent(char message[100]);
void LogWarning(char message[100]);