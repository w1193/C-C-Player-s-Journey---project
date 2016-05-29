#include <stdio.h>
#include <stdlib.h> 
#include <time.h>

//int Power, Stamina, Intel, Luck, Dex, Wealth, Beauty; //캐릭터 스탯
int Power, Intel, Luck, Dex, Wealth, Beauty = 0;
int Stamina = 100;
int Money = 50000;//초기 시작 스탯과 돈
int Stat_min = 0;
int Stat_max = 100;//스탯의 최대치와 최소치

int choise;//선택
int day = 0;//날짜
int class_pro;//수업 받았는지 확인
int back;

void stat()
{
	printf("힘:%d, 체력:%d, 지력:%d, 운: %d\n\n민첩:%d, wealth: %d, 외모:%d, 돈:%d\n\n", Power, Stamina, Intel, Luck, Dex, Wealth, Beauty, Money);
	return;
}

int Stat_Limit(int& stat) {
	if (stat <= Stat_min) {
		stat = 0;
	}
	if (stat >= Stat_max) {
		stat = 100;
	}
	else {
		stat = stat;
	}
	return stat;
}//스탯의 최대치와 최소치를 제한한다.

int Money_Limit() {
	if (Money <= 0) {
		Money = 0;
	}
	else
	{
		Money = Money;
	}
	return Money;
}//돈의 최소값을 제한.

void sleep()
{
	if (class_pro == 1)
	{
		system("PAUSE");
		class_pro--;
		day++;
		Stamina += Stat_max / 2;
		Stat_Limit(Stamina);//여기에 잠자기 했을때 일어나는 상황
		return;
	}
	else
	{


		printf_s("아직 수업을 듣지 않았습니다\n\n그래도 잠을 자겠습니까?\n\n1. 잔다\n\n2. 안잔다\n");
		scanf_s("%d", &choise);
		switch (choise)
		{
		case(1) :
			day++;
			Stamina += Stat_max / 2;
			Stat_Limit(Stamina);//수업을 듣지않고 잠을 잤을 때 일어나는 상황
			return;
		case(2) :
			back = 1;
			return;
		}
	}
}
//잠자는 상황
void week()
{
home: {
	system("cls");
	printf_s("기숙사 입니다                 %d\n\n", day);
	stat();
	printf_s("1. 잠자기 \n\n2. 밥먹기\n\n9. 밖으로 나가기\n\n");
	scanf_s("%d", &choise);
	switch (choise)
	{
	case(1) :
		system("cls");
		sleep();
		if (back == 1)
		{
			back = 0;
			goto home;
		}
		system("cls");
		return;
	case(2) :
		system("cls");
		system("PAUSE");
		Stamina += 5;
		Stat_Limit(Stamina);//여기에 밥먹기 했을때 일어나는 상황
		goto home;
	case(9) :
		system("PAUSE");
		goto school;
	}

}
  school: {
	  system("cls");
	  printf_s("학교입니다\n\n");
	  printf_s("1. 신관 가기\n\n2. 교양동 가기\n\n3. 공대4호관 가기\n\n4. 도서관 가기\n\n5. 기숙사 가기\n\n");
	  scanf_s("%d", &choise);
	  switch (choise)
	  {
	  case(1) :
		  printf_s("신관을 간다\n");
		  system("PAUSE");
		  goto cafe;
	  case(2) :
		  printf_s("교양동을 간다\n");
		  system("PAUSE");
		  goto classroom;
	  case(3) :
		  printf_s("공대 4호관을 간다\n");
		  system("PAUSE");
		  goto eng_univ;
	  case(4) :
		  printf_s("도서관을 간다\n");
		  system("PAUSE");
		  goto lib;
	  case(5) :
		  printf_s("기숙사를 간다\n");
		  system("PAUSE");
		  goto home;
	  }
  }
	  cafe: {
		  system("cls");
		  printf_s("신관입니다\n\n");
		  printf_s("1. 동아리방 가기\n\n2. 식당 가기\n\n9. 밖으로 나가기\n\n");
		  scanf_s("%d", &choise);
		  switch (choise)
		  {
		  case(1) :
			  goto club;
		  case(2) :
			  goto food;
		  case(9) :
			  goto school;
		  }
	  }
		food: {
			system("cls");
			printf_s("식당입니다\n\n");
			printf_s("이곳은 식당입니다\n\n1. 정식\n\n2. 특식\n\n9. 신관으로 돌아가기\n\n");
			scanf_s("%d", &choise);
			switch (choise)
			{
			case(1) :
				system("cls");
				printf_s("정식머금\n\n");
				Money -= 2000;
				Stamina += 10;
				Money_Limit();
				Stat_Limit(Stamina);//정식먹으면 나오는 변화
				system("pause");
				goto food;
			case(2) :
				system("cls");
				printf_s("특식머금\n\n");
				Money -= 3000;
				Stamina += 15;
				Money_Limit();
				Stat_Limit(Stamina);//특식 먹으면 나오는 변화
				system("pause");
				goto food;
			case(9) :
				goto cafe;
			}
		}
		  club: {
			  system("cls");
			  printf_s("동아리방입니다\n\n");
		  }
			classroom: {
				printf_s("교양동 입니다\n\n");
				printf_s("1. 수업 듣기\n\n9. 밖으로 나가기\n\n");
				scanf_s("%d", &choise);
				switch (choise)
				{
				case(1) :
					Stamina -= 5;
					Intel += 5;
					Stat_Limit(Stamina);
					Stat_Limit(Intel);//이곳에 수업 들으면 일어나는 상황
				case(9) :
					goto school;
				}
			}
					   //공대에서 주로 진행
				   eng_univ: {
					   printf_s("공대4호관 입니다\n\n");
					   goto eng_class;
				   }
						 eng_class: {
							 printf_s("교실 입니다\n\n");
							 goto eng_room;
						 }
								eng_room: {
									printf_s("과방 입니다\n\n");
									class_pro++;
									goto home;
								}
									  lib: {
										  printf_s("중앙 도서관 입니다\n\n");
									  }
}
//평일
void weekend()
{
	printf_s("주말입니다\n무엇을 하시겟습니까?\n\n1. 알바\n\n2. 운동\n\n3. 잠자기\n\n");
	scanf_s("%d", &choise);
	switch (choise)
	{
	case(1) :
		printf_s("알바함\n");
		system("pause");
		system("cls");
		day++;
		Money += 6030;
		Stamina -= 15;
		Wealth += 1;
		Stat_Limit(Stamina);
		Stat_Limit(Wealth);//알바 했을 때의 변화
		return;
	case(2) :
		printf_s("운동함\n");
		system("pause");
		system("cls");
		day++;
		Stamina -= 5;
		Power, Dex += 5;
		Beauty += 1;
		Stat_Limit(Stamina);
		Stat_Limit(Power);
		Stat_Limit(Dex);
		Stat_Limit(Beauty);//운동했을 때의 변화
		return;
	case(3) :
		printf("잠\n");
		system("pause");
		system("cls");
		day++;
		Stamina += Stat_max / 2;
		Stat_Limit(Stamina);
		return;
	}
}
//주말
void vacation()
{}
//방학
void main()
{
	while (day != 288)
	{
		if (day <= 60)
		{
			if (day % 3 == 2)
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
