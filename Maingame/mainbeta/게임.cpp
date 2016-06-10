#include <stdio.h>
#include <stdlib.h> 
#include <time.h>


//int Power, Stamina, Intel, Luck, Beauty; //캐릭터 스탯
int Power, Intel, Luck, Beauty = 0;
int Stamina = 1000;
int Money = 50000;//초기 시작 스탯과 돈
int Stat_min = 0;
int Stat_max = 1000;//스탯의 최대치와 최소
char name[100][100] = { "철수(종족 : Terran)","영희(종족 : Protos)","바둑이(종족 : Zerg)" };
int ncode;

int choise;//선택
int day = 0;//날짜
int class_pro;//수업 받았는지 확인
int test;//시험을 봤는지 확인
int D_meal;//기숙사에서 밥을 먹은 횟수
int back;


void setname() {

	printf("플레이 하고 싶은 캐릭터의 번호를 입력하세요.\n\n");
	printf("1. 철수(종족 : Terran)\n\n"); 
	printf("2. 영희(종족 : Protos)\n\n");
	printf("3. 바둑이(종족 : Zerg)\n\n"); 
	scanf_s("%d",&choise);
	switch(choise) {
	case(1):
		printf("Player '철수' 를 선택하셨습니다.\n\n"); getchar();
		ncode = 0;
		printf("<<종족 패시브>>\n"); getchar();
		Power += 200;
		printf("힘이 200증가합니다.\n"); getchar();
		return;
	case(2):
		printf("Player '영희' 를 선택하셨습니다.\n"); getchar();
		ncode =1;
		printf("<<종족 패시브>>\n"); getchar();
		Intel += 200;
		printf("지력이 200증가합니다.\n"); getchar();
		return;
	case(3):
		printf("Player '바둑이' 를 선택하셨습니다.\n"); getchar();
		ncode=2;
		printf("<<종족 패시브>>\n"); getchar();
		Beauty += 200;
		printf("매력이 200증가합니다.\n"); getchar();
		return;
	}
	system("cls");
}

void stat()
{
	printf("1. 이름 : %s\n\n", name[ncode]);
	printf("2. 스탯 \n\n");
	printf("힘:%d, 체력:%d, 지력:%d, 운: %d\n외모:%d, 돈:%d\n\n", Power, Stamina, Intel, Luck, Beauty, Money);
	return;
}

int Stat_Limit(int& stat) {
	if (stat <= Stat_min) {
		stat = Stat_min;
	}
	if (stat >= Stat_max) {
		stat = Stat_max;
	}
	return stat;
}//스탯의 최대치와 최소치를 제한한다.

int Money_Limit() {
	if (Money <= 0) {
		Money = 0;
	}
	return Money;
}//돈의 최소값을 제한.

void talk() {
	srand((unsigned)time(NULL));
	switch (rand() % 3)
	{
	case(0) :
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
			Luck -= 50;
			Stat_Limit(Luck);
			system("cls"); getchar();
			printf("..........\n"); getchar();
			printf("헹? 속았지? 그걸 믿냐ㅋㅋㅋ\n"); getchar();
			printf("500원을 잃었습니다.운이 50 감소 하였습니다.\n"); getchar();
			break;
		case(2) :
			system("cls");
			printf("싫음 말고...\n\n");
			break;
		}
		break;
	case(1) :
		printf_s("뭔가 여러가지가 있다.\n");  getchar();
		printf_s("무엇을 하지??\n");  getchar();
		printf_s("1. 기타를 친다(체력 - 50, 매력 + 50)\n\n2. 술을 마신다(체력 - 300, 지력- 300, 돈 - 10000, 매력 랜덤 증감 및 추가 보상)\n\n");
		scanf_s("%d", &choise);
		switch (choise)
		{
		case 1:
			printf("둥기둥두두두두두둥\n"); getchar();
			printf("생각보다 뜻대로 되지않네...\n"); 
			Beauty += 50;
			Stat_Limit(Beauty);
			system("pause");
			break;
		case 2:
			Stamina -= 300;
			Intel -= 300;
			Money -= 10000;
			Stat_Limit(Stamina);
			Stat_Limit(Intel);
			Money_Limit();
			system("cls");
			switch (rand() %2)
			{
				int Beauty_tmp;
			case(0) :
				Beauty_tmp = rand() % 501;
				Beauty -= Beauty_tmp;
				Stat_Limit(Beauty);
				printf("주량조절에 실패한 당신, 새로 생성된 흑역사로 인하여 매력이 %d만큼 감소하였습니다.\n", Beauty_tmp);
			case(1):
				Beauty_tmp = rand() % 501;
				Beauty += Beauty_tmp;
				Stat_Limit(Beauty);
				Luck += 300;
				Stat_Limit(Luck);
				printf("끝까지 취하지 않고 제정신을 유지한 당신, 매력이 %d만큼 증가하였습니다.(추가 보상 : 운 300 증가)\n", Beauty_tmp);
			}
			break;
		}
		break;
	case(2) :
		printf_s("아무도 없다.\n"); getchar();
		printf_s("..."); getchar();
		printf_s("..\n"); getchar();
		printf_s("ㅠㅠ\n"); getchar();
		break;
	}
}//동아리방 입장 시 대화

void lib_talk() {
	printf_s("중앙 도서관 입니다\n\n");
	srand((unsigned)time(NULL));
	switch (rand() % 3)
	{
	case(0) :
		printf_s("책을 빌리러 왔다.\n\n");  getchar();
		printf_s("음...정말 많은 책들이 있네.\n");  getchar();
		printf_s("아니, ㅇ...이것은!!!\n");  getchar();
		printf_s("1000원을 획득했다!!(운 + 300)\n"); getchar();
		Money += 10000;
		Luck += 300;
		Stat_Limit(Luck);
		printf("득템!!!!!!"); getchar();
		break;
	case(1) :
		printf_s("금일 중앙도서관은 휴무입니다.\n");  getchar();
		printf_s("..");  getchar();
		printf_s("..\n"); getchar();
		printf_s("ㅠㅠ\n");  getchar();
		Luck -= 100;
		Stat_Limit(Luck);
		printf_s("운 -100 감소\n"); getchar();
		break;
	case(2) :
		printf_s("무엇을 하지??\n"); getchar();
		printf_s("1. 책을 읽는다.(지력 + 100)\n\n2. 혼자서 공부를 한다.(+50)\n");
		scanf_s("%d", &choise);
		switch (choise) {
		case 1:
			system("cls");
			printf_s("개미는~~~~~\n\n");  getchar();
			printf_s("빠 밤~~\n");  getchar();
			printf_s("오늘도~~~~\n"); getchar();
			printf_s("빠 밤~~~\n");  getchar();
			printf_s("열심히~~~~~\n");  getchar();
			printf_s("일을~~ 하~~네~~\n\n");  getchar();
			printf_s("과로사!!!!!!\n\n"); getchar();
			Intel += 100;	Stat_Limit(Intel);
			Luck += 50; Stat_Limit(Luck);
			printf_s("재밌었다. 읽는 보람이 있는 책이었다."); getchar();
			break;
		case 2:
			system("cls");
			printf_s("공부를 하는 중...\n");  getchar();
			printf_s("머리가 아파온다ㅠㅠ\n");  getchar();
			printf_s("역시 공부는 몸에 해로워.(체력 - 100)\n"); getchar();
			Intel += 50; Stamina -= 100;
			break;
		}
		break;
	}
}//중앙도서관 입장 시 대화

void sleep()
{
	system("cls");
	if (day == 60 || day == 60 + 72 || day == 60 + 72 + 72 || day == 60 + 72 + 72 + 72)
	{
		if (test != 1)
		{
			printf("아직 시험을 보지 않았습니다");
			system("pause");
			back = 1;
			return;
		}
	}
	if (class_pro >= 1)
	{

		printf("자는중~\n");
		system("PAUSE");
		test = 0;
		class_pro = 0;
		D_meal = 0;
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
			Intel -= 45;
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
	if (day == 60 || day == 60 + 72 || day == 60 + 72 + 72 || day == 60 + 72 + 72 + 72)
	{
		printf("오늘은 시험을 보는 날입니다. 공대4호관 교실로 가세요.\n\n");
		if (Intel <= 500)
		{
			printf("어디선가 자신감이 솟구친다!!\n\n");
		}
	}
	printf_s("1. 잠자기 \n\n2. 밥먹기\n\n3. 밖으로 나가기\n\n4. 스텟보기\n\n");
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
		system("cls"); getchar();
		if (Stamina >= Stat_max) {
			printf("배부른데...\n"); getchar();
			printf("먹을까? 말까?\n"); getchar();
			printf("1. 먹는다\n\n2. 먹지않는다\n"); 
			scanf_s("%d", &choise);
			switch(choise) {
				case 1:
					system("cls"); getchar();
					printf("우웨에에에에에에에에에웨에에에에에에엑\n"); getchar();
					printf("억지로 밥을 먹어 역효과가 나타났습니다.(체력 - 100, 지력 - 150, 매력 -50)\n"); getchar();
					Stamina -= 100;
					Intel -= 150;
					Beauty -= 50;
					Stat_Limit(Stamina);
					Stat_Limit(Intel);
					Stat_Limit(Beauty);
					D_meal++;
					system("pause");
					break;
				case 2:
					system("cls"); getchar();
					printf("그래, 과식은 몸에 좋지않아.\n"); getchar();
					system("pause");
					break;
			}
		}//체력이 full인 상태에서 밥을 먹었을 때 일어나는 상황
		else
		{
			if (D_meal >= 1) {
				printf("오늘 먹을 수 있는 횟수를 초과하였습니다.\n");
			}
			else {
				Stamina += 150;
				Stat_Limit(Stamina);
				printf("체력 + 150 증가 ! !\n\n");
				D_meal++;
			}
			system("PAUSE");//밥먹기 했을때 일어나는 상황
		}
		goto home;
	case(3) :
		system("PAUSE");
		goto school;
	case(4) :
		system("cls");
		stat();//캐릭터 정보보기
		system("PAUSE");
		goto home;
	}

}
  school: {
	  system("cls");
	  printf_s("학교입니다\n\n");
	  printf_s("1. 신관 가기\n\n2. 교양동 가기\n\n3. 공대4호관 가기\n\n4. 도서관 가기\n\n5. 기숙사 가기\n\n6. 스텟보기\n\n");
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
	  case(6) :
		  system("cls");
		  stat();//캐릭터 정보보기
		  system("PAUSE");
		  goto school;
	  }
  }//학교
	  cafe: {
		  system("cls");
		  printf_s("신관입니다\n\n");
		  printf("무엇을 하시겠습니까?\n\n");
		  printf_s("1. 동아리방 가기\n\n2. 식당 가기\n\n3. 밖으로 나가기\n\n4. 스텟보기\n\n");
		  scanf_s("%d", &choise);
		  switch (choise)
		  {
		  case(1) :
			  goto club;
		  case(2) :
			  goto food;
		  case(3) :
			  goto school;
		  case(4) :
			  system("cls");
			  stat();//캐릭터 정보보기
			  system("PAUSE");
			  goto cafe;
		  }
	  }//신관
		food: {
			system("cls");
			printf_s("식당입니다   현재 남은 돈 : %d\n\n", Money);
			printf_s("이곳은 식당입니다\n\n1. 정식(2000원)\n\n2. 특식(3000원)\n\n3. 신관으로 돌아가기\n\n4. 스텟보기\n\n");
			scanf_s("%d", &choise);
			switch (choise)
			{
			case(1) :
				system("cls");
				if (Money > 2000)
				{
					printf_s("정식 머금\n\n");
					Money -= 2000;
					Stamina += 300;
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
					Stamina += 500;
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
			case(4) :
				system("cls");
				stat();//캐릭터 정보보기
				system("PAUSE");
				goto food;
			}
		}//학생식당
		  club: {
			  system("cls");
			  printf_s("동아리방입니다\n\n");
			  system("cls");
			  talk();
			  system("PAUSE");
			  goto cafe;
		  }//동아리방
			classroom: {
				system("cls");
				printf_s("교양동 입니다\n\n");
				printf("무엇을 하시겠습니까?\n\n");
				printf_s("1. 수업 듣기(체력 200감소, 지능 45 증가)\n\n2. 밖으로 나가기\n\n3. 스텟보기\n\n");
				scanf_s("%d", &choise);
				switch (choise)
				{
				case(1) :
					system("cls");
					printf("수업을 듣는 중...\n\n");  system("PAUSE");
					class_pro++;
					Stamina -= 200;
					Intel += 45;
					Stat_Limit(Stamina);
					Stat_Limit(Intel);//이곳에 수업 들으면 일어나는 상황
					system("cls");
					printf(".\n.\n수업이 끝났습니다.\n\n");  system("PAUSE");
				case(2) :
					goto school;
				case(3) :
					system("cls");
					stat();//캐릭터 정보보기
					system("PAUSE");
					goto classroom;
				}
			}//교양동
					   //공대에서 주로 진행
				   eng_univ: {
					   system("cls");
					   printf_s("공대4호관 입니다\n\n");
					   printf("어디로 가시겠습니까?\n\n");
					   printf("1. 교실\n\n2. 과방\n\n3. 돌아간다.\n\n4. 스탯보기\n\n");
					   scanf_s("%d", &choise);
					   switch (choise)
					   {
					   case(1) :
						   goto eng_class;
					   case(2) :
						   goto eng_room;
					   case(3) :
						   goto school;
					   case(4) :
						   system("cls");
						   stat();//캐릭터 정보보기
						   system("PAUSE");
						   goto eng_univ;
					   }
				   eng_class: {
					   system("cls");
					   if (day == 60 || day == 60 + 72 || day == 60 + 72 + 72 || day == 60 + 72 + 72 + 72)
					   {
						   printf("시험을 봅니다\n\n");
						   //시험보는부분 게임 삽입
						   test++;
						   class_pro++;
						   system("pause");
					   }
					   printf_s("교실 입니다\n\n");
					   system("PAUSE");
					   goto eng_univ;
				   }//공대 4호관 강의실
						  eng_room: {
							  system("cls"); getchar();
							  printf("과방입니다.\n"); getchar();
							  printf("야생의 오픈소스가 나타났다 ! !\n"); getchar();
							  printf("으아아아아아아아아아아아아\n\n");
							  system("PAUSE");
							  class_pro++;
							  goto eng_univ;
						  }//과방
				   }//공대 4호관
						 lib: {
							 system("cls");
							 lib_talk();
							 system("pause");
							 goto school;
						 }//중앙도서관
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
		//게임 삽입
		Money += //스코어;
		Stamina -= 150;
		Stat_Limit(Stamina);//알바 했을 때의 변화
		return;
	case(2) :
		printf_s("운동함\n");
		system("pause");
		system("cls");
		day++;
		//게임 삽입
		Stamina -= 300;
		Power+= 80;
		Beauty += 50;
		Stat_Limit(Stamina);
		Stat_Limit(Power);
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
	system("cls");
	printf("방학이에염\n");
	day++;
	system("pause");
}
//방학
void endings() {
	int sum = Power + Intel + Beauty + Luck;
	if(sum <= 1200){
		printf("학교를 졸업하였다\n"); getchar();
		printf("졸업장을 받으러 학교에 가자.\n"); getchar();
		printf("이런....!!\n"); getchar();
		printf("..."); getchar();
		printf("...\n"); getchar();
		printf("옆에서 다가오는 차를 미처 보지 못하고 그만....\n\n"); getchar();
		printf("<______________>\n");
		printf("<돌연사!!!!!!!!>\n"); 
		printf("<-------------->\n"); getchar();
		printf("...고인의 명복을 바랍니다.\n"); getchar();
	}
	else
	{
		if (sum >= 3200)
		{
			printf("학교를 졸업하였다\n\n"); getchar();
			printf("대기업에 취직하기 위한 경력을 얻기 위하여 중소기업에 취직하였다.\n\n"); getchar();
			printf("대기업에 취직했지만 곧 백수가 되었다.\n\n"); getchar();
			printf("퇴직금으로 치킨집을 열었다.\n\n"); getchar();
			printf("그러나 먼저 치킨집을 연 문과들에게 밀려 치킨집은 망했다.\n\n"); getchar();
			printf("내 인생은 망했어....\n\n\n"); getchar();
			printf("------THE (Happy)END-------\n\n"); getchar();
		}
		else
		{
			if (2000 <= sum <= 3200) {
				printf("졸업이 코앞이다.\n"); getchar();
				printf("그전에 밀린 과제를 해야지ㅎㅎ\n"); getchar();
				printf("."); getchar();
				printf("."); getchar();
				printf("..엌!!\n"); getchar();
				printf("<_________________________>\n");
				printf("<과도한 과제로 인한 돌연사>\n"); 
				printf("<------------------------->\n"); getchar();
				printf("...고인의 명복을 바랍니다.\n"); getchar();
			}
			else {
				switch (rand() %3)
				{
				case(0) :
					printf("행복한 대학생활을 즐기는 중");
					printf("...\n\n"); getchar();
					printf("system:\n"); getchar();
					printf("<---------------->\n"); 
					printf("<운석이 떨어진다!>\n"); 
					printf("<---------------->\n"); getchar();
					printf("...사망\n\n"); getchar();
					return;
				case(1) :
					printf("행복한 대학생활을 즐기는 중");
					printf("...\n\n"); getchar();
					printf("system:\n"); getchar();
					printf("<---------------->\n");
					printf("<해일이 밀려온다!>\n");
					printf("<---------------->\n"); getchar();
					printf("...사망\n\n"); getchar();
					return;
				case(2) :
					printf("행복한 대학생활을 즐기는 중");
					printf("...\n\n"); getchar();
					printf("system:\n"); getchar();
					printf("<---------------->\n");
					printf("<지진이 일어났다!>\n");
					printf("<---------------->\n"); getchar();
					printf("...사망\n\n"); getchar();
					return;
				}
			}
		}
	} return;
} 
//엔딩 삽입
void main()
{
	setname();

	while (day != 144)
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
