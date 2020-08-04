#pragma warning(disable:4996)
#include"fps.h"
#include"Screen.h"

void InitFPSData(FPSData** fpsData)
{
	(*fpsData) = (FPSData*)malloc(sizeof(FPSData));
	(*fpsData)->FrameCnt = 0;
	(*fpsData)->FPSTextBuffer = (char*)malloc(sizeof(char) * 10);
	sprintf((*fpsData)->FPSTextBuffer, "FPS : %d", (*fpsData)->FrameCnt);
	(*fpsData)->FPSOldTime = clock();
}

void DrawFPS(FPSData** fpsData)
{
	(*fpsData)->FrameCnt++;
	(*fpsData)->FPSCurTime = clock();
	if ((*fpsData)->FPSCurTime - (*fpsData)->FPSOldTime >= 1000) 
	{
		sprintf((*fpsData)->FPSTextBuffer, "FPS : %d", (*fpsData)->FrameCnt);
		(*fpsData)->FPSOldTime = clock();
		(*fpsData)->FrameCnt = 0;
	}
	ScreenPrint(0, 0, (*fpsData)->FPSTextBuffer);
}

void DestroyFPSData(FPSData** fpsData) 
{
	free((*fpsData)->FPSTextBuffer);
	free(*fpsData);
}
