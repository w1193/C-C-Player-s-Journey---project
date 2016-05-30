#include <stdio.h>
#include <conio.h>
#include <string.h>
#include "Screen.c"
#include <windows.h>
#include <time.h>
#pragma warning(disable:4996)

enum ControlKeys
{
	SPACE = 32,
	LEFT = 75,
	RIGHT = 77
}; // Ű ����

//typedef

typedef enum _DIRECT { TOP, L_TOP, L_DOWN, DOWN, R_DOWN, R_TOP} DIRECT; // ����� �ð�ݴ����
typedef struct _BALL 
{
	int InReady; // �غ�����ΰ�?
	int Life; // Life. (=������ȸ?)
	int X, Y; // ���� ��ǥ
	DIRECT Direct; // ���� �̵�����
	clock_t MoveTime, OldTime;
} BALL; // ��
typedef struct _STICK
{
	int X[3]; // ������� : 3
	int Y;
}STICK; // ����

// ���� ����

clock_t CurTime, OldTime;
char *p_KeyMessage[] = { "Left", "Right", "Shoot", "Catch" }; // Ű �Է¿� ���� ���
int p_Index = 1; // ��� �޽��� �ε���.

//�Լ� ����

void Init();
void Update();
void Render();
void Release();

void main()
{
	int Key;

	ScreenInit();
	Init();

	while (1)
	{
		Key = _getch();
		OldTime = clock();

		if (Key == 'q')
			break; // ��������

		switch (Key)
		{
		case LEFT:
			p_Index = 0;

			break;

		case RIGHT:
			p_Index = 1;

			break;

		case SPACE:
			if (p_Index == 2)
			{
				p_Index = 3;
			}
			else
			{
				p_Index = 2;
			}

			break;

		}

		Update();
		Render();

	}
	
	Release();
	ScreenRelease();
}

void Init()
{

}

void Update()
{

}

void Render()
{
	ScreenClear();

	if (p_Index >= 0) // ��� �ε����� -1�� ��� X
		ScreenPrint(10, 10, p_KeyMessage[p_Index]);	



	// �ð� ��
	CurTime = clock();
	ScreenFlipping();
}

void Release()
{

}