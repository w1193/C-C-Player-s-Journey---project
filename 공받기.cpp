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
};

typedef struct _GOAL
{
	int gMoveX, gMoveY;
	int gLength; //∞Ò¥Î¿« ±Ê¿Ã 
	int gLineX[9]; //∞Ò¥Î¿« ∞Ò¿ŒΩƒ ¡¬«• 
	int gDistance; // ∞Ò¥Î ¿Ãµø∞≈∏Æ 
	clock_t MoveTime;
	clock_t OldTime;
} GOAL;


typedef struct _Ball
{
	int ReadyB; // 1 = ¡ÿ∫Ò, 0 = Ω∏ 
	int bMoveX, bMoveY; //∞¯ ¿Ãµø ¡¬«•
	clock_t MoveTime; // ¿Ãµø¡ﬂ ∞…∏∞ Ω√∞£
	clock_t OldTime; // ¿Ã¿¸ ¿ÃµøΩ√∞£ 
} BALL;

typedef struct _Player
{
	int CenterX, CenterY; //X, Y ¡¬«• ºæ≈Õ 
	int MoveX, MoveY; // X, Y ¡¬«• ¿Ãµø 
	int X, Y; // X, Y «ˆ¿Á √‚∑¬ ¡¬«• ∞™ 
	int Index; // ¡ﬂΩ…¡¬«•¿« ¿Œµ¶Ω∫ 
} PLAYER;

typedef struct _Position
{
	int X, Y; // X, Y «ˆ¿Á ¡¬«• 
} Position;

GOAL Goal;
BALL Ball;
PLAYER Player;
char strPlayer[] = { "|__°‹__|" }; //ƒ≥∏Ø≈Õ
int Length; // ¡÷¿Œ∞¯ ƒ≥∏Ø≈Õ ±Ê¿Ã
int BallCount = 0;
// √ ±‚»≠
void Init() {

	Player.CenterX = 3; //¡÷¿Œ∞¯ X ¡ﬂΩ… ¡¬«•
	Player.CenterY = 0; //¡÷¿Œ∞¯ Y ¡ﬂΩ… ¡¬«• 
	Player.MoveX = 20; // ¡÷¿Œ∞¯ ¿Ãµø §º¡¬«• √ ±‚»≠
	Player.Y = Player.MoveY = 22; // ¡÷¿Œ∞¯ ¿Ãµµ Y¡¬«• √ ±‚»≠
	Player.X = Player.MoveX - Player.CenterX; //¡÷¿Œ∞¯ ƒ≥∏Ø≈Õ √‚∑¬ ¡¬«•
	Length = strlen(strPlayer); //¡÷¿Œ∞¯ ¿¸√º ±Ê¿Ã

	Ball.ReadyB = 1;
	Ball.bMoveX = Player.MoveX;
	Ball.bMoveY = Player.MoveY - 1;
	Ball.MoveTime = 100;

	int gLength, i;

	Goal.gMoveX = 20;
	Goal.gMoveY = 2;
<<<<<<< HEAD:ÏäõÍ≥®Ïù∏/Í≥µÎ∞õÍ∏∞.cpp
	Goal.gLength = 3; // ∞Ò¥Î ±Ê¿Ã = gLength * 2 + 1 
=======
	Goal.gLength = 2;
>>>>>>> 8db8968ed5b14923f3f4ff070dcb587be84b5187:Í≥µÎ∞õÍ∏∞.cpp
	Goal.MoveTime = 100;
	Goal.OldTime = clock();
	Goal.gDistance = 1;
	gLength = Goal.gLength * 2 + 1;
	for (i = 0; i < gLength; i++) {
		Goal.gLineX[i] = Goal.gMoveX + 2 * (i + 1);
	}
}
// µ•¿Ã≈Õ ∞ªΩ≈
void Update()
{
	clock_t CurTime = clock();
	int gLength = Goal.gLength * 2 + 1;
	int i;
<<<<<<< HEAD:ÏäõÍ≥®Ïù∏/Í≥µÎ∞õÍ∏∞.cpp



	if ((CurTime - Goal.OldTime) > Goal.MoveTime)
=======
	int BallCount = 0;
	
	if(Ball.ReadyB == 0) {//¿Ãµø¡ﬂ¿œ ∞ÊøÏ
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
>>>>>>> 8db8968ed5b14923f3f4ff070dcb587be84b5187:Í≥µÎ∞õÍ∏∞.cpp
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
			Goal.gDistance = Goal.gDistance * (-1); // πÊ«‚πŸ≤Ÿ±‚ 
		}
	}

	if (Ball.ReadyB == 0) //∞¯¿Ãµø¡ﬂ 
	{
		if ((CurTime - Ball.OldTime) > Ball.MoveTime) {
			if (Ball.bMoveY - 1 > 0) {
				Ball.bMoveY--;
				Ball.OldTime = CurTime;

				//∞Ò¥Î¿«∂Û¿Œ∞˙ √Êµπ 
<<<<<<< HEAD:ÏäõÍ≥®Ïù∏/Í≥µÎ∞õÍ∏∞.cpp
				if (Ball.bMoveX >= Goal.gLineX[0] && Ball.bMoveX + 1 <= Goal.gLineX[gLength - 1]) {
					if (Ball.bMoveY <= Goal.gMoveY) {//∞¯ √ ±‚»≠ 
=======
				if(Ball.bMoveX >= Goal.gLineX[0] && Ball.bMoveX + 1 <= Goal.gLineX[gLength - 1]){
					if(Ball.bMoveY <= Goal.gMoveY) //∞¯ √ ±‚»≠ 
>>>>>>> 8db8968ed5b14923f3f4ff070dcb587be84b5187:Í≥µÎ∞õÍ∏∞.cpp
						Ball.ReadyB = 1;
						Ball.bMoveY = Player.MoveY - 1;
<<<<<<< HEAD:ÏäõÍ≥®Ïù∏/Í≥µÎ∞õÍ∏∞.cpp
						BallCount++; //µÊ¡°
					}
					//∞Ò¥Î √Êµπ 
				}
				else if ((Ball.bMoveX >= Goal.gLineX[0] - 2 && Ball.bMoveX <= Goal.gLineX[0] - 1) || (Ball.bMoveX + 1 >= Goal.gLineX[0] - 2) && (Ball.bMoveX + 1 <= Goal.gLineX[0] - 1) || (Ball.bMoveX >= Goal.gLineX[gLength - 1]) + 2 && (Ball.bMoveX <= Goal.gLineX[gLength - 1] + 3) || (Ball.bMoveX + 1 >= Goal.gLineX[gLength - 1]) + 2 && (Ball.bMoveX + 1 <= Goal.gLineX[gLength - 1] + 3)) {
					if (Ball.bMoveY <= Goal.gMoveY) {
						Ball.ReadyB = 1;
=======
>>>>>>> 8db8968ed5b14923f3f4ff070dcb587be84b5187:Í≥µÎ∞õÍ∏∞.cpp
						Ball.bMoveX = Player.MoveX;
						BallCount++; //µÊ¡°
						printf("º∫∞¯!");
					}
<<<<<<< HEAD:ÏäõÍ≥®Ïù∏/Í≥µÎ∞õÍ∏∞.cpp
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
}
=======
					//∞Ò¥Î √Êµπ 
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


>>>>>>> 8db8968ed5b14923f3f4ff070dcb587be84b5187:Í≥µÎ∞õÍ∏∞.cpp
// √‚∑¬
void Render()
{
	char string[100] = { 0 };
	ScreenClear();
	int gLength, i;
	// √‚∑¬ Ω√¿€

	// ¡¬øÏø° ∫Æ¿ª ∏∏µÎ (≈¨∏Æ«Œ) 

	if (Player.X < 0)
		ScreenPrint(0, Player.MoveY, &strPlayer[Player.X * (-1)]);
	else if (Player.MoveX + (Length - Player.MoveX + Player.CenterX + 1) > 79)
	{
<<<<<<< HEAD:ÏäõÍ≥®Ïù∏/Í≥µÎ∞õÍ∏∞.cpp
		strncat(string, strPlayer, Length - ((Player.MoveX + Player.CenterX + 1) - 79));
		ScreenPrint(Player.X, Player.Y, string);
	}
	else {
		ScreenPrint(Player.X, Player.Y, strPlayer);
	}

	ScreenPrint(Ball.bMoveX, Ball.bMoveY, "°›");
	sprintf(string, "¡÷¿Œ∞¯ ¿Ãµø¡¬«• : %d, %d              ¡° ºˆ : %d               √ ±‚»≠ : R πˆ∆∞ ", Player.MoveX, Player.Y, BallCount);
=======
		strncat_s(string, strPlayer, Length - ((Player.MoveX + Player.CenterX + 1) - 79));	
	 	ScreenPrint(Player.X, Player.Y, string);
	 }else{
		ScreenPrint(Player.X, Player.Y, strPlayer);
	}
	
	ScreenPrint(Ball.bMoveX, Ball.bMoveY, "°€");
	sprintf_s(string, "¡÷¿Œ∞¯ ¿Ãµø¡¬«• : %d, %d", Player.MoveX, Player.Y);
>>>>>>> 8db8968ed5b14923f3f4ff070dcb587be84b5187:Í≥µÎ∞õÍ∏∞.cpp
	ScreenPrint(0, 0, string);


	//∞Ò¥Î √‚∑¬ 

	ScreenPrint(Goal.gMoveX, Goal.gMoveY, "§±");
	gLength = Goal.gLength * 2 + 1;

	for (i = 0; i < gLength; i++)
		ScreenPrint(Goal.gLineX[i], Goal.gMoveY, "§—");

	ScreenPrint(Goal.gLineX[gLength - 1] + 2, Goal.gMoveY, "§±");

	//√‚∑¬ ≥°
<<<<<<< HEAD:ÏäõÍ≥®Ïù∏/Í≥µÎ∞õÍ∏∞.cpp


	ScreenFlipping();
}

//«ÿ¡¶

void Release()
{
}


int main(void) {
	int Key, Remain;
=======
    		
	
	ScreenFlipping(); 
 }
 
    //«ÿ¡¶
 
 void Release()
 {
  }
  
  
int main (void){

	int Key, Remain;
	clock_t CurTime, OldTime;
>>>>>>> 8db8968ed5b14923f3f4ff070dcb587be84b5187:Í≥µÎ∞õÍ∏∞.cpp

	ScreenInit();
	Init(); // √ ±‚»≠

	while (1) //π´«—π›∫π 
	{
		if (_kbhit())
		{
			Key = _getch();
			if (Key == 'q')
				break;
			switch (Key)
			{
<<<<<<< HEAD:ÏäõÍ≥®Ïù∏/Í≥µÎ∞õÍ∏∞.cpp
			case LEFT:
				if (Player.MoveX > 0) {
					Player.MoveX--;
					Remain = Length - (Player.CenterX + 1); // ≥≤¿∫±Ê¿Ã = ¿¸√º ±Ê¿Ã - (¡ﬂΩ…¡¬«• + 1)
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
=======
				case LEFT :
					if(Player.MoveX > 0){
					Player.MoveX--; 
					Remain =  Length - (Player.CenterX); // ≥≤¿∫±Ê¿Ã = ¿¸√º ±Ê¿Ã - (¡ﬂΩ…¡¬«• + 1)
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
>>>>>>> 8db8968ed5b14923f3f4ff070dcb587be84b5187:Í≥µÎ∞õÍ∏∞.cpp
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

		Update();//µ•¿Ã≈Õ ∞ªΩ≈ 
		Render(); //»≠∏È √‚∑¬ 
<<<<<<< HEAD:ÏäõÍ≥®Ïù∏/Í≥µÎ∞õÍ∏∞.cpp

	}

	Release();
	ScreenRelease();
	return 0;
}
=======
		
		OldTime = clock();

		while (1)
		{
			CurTime = clock();
			if (CurTime - OldTime > 20)
			{
				OldTime = CurTime;
				break;
			}
		}//¥Î±‚Ω√∞£
	 } 
	 
	 Release();
	 ScreenRelease();
	 return 0;
}
>>>>>>> 8db8968ed5b14923f3f4ff070dcb587be84b5187:Í≥µÎ∞õÍ∏∞.cpp
