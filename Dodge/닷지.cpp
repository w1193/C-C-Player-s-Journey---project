#include <stdio.h> // printf scanf sprintf
#include <stdlib.h> // rand
#include <time.h> // time, clock_t
#include <conio.h> // _getch
#include "Screen.c"
#pragma warning(disable:4996)

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
DOT Dot[100];

// 플레이어와 점의 모양 

char Player_Shape[] = "*";
char Dot_Shape[] = "·";

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
	srand((unsigned)time(0)); // rand() 함수로 랜덤값을 주기 위해서 초기값 부여

	int i;
	for (i = 0; i < 100; i++)
	{
		DOT[i].A = rand();
	}
	*/

	// PLAYER 초기화

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