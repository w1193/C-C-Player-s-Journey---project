#include <stdio.h> // printf scanf sprintf
#include <stdlib.h> // rand
#include <time.h> // time, clock_t
#include <conio.h> // _getch
#include "Screen.c"
#pragma warning(disable:4996)

#define DotNum 10
#define BOARD_WIDTH 35       // ���� ������ ����(��) >= 10 : ��
#define BOARD_HEIGHT 20      // ���� ������ ����(��) >= 20 : | 

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
DOT Dot[DotNum];

// �÷��̾�� ���� ��� 

char Player_Shape[] = {"*"};
char Dot_Shape[] = "��";

void KeyControl(int key)
{

	switch (key)
	{
	case UP:
		Player.Y--;
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
/*
	case SPACE:

		break;
		*/
	}
}

void TimeTerm()
{
	clock_t CurTime, OldTime;

	OldTime = clock();
	while (1)
	{
		CurTime = clock();

		if (CurTime - OldTime > 0.1 * 1000)
		{
			break;
		}
	}
}
void DrawField(void) // �ʵ� Ʋ ����. (���� �ʿ�)
{
	int x, y;

	//�� ���� ����
	for (x = 1; x < BOARD_WIDTH ; x++)
	{
		ScreenPrint(x,0," �� ");
	}
	//�Ʒ� ���� ����
	for (x = 1; x < BOARD_WIDTH ; x++)
	{
		ScreenPrint(x, BOARD_HEIGHT, " �� ");
	}
	//���� ���� ����
	for (y = 0; y < BOARD_HEIGHT + 1; y++)
	{

		if (y == BOARD_HEIGHT)
			ScreenPrint(0, y, "��");
		else if (y == 0)
			ScreenPrint(0, y, "��");
		else
			ScreenPrint(0,y,"��");
	}
	//������ ���� ����
	for (y = 0; y < BOARD_HEIGHT + 1; y++)
	{
		if (y == BOARD_HEIGHT)
			ScreenPrint(BOARD_WIDTH, y, "��");
		else if (y ==0)
			ScreenPrint(BOARD_WIDTH, y, "��");
		else
			ScreenPrint(BOARD_WIDTH,y,"��");
	}
}

// �����ӿ�ũ �Լ� ����

void Init()
{
	// �ʵ� ǥ��

	// PLAYER �ʱ�ȭ

	Player.X =10;
	Player.Y = 10;

	// DOT[] �ʱ�ȭ
	
	//int i=0;
	srand((unsigned)time(NULL));

	for (int i = 0; i < DotNum; i++)
	{
		Dot[i].A = rand()%9;
		Dot[i].K = rand()%9;
		
		Dot[i].X = 0;
		Dot[i].Y = Dot[i].A * Dot[i].X + Dot[i].K;
	}
	
}

void Update()
{
	for (int i = 0; i < DotNum; i++)
	{
		Dot[i].X++;
	}

	for (int i = 0; i < DotNum; i++)
	{
		if (Dot[i].X > BOARD_WIDTH)
		{
			Dot[i].X = Dot[i].Y=0;
		}
		if (Dot[i].Y > BOARD_HEIGHT || Dot[i].Y < 0)
		{
			Dot[i].X = Dot[i].Y = 0;
		}

	}
}

void Render()
{
	ScreenClear();

	// ȭ�� ǥ��
	DrawField();

	ScreenPrint(Player.X, Player.Y, Player_Shape); // �÷��̾� ǥ��

	for (int i = 0; i < DotNum; i++)
	{
		ScreenPrint(Dot[i].X, Dot[i].Y, Dot_Shape); // �� ǥ��
	}

	ScreenFlipping();
}

void Release()
{

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

	//	TimeTerm();
	}

	Release();
	ScreenRelease();
}