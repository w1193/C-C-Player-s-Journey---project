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

typedef enum _GAMESTATUS { START, INIT, READY, RUNNING, STOP, RESULT } GAMESTATUS;

// ����ü ����

typedef struct _PLAYER
{
	int X, Y; // �÷��̾� ĳ������ X, Y ��ǥ
//	clock_t MoveTime;
	int InStop; // Stop����? OR Move ����?
	int Life; // Life.
//	int Crash; // Dot���� �浹. if (Crash==1) -> Life--; Crash=0;
}PLAYER;

typedef struct _DOT
{
	int X, Y; // ���� X, Y ��ǥ
//	int Crash; // ���� �浹?
	clock_t MoveTime, OldTime;
	clock_t	Speed; // �ӵ�
	int DirectionX,DirectionY; // �̵�����
}DOT;

// ���� ���� ����

PLAYER Player;
DOT Dot[DotNum];
GAMESTATUS GameStatus;

char String[100];

// �÷��̾�� ���� ��� 

char Player_Shape[] = {"*"};
char Dot_Shape[] = "��";

// �Լ� ����

void KeyControl(int key) // Ű �Է� ó��
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

	case SPACE:
		//���� ���� / �Ͻ����� 
		if (GameStatus == START)
			GameStatus = INIT;
		break;
		
	}
}

void IfCrash(int i) // Crash �߻� ó��
{
	if (Player.X == Dot[i].X)
		Player.Life--;
	
	if (Player.Life==0)
		GameStatus = STOP;
		
}

void MoveCoord(int i) // ��ǥ �̵�
{
	clock_t CurTime = clock();
	
	if (CurTime - Dot[i].OldTime > Dot[i].MoveTime) // MoveTime�� ������ Update. -> �ӵ� ����
	{

		// ��ǥ �̵� ����

		Dot[i].Y++;

		if (Dot[i].Y == BOARD_HEIGHT - 1)
			Dot[i].Y = 2;

		// �ð� �缳��

		Dot[i].OldTime = CurTime;

	}
}

void StatusPrint()
{
	switch (GameStatus)
	{
	case START:

		break;

	case INIT:

		break;

	case READY:

		break;

	case RUNNING:

		break;

	case STOP:

		break;

	case RESULT:

		break;
	}
}

// �����ӿ�ũ �Լ� ����

void Init()
{
	// �ʵ� ǥ��

	// GameStatus �ʱ�ȭ

	GameStatus = INIT;

	// PLAYER �ʱ�ȭ

	Player.X =10;
	Player.Y = 10;

	Player.Life = 3;
//	Player.Crash = 0; 

	// DOT[] �ʱ�ȭ

	srand((unsigned)time(NULL));

	for (int i = 0; i < DotNum; i++)
	{
		// X Y ��ǥ �ʱ�ȭ
		
		Dot[i].X = rand() % BOARD_WIDTH;
		Dot[i].Y = 2;

		// Dot �ð� & �ӵ� ����

		Dot[i].OldTime = clock();
		Dot[i].Speed = rand() % 3 + 1; // ���ڰ� ���� ���� �ӵ��� ������.
		Dot[i].MoveTime = Dot[i].Speed * 0.1 * 1000; // �� Dot���� �ٸ� MoveTime �ο�
		
	}
}

void Update()
{

	for (int i = 0; i < DotNum; i++)
	{
		MoveCoord(i); // ��ǥ�̵�
		
		IfCrash(i);
	}
}

void Render()
{
	char string[100];

	ScreenClear();
	
	// ������

	sprintf(string, "���ΰ� �̵���ǥ : %d, %d              �� �� : Test              �ʱ�ȭ : R ��ư\n", Player.X, Player.Y); // ��Ʈ �����ϱ�
	ScreenPrint(0, 0, string);
	
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