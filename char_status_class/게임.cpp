#include <stdio.h>
#include <stdlib.h> 
#include <time.h>

int choise;//����
int day = 0;//��¥
int class_pro;//���� �޾Ҵ��� Ȯ��

void week()
{
home:
	system("cls");
	printf_s("����� �Դϴ�                 %d\n\n", day);
	printf_s("1. ���ڱ� \n\n2. ��Ա�\n\n9. ������ ������\n\n");
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
			//���⿡ ���ڱ� ������ �Ͼ�� ��Ȳ
			return;
		}
		else
		{
			printf_s("���� ������ ���� �ʾҽ��ϴ�\n\n�׷��� ���� �ڰٽ��ϱ�?\n\n1. �ܴ�\n\n2. ���ܴ�\n");
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
		//���⿡ ��Ա� ������ �Ͼ�� ��Ȳ
		goto home;
	case(9):
		system("PAUSE");
		goto school;
	}

school:
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

cafe:
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

food:
	system("cls");
	printf_s("�Ĵ��Դϴ�\n\n");
	printf_s("�̰��� �Ĵ��Դϴ�\n\n1. ����\n\n2. Ư��\n\n9. �Ű����� ���ư���\n\n");
	scanf_s("%d", &choise);
	switch (choise)
	{
	case(1):
		system("cls");
		printf_s("���ĸӱ�");
		//���ĸ����� ������ ��ȭ
		system("pause");
		goto food;
	case(2):
		system("cls");
		printf_s("Ư�ĸӱ�");
		//Ư�� ������ ������ ��ȭ
		system("pause");
		goto food;
	case(9):
		goto cafe;
	}
club:
	system("cls");
	printf_s("���Ƹ����Դϴ�\n\n");


classroom:
	printf_s("���絿 �Դϴ�\n\n");
	printf_s("1. ���� ���\n\n9. ������ ������\n\n");
	scanf_s("%d", &choise);
	switch (choise)
	{
	case(1):
		//�̰��� ���� ������ �Ͼ�� ��Ȳ
	case(9):
		goto school;
	}

eng_univ:
	printf_s("����4ȣ�� �Դϴ�\n\n");
	goto eng_class;

eng_class:
	printf_s("���� �Դϴ�\n\n");
	goto eng_room;

eng_room:
	printf_s("���� �Դϴ�\n\n");
	class_pro++;
	goto home;

lib:
	printf_s("�߾� ������ �Դϴ�\n\n");

}
void weekend()
{
	printf_s("�ָ��Դϴ�\n");
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