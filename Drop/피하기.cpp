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

typedef enum _GAMESTATUS { START, INIT, READY, RUNNING, STOP, RESULT } GAMESTATUS;

// 구조체 선언

typedef struct _PLAYER
{
	int X, Y; // 플레이어 캐릭터의 X, Y 좌표
//	clock_t MoveTime;
	int InStop; // Stop상태? OR Move 상태?
	int Life; // Life.
//	int Crash; // Dot과의 충돌. if (Crash==1) -> Life--; Crash=0;
}PLAYER;

typedef struct _DOT
{
	int X, Y; // 점의 X, Y 좌표
//	int Crash; // 벽에 충돌?
	clock_t MoveTime, OldTime;
	clock_t	Speed; // 속도
	int DirectionX,DirectionY; // 이동방향
}DOT;

// 전역 변수 선언

PLAYER Player;
DOT Dot[DotNum];
GAMESTATUS GameStatus;

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

	case SPACE:
		//게임 시작 / 일시정지 
		if (GameStatus == START)
			GameStatus = INIT;
		break;
		
	}
}

void IfCrash(int i) // Crash 발생 처리
{
	if (Player.X == Dot[i].X)
		Player.Life--;
	
	if (Player.Life==0)
		GameStatus = STOP;
		
}

void MoveCoord(int i) // 좌표 이동
{
	clock_t CurTime = clock();
	
	if (CurTime - Dot[i].OldTime > Dot[i].MoveTime) // MoveTime이 지나야 Update. -> 속도 조절
	{

		// 좌표 이동 시작

		Dot[i].Y++;

		if (Dot[i].Y == BOARD_HEIGHT - 1)
			Dot[i].Y = 2;

		// 시간 재설정

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

// 프레임워크 함수 시작

void Init()
{
	// 필드 표시

	// GameStatus 초기화

	GameStatus = INIT;

	// PLAYER 초기화

	Player.X =10;
	Player.Y = 10;

	Player.Life = 3;
//	Player.Crash = 0; 

	// DOT[] 초기화

	srand((unsigned)time(NULL));

	for (int i = 0; i < DotNum; i++)
	{
		// X Y 좌표 초기화
		
		Dot[i].X = rand() % BOARD_WIDTH;
		Dot[i].Y = 2;

		// Dot 시간 & 속도 설정

		Dot[i].OldTime = clock();
		Dot[i].Speed = rand() % 3 + 1; // 숫자가 작을 수록 속도가 빠르다.
		Dot[i].MoveTime = Dot[i].Speed * 0.1 * 1000; // 각 Dot마다 다른 MoveTime 부여
		
	}
}

void Update()
{

	for (int i = 0; i < DotNum; i++)
	{
		MoveCoord(i); // 좌표이동
		
		IfCrash(i);
	}
}

void Render()
{
	char string[100];

	ScreenClear();
	
	// 렌더링

	sprintf(string, "주인공 이동좌표 : %d, %d              점 수 : Test              초기화 : R 버튼\n", Player.X, Player.Y); // 멘트 수정하기
	ScreenPrint(0, 0, string);
	
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