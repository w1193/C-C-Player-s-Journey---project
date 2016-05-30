#include <stdio.h>
#include <conio.h>
#include <string.h>
#include "Screen.c"
#include <windows.h>
#include <time.h>
#pragma warning(disable:4996)

enum ControlKeys
{
	SPACE = 32,
	LEFT = 75,
	RIGHT = 77
}; // 키 설정

//typedef

typedef enum _DIRECT { TOP, L_TOP, L_DOWN, DOWN, R_DOWN, R_TOP} DIRECT; // ↑부터 시계반대방향
typedef struct _BALL 
{
	int InReady; // 준비상태인가?
	int Life; // Life. (=도전기회?)
	int X, Y; // 공의 좌표
	DIRECT Direct; // 공의 이동방향
	clock_t MoveTime, OldTime;
} BALL; // 공
typedef struct _STICK
{
	int X[3]; // 막대길이 : 3
	int Y;
}STICK; // 막대

// 전역 변수

clock_t CurTime, OldTime;
char *p_KeyMessage[] = { "Left", "Right", "Shoot", "Catch" }; // 키 입력에 따른 출력
int p_Index = 1; // 출력 메시지 인덱스.

//함수 시작

void Init();
void Update();
void Render();
void Release();

void main()
{
	int Key;

	ScreenInit();
	Init();

	while (1)
	{
		Key = _getch();
		OldTime = clock();

		if (Key == 'q')
			break; // 강제종료

		switch (Key)
		{
		case LEFT:
			p_Index = 0;

			break;

		case RIGHT:
			p_Index = 1;

			break;

		case SPACE:
			if (p_Index == 2)
			{
				p_Index = 3;
			}
			else
			{
				p_Index = 2;
			}

			break;

		}

		Update();
		Render();

	}
	
	Release();
	ScreenRelease();
}

void Init()
{

}

void Update()
{

}

void Render()
{
	ScreenClear();

	if (p_Index >= 0) // 출력 인덱스가 -1면 출력 X
		ScreenPrint(10, 10, p_KeyMessage[p_Index]);	



	// 시간 텀
	CurTime = clock();
	ScreenFlipping();
}

void Release()
{

}