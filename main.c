#pragma warning(disable:4996)
#include<stdio.h>
#include<time.h>
#include<conio.h>
#include<string.h>
#include"Screen.h"
#include"fps.h"

FPSData* fpsData;
char PLAYER_STR[] = "   └─●─┘   ";

typedef struct _Position
{
	int x, y;
}Position;

typedef struct
{
	Position position;
	Position center;
	char* strPlayer;
	int nLength;
}Player;

Player g_Player;

void Init()
{
	InitFPSData(&fpsData);
	g_Player.position.x = 4;
	g_Player.position.y = 22;
	g_Player.center.x = 4;
	g_Player.center.y = 0;

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

	char string[100] = { 0, };
	int printX = g_Player.position.x - g_Player.center.x;
	if (printX < 0) //왼쪽 팔이 경계를 넘어갔을 경우
	{
		ScreenPrint(0, g_Player.position.y, &g_Player.strPlayer[printX * -1]);
	}
	else if (g_Player.position.x + g_Player.center.x + 1 > 40)//오른쪽 경계선을 넘을 경우
	{
		strncat(string, g_Player.strPlayer,g_Player.nLength-((g_Player.position.x + g_Player.center.x + 1) - 40));
		ScreenPrint(printX, g_Player.position.y, string);
	}
	else 
	{
		ScreenPrint(printX, g_Player.position.y, g_Player.strPlayer);
	}
	sprintf(string, "Player 좌표 : %d , %d", g_Player.position.x, g_Player.position.y);
	ScreenPrint(0, 3, string);

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
	case 'a':
		g_Player.position.x--;
		if (g_Player.position.x - g_Player.center.x < 0
			|| g_Player.position.x + (g_Player.center.x * 2) + 1 >40)
		{
			g_Player.position.x--;
		}
		break;
	case'd':
		g_Player.position.x++;
		if (g_Player.position.x + (g_Player.center.x * 2) + 1 > 40
			|| g_Player.position.x - g_Player.center.x < 0)
		{
			g_Player.position.x++;
		}
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