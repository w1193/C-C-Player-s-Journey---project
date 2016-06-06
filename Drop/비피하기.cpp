#include <stdio.h> // printf scanf sprintf
#include <stdlib.h> // rand
#include <time.h> // time, clock_t
#include <conio.h> // _getch
#include "Screen.c"
#pragma warning(disable:4996)

#define DotNum 15 // Dot의 개수
#define StageNum 3 // Stage 개수
#define BOARD_WIDTH 80      // 화면의 너비
#define BOARD_HEIGHT 25      // 화면의 높이
#define Invincible 3 // 무적시간

// 열거형 선언

enum ControlKeys
{
	UP = 72,
	DOWN = 80,
	LEFT = 75,
	RIGHT = 77,
	SPACE = 32
};

typedef enum _GAMESTATUS { START, INIT, READY, RUNNING, STOP, JUDGMENT, NEXT, RESULT } GAMESTATUS;

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
/*
typedef struct _STAGE
{
	int MinSpeed, MaxSpeed; // Dot의 최소 최대 속도
	int DotNum; // Dot의 개수
}STAGE;
*/
// 전역 변수 선언

// 구조체 변수

PLAYER Player;
DOT Dot[DotNum*4];
//STAGE Stage[3] = { {},{},{} }; // 최소속도, 최대속도, 개수
GAMESTATUS GameStatus;

// 스테이지 관련

int Stage=0;

// 게임 상태 관련

char StatString[500]; // 게임 상태 String
int PrintTime = 3 * 1000; // 게임 상태 표시 시간
clock_t Stat_OldTime = clock(); // PrintTime의 OldTime

// 플레이어와 점의 모양 

char Player_Shape[] = {"*"};
char Dot_Shape[4][3] = { {"↓"},{"↑"},{"→"},{"←"} };

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

void IfCrash(int i) // Crash 발생 처리
{
	if ((Player.X == Dot[i].X && Player.Y == Dot[i].Y) || ( (Player.X-1) == Dot[i].X && Player.Y == Dot[i].Y) )
	{
		Player.Life--;
		Dot[i].Y = 0;
	}

	if (Player.Life<=0)
		GameStatus = NEXT;
		
}

void MoveCoord(int i) // 좌표 이동
{
	clock_t CurTime = clock();
	
	if (CurTime - Dot[i].OldTime > Dot[i].MoveTime) // MoveTime이 지나야 Update. -> 속도 조절
	{

		// 좌표 이동 시작
		
		if (i >= 0 && i < DotNum) // ↓
		{
			Dot[i].Y++;
			if (Dot[i].Y == BOARD_HEIGHT - 1)
				Dot[i].Y = 2;
		}
		if (i >= DotNum && i < DotNum*2) // ↑
		{
			Dot[i].Y--;
			if (Dot[i].Y == 2)
				Dot[i].Y = BOARD_HEIGHT - 1;
		}
		if (i >= DotNum*2 && i < DotNum*3) // →
		{
			Dot[i].X++;
			if (Dot[i].X == BOARD_WIDTH - 1)
				Dot[i].X = 0;
		}
		if (i >= DotNum*3 && i < DotNum*4) // ←
		{
			Dot[i].X--;
			if (Dot[i].X == 0)
				Dot[i].X = BOARD_WIDTH - 1;
		}

		// 시간 재설정

		Dot[i].OldTime = CurTime;

	}
}

void DotInit()
{
	int i;

	srand((unsigned)time(NULL));

	switch (Stage)
	{
	case 2: // → ←
		for (i = DotNum * 2; i < DotNum * 3; i++) // →
		{
			// X Y 좌표 초기화

			Dot[i].X = 0;
			Dot[i].Y = rand() % BOARD_HEIGHT;

			// Dot 시간 & 속도 설정

			Dot[i].OldTime = clock();
			Dot[i].Speed = rand() % 3 + 1; // 숫자가 작을 수록 속도가 빠르다.
			Dot[i].MoveTime = Dot[i].Speed * 0.1 * 1000; // 각 Dot마다 다른 MoveTime 부여
		}

		for (i = DotNum * 3; i < DotNum * 4; i++) // ←
		{
			// X Y 좌표 초기화

			Dot[i].X = BOARD_WIDTH - 1;
			Dot[i].Y = rand() % BOARD_HEIGHT;

			// Dot 시간 & 속도 설정

			Dot[i].OldTime = clock();
			Dot[i].Speed = rand() % 3 + 1; // 숫자가 작을 수록 속도가 빠르다.
			Dot[i].MoveTime = Dot[i].Speed * 0.1 * 1000; // 각 Dot마다 다른 MoveTime 부여
		}
	case 1: // ↑
		for (i = DotNum; i < DotNum * 2; i++)
		{
			// X Y 좌표 초기화

			Dot[i].X = rand() % BOARD_WIDTH;
			Dot[i].Y = BOARD_HEIGHT - 1;

			// Dot 시간 & 속도 설정

			Dot[i].OldTime = clock();
			Dot[i].Speed = rand() % 3 + 1; // 숫자가 작을 수록 속도가 빠르다.
			Dot[i].MoveTime = Dot[i].Speed * 0.1 * 1000; // 각 Dot마다 다른 MoveTime 부여
		}
	case 0: // ↓
		for (i = 0; i < DotNum; i++)
		{
			// X Y 좌표 초기화

			Dot[i].X = rand() % BOARD_WIDTH;
			Dot[i].Y = 2;

			// Dot 시간 & 속도 설정

			Dot[i].OldTime = clock();
			Dot[i].Speed = rand() % 3 + 1; // 숫자가 작을 수록 속도가 빠르다.
			Dot[i].MoveTime = Dot[i].Speed * 0.1 * 1000; // 각 Dot마다 다른 MoveTime 부여
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
		sprintf(StatString, "\t\t\t  [비 피하기 게임] \n\n"
			"\t\t===================================\n\n"
			"\t\t떨어지는 비를 피하는 게임입니다.\n"
			"\t\t각 스테이지 당 Life는 3 입니다. \n"
			"\t\t점수는 버티는 시간으로 계산됩니다.\n"
			"\t\t스테이지는 총 3레벨로 구성되어있습니다.\n\n"
			"\t\t===================================\n\n"
			"\t\t\t  - 조 작 법 -\n\n"
			"\t\t이동 : 방향키 | 일시정지 : SPACE BAR\n\n"
			"\t\t-----------------------------------\n"
			"\t\t게임 시작 : SPACE BAR | 게임 종료 : q\n\n");
		ScreenPrint(0, 3, StatString);

		break;

	case INIT:
		if (CurTime - Stat_OldTime < PrintTime)
		{

			DotInit(); // Dot 초기화
			Player.Life = 3;

			sprintf(StatString, "INIT 화면");
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
			sprintf(StatString, "REDAY 화면");
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
		sprintf(StatString, "STOP 화면");
		ScreenPrint(10, 10, StatString);

		break;

	case JUDGMENT:


		break;

	case NEXT:
		if (CurTime - Stat_OldTime < PrintTime)
		{
			sprintf(StatString, "NEXT 화면");
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
		sprintf(StatString, "RESULT 화면");
		ScreenPrint(10, 10, StatString);
		
		break;
	}
}

// 프레임워크 함수 시작

void Init()
{
	// 필드 표시

	// GameStatus 초기화

	GameStatus = START; // 최초의 상태 : START

	// PLAYER 초기화

	Player.X =10;
	Player.Y = 10;

	Player.Life = 3;

	// DOT[] 초기화

}

void Update()
{
	if (GameStatus == RUNNING)
	{
		for (int i = 0; i < DotNum; i++)
		{
			MoveCoord(i); // 좌표이동

			IfCrash(i);
		}
	}
}

void Render()
{
	char string[100];

	ScreenClear();
	
	// 렌더링

	StatusPrint();

	if (GameStatus == RUNNING)
	{
		sprintf(string, "주인공 이동좌표 : %d, %d              Life : %d              초기화 : R 버튼\n", Player.X, Player.Y, Player.Life); // 멘트 수정하기
		ScreenPrint(0, 0, string);

		ScreenPrint(Player.X, Player.Y, Player_Shape); // 플레이어 표시

		switch (Stage)
		{
		case 2:
			for (int i = DotNum*2; i < DotNum*3; i++)
			{
				ScreenPrint(Dot[i].X, Dot[i].Y, Dot_Shape[2]); // 점 표시
			}
			for (int i = DotNum*3; i < DotNum*4; i++)
			{
				ScreenPrint(Dot[i].X, Dot[i].Y, Dot_Shape[3]); // 점 표시
			}

		case 1:
			for (int i = DotNum; i < DotNum*2; i++)
			{
				ScreenPrint(Dot[i].X, Dot[i].Y, Dot_Shape[1]); // 점 표시
			}

		case 0:
			for (int i = 0; i < DotNum; i++)
			{
				ScreenPrint(Dot[i].X, Dot[i].Y, Dot_Shape[0]); // 점 표시
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