#include<Windows.h>

static int cur_screen_index;
static HANDLE screen_buffer[2];

// ȭ�� ���� �ʱ�ȭ. ��, ���� ���� ����. Ŀ�� ����.
void ScreenInit()
{
	// �ܼ��� Ŀ���� ���� ������ ������ �ִ�.
	// dwSize : Ŀ���� ä������ ���� ���� ����(1~100), bVisible : ȭ�� ǥ�� ����
	CONSOLE_CURSOR_INFO cci;

	// ȭ�� ���� 2���� �����
	screen_buffer[0] = CreateConsoleScreenBuffer
	(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	screen_buffer[1] = CreateConsoleScreenBuffer
	(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);

	//Ŀ�� �����
	cci.dwSize = 1;
	cci.bVisible = FALSE;

	//������ ��ũ�� ���ۿ� ������ Ŀ���� ������ �����Ѵ�
	SetConsoleCursorInfo(screen_buffer[0], &cci);
	SetConsoleCursorInfo(screen_buffer[1], &cci);
}

// ���۰� ��ü�Ǳ� �� ���� ����� ���� ���۸� ����
void ScreenClear()
{
	//COORD ��ǥ���� �����ϴ� ����ü
	COORD coor = { 0,0 };
	DWORD dw;

	//buffer�� Coor��ǥ(0,0)���� ������ 80*25��ŭ ' '(����)���� ä���.
	//dw���� ���ۿ� ���� ��ϵ� ���ڼ��� �޴� ���� ������ *�̰� ��������� �𸣰ڴ� ���߿� �˾ƺ���
	FillConsoleOutputCharacter(screen_buffer[cur_screen_index], ' ', 80 * 25, coor, &dw);
}

// Ȱ��ȭ�� ���ۿ� ��Ȱ��ȭ�� ������ ���¸� �ٲٴ� �Լ�
void ScreenFlipping()
{
	//SetConsoleActiveScreenBuffer() : ��ũ�� ���� �� �ֿܼ� ǥ�õǴ� ���۸� �����Ѵ�
	SetConsoleActiveScreenBuffer(screen_buffer[cur_screen_index]);
	cur_screen_index = !cur_screen_index;
}

// ��, ���� ���۸� ��� �����ϴ� �Լ�
void ScreenRelease()
{
	CloseHandle(screen_buffer[0]);
	CloseHandle(screen_buffer[1]);
}

// ��ǥ�� string�� ���
void ScreenPrint(int x, int y, char* string)
{
	COORD cursor_posision = { x, y };
	DWORD dw;

	// SetConsoleCursorPosition : �ֿܼ� �ִ� Ŀ���� �Էµ� ��ǥ�� �̵����ִ� �Լ�
	SetConsoleCursorPosition(screen_buffer[cur_screen_index], cursor_posision);

	// WriteFile : ���ϵ����͸� ���� �Լ�. �� ����, �����͸� ���� ��¼���� ������, �������� ����,
    // ����Ʈ ���� ���Ϲ޴� �μ�(�Լ��� ȣ��Ǿ����� 0���� �ʱ�ȭ��), �񵿱� ����� ��¼�� �ٵ� ������ �Ⱦ��ϱ� NULL
	WriteFile(screen_buffer[cur_screen_index], string, strlen(string), &dw, NULL);
}

// ȭ�鿡 ����� ���� ���� ����
void SetColor(unsigned short color)
{
	//SetConsoleTextAttribute() : ����ڵ�� ������ �Է��ϸ� ������ �ٲ۴�
	SetConsoleTextAttribute(screen_buffer[cur_screen_index], color);
}
