#pragma warning(disable:4996)
#include<stdio.h>
#include<time.h>//C��� ǥ�� ���̺귯��. �ð�/��¥�� ��� ����
#include<conio.h>//�ܼ� ����� ����
#include"Screen.h"
#include"fps.h"


void Init() 
{
	
}

void Update() 
{

}

void Render()
{
	ScreenClear();
	ScreenFlipping();
}

void Release()
{

}

int main() //�ʱ�ȭ->((�ݺ�)�����Ͱ���->ȭ�����)->����
{
	int nKey;
	clock_t CurTime, OldTime;//clock_t : ƽ(�ð��� �����ϴ� �����ֱ�)�� �����ϴ� ����
	
	ScreenInit();
	Init();//�ʱ�ȭ
	
	while (1)
	{
		if (_kbhit()) //_kbhit() : Ű�� �������� Ȯ���ϴ� �Լ�
		{
			nKey = _getch();//_getch() : ���� ���ڸ� ��ȯ
			if (nKey == 'q')break;
			switch (nKey) 
			{
			case 'j':
				break;
			case 'l':
				break;
			}
		}

		OldTime = clock();//OldTime�� clock()�Լ��� render�� �ð��� �Է�
		//clock() : ���α׷��� ���۵ɶ� ���� ���� ƽ �� ��ȯ
		Update();//�����Ͱ���
		Render();//ȭ�����
		
		while (1) 
		{
			CurTime = clock();//�����¿� �� �� CurTime�� ��� ����
			if (CurTime - OldTime > 33) break;//CurTime�� OldTime�� ���� 33(ms)�� �� �����¸� ����������.
			/*�ֿܼ��� ������� ȸ���� ����� �ϸ� �������� �߻��Ѵ�
			->������� �׸��� ���ð��� �ξ� ������ �ӵ��� �����
			->���� 1�ʿ� 30�̻��� ȭ����ȯ�� �ε巴�� �ν���->33ms�� ���ð�*/
		} //33ms ���
	}

	Release();//����
	ScreenRelease();
	return 0;
}