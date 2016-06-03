#include <stdio.h> // printf scanf sprintf
#include <stdlib.h> // rand
#include <time.h> // time, clock_t
#include <conio.h> // _getch
#include "Screen.c"
#pragma warning(disable:4996)

#define DotNum 10
#define BOARD_WIDTH 35       // 게임 영역의 가로(열) >= 10 : ━
#define BOARD_HEIGHT 20      // 게임 영역의 세로(행) >= 20 : | 

// 열거형 선언

enum ControlKeys
{
	UP = 72,
	DOWN = 80,
	LEFT = 75,
	RIGHT = 77,
	SPACE = 32
};

// 구조체 선언

typedef struct _PLAYER
{
	int X, Y; // 플레이어 캐릭터의 X, Y 좌표
	clock_t MoveTime;
	int InStop; // Stop상태? OR Move 상태?
}PLAYER;

typedef struct _DOT
{
	int X, Y; // 점의 X, Y 좌표
	int A, K; // 일차함수의 기울기, y절편
	int Crash; // 벽에 충돌?
}DOT;

PLAYER Player;
DOT Dot[DotNum];

// 플레이어와 점의 모양 

char Player_Shape[] = {"*"};
char Dot_Shape[] = "·";

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
void DrawField(void) // 필드 틀 제시. (수정 필요)
{
	int x, y;

	//위 보드 라인
	for (x = 1; x < BOARD_WIDTH ; x++)
	{
		ScreenPrint(x,0," ━ ");
	}
	//아래 보드 라인
	for (x = 1; x < BOARD_WIDTH ; x++)
	{
		ScreenPrint(x, BOARD_HEIGHT, " ━ ");
	}
	//왼쪽 보드 라인
	for (y = 0; y < BOARD_HEIGHT + 1; y++)
	{

		if (y == BOARD_HEIGHT)
			ScreenPrint(0, y, "┗");
		else if (y == 0)
			ScreenPrint(0, y, "┏");
		else
			ScreenPrint(0,y,"┃");
	}
	//오른쪽 보드 라인
	for (y = 0; y < BOARD_HEIGHT + 1; y++)
	{
		if (y == BOARD_HEIGHT)
			ScreenPrint(BOARD_WIDTH, y, "┛");
		else if (y ==0)
			ScreenPrint(BOARD_WIDTH, y, "┓");
		else
			ScreenPrint(BOARD_WIDTH,y,"┃");
	}
}

// 프레임워크 함수 시작

void Init()
{
	// 필드 표시

	// PLAYER 초기화

	Player.X =10;
	Player.Y = 10;

	// DOT[] 초기화
	
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

	// 화면 표시
	DrawField();

	ScreenPrint(Player.X, Player.Y, Player_Shape); // 플레이어 표시

	for (int i = 0; i < DotNum; i++)
	{
		ScreenPrint(Dot[i].X, Dot[i].Y, Dot_Shape); // 점 표시
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