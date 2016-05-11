#include <stdio.h>
#include <stdlib.h> 
#include <time.h>

int choise;

void main()
{
home:
	system("cls");
	printf_s("집 입니다\n\n");
	printf("1. 잠자기 \n\n2. 밥먹기\n\n9. 이동하기\n\n");
	scanf_s("%d", &choise);
	switch (choise)
	{
	case(1) :
		system("cls");
		system("PAUSE");
		goto home;
	case(2) :
		system("cls");
		system("PAUSE");
		goto home;
	case(9) :
		system("cls");
		printf("어디로 이동하시겟습니까?\n\n");
		printf("1. 학교\n\n2. 돌아가기\n ");
		scanf_s("%d", &choise);
		switch (choise)
		{
		case(1) :
			printf("학교로 가는중... \n");
			system("PAUSE");
			goto school;
		case(2) :
			goto home;
		}
	}

school:
	system("cls");
	printf_s("학교입니다\n\n");
	printf("1. 동방가기\n\n2. 교양동가기\n\n3. 공대4호관가기\n\n4. 도서관 가기\n\n5. 아라홀\n\n9. 이동하기");
	scanf_s("%d", &choise);
	switch (choise)
	{
	case(1) :
		printf(" 동방을 간다");
		system("PAUSE");
		goto club;
	case(2) :
		printf("교양동을 간다");
		system("PAUSE");
		goto classroom;
	}

club:
	printf_s("동아리방입니다\n\n");
	printf("1. 기타치기\n\n2. 노가리 까기\n\n3. 자기\n\n4. 콜라먹기\n\n8. 학교하기\n\n");
	scanf_s("%d", &choise);
	switch (choise)
	{
	case(1) :
		goto club;
	case(2) :
		goto club;
	case(3) :
		goto club;
	case(4) :
		goto club;
	case(8) :
		goto school;
	}
classroom:
	printf_s("교실입니다\n\n");
}