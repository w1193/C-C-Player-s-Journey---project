#include <stdio.h>
#include <conio.h>
#include <string.h>
#include "Screen.c"
#include <windows.h>
#include <time.h>


enum ControlKeys
{
    SPACE = 32,
    LEFT = 75,
    RIGHT = 77
};



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
char strPlayer[] = {"|__●__|"}; //캐릭터
int Length; // 주인공 캐릭터 길이
// 초기화 

void Init() {
	
	Player.CenterX = 3; //주인공 X 중심 좌표
	Player.CenterY = 0; //주인공 Y 중심 좌표 
 	Player.MoveX = 20; // 주인공 이동 ㅌ좌표 초기화
	Player.Y = Player.MoveY = 22; // 주인공 이도 Y좌표 초기화
	Player.X = Player.MoveX - Player.CenterX; //주인공 캐릭터 출력 좌표
	Length = strlen(strPlayer); //주인공 전체 길이 

	
	Ball.ReadyB = 1;
	Ball.bMoveX = Player.MoveX;
	Ball.bMoveY = Player.MoveY - 1;
	Ball.MoveTime = 100;
	
	int gLength, i;
	
	Goal.gMoveX = 20;
	Goal.gMoveY = 2;
	Goal.gLength = 2;
	Goal.MoveTime = 100;
	Goal.OldTime = clock();
	Goal.gDistance = 1;
	gLength = Goal.gLength*2 + 1;

	for(i = 0; i < gLength; i++){
		Goal.gLineX[i] = Goal.gMoveX + 2 * (i + 1);
	}
}

// 데이터 갱신

void Update()
{	
	clock_t CurTime = clock();
	int gLength = Goal.gLength * 2 + 1;
	int i;
	int BallCount = 0;
	
	if(Ball.ReadyB == 0) {//이동중일 경우
		if ((CurTime - Ball.OldTime) > Ball.MoveTime)
	 		{
			 if(Ball.bMoveY - 1 > 0){
	 			Ball.bMoveY--;
	 			Ball.OldTime = CurTime;
		 	}else{
			 	Ball.ReadyB = 1;
			 	Ball.bMoveX = Player.MoveX;
			 	Ball.bMoveY = Player.MoveY - 1;
			  }
             }
		}else{
		Ball.bMoveX = Player.MoveX;
	}
	
	if((CurTime - Goal.OldTime) > Goal.MoveTime)
	{
		Goal.OldTime = CurTime;
		if(Goal.gMoveX + Goal.gDistance >= 0 && ((Goal.gLineX[gLength - 1] + 3) + Goal.gDistance) <= 79)
		{
			Goal.gMoveX += Goal.gDistance;
			for(i = 0; i < gLength; i++)
			{
				Goal.gLineX[i] = Goal.gMoveX + 2 * (i + 1);
			}
		}else{
			Goal.gDistance = Goal.gDistance * (-1); // 방향바꾸기 
		}
	}
	
	if(Ball.ReadyB == 0) //공이동중 
	{
		if((CurTime - Ball.OldTime) > Ball.MoveTime){
			if(Ball.bMoveY - 1 > 0){
				Ball.bMoveY--;
				Ball.OldTime = CurTime;
				
				//골대의라인과 충돌 
				if(Ball.bMoveX >= Goal.gLineX[0] && Ball.bMoveX + 1 <= Goal.gLineX[gLength - 1]){
					if(Ball.bMoveY <= Goal.gMoveY) //공 초기화 
						Ball.ReadyB = 1;
						Ball.bMoveY = Player.MoveY - 1;
						Ball.bMoveX = Player.MoveX;
						BallCount++; //득점
						printf("성공!");
					}
					//골대 충돌 
			}else if((Ball.bMoveX >= Goal.gLineX[0] - 2 && Ball.bMoveX <= Goal.gLineX[0] - 1) || (Ball.bMoveX + 1 >= Goal.gLineX[0] - 2) && (Ball.bMoveX + 1 <= Goal.gLineX[0] - 1) || (Ball.bMoveX >= Goal.gLineX[gLength - 1]) + 2 && (Ball.bMoveX <= Goal.gLineX[gLength - 1] + 3) || (Ball.bMoveX + 1 >= Goal.gLineX[gLength - 1]) + 2 && (Ball.bMoveX + 1 <= Goal.gLineX[gLength - 1] + 3)){
				if(Ball.bMoveY <= Goal.gMoveY){
					Ball.ReadyB = 1;
					Ball.bMoveX = Player.MoveX;
					Ball.bMoveY = Player.MoveY - 1;
				}
			}else {
				Ball.ReadyB = 1;
				Ball.bMoveX = Player.MoveX;
				Ball.bMoveY = Player.MoveY - 1;
			}
				
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
	int gLength, i;
	// 출력 시작
	
	// 좌우에 벽을 만듬 (클리핑) 
	
	if(Player.X < 0) 
		ScreenPrint(0, Player.MoveY, &strPlayer[Player.X * (-1)]);
	else if(Player.MoveX + (Length - Player.MoveX + Player.CenterX + 1) > 79)
	{
		strncat_s(string, strPlayer, Length - ((Player.MoveX + Player.CenterX + 1) - 79));	
	 	ScreenPrint(Player.X, Player.Y, string);
	 }else{
		ScreenPrint(Player.X, Player.Y, strPlayer);
	}
	
	ScreenPrint(Ball.bMoveX, Ball.bMoveY, "○");
	sprintf_s(string, "주인공 이동좌표 : %d, %d", Player.MoveX, Player.Y);
	ScreenPrint(0, 0, string);
	
	
	//골대 출력 
	
	ScreenPrint(Goal.gMoveX, Goal.gMoveY, "ㅁ");
	gLength = Goal.gLength * 2 + 1;
	
	for(i = 0; i < gLength; i++)
		ScreenPrint(Goal.gLineX[i], Goal.gMoveY, "ㅡ");
		
	ScreenPrint(Goal.gLineX[gLength - 1] + 2, Goal.gMoveY, "ㅁ");
	
	//출력 끝
    		
	
	ScreenFlipping(); 
 }
 
    //해제
 
 void Release()
 {
  }
  
  
int main (void){

	int Key, Remain;
	clock_t CurTime, OldTime;

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
				case LEFT :
					if(Player.MoveX > 0){
					Player.MoveX--; 
					Remain =  Length - (Player.CenterX); // 남은길이 = 전체 길이 - (중심좌표 + 1)
					if(Player.MoveX + Remain > 79 || Player.MoveX - Player.CenterX - 1 < 0)
						Player.MoveX--;
					Player.X = Player.MoveX - Player.CenterX;
					}
					break;
				case RIGHT :
					if(Player.MoveX + 1< 79){
					Player.MoveX++;
					Remain = Length - (Player.CenterX);
					if(Player.MoveX + Remain >79 || Player.MoveX - Player.CenterX < 0)
						Player.MoveX++;
					Player.X = Player.MoveX - Player.CenterX;
					}
					break;
				case SPACE :
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
		
		OldTime = clock();

		while (1)
		{
			CurTime = clock();
			if (CurTime - OldTime > 20)
			{
				OldTime = CurTime;
				break;
			}
		}//대기시간
	 } 
	 
	 Release();
	 ScreenRelease();
	 return 0;
}
