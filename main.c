#pragma warning(disable:4996)
#include<stdio.h>
#include<time.h>
#include<conio.h>
#include"Screen.h"
#include"fps.h"

FPSData* fpsData;
char PLAYER_STR[] = "¦¦¦¡¡Ü¦¡¦¥";
typedef struct _Position
{
	int x, y;
}Position;

typedef struct
{
	Position position;
	char* strPlayer;
	int nLength;
}Player;

Player g_Player;

void Init()
{
	InitFPSData(&fpsData);
	g_Player.position.x = 0;
	g_Player.position.y = 22;

	g_Player.nLength = strlen(PLAYER_STR);

	g_Player.strPlayer = (char*)malloc(sizeof(char) * g_Player.nLength);
	strcpy(g_Player.strPlayer, PLAYER_STR);
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
	DestroyFPSData(&fpsData);
}

void WaitRender(clock_t OldTime)

{
	clock_t CurTime;
	while (1)
	{
		CurTime = clock();
		if (CurTime - OldTime > 33) break;
	}
}

int GetkeyEvent()
{
	if (_kbhit()) return _getch();

	else return -1;
}

void KeyProcess(int key)
{
	switch (key)
	{
	case 'i':
		break;
	case'j':
		break;
	}
}

int main()
{
	ScreenInit();
	Init();

	while (1)
	{
		int nKey = GetkeyEvent();

		if (nKey == 'q') break;
		KeyProcess(nKey);

		Update();

		Render();

		WaitRender(clock());
	}

	Release();
	ScreenRelease();
	return 0;
}