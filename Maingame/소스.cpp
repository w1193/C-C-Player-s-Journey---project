#include <stdio.h>
#include <stdlib.h> 
#include <time.h>


//int Power, Stamina, Intel, Luck, Dex, Wealth, Beauty; //ĳ���� ����
int Power, Intel, Luck, Dex, Wealth, Beauty = 0;
int Stamina = 100;
int Money = 50000;//�ʱ� ���� ���Ȱ� ��
int Stat_min = 0;
int Stat_max = 1000;//������ �ִ�ġ�� �ּ�ġ

int choise;//����
int day = 0;//��¥
int class_pro;//���� �޾Ҵ��� Ȯ��
int test;//������ �ô��� Ȯ��
int back;

void stat()
{
	printf_s("1. �̸� : \n\n");
	printf("2. ���� \n\n");
	printf("��:%d, ü��:%d, ����:%d, ��: %d\n\n��ø:%d, wealth: %d, �ܸ�:%d, ��:%d\n\n", Power, Stamina, Intel, Luck, Dex, Wealth, Beauty, Money);
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
}//������ �ִ�ġ�� �ּ�ġ�� �����Ѵ�.

int Money_Limit() {
	if (Money <= 0) {
		Money = 0;
	}
	return Money;
}//���� �ּҰ��� ����.

void sleep()
{
	system("cls");
	if (day == 60 || day == 60 + 72 || day == 60 + 72 + 72 || day == 60 + 72 + 72 + 72)
	{
		if (test != 1)
		{
			printf("���� ������ ���� �ʾҽ��ϴ�");
			system("pause");
			back = 1;
			return;
		}
	}
	if (class_pro == 1)
	{

		printf("�ڴ���~\n");
		system("PAUSE");
		test = 0;
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
			Intel -= 45;
			Stat_Limit(Stamina);
			Stat_Limit(Intel);//������ �����ʰ� ���� ���� �� �Ͼ�� ��Ȳ
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
	printf_s("����� �Դϴ�               ��¥: %d ��\n\n", day);
	if (day == 60 || day == 60 + 72 || day == 60 + 72 + 72 || day == 60 + 72 + 72 + 72)
	{
		printf("������ ������ ���³��Դϴ� ����4ȣ�� ���Ƿ� ���ʽÿ�\n\n");
		if (Intel <= 500)
		{
			printf("��𼱰� �ڽŰ��� ����ģ��\n\n");
		}
	}
	printf_s("1. ���ڱ� \n\n2. ��Ա�\n\n3. ������ ������\n\n9. ���ݺ���\n\n");
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
		Stamina += 150;
		Stat_Limit(Stamina);
		printf("Stamina + 150 ���� ! !\n\n");
		system("PAUSE");//���⿡ ��Ա� ������ �Ͼ�� ��Ȳ
		goto home;
	case(3):
		system("PAUSE");
		goto school;
	case(9):
		system("cls");
		stat();//ĳ���� ��������
		system("PAUSE");
		goto home;
	}

	}
  school: {
	  system("cls");
	  printf_s("�б��Դϴ�\n\n");
	  printf_s("1. �Ű� ����\n\n2. ���絿 ����\n\n3. ����4ȣ�� ����\n\n4. ������ ����\n\n5. ����� ����\n\n9. ���ݺ���\n\n");
	  scanf_s("%d", &choise);
	  switch (choise)
	  {
	  case(1):
		  printf_s("\n�Ű��� ����\n\n");
		  system("PAUSE");
		  goto cafe;
	  case(2):
		  printf_s("\n���絿�� ����\n\n");
		  system("PAUSE");
		  goto classroom;
	  case(3):
		  printf_s("\n���� 4ȣ���� ����\n\n");
		  system("PAUSE");
		  goto eng_univ;
	  case(4):
		  printf_s("\n�������� ����\n\n");
		  system("PAUSE");
		  goto lib;
	  case(5):
		  printf_s("����縦 ����\n\n");
		  system("PAUSE");
		  goto home;
	  case(9):
		  system("cls");
		  stat();//ĳ���� ��������
		  system("PAUSE");
		  goto school;
	  }
}
	  cafe: {
		  system("cls");
		  printf_s("�Ű��Դϴ�\n\n");
		  printf("������ �Ͻðڽ��ϱ�?\n\n");
		  printf_s("1. ���Ƹ��� ����\n\n2. �Ĵ� ����\n\n3. ������ ������\n\n9. ���ݺ���\n\n");
		  scanf_s("%d", &choise);
		  switch (choise)
		  {
		  case(1):
			  goto club;
		  case(2):
			  goto food;
		  case(3):
			  goto school;
		  case(9):
			  system("cls");
			  stat();//ĳ���� ��������
			  system("PAUSE");
			  goto cafe;
		  }
  }
		food: {
			system("cls");
			printf_s("�Ĵ��Դϴ�   ���� ���� �� : %d\n\n", Money);
			printf_s("�̰��� �Ĵ��Դϴ�\n\n1. ����(2000��)\n\n2. Ư��(3000��)\n\n3. �Ű����� ���ư���\n\n9. ���ݺ���\n\n");
			scanf_s("%d", &choise);
			switch (choise)
			{
			case(1):
				system("cls");
				if (Money > 2000)
				{
					printf_s("���� �ӱ�\n\n");
					Money -= 2000;
					Stamina += 300;
					Money_Limit();
					Stat_Limit(Stamina);//���ĸ����� ������ ��ȭ
					system("pause");
				}
				else
				{
					printf("���� �����մϴ�.\n\n");
					system("pause");
				}
				goto food;
			case(2):
				system("cls");
				if (Money > 3000)
				{
					printf_s("Ư�ĸӱ�\n\n");
					Money -= 3000;
					Stamina += 500;
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
			case(3):
				goto cafe;
			case(9):
				system("cls");
				stat();//ĳ���� ��������
				system("PAUSE");
				goto food;
			}
	  }
		  club: {
			  system("cls");
			  printf_s("���Ƹ����Դϴ�\n\n");  getchar();
			  printf_s("�̰����� ���� ������ ����...\n");  getchar();
			  printf_s("�˰�ͳ�?\n");  getchar();
			  printf_s("�׷� 500��.\n");  getchar();
			  printf_s("��� ����??\n\n1. 500���� �ش�\n\n2. �����ʴ´�\n");
			  scanf_s("%d", &choise);
			  switch (choise)
			  {
			  case(1):
				  Money -= 500;
				  Money_Limit();
				  system("cls"); getchar();
				  printf("..........\n"); getchar();
				  printf("��? �Ӿ���? �װ� ��?r������\n"); getchar();
				  printf("500���� �Ҿ����ϴ�.\n"); getchar();
				  system("PAUSE");
				  goto cafe;
			  case(2):
				  system("cls");
				  printf("���� ����...\n\n");
			  }
			  system("PAUSE");
			  goto cafe;
		}
			classroom: {
				system("cls");
				printf_s("���絿 �Դϴ�\n\n");
				printf("������ �Ͻðڽ��ϱ�?\n\n");
				printf_s("1. ���� ���(ü�� 200����, ���� 45 ����\n\n2. ������ ������\n\n9. ���ݺ���\n\n");
				scanf_s("%d", &choise);
				switch (choise)
				{
				case(1):
					system("cls");
					printf("������ ��� ��...\n\n");  system("PAUSE");
					class_pro++;
					Stamina -= 200;
					Intel += 45;
					Stat_Limit(Stamina);
					Stat_Limit(Intel);//�̰��� ���� ������ �Ͼ�� ��Ȳ
					system("cls");
					printf(".\n.\n������ �������ϴ�.\n\n");  system("PAUSE");
				case(2):
					goto school;
				case(9):
					system("cls");
					stat();//ĳ���� ��������
					system("PAUSE");
					goto classroom;
				}
		  }
					   //���뿡�� �ַ� ����
				   eng_univ: {
					   system("cls");
					   printf_s("����4ȣ�� �Դϴ�\n\n");
					   printf("���� ���ðڽ��ϱ�?\n\n");
					   printf("1. ����\n\n2. ����\n\n3. ���ư���.\n\n9. ���Ⱥ���\n\n");
					   scanf_s("%d", &choise);
					   switch (choise)
					   {
					   case(1):
						   goto eng_class;
					   case(2):
						   goto eng_room;
					   case(3):
						   goto school;
					   case(9):
						   system("cls");
						   stat();//ĳ���� ��������
						   system("PAUSE");
						   goto eng_univ;
					   }
				   eng_class: {
					   system("cls");
					   if (day == 60 || day == 60 + 72 || day == 60 + 72 + 72 || day == 60 + 72 + 72 + 72)
					   {
						   printf("������ ���ϴ�\n\n");
						   //���躸�ºκ� ���� ����
						   test++;
						   class_pro++;
						   system("pause");
					   }
					   printf_s("���� �Դϴ�\n\n");
					   system("PAUSE");
					   goto eng_univ;
					   }
						  eng_room: {
							  system("cls"); getchar();
							  printf("�����Դϴ�.\n"); getchar();
							  printf("�߻��� ���¼ҽ��� ��Ÿ���� ! !\n"); getchar();
							  printf("���ƾƾƾƾƾƾƾƾƾƾƾ�\n\n");
							  system("PAUSE");
							  class_pro++;
							  goto eng_univ;
				   }
								lib: {
									system("cls");
									printf_s("�߾� ������ �Դϴ�\n\n");
						  }
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
		Stamina -= 150;
		Wealth += 50;
		Stat_Limit(Stamina);
		Stat_Limit(Wealth);//�˹� ���� ���� ��ȭ
		return;
	case(2):
		printf_s("���\n");
		system("pause");
		system("cls");
		day++;
		Stamina -= 300;
		Power, Dex += 80;
		Beauty += 50;
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
	printf("�����̿���\n");
	day++;
	system("pause");
}
//����
void endings() {
	printf("�б��� �����Ͽ���\n\n");
}
//���� ����
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
