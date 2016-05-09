#include <stdio.h>
#include <conio.h>
#include <string.h>
#include "Screen.c"
#include <windows.h>
#include <time.h>

typedef struct _GOAL
{
	int gMoveX, gMoveY;
	int gLength; //골대의 길이 
	int gLineX[9]; //골대의 골인식 좌표 
	int gDistance; // 골대 이동거리 
	clock_t MoveTime;
	clock_t OldTime;
} GOAL;




typedef struct _Ball
{
	int ReadyB; // 1 = 준비, 0 = 슛 
	int bMoveX, bMoveY; //공 이동 좌표
	clock_t MoveTime; // 이동중 걸린 시간
	clock_t OldTime; // 이전 이동시간 
} BALL; 


typedef struct _Player
{
	int CenterX, CenterY; //X, Y 좌표 센터 
	int MoveX, MoveY; // X, Y 좌표 이동 
	int X, Y; // X, Y 현재 출력 좌표 값 
	int Index; // 중심좌표의 인덱스 
} PLAYER;


typedef struct _Position
{
	int X, Y; // X, Y 현재 좌표 
} Position; 


GOAL Goal;
BALL Ball;
PLAYER Player;
char StrPlayer[] = {"|__O__|"}; //캐릭터
int Length; // 주인공 캐릭터 길이

// 초기화 

void Init() {
	Player.CenterX = 3; //주인공 X 중심 좌표
	Player.CenterY = 0; //주인공 Y 중심 좌표 
 	Player.MoveX = 20; // 주인공 이동 ㅌ좌표 초기화
	Player.Y = Player.MoveY = 22; // 주인공 이도 Y좌표 초기화
	Player.X = Player.MoveX - Player.CenterX; //주인공 캐릭터 출력 좌표
	Length = strlen(StrPlayer); //주인공 전체 길이 

	
	Ball.ReadyB = 1;
	Ball.bMoveX = Player.MoveX;
	Ball.bMoveY = Player.MoveY - 1;
	Ball.MoveTime = 100;
}

// 데이터 갱신

void Update()
{
	clock_t CurTime = clock();
	if(Ball.ReadyB == 0) {//이동중일 경우
		if ((CurTime - Ball.OldTime) > Ball.MoveTime) 
	 		{
			 if(Ball.bMoveY - 1 > 0)
	 			Ball.bMoveY--;
	 			Ball.OldTime = CurTime;
			 	}else{
			 		Ball.ReadyB = 1;
			 		Ball.bMoveX = Player.MoveX;
			 		Ball.bMoveY = Player.MoveY - 1;
				 }
	 		}else{
		Ball.bMoveX = Player.MoveX;
	}
}

// 출력

void Render()
{
	char string[100] = {0};
	ScreenClear();
	
	// 출력 시작
	// 좌우에 벽을 만듬 (클리핑) 
	
	if(Player.X < 0) //왼쪽 클리핑 
		{ScreenPrint(0, Player.MoveY, &StrPlayer[Player.X*-1]);}
	else if(Player.MoveX + (Length - ((Player.MoveX + Player.CenterX + 1) > 79 )))
	{
		strncat(string, StrPlayer, Length - ((Player.MoveX + Player.CenterX + 1) -79));	
	 	ScreenPrint(Player.X, Player.Y, StrPlayer);
	 }else{
		ScreenPrint(Player.X, Player.Y, StrPlayer);
	}

	sprintf(string, "주인공 이동좌표 : %d, %d", Player.MoveX, Player.Y);
	ScreenPrint(0, 0, string);
	
	//출력 끝
	
	ScreenFlipping(); 
 }
 
 //해제
 
 void Release()
 {
  }
  
  
int main (void){
	int Key, Remain;
	
	ScreenInit();
	Init(); // 초기화
	
	while( 1 ) //무한반복 
	{
		if(_kbhit())
		{
			Key = _getch();
			if(Key == 'q')
				break;
			switch(Key)
			{
				case '1' :
					Player.MoveX--; 
					Remain =  Length - (Player.CenterX + 1); // 남은길이 = 전체 길이 - (중심좌표 + 1)
					if(Player.MoveX + Remain > 79 || Player.MoveX - Player.CenterX < 0)
					Player.MoveX++;
					Player.X = Player.MoveX - Player.CenterX;
					break;
				case '2' :
					Player.MoveX++;
					Remain = Length - (Player.CenterX + 1);
					if(Player.MoveX + Remain >79 || Player.MoveX - Player.CenterX < 0)
						Player.MoveX++;
					Player.X = Player.MoveX - Player.CenterX;
					break;
				case '3' :
					if(Ball.ReadyB)
					{
						Ball.bMoveX = Player.MoveX;
						Ball.bMoveY = Player.MoveY - 1;
						Ball.OldTime = clock();
						Ball.ReadyB = 0;
					}
					break;	
			}
		}
		
		Update();//데이터 갱신 
		Render(); //화면 출력 
		
	 } 
	 
	 Release();
	 ScreenRelease();
	 return 0;
}
