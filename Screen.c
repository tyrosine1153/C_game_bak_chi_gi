#include<windows.h>

static int g_nScreenIndex;
static HANDLE g_hScreen[2];

void ScreenInit()//ȭ�� ���� �ʱ�ȭ. ��, ���� ���� ����. Ŀ�� ����.
{
	CONSOLE_CURSOR_INFO cci;
	//�ܼ��� Ŀ���� ���� ������ ������ �ִ�.
	//dwSize : Ŀ���� ä������ ���� ���� ����(1~100), bVisible : ȭ�� ǥ�� ����

	//ȭ�� ���� 2���� �����
	g_hScreen[0] = CreateConsoleScreenBuffer
		//CreateConsoleScreenBuffer() : Screen Buffer�� �����Ѵ�. Flipping�� �����ϰ��ִ�.
	(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	g_hScreen[0] = CreateConsoleScreenBuffer
	(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);

	//Ŀ�� �����
	cci.dwSize = 1;
	cci.bVisible = FALSE;
	SetConsoleCursorInfo(g_hScreen[0], &cci);
	//������ ��ũ�� ���ۿ� ������ Ŀ���� ������ �����Ѵ�
	SetConsoleCursorInfo(g_hScreen[1], &cci);
}

void ScreenClear() //���۰� ��ü�Ǳ� �� ���� ����� ���� ���۸� ����
{
	COORD Coor = { 0,0 };
	//COORD ��ǥ���� �����ϴ� ����ü
	DWORD dw;
	FillConsoleOutputCharacter(g_hScreen[g_nScreenIndex], ' ', 80 * 25, Coor, &dw);
	//buffer�� Coor��ǥ(0,0)���� ������ 80*25��ŭ ' '(����)���� ä���.
	//dw���� ���ۿ� ���� ��ϵ� ���ڼ��� �޴� ���� ������ *�̰� ��������� �𸣰ڴ� ���߿� �˾ƺ���
}

void ScreenFlipping() //ȯ��ȭ�� ���ۿ� ��Ȱ��ȭ�� ������ ���¸� �ٲٴ� �Լ�
{
	SetConsoleActiveScreenBuffer(g_hScreen[g_nScreenIndex]);
		//SetConsoleActiveScreenBuffer() : ��ũ�� ���� �� �ֿܼ� ǥ�õǴ� ���۸� �����Ѵ�
	g_nScreenIndex = !g_nScreenIndex;
}

void ScreenRelease() //��, ���� ���۸� ��� �����ϴ� �Լ�
{
	CloseHandle(g_hScreen[0]);
	//ȭ�� ����
	CloseHandle(g_hScreen[1]);
}

void ScreenPrint(int x, int y, char* string)//��ǥ�� string�� ���
{
	DWORD dw;
	COORD CursorPosision = { x,y };
	SetConsoleCursorPosition(g_hScreen[g_nScreenIndex], CursorPosision);
		//SetConsoleCursorPosition : �ֿܼ� �ִ� Ŀ���� �Էµ� ��ǥ�� �̵����ִ� �Լ�
	WriteFile(g_hScreen[g_nScreenIndex], string, strlen(string), &dw, NULL);
		//WriteFile : ���ϵ����͸� ���� �Լ�. �� ����, �����͸� ���� ��¼���� ������, �������� ����, 
		//����Ʈ ���� ���Ϲ޴� �μ�(�Լ��� ȣ��Ǿ����� 0���� �ʱ�ȭ��), �񵿱� ����� ��¼�� �ٵ� ������ �Ⱦ��ϱ� NULL
}

void SetColor(unsigned short color)//ȭ�鿡 ����� ���� ���� ����
{
	SetConsoleTextAttribute(g_hScreen[g_nScreenIndex], color);
		//SetConsoleTextAttribute() : ����ڵ�� ������ �Է��ϸ� ������ �ٲ۴�
}