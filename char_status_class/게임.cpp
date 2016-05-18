#include <stdio.h>
#include <stdlib.h> 
#include <time.h>

int choise;//선택
int day = 0;//날짜
int class_pro;//수업 받았는지 확인

void week()
{
home:
	system("cls");
	printf_s("기숙사 입니다                 %d\n\n", day);
	printf_s("1. 잠자기 \n\n2. 밥먹기\n\n9. 밖으로 나가기\n\n");
	scanf_s("%d", &choise);
	switch (choise)
	{
	case(1):
		system("cls");
		if (class_pro == 1)
		{
			system("PAUSE");
			class_pro--;
			day++;
			//여기에 잠자기 했을때 일어나는 상황
			return;
		}
		else
		{
			printf_s("아직 수업을 듣지 않았습니다\n\n그래도 잠을 자겟습니까?\n\n1. 잔다\n\n2. 안잔다\n");
			scanf_s("%d", &choise);
			switch (choise)
			{
			case(1):
				day++;
				return;
			case(2):
				goto home;
			}
		}
	case(2):
		system("cls");
		system("PAUSE");
		//여기에 밥먹기 했을때 일어나는 상황
		goto home;
	case(9):
		system("PAUSE");
		goto school;
	}

school:
	system("cls");
	printf_s("학교입니다\n\n");
	printf_s("1. 신관 가기\n\n2. 교양동 가기\n\n3. 공대4호관 가기\n\n4. 도서관 가기\n\n5. 기숙사 가기\n\n");
	scanf_s("%d", &choise);
	switch (choise)
	{
	case(1):
		printf_s("신관을 간다\n");
		system("PAUSE");
		goto cafe;
	case(2):
		printf_s("교양동을 간다\n");
		system("PAUSE");
		goto classroom;
	case(3):
		printf_s("공대 4호관을 간다\n");
		system("PAUSE");
		goto eng_univ;
	case(4):
		printf_s("도서관을 간다\n");
		system("PAUSE");
		goto lib;
	case(5):
		printf_s("기숙사를 간다\n");
		system("PAUSE");
		goto home;
	}

cafe:
	system("cls");
	printf_s("신관입니다\n\n");
	printf_s("1. 동아리방 가기\n\n2. 식당 가기\n\n9. 밖으로 나가기\n\n");
	scanf_s("%d", &choise);
	switch (choise)
	{
	case(1):
		goto club;
	case(2):
		goto food;
	case(9):
		goto school;
	}

food:
	system("cls");
	printf_s("식당입니다\n\n");
	printf_s("이곳은 식당입니다\n\n1. 정식\n\n2. 특식\n\n9. 신관으로 돌아가기\n\n");
	scanf_s("%d", &choise);
	switch (choise)
	{
	case(1):
		system("cls");
		printf_s("정식머금");
		//정식먹으면 나오는 변화
		system("pause");
		goto food;
	case(2):
		system("cls");
		printf_s("특식머금");
		//특식 먹으면 나오는 변화
		system("pause");
		goto food;
	case(9):
		goto cafe;
	}
club:
	system("cls");
	printf_s("동아리방입니다\n\n");


classroom:
	printf_s("교양동 입니다\n\n");
	printf_s("1. 수업 듣기\n\n9. 밖으로 나가기\n\n");
	scanf_s("%d", &choise);
	switch (choise)
	{
	case(1):
		//이곳에 수업 들으면 일어나는 상황
	case(9):
		goto school;
	}

eng_univ:
	printf_s("공대4호관 입니다\n\n");
	goto eng_class;

eng_class:
	printf_s("교실 입니다\n\n");
	goto eng_room;

eng_room:
	printf_s("과방 입니다\n\n");
	class_pro++;
	goto home;

lib:
	printf_s("중앙 도서관 입니다\n\n");

}
void weekend()
{
	printf_s("주말입니다\n");
	system("pause");
	day++;
}
void vacation()
{}

void main()
{
	while (day != 288)
	{
		if (day <= 60)
		{
			if (day % 3 == 1)
			{
				weekend();
			}
			else
			{
				week();
			}
		}
		else
		{
			vacation();
		}
	}
}