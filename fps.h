#pragma once
#include<time.h>

typedef struct fps_data
{
	clock_t FPSCurTime, FPSOldTime;
	int FPSCount;
	char* FPSTextBuffer;

}FPSData;

void InitFPSData(FPSData** fpsData);
void DrawFPS(FPSData** fpsData);
void DestroyFPSData(FPSData** fpsData);