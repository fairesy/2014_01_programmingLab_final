#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "member.h"
#pragma warning(disable:4996)

#define MAX_SIZE 50

static int curMemberNum; //���� ����� �� ��� ��
static int nowMemberNum;
static student member[MAX_SIZE];

int main(void){
	readMemberData(); //���α׷��� ����Ǹ� ������ �ε��Ѵ�
	showMenu(); //�޴�ȭ���� �����ش�
	return 0;
}
/*
showMenu : ���θ޴�ȭ���� �����ش�.
*/
void showMenu(void)
{
	system("cls");
	char choice;
	int i;

	char* menu[] = { "1  ȸ �� �� ��", "2  ȸ �� �� ��", "3  ȸ �� �� ��",
		"4  ȸ �� �� ��", "5  ȸ �� �� ��", "6  �� �� �� ��", "7  �� �� �� ��" };

	gotoxy(17, 1); printf("����������������������������������������������\n");
	gotoxy(17, 2); printf("��                                          ��\n");
	gotoxy(17, 3); printf("��         ȸ �� �� �� �� �� �� ��          ��\n");
	gotoxy(17, 4); printf("��                                          ��\n");
	gotoxy(17, 5); printf("����������������������������������������������\n");


	for (i = 0; i < 7; i++)
	{
		gotoxy(32, 8 + i); puts(menu[i]); //�޴���� ���
	}

	gotoxy(17, 16); printf("���ϴ� �۾��� �������ּ���  ");
	choice = getche();
	Beep(rand() % 200 + 300, 80);
	switch (choice)
	{
	case '1':
		viewAllMember();
		break;
	case '2':
		addNewMember();
		break;
	case '3':
		system("cls");
		deleteMember();
		break;
	case '4':
		system("cls");
		editMember();
		break;
	case '5':
		system("cls");
		searchMember();
		break;
	case '6':
		saveData();
		break;
	case '7':
		exitProgram();
		break;
	default:
		showMenu();
		break;
	}
}

/*
returnToMenu : ���θ޴��� ���ư���
*/
void returnToMenu(void)
{
	char user_choice;

	printf("	���θ޴��� ���ư��÷��� 0�� �����ּ��� : ");
	user_choice = getche();
	fflush(stdin);
			
	while (user_choice != '0')
	{
		printf("\n\n	�ùٸ� ���� �Է����ּ���!\n");
		fflush(stdin);
		returnToMenu();
	}
	showMenu();
}

/*
readMemberData : ������ �ҷ��´�. 
*/
void readMemberData(void)
{
	curMemberNum = 0;
	nowMemberNum = 0; 
	char memberInfo[120];//���Ͽ��� �о���� �� ���� �����ص� ����
	char* token;
	int i = 0;

	FILE* fp;
	fp = fopen("data.txt", "rt");//������ �б� ���� ����

	if (fp == NULL)
	{
		puts("file open error"); return -1;
	}

	fgets(memberInfo, sizeof(memberInfo), fp);//file�� ù���� �л������� �ƴ϶� �й�/�̸����� �з������̹Ƿ� ����ü�� ���� ����

	while (!feof(fp) && fgets(memberInfo, sizeof(memberInfo), fp))//���Ͽ� �о���� ������ �ִ� ����
	{
		//strtok : ���� �������� �޾ƿ� ���ڿ��� �ڸ���.
		token = strtok(memberInfo, "	");
		member[i].userid = atoi(token); //char���� int������ �ٲ㼭(atoi) member[i].userid�� �ִ´�
		token = strtok(NULL, "	");
		strcpy(member[i].name, token);
		token = strtok(NULL, "	");
		strcpy(member[i].address, token);
		token = strtok(NULL, "	");
		token[strlen(token) - 1] = '\0'; 
		strcpy(member[i].phone, token);
	
		if (nowMemberNum < member[i].userid)
			nowMemberNum = member[i].userid;

		i++;
		
	}
	curMemberNum = i;
	nowMemberNum++;
	fclose(fp);
}

/*
memoryExtension : �޸𸮰� �� ���� �޸𸮸� 2��� Ȯ���Ѵ�. 
*/
void memoryExtension(void)
{
#define MAX_SIZE = MAX_SIZE * 2;
}

/*
1. ȸ���������� : viewAllMember
data.txt ������ �ҷ��ͼ� �� ���� tap�� �������� �߶� ����ü�� ����ִ´�.
����ü ������ ����Ѵ�.
*/

void viewAllMember(void)
{
	system("cls");
	int i; 

	gotoxy(5, 1); printf("������������������������������������������������������������������\n");
	gotoxy(5, 2); printf("��  �й�  ��  �̸�  ��  �ּ�                    ��  ��ȭ��ȣ    ��\n");
	gotoxy(5, 3); printf("������������������������������������������������������������������\n");

	for (i = 0; i<curMemberNum ; i++){
		gotoxy(5, 4 + i); printf("��%6d  ��%7s ��%-25s ��%10s ��",
			member[i].userid, member[i].name, member[i].address, member[i].phone);
	}
	gotoxy(5, 4 + curMemberNum); printf("������������������������������������������������������������������\n");

	printf("\n");
	fflush(stdin); 
	returnToMenu();

}

/*
2. ȸ������ϱ� : addNewMember
*/
void addNewMember(void)
{
	int i;
	char buf[80];
	int chk;

	system("cls");

	gotoxy(18, 4); printf(" ��������������������������������������\n");
	gotoxy(18, 5); printf(" ��     ���ο� �л��� ����մϴ�     ��\n");
	gotoxy(18, 6); printf(" ��������������������������������������\n");

	// ���ο� �л������� �Է¹޴´�. �ԷµǴ� ���� �ƹ��͵� ������ �Է°��� ���������� �Է��� �䱸�Ѵ�.
	// ���۰���ŭ�� ���� �ȿ� ������ Ȯ��. ������ ���ۿ� ���� �� ���� ū ���� �Է��ϸ� �ٽ��Է¹޴´�.
	
	member[curMemberNum].userid = nowMemberNum++;
	printf("			��    �� : %d\n", member[curMemberNum].userid); //�й��� �ڵ�����
	fflush(stdin);

	printf("\n			��    �� : ");
	while (1)
	{
		fgets(buf, sizeof(buf), stdin);
		chk = 0; //�����Է»������� üũ���ֱ� ���� ���� chk. chk=1�̸� ���� �Է� ����
		
		if (buf[0]!='\n' && strlen(buf) < 10)
		{
			buf[strlen(buf)-1] = 0;
			strcpy(member[curMemberNum].name, buf);
			fflush(stdin);
			chk = 1;
		}

		// �ѱ��Է� Ȯ��
		for (i = 0; i < strlen(member[curMemberNum].name); i++)
		{
			if (member[curMemberNum].name[i] >= '0' && member[curMemberNum].name[i] <= '127')
			{
				chk = 0;//�ѱ��� �ƴ� ���� member[curMemberNum].name �迭�� ��ҿ� ������ chk���� 0�� �ִ´�(�����Է¾ƴ�)
				break;
			}
		}

		if (chk) //���������� chk���� 0�� �ƴϸ�(�����Է� �����̸�) while���� �������� �ּҸ� �Է¹޴´�
			break;

		printf("			�ùٸ� �̸��� �Է����ּ��� :");
	}
	
	printf("\n			��    �� : "); 
	while (1)
	{
		fgets(buf, sizeof(buf), stdin);
		if (buf[0] != '\n'&&strlen(buf) < 80)
		{
			buf[strlen(buf) - 1] = 0;
			strcpy(member[curMemberNum].address, buf);
			fflush(stdin);
			break;
		}
		printf("			�ּҸ� �Է����ּ��� :"); 
	}
	
	printf("\n			000-0000-0000�������� �Է����ּ���\n");
	printf("			��ȭ��ȣ : "); 
	while (1)
	{
		fgets(buf, sizeof(buf), stdin);
		if (buf[0] != '\n'&&strlen(buf) <= 14)
		{
			buf[strlen(buf) - 1] = 0;
			strcpy(member[curMemberNum].phone, buf);
			fflush(stdin);
			break;
		}
		printf("			��ȭ��ȣ�� �Է����ּ��� :"); 
	}
	
	while (1)
	{
		// ����, - �� �Էµ� �� �ֵ��� �Ѵ�
		for (i = 0; i < strlen(member[curMemberNum].phone)-1; i++)
		{
			if (!(member[curMemberNum].phone[i] >= '0' && member[curMemberNum].phone[i] <= '9') 
				&& member[curMemberNum].phone[i] != '-')
				break;
		}

		// (1) -�� ����ġ�� �ִ��� Ȯ�� : ����ġ�� ������ break;
		// (2) �ùٸ� �������� �ԷµǾ����� Ȯ�� : �ùٸ��� break 
		if (!(member[curMemberNum].phone[3] != '-' || member[curMemberNum].phone[8] != '-') 
			&& i == strlen(member[curMemberNum].phone) - 1)
			break;

		printf("			���Ŀ� ���߾� �Է����ּ��� : "); gets(member[curMemberNum].phone); fflush(stdin);
	}
	curMemberNum++;// ���� ����� �� ��� �� ++
	showMenu();
}

/*
3. ȸ�������ϱ� : deleteMember
*/
void deleteMember(void)
{
	gotoxy(18, 4); printf(" ��������������������������������������\n");
	gotoxy(18, 5); printf(" ��       �л������� �����մϴ�      ��\n");
	gotoxy(18, 6); printf(" ��������������������������������������\n");

	returnToMenu();
}
/*
4. ȸ�������ϱ� : editMember
*/
void editMember(void)
{
	gotoxy(18, 4); printf(" ��������������������������������������\n");
	gotoxy(18, 5); printf(" ��       �л������� �����մϴ�      ��\n");
	gotoxy(18, 6); printf(" ��������������������������������������\n");

	returnToMenu();
}
/*
5. ȸ���˻��ϱ� : searchMember
*/
void searchMember(void)
{
	gotoxy(18, 4); printf(" ��������������������������������������\n");
	gotoxy(18, 5); printf(" ��       �л������� �˻��մϴ�      ��\n");
	gotoxy(18, 6); printf(" ��������������������������������������\n");

	returnToMenu();
}
/*
6. �����ϱ� : saveData
*/
void saveData(void)
{
	char user_input;
	int i = 0;

	system("cls");
	gotoxy(18, 7); printf(" ��������������������������������������\n");
	gotoxy(18, 8); printf(" ��  ��� ��������� �����մϴ� :^)  ��\n");
	gotoxy(18, 9); printf(" ��������������������������������������\n");

	FILE* fp = fopen("data.txt", "wt");

	if (fp == NULL)
	{
		puts("file open error"); return -1;//������ ���� �������� ������ ������ �����޽��� ��� �� -1 ����(����������)
	}

	fprintf(fp, "ȸ�� ���̵�	ȸ���̸�	ȸ���ּ�	�ڵ��� ��ȣ\n");//������ ó���� �ε��� ����
	
	//����ü�� �ҷ��ͼ� ���Ͽ� ���� ����
	while (i<curMemberNum){
		fprintf(fp, "%d\t%s\t%s\t%s\n", member[i].userid, member[i].name, member[i].address, member[i].phone);
		i++;
	}

	fclose(fp);//�� ���� ���� �ݱ�

	gotoxy(19, 13); printf("���θ޴��� ���ư��÷��� 0�� �����ּ���\n");
	gotoxy(19, 14); printf("�ٸ����� ������ ����ȭ������ ���ϴ� : "); 
	user_input = getche();

	if (user_input == '0') showMenu(); 
	else
	{
		gotoxy(19, 16); exitProgram();
	}
	
}

/*
7. �����ϱ� : exitProgram
*/
void exitProgram(void)
{
	system("cls");//ȭ����ȯ
	char user_input;//����ڰ� ���忩�θ� ���ϴ��� Ȯ���ϱ� ���� �Է¹޴� ��(yes/no)
	gotoxy(18, 7); printf(" ��������������������������������������\n");
	gotoxy(18, 8); printf(" ��   �����ϱ� ���� �����Ͻðھ��?  ��\n");
	gotoxy(18, 9); printf(" ��������������������������������������\n");
	gotoxy(32, 11); printf("y/n :  ");
	user_input = getche();//����� �Է��� �޴´�. getche() : �ѱ��ڸ� �Է¹ް�, �Է¹��� ���ڸ� ȭ�鿡 �����ش�.

	if (user_input == 'y') saveData();//����ڰ� y�� �Է�(���� ���� �����ϰ��ʹ�)�ϸ� ���������� ��ȯ
	else if (user_input == 'n')
	{
		gotoxy(20, 13); return 0;
	}
	else exitProgram();
}

/*
gotoxy : UI������ ���� ��ǥ �����Լ�
�Ű����� : x,y��ǥ
*/
void gotoxy(int x, int y)
{
	COORD CursorPosition = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), CursorPosition);
}