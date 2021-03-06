#include <stdio.h> // printf scanf sprintf
#include <stdlib.h> // rand
#include <time.h> // time, clock_t
#include <conio.h> // _getch
#include "Screen.c"
#pragma warning(disable:4996)

#define DotNum 15 // Dot의 개수
#define BOARD_WIDTH 80      // 화면의 너비
#define BOARD_HEIGHT 25      // 화면의 높이

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
	int Life; // Life.
	int Crash; // Dot과의 충돌. if (Crash==1) -> Life--; Crash=0;
}PLAYER;

typedef struct _DOT
{
	int X, Y; // 점의 X, Y 좌표
	int A, K; // 일차함수의 기울기, y절편
	int Crash; // 벽에 충돌?
	clock_t MoveTime, OldTime;
	int DirectionX,DirectionY; // 이동방향
}DOT;

// 전역 변수 선언

PLAYER Player;
DOT Dot[DotNum];

char String[100];

// 플레이어와 점의 모양 

char Player_Shape[] = {"*"};
char Dot_Shape[] = "·";

// 함수 설정

void KeyControl(int key) // 키 입력 처리
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
		게임 시작 / 일시정지 
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


// 프레임워크 함수 시작

void Init()
{
	// 필드 표시

	// PLAYER 초기화

	Player.X =10;
	Player.Y = 10;

	Player.Life = 3;
	Player.Crash = 0; 

	// DOT[] 초기화

	srand((unsigned)time(NULL));

	for (int i = 0; i < DotNum; i++)
	{
		Dot[i].A = rand() % 5;
		Dot[i].K = rand() % 9;
		
		// Dot 위치 분배
		
		int remainder = i % 4;

		switch (remainder)
		{
		case 0: // x==0
			Dot[i].X = 0;
			Dot[i].Y = rand() % BOARD_HEIGHT;

			break;

		case 1: // x==WIDTH
			Dot[i].X = BOARD_WIDTH - 1;
			Dot[i].Y = rand() % BOARD_HEIGHT;

			break;

		case 2: // y==0
			Dot[i].X = rand() % BOARD_WIDTH;
			Dot[i].Y = 0;

			break;

		case 3: // y==HEIGHT
			Dot[i].X = rand() % BOARD_WIDTH;
			Dot[i].Y = BOARD_HEIGHT-1;

			break;

		}

		// 초기 Dot 방향 설정

		if (0 <= Dot[i].X  && Dot[i].X<= BOARD_WIDTH / 2)
			Dot[i].DirectionX = 1; // 방향 : →
		else
			Dot[i].DirectionX = -1; // 방향 : ←

		if (0 <= Dot[i].Y  && Dot[i].Y <= BOARD_HEIGHT / 2)
			Dot[i].DirectionY = 1; // 방향 : →
		else
			Dot[i].DirectionY = -1; // 방향 : ←

		// Dot 시간 설정

		Dot[i].OldTime = clock();
		Dot[i].MoveTime = Dot[i].A * 0.1 * 1000; // 각 Dot마다 다른 MoveTime 부여
		
	}
}

void Update()
{
	clock_t CurTime = clock();

	for (int i = 0; i < DotNum; i++)
	{

		if (CurTime - Dot[i].OldTime > Dot[i].MoveTime) // MoveTime이 지나야 Update. -> 속도 조절
		{
			// 벽에서의 변화

			if ((Dot[i].X == 0) || (Dot[i].X == BOARD_HEIGHT-1))
			{
				Dot[i].DirectionX *= -1; // 벽에 닿으면 방향 변화
				Dot[i].K = Dot[i].Y; // 함수 변화
			}
			if ((Dot[i].Y == 0) || (Dot[i].Y == BOARD_HEIGHT - 1))
			{
				Dot[i].DirectionY *= -1;
				Dot[i].K = (-1) * Dot[i].A * Dot[i].X;
			}

			// 좌표 이동 시작

			Dot[i].X = Dot[i].X + Dot[i].DirectionX;
			Dot[i].Y = Dot[i].DirectionY * (Dot[i].A * Dot[i].X + Dot[i].K); // 일차함수 y=ax+k

			// 시간 재설정

			Dot[i].OldTime = CurTime;
			
		}
	}
}

void Render()
{
	ScreenClear();


	// 렌더링

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

	}

	Release();
	ScreenRelease();
}