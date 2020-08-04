#include<malloc.h>
#include<stdio.h>
#include<time.h>

typedef struct _FPSData
{
	clock_t FPSCurTime, FPSOldTime;
	int FrameCnt;
	char* FPSTextBuffer;
}FPSData;

void InitFPSData(FPSData** fpsData);//Init()�� �ִ���
void DrawFPS(FPSData** fpsData);//Render()�� �ִ��� 
void DestroyFPSData(FPSData** fpsData);//Release()�� �ִ���