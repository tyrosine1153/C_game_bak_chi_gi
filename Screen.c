#include<windows.h>

static int g_nScreenIndex;
static HANDLE g_hScreen[2];

void ScreenInit()//화면 버퍼 초기화. 전, 후위 버퍼 생성. 커서 설정.
{
	CONSOLE_CURSOR_INFO cci;
	//콘솔의 커서에 대한 정보를 가지고 있다.
	//dwSize : 커서로 채워지는 문자 셀의 비율(1~100), bVisible : 화면 표시 여부

	//화면 버퍼 2개를 만든다
	g_hScreen[0] = CreateConsoleScreenBuffer
		//CreateConsoleScreenBuffer() : Screen Buffer를 생성한다. Flipping을 구현하고있다.
	(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	g_hScreen[0] = CreateConsoleScreenBuffer
	(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);

	//커서 숨기기
	cci.dwSize = 1;
	cci.bVisible = FALSE;
	SetConsoleCursorInfo(g_hScreen[0], &cci);
	//생성한 스크린 버퍼에 설정한 커서의 정보를 대입한다
	SetConsoleCursorInfo(g_hScreen[1], &cci);
}

void ScreenClear() //버퍼가 교체되기 전 다음 장면을 위해 버퍼를 지움
{
	COORD Coor = { 0,0 };
	//COORD 좌표값을 저장하는 구조체
	DWORD dw;
	FillConsoleOutputCharacter(g_hScreen[g_nScreenIndex], ' ', 80 * 25, Coor, &dw);
	//buffer에 Coor좌표(0,0)부터 시작해 80*25만큼 ' '(공백)으로 채운다.
	//dw값은 버퍼에 실제 기록된 문자수를 받는 변수 포인터 *이거 어따쓰는지 모르겠다 나중에 알아보자
}

void ScreenFlipping() //환성화된 버퍼와 비활성화된 버퍼의 상태를 바꾸는 함수
{
	SetConsoleActiveScreenBuffer(g_hScreen[g_nScreenIndex]);
		//SetConsoleActiveScreenBuffer() : 스크린 버퍼 중 콘솔에 표시되는 버퍼를 결정한다
	g_nScreenIndex = !g_nScreenIndex;
}

void ScreenRelease() //전, 후위 버퍼를 모두 해제하는 함수
{
	CloseHandle(g_hScreen[0]);
	//화면 해제
	CloseHandle(g_hScreen[1]);
}

void ScreenPrint(int x, int y, char* string)//좌표에 string을 출력
{
	DWORD dw;
	COORD CursorPosision = { x,y };
	SetConsoleCursorPosition(g_hScreen[g_nScreenIndex], CursorPosision);
		//SetConsoleCursorPosition : 콘솔에 있는 커서를 입력된 좌표로 이동해주는 함수
	WriteFile(g_hScreen[g_nScreenIndex], string, strlen(string), &dw, NULL);
		//WriteFile : 파일데이터를 쓰는 함수. 쓸 파일, 데이터를 가진 어쩌구의 포인터, 데이터의 길이, 
		//바이트 수를 리턴받는 인수(함수가 호출되었을때 0으로 초기화됨), 비동기 입출력 어쩌구 근데 지금은 안쓰니까 NULL
}

void SetColor(unsigned short color)//화면에 출력할 문자 색상값 지정
{
	SetConsoleTextAttribute(g_hScreen[g_nScreenIndex], color);
		//SetConsoleTextAttribute() : 출력핸들과 색상을 입력하면 색상을 바꾼다
}