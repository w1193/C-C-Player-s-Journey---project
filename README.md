#This Project is made by JNU(Jeju National University) students.


This project is for learning about C / Cpp programming, and we are just beginners, So This Project's code will be very simple.

If you see typo on this project please tell us :>

and this project will be made in Korean

```
기초적인 변수명
```


##Mini Game
    ```
    * Catch Ball
      - For player :
          MoveX, MoveY, CenterX, CenterY, X, Y
      - For Ball :
          bMoveX, bMoveY ....
    ```
    
##Main Game
    ```
    * Stat
          Power, Stamina, Intel, Luck, Dex, Wealth, Beauty, Money
    * Places 
          home, school, cafe, club, food, classroom, eng_univ, eng_class, eng_room, lib
    ```


##Frame Work
    ```
    * Screen.h
        -#include <windows.h>

            static int g_nScreenIndex;
            static HANDLE g_hScreen[2];

            void ScreenInit()
            {
            	CONSOLE_CURSOR_INFO cci;
	
            	g_hScreen[0] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL); // 화면 버퍼 1 생성 
            	g_hScreen[1] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL); // 화면 버퍼 2 생성
	
            	cci.dwSize = 1;
            	cci.bVisible = FALSE;
            	SetConsoleCursorInfo(g_hScreen[0], &cci);
            	SetConsoleCursorInfo(g_hScreen[1], &cci); // 커서 숨기기 13 - 16
            }

            void ScreenFlipping()
            {
            	SetConsoleActiveScreenBuffer(g_hScreen[g_nScreenIndex]);
            	g_nScreenIndex = !g_nScreenIndex;
            }

            void ScreenClear()
            {
            	COORD Coor = {0, 0};
            	DWORD dw;
            	FillConsoleOutputCharacter(g_hScreen[g_nScreenIndex], ' ', 80*25, Coor, &dw); 
            }

            void ScreenRelease()
            {
            	CloseHandle(g_hScreen[0]);
            	CloseHandle(g_hScreen[1]);
            }

            void ScreenPrint(int x, int y, char *string)
            {
            	DWORD dw;
            	COORD CursorPosition = {x, y};
            	SetConsoleCursorPosition(g_hScreen[g_nScreenIndex], CursorPosition);
            	WriteFile(g_hScreen[g_nScreenIndex], string, strlen(string), &dw, NULL);
            }

            void SetColor(unsigned short color)
            {
            	SetConsoleTextAttribute(g_hScreen[g_nScreenIndex], color);
            }
    ```
