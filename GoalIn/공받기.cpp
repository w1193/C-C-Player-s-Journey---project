#include <stdio.h>
#include <conio.h>
#include <string.h>
#include "Screen.c"
#include <windows.h>
#include <time.h>
#pragma warning(disable:4996)

// typedef �ø���
enum ControlKeys
{
	SPACE = 32,
	LEFT = 75,
	RIGHT = 77
};

typedef struct _GOAL
{
	int gMoveX, gMoveY;
	int gLength; //����� ���� 
	int gLineX[9]; //����� ���ν� ��ǥ 
	int gDistance; // ��� �̵��Ÿ� 
	clock_t MoveTime;
	clock_t OldTime;
} GOAL;

typedef struct _Ball
{
	int ReadyB; // 1 = �غ�, 0 = �� 
	int bMoveX, bMoveY; //�� �̵� ��ǥ
	clock_t MoveTime; // �̵��� �ɸ� �ð�
	clock_t OldTime; // ���� �̵��ð� 
} BALL;

typedef struct _Player
{
	int CenterX, CenterY; //X, Y ��ǥ ���� 
	int MoveX, MoveY; // X, Y ��ǥ �̵� 
	int X, Y; // X, Y ���� ��� ��ǥ �� 
	int Index; // �߽���ǥ�� �ε��� 
} PLAYER;

typedef struct _Position
{
	int X, Y; // X, Y ���� ��ǥ 
} Position;

typedef struct _Effect
{
	clock_t StartTime; // ȿ�� �߻� �ð�
	clock_t StayTime; // ȿ�� ���ӽð�
}EFFECT;

typedef enum _GameState {INIT, READY, RUNNING, STOP, SUCCESS, FAILED, RESULT} GameState;

typedef struct _StageInfo // �������� �ʱ�ȭ ��, Init���� �ʱ�ȭ.
{
	int GoalBall; // ��ǥ ���� ����
	clock_t LimitTime; // ���� �ð�
	int GD_Length; // ��� ����
	int GD_X; // ���� X��ǥ
	int GD_Y; // ���� Y��ǥ
	clock_t GD_MoveTime; // ��� �̵� �ð� ����
	int GD_Dist; // ��� �̵� �Ÿ� 
} StageInfo;

GameState p_GameState = INIT; // ������ ���� : INIT
int p_Goal, p_Stage=-1, p_GameStartTime; // GoalIn? , �� ��������, ���� ���� �ð�

char StateString[100]; // ���� ���� ����
clock_t p_OldTime; // ���� ���� ���̸� ���� �̵� �ð� ����

StageInfo p_StageInfo[] = { { 5, 1000 * 20, 1, 20, 3, 300,2}, {10, 1000 * 30, 2, 20, 5, 300,2 } };
EFFECT Effect;
GOAL Goal;
BALL Ball;
PLAYER Player;
char strPlayer[] = { "|__��__|" }; //ĳ����
int Length; // ���ΰ� ĳ���� ����
int BallCount = 0; // �� ���� ���� ����
int GoalIn; // GoalIn �ߴ°�?
clock_t p_LimitTime; // ���� �ð�
int p_GoalCount; // ��ǥ ���� ����

void FirstScreen(int X, int Y) // ù ȭ�� 
{ 
	ScreenPrint(X, Y,     "�١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١�");
	ScreenPrint(X, Y + 1, "�١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١�");
	ScreenPrint(X, Y + 2, "�١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١�");
	ScreenPrint(X, Y + 3, "�١ڡ١ڡ١ڽ� �� �Ρ١ڡ١ڰ� �ӡڡ١ڡ١ڡ١�");
	ScreenPrint(X, Y + 4, "�١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١�");
	ScreenPrint(X, Y + 5, "�١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١�");
	ScreenPrint(X, Y + 6, "�١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١�");
}

void GoalCere(int X, int Y) // �� �����Ӵ� ȭ��
{
	ScreenPrint(X, Y,   "�١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١�");
	ScreenPrint(X, Y+1, "�١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١�");
	ScreenPrint(X, Y+2, "�١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١�");
	ScreenPrint(X, Y+3, "�١ڡ١ڡ١ڡ١�G O A L�١ڡ١�I N�ڡ١ڡ١ڡ١�");
	ScreenPrint(X, Y+4, "�١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١�");
	ScreenPrint(X, Y+5, "�١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١�");
	ScreenPrint(X, Y+6, "�١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١�");
} 

void MissionSuccess(int X, int Y) // �̼� ���� ȭ��
{
	ScreenPrint(X, Y,     "�١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١�");
	ScreenPrint(X, Y + 1, "�١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١�");
	ScreenPrint(X, Y + 2, "�١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١�");
	ScreenPrint(X, Y + 3, "�١ڡ١ڡ١ڡٹ� �ǡ١ڡټ� ���ڡ١ڡ١ڡ١ڡ١�");
	ScreenPrint(X, Y + 4, "�١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١�");
	ScreenPrint(X, Y + 5, "�١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١�");
	ScreenPrint(X, Y + 6, "�١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١�");
}

void MissionFailed(int X, int Y) // �̼� ���� ȭ��
{
	ScreenPrint(X, Y,     "�١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١�");
	ScreenPrint(X, Y + 1, "�١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١�");
	ScreenPrint(X, Y + 2, "�١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١�");
	ScreenPrint(X, Y + 3, "�١ڡ١ڡ١ڡٹ� �ǡ١ڡٽ� �Сڡ١ڡ١ڡ١ڡ١�");
	ScreenPrint(X, Y + 4, "�١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١�");
	ScreenPrint(X, Y + 5, "�١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١�");
	ScreenPrint(X, Y + 6, "�١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١�");
}

void Quit(int X, int Y) // ���� ���� ȭ��
{
	ScreenPrint(X, Y,     "�١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١�");
	ScreenPrint(X, Y + 1, "�١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١�");
	ScreenPrint(X, Y + 2, "�١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١�");
	ScreenPrint(X, Y + 3, "�١ڡ١ڡ١ڡٰ� �ӡ١ڡ١��� ��١ڡ١ڡ١ڡ١�");
	ScreenPrint(X, Y + 4, "�١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١�");
	ScreenPrint(X, Y + 5, "�١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١�");
	ScreenPrint(X, Y + 6, "�١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١�");
}

void StageScreen(int X, int Y) // �������� ȭ��
{
	ScreenPrint(X, Y,     "�١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١�");
	ScreenPrint(X, Y + 1, "�١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١�");
	ScreenPrint(X, Y + 2, "�١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١�");
	ScreenPrint(X, Y + 3, "�١ڡ١ڡ١ڡ�S T A G E�١ڡ١�N�١ڡ١ڡ١ڡ١�");
	ScreenPrint(X, Y + 4, "�١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١�");
	ScreenPrint(X, Y + 5, "�١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١�");
	ScreenPrint(X, Y + 6, "�١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١�");
}

// �ʱ�ȭ
void Init() {
	
	//StageInfo. �������� �������
	if (p_Stage == -1) // ���� ù ����
		p_Stage = 0;

	p_LimitTime = p_StageInfo[p_Stage].LimitTime; // ���� �ð� ����
	p_GoalCount = p_StageInfo[p_Stage].GoalBall; // ��ǥ ���� ����

	//�÷��̾�
	Player.CenterX = 3; //���ΰ� X �߽� ��ǥ
	Player.CenterY = 0; //���ΰ� Y �߽� ��ǥ 
	Player.MoveX = 20; // ���ΰ� �̵� X��ǥ �ʱ�ȭ
	Player.Y = Player.MoveY = 22; // ���ΰ� �̵� Y��ǥ �ʱ�ȭ
	Player.X = Player.MoveX - Player.CenterX; //���ΰ� ĳ���� ��� ��ǥ
	Length = strlen(strPlayer); //���ΰ� ��ü ����

	//��
	Ball.ReadyB = 1;
	Ball.bMoveX = Player.MoveX;
	Ball.bMoveY = Player.MoveY - 1;
	Ball.MoveTime = 100;

	//��� (����)
	int gLength, i;

	Goal.gMoveX = p_StageInfo[p_Stage].GD_X;
	Goal.gMoveY = p_StageInfo[p_Stage].GD_Y;
	Goal.gLength = p_StageInfo[p_Stage].GD_Length; // ��� ���� = gLength * 2 + 1 
	Goal.MoveTime = p_StageInfo[p_Stage].GD_MoveTime;
	Goal.OldTime = clock();
	Goal.gDistance = p_StageInfo[p_Stage].GD_Dist;
	gLength = Goal.gLength * 2 + 1; // �迭�� �ִ� ����
	for (i = 0; i < gLength; i++) {
		Goal.gLineX[i] = Goal.gMoveX + 2 * (i + 1);
	}

	//�����Ӵ�
	Effect.StayTime = 3000; // �����Ӵ� ȭ�� 3��

	//
	p_OldTime = clock();
}
// ������ ����
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
			Goal.gDistance = Goal.gDistance * (-1); // ����ٲٱ� 
		}
	}

	if (Ball.ReadyB == 0) //���̵��� 
	{
		if ((CurTime - Ball.OldTime) > Ball.MoveTime) {
			if (Ball.bMoveY - 1 > 0) {
				Ball.bMoveY--;
				Ball.OldTime = CurTime;

				//����Ƕ��ΰ� �浹 
				if (Ball.bMoveX >= Goal.gLineX[0] && Ball.bMoveX + 1 <= Goal.gLineX[gLength - 1]) {
					if (Ball.bMoveY <= Goal.gMoveY) {//�� �ʱ�ȭ 
						Ball.ReadyB = 1;
						Ball.bMoveX = Player.MoveX;
						Ball.bMoveY = Player.MoveY - 1;
						BallCount++; //����
						GoalIn = 1;
						Effect.StartTime = clock();
					}
					//��� �浹 
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

	//�����Ӵ�
	if (GoalIn == 1)
	{
		if ((CurTime - Effect.StartTime) > Effect.StayTime)
			GoalIn = 0;
	}

	//
	switch (p_GameState)
	{
	case INIT: // case �ʱ�ȭ
		if (p_Stage == 0)
		{
			sprintf(StateString, "%s", "���� �� ���� �ʱ�ȭ");
			if (CurTime - p_OldTime > 3000) // ���� ���� ����?
			{
				p_OldTime = CurTime;
				p_Stage = 1; // �������� �Ѿ
				p_GameState = READY; // READY ���·� �Ѿ
			}
			else // �ð��� �� ����.
			{ // INIT â ���
				sprintf(StateString, "[INIT] ���� %d �������� �ʱ�ȭ", p_Stage);

				if (CurTime - p_OldTime > 3000) // â ��� ��, ���� ����?
				{
					p_OldTime = CurTime;
				}
			}
		}
		break;

	case READY: // READY ����
		sprintf(StateString, "[READY] %d ��������", p_Stage);
		if (CurTime - p_OldTime > 3000)
		{
			p_OldTime = CurTime;
			p_GameState = RUNNING;
			p_GameStartTime = CurTime;
		}
		break;

	case RUNNING: // RUNNING ����
		if (CurTime - p_GameStartTime > 10000) // ���ѽð� 10�ʸ� �ѱ�
		{
			p_GameState = STOP; // STOP ���·� �Ѿ -> �Ǻ�
		}
		else
		{
			sprintf(StateString, "[RUNNING] ���� �ð� : 10��. ���� �ð� : %d", (CurTime - p_GameStartTime) / 1000); // ���� ���
		}
		break;
	case STOP: // STOP ����. ����/���� ����
		if (BallCount == 0)
		{
			p_GameState = FAILED;
		}
		else
		{
			p_GameState = SUCCESS;
		}
		break;
	case SUCCESS: // SUCCESS ����. �̼� ����
		sprintf(StateString, "%s", "�̼� ����");
		if (CurTime - p_OldTime > 3000)
		{
			p_OldTime = CurTime;
			p_GameState = INIT; // INIT �ܰ�� ���ư�
			++p_Stage; // Stage ���� ����
		}
		break;
	case FAILED: // FAILED ����. �̼� ����
		sprintf(StateString, "%s", "�̼� ����. �絵��? (Y/N)"); // Y,N �Է�. Stage ���� �״��.
		if (CurTime - p_OldTime > 3000)
		{
			p_OldTime = CurTime;
		}
		break;
	case RESULT: // RESULT ����. ���� ���
		sprintf(StateString, "%s", "���� ��� ȭ��");
		if (CurTime - p_OldTime > 3000)
		{
			p_OldTime = CurTime;
		}
		break;
	}
}
// ���
void Render()
{
	char string[100] = { 0 };
	ScreenClear();
	int gLength, i;
	// ��� ����

	if (p_GameState == RUNNING)
	{

		// �¿쿡 ���� ���� (Ŭ����) 

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

		ScreenPrint(Ball.bMoveX, Ball.bMoveY, "��");
		sprintf(string, "���ΰ� �̵���ǥ : %d, %d              �� �� : %d               �ʱ�ȭ : R ��ư ", Player.MoveX, Player.Y, BallCount);
		ScreenPrint(0, 0, string);


		//��� ��� 

		ScreenPrint(Goal.gMoveX, Goal.gMoveY, "��");
		gLength = Goal.gLength * 2 + 1;

		for (i = 0; i < gLength; i++)
			ScreenPrint(Goal.gLineX[i], Goal.gMoveY, "��");

		ScreenPrint(Goal.gLineX[gLength - 1] + 2, Goal.gMoveY, "��");

		//�����Ӵ� ���

		if (GoalIn == 1)
		{
			//ScreenClear();
			//GoalCere(10,5);
			ScreenPrint(50, 5, "** G O A L  I N **");
		}

	}
	// ���� ���
	ScreenPrint(20, 10, StateString);

	//��� ��


	ScreenFlipping();
}

//����

void Release()
{
}


int main(void) {
	int Key, Remain;

	ScreenInit();
	Init(); // �ʱ�ȭ

	while (1) //���ѹݺ� 
	{
		if (_kbhit()) // Ű �Է�?
		{
			Key = _getch();
			if (p_GameState == RESULT || p_GameState==SUCCESS) // RESULT , SUCCESS���� Ű�Է� -> ����
				break;
			
			// RESULT, SUCCESS ���°� �ƴ� ��
			
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

				// �÷��̾� ĳ���� ����
			case LEFT:
				if (Player.MoveX > 0) {
					Player.MoveX--;
					Remain = Length - (Player.CenterX + 1); // �������� = ��ü ���� - (�߽���ǥ + 1)
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

		Update();//������ ���� 
		Render(); //ȭ�� ��� 

	}

	Release();
	ScreenRelease();
	return 0;
}