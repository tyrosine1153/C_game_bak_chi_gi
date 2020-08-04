#include<malloc.h>
#include<stdio.h>
#include<time.h>

typedef struct _FPSData
{
	clock_t FPSCurTime, FPSOldTime;
	int FrameCnt;
	char* FPSTextBuffer;
}FPSData;

void InitFPSData(FPSData** fpsData);//Init()俊 持带芭
void DrawFPS(FPSData** fpsData);//Render()俊 持带芭 
void DestroyFPSData(FPSData** fpsData);//Release()俊 持带芭