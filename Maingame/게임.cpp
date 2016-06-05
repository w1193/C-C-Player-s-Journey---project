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
	printf("1. 이름 : \n\n");
	printf("2. 스탯 \n\n");
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
	system("cls");
	if (class_pro == 1)
	{

		printf("자는중~\n");
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
			Intel -= 15;
			Stat_Limit(Stamina);
			Stat_Limit(Intel);//수업을 듣지않고 잠을 잤을 때 일어나는 상황
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
	printf_s("기숙사 입니다               날짜: %d 일\n\n", day);
	printf_s("1. 잠자기 \n\n2. 밥먹기\n\n3. 캐릭터정보\n\n4. 밖으로 나가기\n\n");
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
		Stamina += 5;
		Stat_Limit(Stamina);
		printf("Stamina + 5 증가 ! !\n\n");
		system("PAUSE");//여기에 밥먹기 했을때 일어나는 상황
		goto home;
	case(3) :
		system("cls");
		stat();//캐릭터 정보보기
		system("PAUSE");
		goto home;
	case(4) :
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
		  printf_s("\n신관을 간다\n\n");
		  system("PAUSE");
		  goto cafe;
	  case(2) :
		  printf_s("\n교양동을 간다\n\n");
		  system("PAUSE");
		  goto classroom;
	  case(3) :
		  printf_s("\n공대 4호관을 간다\n\n");
		  system("PAUSE");
		  goto eng_univ;
	  case(4) :
		  printf_s("\n도서관을 간다\n\n");
		  system("PAUSE");
		  goto lib;
	  case(5) :
		  printf_s("기숙사를 간다\n\n");
		  system("PAUSE");
		  goto home;
	  }
  }
	  cafe: {
		  system("cls");
		  printf_s("신관입니다\n\n");
		  printf("무엇을 하시겠습니까?\n\n");
		  printf_s("1. 동아리방 가기\n\n2. 식당 가기\n\n3. 밖으로 나가기\n\n");
		  scanf_s("%d", &choise);
		  switch (choise)
		  {
		  case(1) :
			  goto club;
		  case(2) :
			  goto food;
		  case(3) :
			  goto school;
		  }
	  }
		food: {
			system("cls");
			printf_s("식당입니다   현재 남은 돈 : %d\n\n", Money);
			printf_s("이곳은 식당입니다\n\n1. 정식(2000원)\n\n2. 특식(3000원)\n\n3. 신관으로 돌아가기\n\n");
			scanf_s("%d", &choise);
			switch (choise)
			{
			case(1) :
				system("cls");
				if (Money > 2000)
				{
					printf_s("정식 머금\n\n");
					Money -= 2000;
					Stamina += 10;
					Money_Limit();
					Stat_Limit(Stamina);//정식먹으면 나오는 변화
					system("pause");
				}
				else
				{
					printf("돈이 부족합니다.\n\n");
					system("pause");
				}
				goto food;
			case(2) :
				system("cls");
				if (Money > 3000)
				{
					printf_s("특식머금\n\n");
					Money -= 3000;
					Stamina += 15;
					Money_Limit();
					Stat_Limit(Stamina);//특식 먹으면 나오는 변화
					system("pause");
				}
				else
				{
					printf("돈이 부족합니다");
					system("pause");

				}
				goto food;
			case(3) :
				goto cafe;
			}
		}
		  club: {
			  system("cls");
			  printf_s("동아리방입니다\n\n");  getchar();
			  printf_s("이곳에는 슬픈 전설이 있지...\n");  getchar();
			  printf_s("알고싶나?\n");  getchar();
			  printf_s("그럼 500원.\n");  getchar();
			  printf_s("어떻게 하지??\n\n1. 500원을 준다\n\n2. 주지않는다\n");
			  scanf_s("%d", &choise);
			  switch (choise)
			  {
			  case(1) :
				  Money -= 500;
				  Money_Limit();
				  system("cls"); getchar();
				  printf("..........\n"); getchar();
				  printf("헹? 속았지? 그걸 믿냨ㅋㅋㅋ\n"); getchar();
				  printf("500원을 잃었습니다.\n"); getchar();
				  system("PAUSE");
				  goto cafe;
			  case(2) :
				  system("cls");
				  printf("싫음 말고...\n\n");
			  }
			  system("PAUSE");
			  goto cafe;
		  }
			classroom: {
				system("cls");
				printf_s("교양동 입니다\n\n");
				printf("무엇을 하시겠습니까?\n\n");
				printf_s("1. 수업 듣기\n\n2. 밖으로 나가기\n\n");
				scanf_s("%d", &choise);
				switch (choise)
				{
				case(1) :
					system("cls");
					printf("수업을 듣는 중...\n\n");  system("PAUSE");
					class_pro++;
					Stamina -= 5;
					Intel += 5;
					Stat_Limit(Stamina);
					Stat_Limit(Intel);//이곳에 수업 들으면 일어나는 상황
					system("cls");
					printf(".\n.\n수업이 끝났습니다.\n\n");  system("PAUSE");
				case(2) :
					goto school;
				}
			}
					   //공대에서 주로 진행
				   eng_univ: {
					   system("cls");
					   printf_s("공대4호관 입니다\n\n");
					   printf("어디로 가시겠습니까?\n\n");
					   printf("1. 교실\n\n");
					   printf("2. 과방\n\n");
					   printf("3. 돌아간다.\n\n");
					   scanf_s("%d", &choise);
					   switch (choise)
					   {
					   case(1) :
						   goto eng_class;
					   case(2) :
						   goto eng_room;
					   }
					   goto school;
				   }
						 eng_class: {
							 system("cls");
							 printf_s("교실 입니다\n\n");
							 system("PAUSE");
							 goto eng_univ;
						 }
								eng_room: {
									system("cls"); getchar();
									printf("과방입니다.\n"); getchar();
									printf("야생의 오픈소스가 나타났다 ! !\n"); getchar();
									printf("으아아아아아아아아아아아아\n\n");
									system("PAUSE");
									class_pro++;
									goto eng_univ;
								}
									  lib: {
										  system("cls");
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
{
	printf("방학이에염\n");
	day++;
	system("pause");
}
//방학
void endings() {

}//엔딩 삽입
void main()
{
	while (day != 288)
	{
		if (day % 72 <= 60)
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
	endings();
}
