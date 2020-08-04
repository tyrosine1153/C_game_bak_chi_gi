#pragma warning(disable:4996)
#include<stdio.h>
#include<time.h>//C언어 표준 라이브러리. 시간/날짜를 얻고 조작
#include<conio.h>//콘솔 입출력 제궁
#include<malloc.h>
#include"Screen.h"

clock_t FPSCurTime, FPSOldTime;
int FrameCnt;
char* FPSTextBuffer;
//int temp;
//char* stemp;

void Init() 
{
	//temp = 0;
	FrameCnt = 0;
	FPSTextBuffer = (char*)malloc(sizeof(char) * 10);
	//stemp = (char*)malloc(sizeof(char) * 1000);
	sprintf(FPSTextBuffer,"FPS : %d",FrameCnt);
	FPSOldTime = clock();
}

void Update() 
{

}

void Render()
{
	ScreenClear();
	FrameCnt++;
	//temp++;
	FPSCurTime = clock();
	if (FPSCurTime - FPSOldTime >= 1000) {
		sprintf(FPSTextBuffer, "FPS : %d", FrameCnt);
		FPSOldTime = clock();
		FrameCnt = 0;
	}
	ScreenPrint(0, 0, FPSTextBuffer);
	//sprintf(stemp, "%d", temp);
	//ScreenPrint(0,0,stemp);
	ScreenFlipping();
}

void Release()
{
	free(FPSTextBuffer);
}

int main() //초기화->((반복)데이터갱신->화면출력)->해제
{
	int nKey;
	clock_t CurTime, OldTime;//clock_t : 틱(시간을 측정하는 기준주기)를 저장하는 형식
	
	ScreenInit();
	Init();//초기화
	
	while (1)
	{
		if (_kbhit()) //_kbhit() : 키가 눌렸음을 확인하는 함수
		{
			nKey = _getch();//_getch() : 읽은 문자를 반환
			if (nKey == 'q')break;
			switch (nKey) 
			{
			case 'j':
				break;
			case 'l':
				break;
			}
		}

		OldTime = clock();//OldTime에 clock()함수로 render전 시간을 입력
		//clock() : 프로그램이 시작될때 부터 지난 틱 수 반환
		Update();//데이터갱신
		Render();//화면출력
		
		while (1) 
		{
			CurTime = clock();//대기상태에 들어간 후 CurTime을 계속 갱신
			if (CurTime - OldTime > 33) break;//CurTime과 OldTime의 차가 33(ms)일 때 대기상태를 빠져나간다.
			/*콘솔에서 고속으로 회면을 지우게 하면 깜빡임이 발생한다
			->한장면을 그리고 대기시간을 두어 렌더의 속도를 늦춘다
			->눈은 1초에 30이상의 화면전환을 부드럽게 인식함->33ms의 대기시간*/
		} //33ms 대기
	}

	Release();//해제
	ScreenRelease();
	return 0;
}