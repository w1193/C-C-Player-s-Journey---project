#include <stdio.h>
#include <stdlib.h> 
#include <time.h>

//int Power, Stamina, Intel, Luck, Dex, Wealth, Beauty; //ĳ���� ����
int Power, Stamina, Intel, Luck, Dex, Wealth, Beauty = 0;
int Money = 50000;//�ʱ� ���� ���Ȱ� ��
int Stat_min = 0;
int Stat_max = 100;//������ �ִ�ġ�� �ּ�ġ

int choise;//����
int day = 0;//��¥
int class_pro;//���� �޾Ҵ��� Ȯ��
int back;

void stat()
{
	printf("��:%d, ü��:%d, ����:%d, ��: %d\n\n��ø:%d, wealth: %d, �ܸ�:%d, ��:%d\n\n", Power, Stamina, Intel, Luck, Dex, Wealth, Beauty, Money);
	return;
}

int Stat_Limit(int stat) {
	if (stat <= Stat_min) {
		stat = 0;
	}
	if (stat >= Stat_max) {
		stat = 100;
	}
	else
	{
		stat = stat;
	}
	return stat;
}

void sleep()
{
	if (class_pro == 1)
	{
		system("PAUSE");
		class_pro--;
		day++;
		Stamina = Stat_max / 2;
		Stat_Limit(Power);//���⿡ ���ڱ� ������ �Ͼ�� ��Ȳ
		return;
	}
	else
	{
		printf_s("���� ������ ���� �ʾҽ��ϴ�\n\n�׷��� ���� �ڰڽ��ϱ�?\n\n1. �ܴ�\n\n2. ���ܴ�\n");
		scanf_s("%d", &choise);
		switch (choise)
		{
		case(1) :
			day++;
			return;
		case(2) :
			back = 1;
			return;
		}
	}
}
//���ڴ� ��Ȳ
void week()
{
home: {
	system("cls");
	printf_s("����� �Դϴ�                 %d\n\n", day);
	stat();
	printf_s("1. ���ڱ� \n\n2. ��Ա�\n\n9. ������ ������\n\n");
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
		Stamina += 5;//���⿡ ��Ա� ������ �Ͼ�� ��Ȳ
		goto home;
	case(9) :
		system("PAUSE");
		goto school;
	}

}
school: {
	  system("cls");
	  printf_s("�б��Դϴ�\n\n");
	  printf_s("1. �Ű� ����\n\n2. ���絿 ����\n\n3. ����4ȣ�� ����\n\n4. ������ ����\n\n5. ����� ����\n\n");
	  scanf_s("%d", &choise);
	  switch (choise)
	  {
	  case(1) :
		  printf_s("�Ű��� ����\n");
		  system("PAUSE");
		  goto cafe;
	  case(2) :
		  printf_s("���絿�� ����\n");
		  system("PAUSE");
		  goto classroom;
	  case(3) :
		  printf_s("���� 4ȣ���� ����\n");
		  system("PAUSE");
		  goto eng_univ;
	  case(4) :
		  printf_s("�������� ����\n");
		  system("PAUSE");
		  goto lib;
	  case(5) :
		  printf_s("����縦 ����\n");
		  system("PAUSE");
		  goto home;
	  }
}
cafe: {
		  system("cls");
		  printf_s("�Ű��Դϴ�\n\n");
		  printf_s("1. ���Ƹ��� ����\n\n2. �Ĵ� ����\n\n9. ������ ������\n\n");
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
			printf_s("�Ĵ��Դϴ�\n\n");
			printf_s("�̰��� �Ĵ��Դϴ�\n\n1. ����\n\n2. Ư��\n\n9. �Ű����� ���ư���\n\n");
			scanf_s("%d", &choise);
			switch (choise)
			{
			case(1) :
				system("cls");
				printf_s("���ĸӱ�");
				Money -= 2000;
				Stamina += 10;//���ĸ����� ������ ��ȭ
				system("pause");
				goto food;
			case(2) :
				system("cls");
				printf_s("Ư�ĸӱ�");
				Money -= 3000;
				Stamina += 15;//Ư�� ������ ������ ��ȭ
				system("pause");
				goto food;
			case(9) :
				goto cafe;
			}
		}
club: {
	  system("cls");
			  printf_s("���Ƹ����Դϴ�\n\n");
}
classroom: {
				printf_s("���絿 �Դϴ�\n\n");
				printf_s("1. ���� ���\n\n9. ������ ������\n\n");
				scanf_s("%d", &choise);
				switch (choise)
				{
				case(1) :
					Stamina -= 5;
					Intel += 5;//�̰��� ���� ������ �Ͼ�� ��Ȳ
				case(9) :
					goto school;
				}
}
		   //���뿡�� �ַ� ����
eng_univ: {
					   printf_s("����4ȣ�� �Դϴ�\n\n");
					   goto eng_class;
				   }
						 eng_class: {
							 printf_s("���� �Դϴ�\n\n");
							 goto eng_room;
						 }
								eng_room: {
									printf_s("���� �Դϴ�\n\n");
									class_pro++;
									goto home;
								}
									  lib: {
										  printf_s("�߾� ������ �Դϴ�\n\n");
									  }
}
//����
void weekend()
{
	printf_s("�ָ��Դϴ�\n������ �Ͻðٽ��ϱ�?\n\n1. �˹�\n\n2. �\n\n3. ���ڱ�\n\n");
	scanf_s("%d", &choise);
	switch (choise)
	{
	case(1) :
		printf_s("�˹���\n");
		system("pause");
		system("cls");
		day++;
		return;
	case(2) :
		printf_s("���\n");
		system("pause");
		system("cls");
		day++;
		return;
	case(3) :
		printf("��\n");
		system("pause");
		system("cls");
		day++;
		return;
	}
}
//�ָ�
void vacation()
{}
//����
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
