#include <stdio.h> // printf scanf sprintf
#include <stdlib.h> // rand
#include <time.h> // time, clock_t
#include <conio.h> // _getch
#include "Screen.c"
#pragma warning(disable:4996)

#define DotNum 15 // Dot�� ����
#define BOARD_WIDTH 80      // ȭ���� �ʺ�
#define BOARD_HEIGHT 25      // ȭ���� ����

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
	int Life; // Life.
	int Crash; // Dot���� �浹. if (Crash==1) -> Life--; Crash=0;
}PLAYER;

typedef struct _DOT
{
	int X, Y; // ���� X, Y ��ǥ
	int A, K; // �����Լ��� ����, y����
	int Crash; // ���� �浹?
	clock_t MoveTime, OldTime;
	int Direction; // �̵�����
}DOT;

// ���� ���� ����

PLAYER Player;
DOT Dot[DotNum];

char String[100];

// �÷��̾�� ���� ��� 

char Player_Shape[] = {"*"};
char Dot_Shape[] = "��";

// �Լ� ����

void Clipping() // Ŭ����
{

	if (Player.X < 0)
	{
		ScreenPrint(0, Player.Y, Player_Shape);
	}
	else if (Player.X + 1 > 79)
	{
		ScreenPrint(Player.X, Player.Y, Player_Shape);
	}
	else 
	{
		ScreenPrint(Player.X, Player.Y, Player_Shape);
	}

}

void KeyControl(int key) // �Է� Ű ó��
{

	switch (key)
	{
	case UP:
		if (!Player.Y==0)
			Player.Y--;
		break;

	case DOWN:
		if (!(Player.Y==(BOARD_HEIGHT-1)))
			Player.Y++;
		break;

	case LEFT:
		if (!Player.X==0)
			Player.X--;
		break;

	case RIGHT:
		if (!(Player.X==(BOARD_WIDTH-1)))
			Player.X++;
		break;
/*
	case SPACE:
		���� ���� / �Ͻ����� 
		break;
		*/
	}
}

void TimeTerm(int term)
{
	clock_t CurTime, OldTime;

	OldTime = clock();
	while (1)
	{
		CurTime = clock();

		if (CurTime - OldTime > term * 0.1*1000)
		{
			break;
		}
	}
}


// �����ӿ�ũ �Լ� ����

void Init()
{
	// �ʵ� ǥ��

	// PLAYER �ʱ�ȭ

	Player.X =10;
	Player.Y = 10;

	Player.Life = 3;
	Player.Crash = 0; 

	// DOT[] �ʱ�ȭ

	srand((unsigned)time(NULL));

	for (int i = 0; i < DotNum; i++)
	{
		Dot[i].A = rand() % 5;
		Dot[i].K = rand() % 9;
		
		// Dot ��ġ �й�
		
		if (i % 2 == 1)
		{
			Dot[i].X = 0;
			Dot[i].Y = rand() % BOARD_HEIGHT; // Dot�� �̵���ġ�� ��Ÿ���� �����Լ� y=ax+k
		}
		else
		{
			Dot[i].X = rand() % BOARD_WIDTH;
			Dot[i].Y = 0;
		}

		// Dot ���� ����

		if (0 <= Dot[i].X <= BOARD_WIDTH / 2)
			Dot[i].Direction = 1; // ���� : ��
		else
			Dot[i].Direction = -1; // ���� : ��

		// Dot �ð� ����

		Dot[i].OldTime = clock();
		Dot[i].MoveTime = Dot[i].A * 0.1 * 1000; // �� Dot���� �ٸ� MoveTime �ο�
		
	}
}

void Update()
{
	clock_t CurTime = clock();

	for (int i = 0; i < DotNum; i++)
	{

		if (CurTime - Dot[i].OldTime > Dot[i].MoveTime) // MoveTime�� ������ Update. -> �ӵ� ����
		{
			// ��ǥ ��ȯ ����

			if (Dot[i].X == 0 && Dot[i].X == BOARD_HEIGHT-1)
			{
				Dot[i].Direction *= -1; // ���� ������ ���� ��ȭ
			}

			Dot[i].X += Dot[i].Direction;
			Dot[i].Y = Dot[i].Direction * (Dot[i].A * Dot[i].X + Dot[i].K); // �����Լ� y=ax+k

			// �ð� �缳��

			Dot[i].OldTime = CurTime;
			
		}
	}
}

void Render()
{
	ScreenClear();

	// Ŭ���� (���� �ʿ�)

	//Clipping();

	// ������

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

	}

	Release();
	ScreenRelease();
}