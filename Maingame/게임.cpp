#include <stdio.h>
#include <stdlib.h> 
#include <time.h>

//int Power, Stamina, Intel, Luck, Dex, Wealth, Beauty; //ĳ���� ����
int Power, Intel, Luck, Dex, Wealth, Beauty = 0;
int Stamina = 100;
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
}//������ �ִ�ġ�� �ּ�ġ�� �����Ѵ�.

int Money_Limit() {
	if (Money <= 0) {
		Money = 0;
	}
	else
	{
		Money = Money;
	}
	return Money;
}//���� �ּҰ��� ����.

void sleep()
{
	system("cls");
	if (class_pro == 1)
	{
		
		printf("�ڴ���~\n");
		system("PAUSE");
		class_pro--;
		day++;
		Stamina += Stat_max / 2;
		Stat_Limit(Stamina);//���⿡ ���ڱ� ������ �Ͼ�� ��Ȳ
		return;
	}
	else
	{


		printf_s("���� ������ ���� �ʾҽ��ϴ�\n\n�׷��� ���� �ڰڽ��ϱ�?\n\n1. �ܴ�\n\n2. ���ܴ�\n");
		scanf_s("%d", &choise);
		switch (choise)
		{
		case(1):
			day++;
			Stamina += Stat_max / 2;
			Stat_Limit(Stamina);//������ �����ʰ� ���� ���� �� �Ͼ�� ��Ȳ
			return;
		case(2):
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
	case(1):
		system("cls");
		sleep();
		if (back == 1)
		{
			back = 0;
			goto home;
		}
		system("cls");
		return;
	case(2):
		system("cls");
		system("PAUSE");
		Stamina += 5;
		Stat_Limit(Stamina);//���⿡ ��Ա� ������ �Ͼ�� ��Ȳ
		goto home;
	case(9):
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
	  case(1):
		  printf_s("�Ű��� ����\n");
		  system("PAUSE");
		  goto cafe;
	  case(2):
		  printf_s("���絿�� ����\n");
		  system("PAUSE");
		  goto classroom;
	  case(3):
		  printf_s("���� 4ȣ���� ����\n");
		  system("PAUSE");
		  goto eng_univ;
	  case(4):
		  printf_s("�������� ����\n");
		  system("PAUSE");
		  goto lib;
	  case(5):
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
		  case(1):
			  goto club;
		  case(2):
			  goto food;
		  case(9):
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
			case(1):
				system("cls");
				if (Money > 2000)
				{
					printf_s("���ĸӱ�\n\n");
					Money -= 2000;
					Stamina += 10;
					Money_Limit();
					Stat_Limit(Stamina);//���ĸ����� ������ ��ȭ
					system("pause");
				}
				else
				{
					printf("���� �����մϴ�");
					system("pause");
				}
				goto food;
			case(2):
				system("cls");
				if (Money > 3000)
				{
					printf_s("Ư�ĸӱ�\n\n");
					Money -= 3000;
					Stamina += 15;
					Money_Limit();
					Stat_Limit(Stamina);//Ư�� ������ ������ ��ȭ
					system("pause");
				}
				else
				{
					printf("���� �����մϴ�");
					system("pause");

				}
				goto food;
			case(9):
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
				case(1):
					class_pro++;
					Stamina -= 5;
					Intel += 5;
					Stat_Limit(Stamina);
					Stat_Limit(Intel);//�̰��� ���� ������ �Ͼ�� ��Ȳ
				case(9):
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
	case(1):
		printf_s("�˹���\n");
		system("pause");
		system("cls");
		day++;
		Money += 6030;
		Stamina -= 15;
		Wealth += 1;
		Stat_Limit(Stamina);
		Stat_Limit(Wealth);//�˹� ���� ���� ��ȭ
		return;
	case(2):
		printf_s("���\n");
		system("pause");
		system("cls");
		day++;
		Stamina -= 5;
		Power, Dex += 5;
		Beauty += 1;
		Stat_Limit(Stamina);
		Stat_Limit(Power);
		Stat_Limit(Dex);
		Stat_Limit(Beauty);//����� ���� ��ȭ
		return;
	case(3):
		printf("��\n");
		system("pause");
		system("cls");
		day++;
		Stamina += Stat_max / 2;
		Stat_Limit(Stamina);
		return;
	}
}
//�ָ�
void vacation()
{
	printf("�����̿���");
	day++;
	system("pause");
}
//����
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
}
