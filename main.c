#pragma warning(disable:4996)
#include<stdio.h>
#include<time.h>
#include<conio.h>
#include<malloc.h>
#include"Screen.h"
#include"fps.h"

FPSData* fpsData;

void Init()
{
	ScreenInit();
	InitFPSData(&fpsData);
}

void Update()
{

}

void Render()
{
	ScreenClear();
	DrawFPS(&fpsData);
	ScreenFlipping();
}

void Release()
{
	ScreenRelease();
	DestroyFPSData(&fpsData);
}

int GetKey()
{
	return _kbhit() ? _getch() : -1;
}

void Wait(clock_t OldTime)
{
	clock_t CurTime;
	while (1)
	{
		CurTime = clock();
		if (CurTime - OldTime > 33) break;
	} // 33ms ´ë±â
}

void KeyProcess(int inputKey)
{
	switch (inputKey)
	{
	case 'j':
		break;
	case 'l':
		break;
	}
}

int main()
{

	Init();

	while (1)
	{
		int inputKey = GetKey();
		if (inputKey == 'q') break;
		KeyProcess(inputKey);

		Update();

		Render();

		Wait(clock());
	}

	Release();

	return 0;
}
