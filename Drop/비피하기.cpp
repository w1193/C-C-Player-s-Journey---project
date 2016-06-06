#include <stdio.h> // printf scanf sprintf
#include <stdlib.h> // rand
#include <time.h> // time, clock_t
#include <conio.h> // _getch
#include "Screen.c"
#pragma warning(disable:4996)

#define DotNum 15 // Dot�� ����
#define StageNum 3 // Stage ����
#define BOARD_WIDTH 80      // ȭ���� �ʺ�
#define BOARD_HEIGHT 25      // ȭ���� ����
#define Invincible 3 // �����ð�

// ������ ����

enum ControlKeys
{
	UP = 72,
	DOWN = 80,
	LEFT = 75,
	RIGHT = 77,
	SPACE = 32
};

typedef enum _GAMESTATUS { START, INIT, READY, RUNNING, STOP, JUDGMENT, NEXT, RESULT } GAMESTATUS;

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
/*
typedef struct _STAGE
{
	int MinSpeed, MaxSpeed; // Dot�� �ּ� �ִ� �ӵ�
	int DotNum; // Dot�� ����
}STAGE;
*/
// ���� ���� ����

// ����ü ����

PLAYER Player;
DOT Dot[DotNum*4];
//STAGE Stage[3] = { {},{},{} }; // �ּҼӵ�, �ִ�ӵ�, ����
GAMESTATUS GameStatus;

// �������� ����

int Stage=0;

// ���� ���� ����

char StatString[500]; // ���� ���� String
int PrintTime = 3 * 1000; // ���� ���� ǥ�� �ð�
clock_t Stat_OldTime = clock(); // PrintTime�� OldTime

// �÷��̾�� ���� ��� 

char Player_Shape[] = {"*"};
char Dot_Shape[4][3] = { {"��"},{"��"},{"��"},{"��"} };

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
		switch (GameStatus)
		{
		case START:
			GameStatus = INIT;
			break;

		case RUNNING:
			GameStatus = STOP;
			break;

		case STOP:
			GameStatus = RUNNING;
			break;
		}
		break;
		
	}
}

void IfCrash(int i) // Crash �߻� ó��
{
	if ((Player.X == Dot[i].X && Player.Y == Dot[i].Y) || ( (Player.X-1) == Dot[i].X && Player.Y == Dot[i].Y) )
	{
		Player.Life--;
		Dot[i].Y = 0;
	}

	if (Player.Life<=0)
		GameStatus = NEXT;
		
}

void MoveCoord(int i) // ��ǥ �̵�
{
	clock_t CurTime = clock();
	
	if (CurTime - Dot[i].OldTime > Dot[i].MoveTime) // MoveTime�� ������ Update. -> �ӵ� ����
	{

		// ��ǥ �̵� ����
		
		if (i >= 0 && i < DotNum) // ��
		{
			Dot[i].Y++;
			if (Dot[i].Y == BOARD_HEIGHT - 1)
				Dot[i].Y = 2;
		}
		if (i >= DotNum && i < DotNum*2) // ��
		{
			Dot[i].Y--;
			if (Dot[i].Y == 2)
				Dot[i].Y = BOARD_HEIGHT - 1;
		}
		if (i >= DotNum*2 && i < DotNum*3) // ��
		{
			Dot[i].X++;
			if (Dot[i].X == BOARD_WIDTH - 1)
				Dot[i].X = 0;
		}
		if (i >= DotNum*3 && i < DotNum*4) // ��
		{
			Dot[i].X--;
			if (Dot[i].X == 0)
				Dot[i].X = BOARD_WIDTH - 1;
		}

		// �ð� �缳��

		Dot[i].OldTime = CurTime;

	}
}

void DotInit()
{
	int i;

	srand((unsigned)time(NULL));

	switch (Stage)
	{
	case 2: // �� ��
		for (i = DotNum * 2; i < DotNum * 3; i++) // ��
		{
			// X Y ��ǥ �ʱ�ȭ

			Dot[i].X = 0;
			Dot[i].Y = rand() % BOARD_HEIGHT;

			// Dot �ð� & �ӵ� ����

			Dot[i].OldTime = clock();
			Dot[i].Speed = rand() % 3 + 1; // ���ڰ� ���� ���� �ӵ��� ������.
			Dot[i].MoveTime = Dot[i].Speed * 0.1 * 1000; // �� Dot���� �ٸ� MoveTime �ο�
		}

		for (i = DotNum * 3; i < DotNum * 4; i++) // ��
		{
			// X Y ��ǥ �ʱ�ȭ

			Dot[i].X = BOARD_WIDTH - 1;
			Dot[i].Y = rand() % BOARD_HEIGHT;

			// Dot �ð� & �ӵ� ����

			Dot[i].OldTime = clock();
			Dot[i].Speed = rand() % 3 + 1; // ���ڰ� ���� ���� �ӵ��� ������.
			Dot[i].MoveTime = Dot[i].Speed * 0.1 * 1000; // �� Dot���� �ٸ� MoveTime �ο�
		}
	case 1: // ��
		for (i = DotNum; i < DotNum * 2; i++)
		{
			// X Y ��ǥ �ʱ�ȭ

			Dot[i].X = rand() % BOARD_WIDTH;
			Dot[i].Y = BOARD_HEIGHT - 1;

			// Dot �ð� & �ӵ� ����

			Dot[i].OldTime = clock();
			Dot[i].Speed = rand() % 3 + 1; // ���ڰ� ���� ���� �ӵ��� ������.
			Dot[i].MoveTime = Dot[i].Speed * 0.1 * 1000; // �� Dot���� �ٸ� MoveTime �ο�
		}
	case 0: // ��
		for (i = 0; i < DotNum; i++)
		{
			// X Y ��ǥ �ʱ�ȭ

			Dot[i].X = rand() % BOARD_WIDTH;
			Dot[i].Y = 2;

			// Dot �ð� & �ӵ� ����

			Dot[i].OldTime = clock();
			Dot[i].Speed = rand() % 3 + 1; // ���ڰ� ���� ���� �ӵ��� ������.
			Dot[i].MoveTime = Dot[i].Speed * 0.1 * 1000; // �� Dot���� �ٸ� MoveTime �ο�
		}
			break;
		
	}
}


void StatusPrint()
{
	clock_t CurTime;

	CurTime = clock();

	switch (GameStatus)
	{
	case START:
		sprintf(StatString, "\t\t\t  [�� ���ϱ� ����] \n\n"
			"\t\t===================================\n\n"
			"\t\t�������� �� ���ϴ� �����Դϴ�.\n"
			"\t\t�� �������� �� Life�� 3 �Դϴ�. \n"
			"\t\t������ ��Ƽ�� �ð����� ���˴ϴ�.\n"
			"\t\t���������� �� 3������ �����Ǿ��ֽ��ϴ�.\n\n"
			"\t\t===================================\n\n"
			"\t\t\t  - �� �� �� -\n\n"
			"\t\t�̵� : ����Ű | �Ͻ����� : SPACE BAR\n\n"
			"\t\t-----------------------------------\n"
			"\t\t���� ���� : SPACE BAR | ���� ���� : q\n\n");
		ScreenPrint(0, 3, StatString);

		break;

	case INIT:
		if (CurTime - Stat_OldTime < PrintTime)
		{

			DotInit(); // Dot �ʱ�ȭ
			Player.Life = 3;

			sprintf(StatString, "INIT ȭ��");
			ScreenPrint(10, 10, StatString);
		}
		else
		{
			GameStatus = READY;
			Stat_OldTime = CurTime;
		}
		
		break;

	case READY:
		if (CurTime - Stat_OldTime < PrintTime)
		{
			sprintf(StatString, "REDAY ȭ��");
			ScreenPrint(10, 10, StatString);
		}
		else
		{
			GameStatus = RUNNING;
			Stat_OldTime = CurTime;
		}

		break;

	case RUNNING:

		break;

	case STOP:
		sprintf(StatString, "STOP ȭ��");
		ScreenPrint(10, 10, StatString);

		break;

	case JUDGMENT:


		break;

	case NEXT:
		if (CurTime - Stat_OldTime < PrintTime)
		{
			sprintf(StatString, "NEXT ȭ��");
			ScreenPrint(10, 10, StatString);
		}
		else
		{
			Stat_OldTime = CurTime;

			if (Stage < 2)
			{
				Stage++;
				GameStatus = INIT;
			}
			else
				GameStatus = RESULT;
		}
		break;

	case RESULT:
		sprintf(StatString, "RESULT ȭ��");
		ScreenPrint(10, 10, StatString);
		
		break;
	}
}

// �����ӿ�ũ �Լ� ����

void Init()
{
	// �ʵ� ǥ��

	// GameStatus �ʱ�ȭ

	GameStatus = START; // ������ ���� : START

	// PLAYER �ʱ�ȭ

	Player.X =10;
	Player.Y = 10;

	Player.Life = 3;

	// DOT[] �ʱ�ȭ

}

void Update()
{
	if (GameStatus == RUNNING)
	{
		for (int i = 0; i < DotNum; i++)
		{
			MoveCoord(i); // ��ǥ�̵�

			IfCrash(i);
		}
	}
}

void Render()
{
	char string[100];

	ScreenClear();
	
	// ������

	StatusPrint();

	if (GameStatus == RUNNING)
	{
		sprintf(string, "���ΰ� �̵���ǥ : %d, %d              Life : %d              �ʱ�ȭ : R ��ư\n", Player.X, Player.Y, Player.Life); // ��Ʈ �����ϱ�
		ScreenPrint(0, 0, string);

		ScreenPrint(Player.X, Player.Y, Player_Shape); // �÷��̾� ǥ��

		switch (Stage)
		{
		case 2:
			for (int i = DotNum*2; i < DotNum*3; i++)
			{
				ScreenPrint(Dot[i].X, Dot[i].Y, Dot_Shape[2]); // �� ǥ��
			}
			for (int i = DotNum*3; i < DotNum*4; i++)
			{
				ScreenPrint(Dot[i].X, Dot[i].Y, Dot_Shape[3]); // �� ǥ��
			}

		case 1:
			for (int i = DotNum; i < DotNum*2; i++)
			{
				ScreenPrint(Dot[i].X, Dot[i].Y, Dot_Shape[1]); // �� ǥ��
			}

		case 0:
			for (int i = 0; i < DotNum; i++)
			{
				ScreenPrint(Dot[i].X, Dot[i].Y, Dot_Shape[0]); // �� ǥ��
			}
			break;

		}
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