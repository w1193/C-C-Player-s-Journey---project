#include <stdio.h>
#include <stdlib.h> 
#include <time.h>


//int Power, Stamina, Intel, Luck, Beauty; //ĳ���� ����
int Power, Intel, Luck, Beauty = 0;
int Stamina = 1000;
int Money = 50000;//�ʱ� ���� ���Ȱ� ��
int Stat_min = 0;
int Stat_max = 1000;//������ �ִ�ġ�� �ּ�
char name[100][100] = { "ö��(���� : Terran)","����(���� : Protos)","�ٵ���(���� : Zerg)" };
int ncode;

int choise;//����
int day = 0;//��¥
int class_pro;//���� �޾Ҵ��� Ȯ��
int test;//������ �ô��� Ȯ��
int D_meal;//����翡�� ���� ���� Ƚ��
int back;


void setname() {

	printf("�÷��� �ϰ� ���� ĳ������ ��ȣ�� �Է��ϼ���.\n\n");
	printf("1. ö��(���� : Terran)\n\n"); 
	printf("2. ����(���� : Protos)\n\n");
	printf("3. �ٵ���(���� : Zerg)\n\n"); 
	scanf_s("%d",&choise);
	switch(choise) {
	case(1):
		printf("Player 'ö��' �� �����ϼ̽��ϴ�.\n\n"); getchar();
		ncode = 0;
		printf("<<���� �нú�>>\n"); getchar();
		Power += 200;
		printf("���� 200�����մϴ�.\n"); getchar();
		return;
	case(2):
		printf("Player '����' �� �����ϼ̽��ϴ�.\n"); getchar();
		ncode =1;
		printf("<<���� �нú�>>\n"); getchar();
		Intel += 200;
		printf("������ 200�����մϴ�.\n"); getchar();
		return;
	case(3):
		printf("Player '�ٵ���' �� �����ϼ̽��ϴ�.\n"); getchar();
		ncode=2;
		printf("<<���� �нú�>>\n"); getchar();
		Beauty += 200;
		printf("�ŷ��� 200�����մϴ�.\n"); getchar();
		return;
	}
	system("cls");
}

void stat()
{
	printf("1. �̸� : %s\n\n", name[ncode]);
	printf("2. ���� \n\n");
	printf("��:%d, ü��:%d, ����:%d, ��: %d\n�ܸ�:%d, ��:%d\n\n", Power, Stamina, Intel, Luck, Beauty, Money);
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

void talk() {
	srand((unsigned)time(NULL));
	switch (rand() % 3)
	{
	case(0) :
		printf_s("�̰����� ���� ������ ����...\n");  getchar();
		printf_s("�˰�ͳ�?\n");  getchar();
		printf_s("�׷� 500��.\n");  getchar();
		printf_s("��� ����??\n\n1. 500���� �ش�\n\n2. �����ʴ´�\n");
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
			printf("��? �Ӿ���? �װ� �ϳĤ�����\n"); getchar();
			printf("500���� �Ҿ����ϴ�.���� 50 ���� �Ͽ����ϴ�.\n"); getchar();
			break;
		case(2) :
			system("cls");
			printf("���� ����...\n\n");
			break;
		}
		break;
	case(1) :
		printf_s("���� ���������� �ִ�.\n");  getchar();
		printf_s("������ ����??\n");  getchar();
		printf_s("1. ��Ÿ�� ģ��(ü�� - 50, �ŷ� + 50)\n\n2. ���� ���Ŵ�(ü�� - 300, ����- 300, �� - 10000, �ŷ� ���� ���� �� �߰� ����)\n\n");
		scanf_s("%d", &choise);
		switch (choise)
		{
		case 1:
			printf("�ձ�յεεεεε�\n"); getchar();
			printf("�������� ���� �����ʳ�...\n"); 
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
				printf("�ַ������� ������ ���, ���� ������ �濪��� ���Ͽ� �ŷ��� %d��ŭ �����Ͽ����ϴ�.\n", Beauty_tmp);
			case(1):
				Beauty_tmp = rand() % 501;
				Beauty += Beauty_tmp;
				Stat_Limit(Beauty);
				Luck += 300;
				Stat_Limit(Luck);
				printf("������ ������ �ʰ� �������� ������ ���, �ŷ��� %d��ŭ �����Ͽ����ϴ�.(�߰� ���� : �� 300 ����)\n", Beauty_tmp);
			}
			break;
		}
		break;
	case(2) :
		printf_s("�ƹ��� ����.\n"); getchar();
		printf_s("..."); getchar();
		printf_s("..\n"); getchar();
		printf_s("�Ф�\n"); getchar();
		break;
	}
}//���Ƹ��� ���� �� ��ȭ

void lib_talk() {
	printf_s("�߾� ������ �Դϴ�\n\n");
	srand((unsigned)time(NULL));
	switch (rand() % 3)
	{
	case(0) :
		printf_s("å�� ������ �Դ�.\n\n");  getchar();
		printf_s("��...���� ���� å���� �ֳ�.\n");  getchar();
		printf_s("�ƴ�, ��...�̰���!!!\n");  getchar();
		printf_s("1000���� ȹ���ߴ�!!(�� + 300)\n"); getchar();
		Money += 10000;
		Luck += 300;
		Stat_Limit(Luck);
		printf("����!!!!!!"); getchar();
		break;
	case(1) :
		printf_s("���� �߾ӵ������� �޹��Դϴ�.\n");  getchar();
		printf_s("..");  getchar();
		printf_s("..\n"); getchar();
		printf_s("�Ф�\n");  getchar();
		Luck -= 100;
		Stat_Limit(Luck);
		printf_s("�� -100 ����\n"); getchar();
		break;
	case(2) :
		printf_s("������ ����??\n"); getchar();
		printf_s("1. å�� �д´�.(���� + 100)\n\n2. ȥ�ڼ� ���θ� �Ѵ�.(+50)\n");
		scanf_s("%d", &choise);
		switch (choise) {
		case 1:
			system("cls");
			printf_s("���̴�~~~~~\n\n");  getchar();
			printf_s("�� ��~~\n");  getchar();
			printf_s("���õ�~~~~\n"); getchar();
			printf_s("�� ��~~~\n");  getchar();
			printf_s("������~~~~~\n");  getchar();
			printf_s("����~~ ��~~��~~\n\n");  getchar();
			printf_s("���λ�!!!!!!\n\n"); getchar();
			Intel += 100;	Stat_Limit(Intel);
			Luck += 50; Stat_Limit(Luck);
			printf_s("��վ���. �д� ������ �ִ� å�̾���."); getchar();
			break;
		case 2:
			system("cls");
			printf_s("���θ� �ϴ� ��...\n");  getchar();
			printf_s("�Ӹ��� ���Ŀ´٤Ф�\n");  getchar();
			printf_s("���� ���δ� ���� �طο�.(ü�� - 100)\n"); getchar();
			Intel += 50; Stamina -= 100;
			break;
		}
		break;
	}
}//�߾ӵ����� ���� �� ��ȭ

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
	if (class_pro >= 1)
	{

		printf("�ڴ���~\n");
		system("PAUSE");
		test = 0;
		class_pro = 0;
		D_meal = 0;
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
		case(1) :
			day++;
			Stamina += Stat_max / 2;
			Intel -= 45;
			Stat_Limit(Stamina);
			Stat_Limit(Intel);//������ �����ʰ� ���� ���� �� �Ͼ�� ��Ȳ
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
	printf_s("����� �Դϴ�               ��¥: %d ��\n\n", day);
	if (day == 60 || day == 60 + 72 || day == 60 + 72 + 72 || day == 60 + 72 + 72 + 72)
	{
		printf("������ ������ ���� ���Դϴ�. ����4ȣ�� ���Ƿ� ������.\n\n");
		if (Intel <= 500)
		{
			printf("��𼱰� �ڽŰ��� �ڱ�ģ��!!\n\n");
		}
	}
	printf_s("1. ���ڱ� \n\n2. ��Ա�\n\n3. ������ ������\n\n4. ���ݺ���\n\n");
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
			printf("��θ���...\n"); getchar();
			printf("������? ����?\n"); getchar();
			printf("1. �Դ´�\n\n2. �����ʴ´�\n"); 
			scanf_s("%d", &choise);
			switch(choise) {
				case 1:
					system("cls"); getchar();
					printf("�������������������������������������\n"); getchar();
					printf("������ ���� �Ծ� ��ȿ���� ��Ÿ�����ϴ�.(ü�� - 100, ���� - 150, �ŷ� -50)\n"); getchar();
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
					printf("�׷�, ������ ���� �����ʾ�.\n"); getchar();
					system("pause");
					break;
			}
		}//ü���� full�� ���¿��� ���� �Ծ��� �� �Ͼ�� ��Ȳ
		else
		{
			if (D_meal >= 1) {
				printf("���� ���� �� �ִ� Ƚ���� �ʰ��Ͽ����ϴ�.\n");
			}
			else {
				Stamina += 150;
				Stat_Limit(Stamina);
				printf("ü�� + 150 ���� ! !\n\n");
				D_meal++;
			}
			system("PAUSE");//��Ա� ������ �Ͼ�� ��Ȳ
		}
		goto home;
	case(3) :
		system("PAUSE");
		goto school;
	case(4) :
		system("cls");
		stat();//ĳ���� ��������
		system("PAUSE");
		goto home;
	}

}
  school: {
	  system("cls");
	  printf_s("�б��Դϴ�\n\n");
	  printf_s("1. �Ű� ����\n\n2. ���絿 ����\n\n3. ����4ȣ�� ����\n\n4. ������ ����\n\n5. ����� ����\n\n6. ���ݺ���\n\n");
	  scanf_s("%d", &choise);
	  switch (choise)
	  {
	  case(1) :
		  printf_s("\n�Ű��� ����\n\n");
		  system("PAUSE");
		  goto cafe;
	  case(2) :
		  printf_s("\n���絿�� ����\n\n");
		  system("PAUSE");
		  goto classroom;
	  case(3) :
		  printf_s("\n���� 4ȣ���� ����\n\n");
		  system("PAUSE");
		  goto eng_univ;
	  case(4) :
		  printf_s("\n�������� ����\n\n");
		  system("PAUSE");
		  goto lib;
	  case(5) :
		  printf_s("����縦 ����\n\n");
		  system("PAUSE");
		  goto home;
	  case(6) :
		  system("cls");
		  stat();//ĳ���� ��������
		  system("PAUSE");
		  goto school;
	  }
  }//�б�
	  cafe: {
		  system("cls");
		  printf_s("�Ű��Դϴ�\n\n");
		  printf("������ �Ͻðڽ��ϱ�?\n\n");
		  printf_s("1. ���Ƹ��� ����\n\n2. �Ĵ� ����\n\n3. ������ ������\n\n4. ���ݺ���\n\n");
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
			  stat();//ĳ���� ��������
			  system("PAUSE");
			  goto cafe;
		  }
	  }//�Ű�
		food: {
			system("cls");
			printf_s("�Ĵ��Դϴ�   ���� ���� �� : %d\n\n", Money);
			printf_s("�̰��� �Ĵ��Դϴ�\n\n1. ����(2000��)\n\n2. Ư��(3000��)\n\n3. �Ű����� ���ư���\n\n4. ���ݺ���\n\n");
			scanf_s("%d", &choise);
			switch (choise)
			{
			case(1) :
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
			case(2) :
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
			case(3) :
				goto cafe;
			case(4) :
				system("cls");
				stat();//ĳ���� ��������
				system("PAUSE");
				goto food;
			}
		}//�л��Ĵ�
		  club: {
			  system("cls");
			  printf_s("���Ƹ����Դϴ�\n\n");
			  system("cls");
			  talk();
			  system("PAUSE");
			  goto cafe;
		  }//���Ƹ���
			classroom: {
				system("cls");
				printf_s("���絿 �Դϴ�\n\n");
				printf("������ �Ͻðڽ��ϱ�?\n\n");
				printf_s("1. ���� ���(ü�� 200����, ���� 45 ����)\n\n2. ������ ������\n\n3. ���ݺ���\n\n");
				scanf_s("%d", &choise);
				switch (choise)
				{
				case(1) :
					system("cls");
					printf("������ ��� ��...\n\n");  system("PAUSE");
					class_pro++;
					Stamina -= 200;
					Intel += 45;
					Stat_Limit(Stamina);
					Stat_Limit(Intel);//�̰��� ���� ������ �Ͼ�� ��Ȳ
					system("cls");
					printf(".\n.\n������ �������ϴ�.\n\n");  system("PAUSE");
				case(2) :
					goto school;
				case(3) :
					system("cls");
					stat();//ĳ���� ��������
					system("PAUSE");
					goto classroom;
				}
			}//���絿
					   //���뿡�� �ַ� ����
				   eng_univ: {
					   system("cls");
					   printf_s("����4ȣ�� �Դϴ�\n\n");
					   printf("���� ���ðڽ��ϱ�?\n\n");
					   printf("1. ����\n\n2. ����\n\n3. ���ư���.\n\n4. ���Ⱥ���\n\n");
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
				   }//���� 4ȣ�� ���ǽ�
						  eng_room: {
							  system("cls"); getchar();
							  printf("�����Դϴ�.\n"); getchar();
							  printf("�߻��� ���¼ҽ��� ��Ÿ���� ! !\n"); getchar();
							  printf("���ƾƾƾƾƾƾƾƾƾƾƾ�\n\n");
							  system("PAUSE");
							  class_pro++;
							  goto eng_univ;
						  }//����
				   }//���� 4ȣ��
						 lib: {
							 system("cls");
							 lib_talk();
							 system("pause");
							 goto school;
						 }//�߾ӵ�����
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
		//���� ����
		Money += //���ھ�;
		Stamina -= 150;
		Stat_Limit(Stamina);//�˹� ���� ���� ��ȭ
		return;
	case(2) :
		printf_s("���\n");
		system("pause");
		system("cls");
		day++;
		//���� ����
		Stamina -= 300;
		Power+= 80;
		Beauty += 50;
		Stat_Limit(Stamina);
		Stat_Limit(Power);
		Stat_Limit(Beauty);//����� ���� ��ȭ
		return;
	case(3) :
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
	system("cls");
	printf("�����̿���\n");
	day++;
	system("pause");
}
//����
void endings() {
	int sum = Power + Intel + Beauty + Luck;
	if(sum <= 1200){
		printf("�б��� �����Ͽ���\n"); getchar();
		printf("�������� ������ �б��� ����.\n"); getchar();
		printf("�̷�....!!\n"); getchar();
		printf("..."); getchar();
		printf("...\n"); getchar();
		printf("������ �ٰ����� ���� ��ó ���� ���ϰ� �׸�....\n\n"); getchar();
		printf("<______________>\n");
		printf("<������!!!!!!!!>\n"); 
		printf("<-------------->\n"); getchar();
		printf("...������ ���� �ٶ��ϴ�.\n"); getchar();
	}
	else
	{
		if (sum >= 3200)
		{
			printf("�б��� �����Ͽ���\n\n"); getchar();
			printf("������ �����ϱ� ���� ����� ��� ���Ͽ� �߼ұ���� �����Ͽ���.\n\n"); getchar();
			printf("������ ���������� �� ����� �Ǿ���.\n\n"); getchar();
			printf("���������� ġŲ���� ������.\n\n"); getchar();
			printf("�׷��� ���� ġŲ���� �� �����鿡�� �з� ġŲ���� ���ߴ�.\n\n"); getchar();
			printf("�� �λ��� ���߾�....\n\n\n"); getchar();
			printf("------THE (Happy)END-------\n\n"); getchar();
		}
		else
		{
			if (2000 <= sum <= 3200) {
				printf("������ �ھ��̴�.\n"); getchar();
				printf("������ �и� ������ �ؾ�������\n"); getchar();
				printf("."); getchar();
				printf("."); getchar();
				printf("..��!!\n"); getchar();
				printf("<_________________________>\n");
				printf("<������ ������ ���� ������>\n"); 
				printf("<------------------------->\n"); getchar();
				printf("...������ ���� �ٶ��ϴ�.\n"); getchar();
			}
			else {
				switch (rand() %3)
				{
				case(0) :
					printf("�ູ�� ���л�Ȱ�� ���� ��");
					printf("...\n\n"); getchar();
					printf("system:\n"); getchar();
					printf("<---------------->\n"); 
					printf("<��� ��������!>\n"); 
					printf("<---------------->\n"); getchar();
					printf("...���\n\n"); getchar();
					return;
				case(1) :
					printf("�ູ�� ���л�Ȱ�� ���� ��");
					printf("...\n\n"); getchar();
					printf("system:\n"); getchar();
					printf("<---------------->\n");
					printf("<������ �з��´�!>\n");
					printf("<---------------->\n"); getchar();
					printf("...���\n\n"); getchar();
					return;
				case(2) :
					printf("�ູ�� ���л�Ȱ�� ���� ��");
					printf("...\n\n"); getchar();
					printf("system:\n"); getchar();
					printf("<---------------->\n");
					printf("<������ �Ͼ��!>\n");
					printf("<---------------->\n"); getchar();
					printf("...���\n\n"); getchar();
					return;
				}
			}
		}
	} return;
} 
//���� ����
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
