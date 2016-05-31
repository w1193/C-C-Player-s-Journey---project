#include <stdio.h> // printf scanf sprintf
#include <stdlib.h> // rand
#include <time.h> // time, clock_t
#include <conio.h> // _getch
#include "Screen.c"
#pragma warning(disable:4996)

// ������ ����

enum ControlKeys
{
	UP = 72,
	DOWN = 80,
	LEFT = 75,
	RIGHT = 77,
	SPACE = 32
};

// ����ü ����

typedef struct _PLAYER
{
	int X, Y; // �÷��̾� ĳ������ X, Y ��ǥ
	clock_t MoveTime;
	int InStop; // Stop����? OR Move ����?
}PLAYER;

typedef struct _DOT
{
	int X, Y; // ���� X, Y ��ǥ
	int A, K; // �����Լ��� ����, y����
	int Crash; // ���� �浹?
}DOT;

PLAYER Player;
DOT Dot[100];

// �÷��̾�� ���� ��� 

char Player_Shape[] = "*";
char Dot_Shape[] = "��";

/*
int MoveFunction(int x, int y)
{
	int a, k;
	a=
	y = a*x + k;
	return y;
}
*/

void Init()
{
	/*
	srand((unsigned)time(0)); // rand() �Լ��� �������� �ֱ� ���ؼ� �ʱⰪ �ο�

	int i;
	for (i = 0; i < 100; i++)
	{
		DOT[i].A = rand();
	}
	*/

	// PLAYER �ʱ�ȭ

	Player.X = Player.Y = 30;
}

void Update()
{

}

void Render()
{
	ScreenClear();

}

void Release()
{

}

void KeyControl(int key)
{

	switch (key)
	{
	case UP:
		Player.Y--;
		printf("Up");
		break;

	case DOWN:
		Player.Y++;
		break;

	case LEFT:
		Player.X--;
		break;

	case RIGHT:
		Player.X++;
		break;

	case SPACE:

		break;
	}
}

void main()
{
	int Key;

	ScreenInit();
	Init();

	while (1)
	{
		if (_kbhit())
		{
			Key = _getch();

			if (Key == 'q')
				break;

			KeyControl(Key);
			
		}
		Update();
		Render();
	}

	Release();
	ScreenRelease();
}