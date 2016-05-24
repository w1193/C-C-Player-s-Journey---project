#include <stdio.h>
#include <conio.h>
#include <string.h>
#include "Screen.c"
#include <windows.h>
#include <time.h>
#pragma warning(disable:4996)

// typedef 시리즈
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

typedef struct _Effect
{
	clock_t StartTime; // 효과 발생 시각
	clock_t StayTime; // 효과 지속시간
}EFFECT;

typedef enum _GameState {INIT, READY, RUNNING, STOP, SUCCESS, FAILED, RESULT} GameState;

typedef struct _StageInfo // 스테이지 초기화 시, Init에서 초기화.
{
	int GoalBall; // 목표 골인 개수
	clock_t LimitTime; // 제한 시간
	int GD_Length; // 골대 길이
	int GD_X; // 최초 X좌표
	int GD_Y; // 최초 Y좌표
	clock_t GD_MoveTime; // 골대 이동 시간 간격
	int GD_Dist; // 골대 이동 거리 
} StageInfo;

GameState p_GameState = INIT; // 최초의 상태 : INIT
int p_Goal, p_Stage=-1, p_GameStartTime; // GoalIn? , 현 스테이지, 게임 시작 시간

char StateString[100]; // 게임 상태 저장
clock_t p_OldTime; // 게임 상태 전이를 위한 이동 시각 저장

StageInfo p_StageInfo[] = { { 5, 1000 * 20, 1, 20, 3, 300,2}, {10, 1000 * 30, 2, 20, 5, 300,2 } };
EFFECT Effect;
GOAL Goal;
BALL Ball;
PLAYER Player;
char strPlayer[] = { "|__●__|" }; //캐릭터
int Length; // 주인공 캐릭터 길이
int BallCount = 0; // 총 넣은 공의 갯수
int GoalIn; // GoalIn 했는가?
clock_t p_LimitTime; // 제한 시간
int p_GoalCount; // 목표 골인 개수

void FirstScreen(int X, int Y) // 첫 화면 
{ 
	ScreenPrint(X, Y,     "☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★");
	ScreenPrint(X, Y + 1, "☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★");
	ScreenPrint(X, Y + 2, "☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★");
	ScreenPrint(X, Y + 3, "☆★☆★☆★슛 골 인☆★☆★게 임★☆★☆★☆★");
	ScreenPrint(X, Y + 4, "☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★");
	ScreenPrint(X, Y + 5, "☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★");
	ScreenPrint(X, Y + 6, "☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★");
}

void GoalCere(int X, int Y) // 골 세레머니 화면
{
	ScreenPrint(X, Y,   "☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★");
	ScreenPrint(X, Y+1, "☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★");
	ScreenPrint(X, Y+2, "☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★");
	ScreenPrint(X, Y+3, "☆★☆★☆★☆★G O A L☆★☆★I N★☆★☆★☆★");
	ScreenPrint(X, Y+4, "☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★");
	ScreenPrint(X, Y+5, "☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★");
	ScreenPrint(X, Y+6, "☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★");
} 

void MissionSuccess(int X, int Y) // 미션 성공 화면
{
	ScreenPrint(X, Y,     "☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★");
	ScreenPrint(X, Y + 1, "☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★");
	ScreenPrint(X, Y + 2, "☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★");
	ScreenPrint(X, Y + 3, "☆★☆★☆★☆미 션☆★☆성 공★☆★☆★☆★☆★");
	ScreenPrint(X, Y + 4, "☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★");
	ScreenPrint(X, Y + 5, "☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★");
	ScreenPrint(X, Y + 6, "☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★");
}

void MissionFailed(int X, int Y) // 미션 실패 화면
{
	ScreenPrint(X, Y,     "☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★");
	ScreenPrint(X, Y + 1, "☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★");
	ScreenPrint(X, Y + 2, "☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★");
	ScreenPrint(X, Y + 3, "☆★☆★☆★☆미 션☆★☆실 패★☆★☆★☆★☆★");
	ScreenPrint(X, Y + 4, "☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★");
	ScreenPrint(X, Y + 5, "☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★");
	ScreenPrint(X, Y + 6, "☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★");
}

void Quit(int X, int Y) // 게임 종료 화면
{
	ScreenPrint(X, Y,     "☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★");
	ScreenPrint(X, Y + 1, "☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★");
	ScreenPrint(X, Y + 2, "☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★");
	ScreenPrint(X, Y + 3, "☆★☆★☆★☆게 임☆★☆★종 료☆★☆★☆★☆★");
	ScreenPrint(X, Y + 4, "☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★");
	ScreenPrint(X, Y + 5, "☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★");
	ScreenPrint(X, Y + 6, "☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★");
}

void StageScreen(int X, int Y) // 스테이지 화면
{
	ScreenPrint(X, Y,     "☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★");
	ScreenPrint(X, Y + 1, "☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★");
	ScreenPrint(X, Y + 2, "☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★");
	ScreenPrint(X, Y + 3, "☆★☆★☆★☆S T A G E☆★☆★N☆★☆★☆★☆★");
	ScreenPrint(X, Y + 4, "☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★");
	ScreenPrint(X, Y + 5, "☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★");
	ScreenPrint(X, Y + 6, "☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★");
}

// 초기화
void Init() {
	
	//StageInfo. 스테이지 구성요소
	if (p_Stage == -1) // 게임 첫 실행
		p_Stage = 0;

	p_LimitTime = p_StageInfo[p_Stage].LimitTime; // 제한 시간 설정
	p_GoalCount = p_StageInfo[p_Stage].GoalBall; // 목표 골인 개수

	//플레이어
	Player.CenterX = 3; //주인공 X 중심 좌표
	Player.CenterY = 0; //주인공 Y 중심 좌표 
	Player.MoveX = 20; // 주인공 이동 X좌표 초기화
	Player.Y = Player.MoveY = 22; // 주인공 이도 Y좌표 초기화
	Player.X = Player.MoveX - Player.CenterX; //주인공 캐릭터 출력 좌표
	Length = strlen(strPlayer); //주인공 전체 길이

	//공
	Ball.ReadyB = 1;
	Ball.bMoveX = Player.MoveX;
	Ball.bMoveY = Player.MoveY - 1;
	Ball.MoveTime = 100;

	//골대 (수정)
	int gLength, i;

	Goal.gMoveX = p_StageInfo[p_Stage].GD_X;
	Goal.gMoveY = p_StageInfo[p_Stage].GD_Y;
	Goal.gLength = p_StageInfo[p_Stage].GD_Length; // 골대 길이 = gLength * 2 + 1 
	Goal.MoveTime = p_StageInfo[p_Stage].GD_MoveTime;
	Goal.OldTime = clock();
	Goal.gDistance = p_StageInfo[p_Stage].GD_Dist;
	gLength = Goal.gLength * 2 + 1; // 배열의 최대 길이
	for (i = 0; i < gLength; i++) {
		Goal.gLineX[i] = Goal.gMoveX + 2 * (i + 1);
	}

	//세레머니
	Effect.StayTime = 3000; // 세레머니 화면 3초

	//
	p_OldTime = clock();
}
// 데이터 갱신
void Update()
{
	clock_t CurTime = clock();
	int gLength = Goal.gLength * 2 + 1;
	int i;



	if ((CurTime - Goal.OldTime) > Goal.MoveTime)
	{
		Goal.OldTime = CurTime;
		if (Goal.gMoveX + Goal.gDistance >= 0 && ((Goal.gLineX[gLength - 1] + 3) + Goal.gDistance) <= 79)
		{
			Goal.gMoveX += Goal.gDistance;
			for (i = 0; i < gLength; i++)
			{
				Goal.gLineX[i] = Goal.gMoveX + 2 * (i + 1);
			}
		}
		else {
			Goal.gDistance = Goal.gDistance * (-1); // 방향바꾸기 
		}
	}

	if (Ball.ReadyB == 0) //공이동중 
	{
		if ((CurTime - Ball.OldTime) > Ball.MoveTime) {
			if (Ball.bMoveY - 1 > 0) {
				Ball.bMoveY--;
				Ball.OldTime = CurTime;

				//골대의라인과 충돌 
				if (Ball.bMoveX >= Goal.gLineX[0] && Ball.bMoveX + 1 <= Goal.gLineX[gLength - 1]) {
					if (Ball.bMoveY <= Goal.gMoveY) {//공 초기화 
						Ball.ReadyB = 1;
						Ball.bMoveX = Player.MoveX;
						Ball.bMoveY = Player.MoveY - 1;
						BallCount++; //득점
						GoalIn = 1;
						Effect.StartTime = clock();
					}
					//골대 충돌 
				}
				else if ((Ball.bMoveX >= Goal.gLineX[0] - 2 && Ball.bMoveX <= Goal.gLineX[0] - 1) || (Ball.bMoveX + 1 >= Goal.gLineX[0] - 2) && (Ball.bMoveX + 1 <= Goal.gLineX[0] - 1) || (Ball.bMoveX >= Goal.gLineX[gLength - 1]) + 2 && (Ball.bMoveX <= Goal.gLineX[gLength - 1] + 3) || (Ball.bMoveX + 1 >= Goal.gLineX[gLength - 1]) + 2 && (Ball.bMoveX + 1 <= Goal.gLineX[gLength - 1] + 3)) {
					if (Ball.bMoveY <= Goal.gMoveY) {
						Ball.ReadyB = 1;
						Ball.bMoveX = Player.MoveX;
						Ball.bMoveY = Player.MoveY - 1;
					}
				}
			}
			else {
				Ball.ReadyB = 1;
				Ball.bMoveX = Player.MoveX;
				Ball.bMoveY = Player.MoveY - 1;
			}
		}
	}
	else {
		Ball.bMoveX = Player.MoveX;
	}

	//세레머니
	if (GoalIn == 1)
	{
		if ((CurTime - Effect.StartTime) > Effect.StayTime)
			GoalIn = 0;
	}

	//
	switch (p_GameState)
	{
	case INIT: // case 초기화
		if (p_Stage == 0)
		{
			sprintf(StateString, "%s", "게임 및 사운드 초기화");
			if (CurTime - p_OldTime > 3000) // 게임 상태 전이?
			{
				p_OldTime = CurTime;
				p_Stage = 1; // 스테이지 넘어감
				p_GameState = READY; // READY 상태로 넘어감
			}
			else // 시간이 안 됐음.
			{ // INIT 창 띄움
				sprintf(StateString, "[INIT] 게임 %d 스테이지 초기화", p_Stage);

				if (CurTime - p_OldTime > 3000) // 창 띄운 후, 상태 전이?
				{
					p_OldTime = CurTime;
				}
			}
		}
		break;

	case READY: // READY 상태
		sprintf(StateString, "[READY] %d 스테이지", p_Stage);
		if (CurTime - p_OldTime > 3000)
		{
			p_OldTime = CurTime;
			p_GameState = RUNNING;
			p_GameStartTime = CurTime;
		}
		break;

	case RUNNING: // RUNNING 상태
		if (CurTime - p_GameStartTime > 10000) // 제한시간 10초를 넘김
		{
			p_GameState = STOP; // STOP 상태로 넘어감 -> 판별
		}
		else
		{
			sprintf(StateString, "[RUNNING] 제한 시간 : 10초. 현재 시간 : %d", (CurTime - p_GameStartTime) / 1000); // 문구 출력
		}
		break;
	case STOP: // STOP 상태. 성공/실패 판정
		if (BallCount == 0)
		{
			p_GameState = FAILED;
		}
		else
		{
			p_GameState = SUCCESS;
		}
		break;
	case SUCCESS: // SUCCESS 상태. 미션 성공
		sprintf(StateString, "%s", "미션 성공");
		if (CurTime - p_OldTime > 3000)
		{
			p_OldTime = CurTime;
			p_GameState = INIT; // INIT 단계로 돌아감
			++p_Stage; // Stage 레벨 증가
		}
		break;
	case FAILED: // FAILED 상태. 미션 실패
		sprintf(StateString, "%s", "미션 실패. 재도전? (Y/N)"); // Y,N 입력. Stage 레벨 그대로.
		if (CurTime - p_OldTime > 3000)
		{
			p_OldTime = CurTime;
		}
		break;
	case RESULT: // RESULT 상태. 게임 결과
		sprintf(StateString, "%s", "게임 결과 화면");
		if (CurTime - p_OldTime > 3000)
		{
			p_OldTime = CurTime;
		}
		break;
	}
}
// 출력
void Render()
{
	char string[100] = { 0 };
	ScreenClear();
	int gLength, i;
	// 출력 시작

	if (p_GameState == RUNNING)
	{

		// 좌우에 벽을 만듬 (클리핑) 

		if (Player.X < 0)
			ScreenPrint(0, Player.MoveY, &strPlayer[Player.X * (-1)]);
		else if (Player.MoveX + (Length - Player.MoveX + Player.CenterX + 1) > 79)
		{
			strncat(string, strPlayer, Length - ((Player.MoveX + Player.CenterX + 1) - 79));
			ScreenPrint(Player.X, Player.Y, string);
		}
		else {
			ScreenPrint(Player.X, Player.Y, strPlayer);
		}

		ScreenPrint(Ball.bMoveX, Ball.bMoveY, "◎");
		sprintf(string, "주인공 이동좌표 : %d, %d              점 수 : %d               초기화 : R 버튼 ", Player.MoveX, Player.Y, BallCount);
		ScreenPrint(0, 0, string);


		//골대 출력 

		ScreenPrint(Goal.gMoveX, Goal.gMoveY, "ㅁ");
		gLength = Goal.gLength * 2 + 1;

		for (i = 0; i < gLength; i++)
			ScreenPrint(Goal.gLineX[i], Goal.gMoveY, "ㅡ");

		ScreenPrint(Goal.gLineX[gLength - 1] + 2, Goal.gMoveY, "ㅁ");

		//세레머니 출력

		if (GoalIn == 1)
		{
			//ScreenClear();
			//GoalCere(10,5);
			ScreenPrint(50, 5, "** G O A L  I N **");
		}

	}
	// 상태 출력
	ScreenPrint(20, 10, StateString);

	//출력 끝


	ScreenFlipping();
}

//해제

void Release()
{
}


int main(void) {
	int Key, Remain;

	ScreenInit();
	Init(); // 초기화

	while (1) //무한반복 
	{
		if (_kbhit()) // 키 입력?
		{
			Key = _getch();
			if (p_GameState == RESULT || p_GameState==SUCCESS) // RESULT , SUCCESS에서 키입력 -> 종료
				break;
			
			// RESULT, SUCCESS 상태가 아닐 시
			
			if (Key == 'q')
				break;

			if (p_GameState == FAILED)
			{
				switch (Key)
				{
				case 'Y': case 'y':
					p_GameState = INIT;
					p_OldTime = clock();
					break;
				case 'N': case 'n':
					p_GameState = RESULT;
					p_OldTime = clock();
					break;
				}
			}
			switch (Key)
			{
				// S F Y N
			case 'S': case 's':
				p_Goal = 1;
				break;
			case 'F': case 'f':
				p_Goal = 0;
				break;

				// 플레이어 캐릭터 조작
			case LEFT:
				if (Player.MoveX > 0) {
					Player.MoveX--;
					Remain = Length - (Player.CenterX + 1); // 남은길이 = 전체 길이 - (중심좌표 + 1)
					if (Player.MoveX + Remain > 79 || Player.MoveX - Player.CenterX < 0)
						Player.MoveX--;
					Player.X = Player.MoveX - Player.CenterX;
				}
				break;
			case RIGHT:
				if (Player.MoveX + 1 < 79) {
					Player.MoveX++;
					Remain = Length - (Player.CenterX + 1);
					if (Player.MoveX + Remain >79 || Player.MoveX - Player.CenterX < 0)
						Player.MoveX++;
					Player.X = Player.MoveX - Player.CenterX;
				}
				break;
			case SPACE:
				if (Ball.ReadyB)
				{
					Ball.bMoveX = Player.MoveX;
					Ball.bMoveY = Player.MoveY - 1;
					Ball.OldTime = clock();
					Ball.ReadyB = 0;
				}				

				break;
			case 'r':
				if (BallCount != 0)
				{
					BallCount = 0;
					Ball.ReadyB = 1;
					Ball.bMoveX = Player.MoveX;
					Ball.bMoveY = Player.MoveY - 1;
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