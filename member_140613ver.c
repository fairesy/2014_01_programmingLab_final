
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <conio.h>
#include "member_140613.h"

#pragma warning(disable:4996)

#define MAX_SIZE 200
#define LEFT 75
#define RIGHT 77
#define ESC 27
#define BLACK textcolor(7)
#define CYAN textcolor(3)
#define CYAN_BACKGROUND textcolor(55) 
#define CLEAR_LINE printf("\t\t\t\t\t\t\t\t\t\t\t\n")

static int curMemberNum; //���� ����� �� ��� ��
static int nowMemberNum; //�й� �ڵ������� ���� ���� ū �й� ����
static student member[MAX_SIZE]; //����ü �迭 ����

int main(void)
{
	helloMessage();
	readMemberData();
	showMenu();
	return 0;
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
		puts("file open error"); return;
	}

	fgets(memberInfo, sizeof(memberInfo), fp);//file�� ù���� �л������� �ƴ϶� �й�/�̸����� �з������̹Ƿ� ����ü�� ���� ����

	while (!feof(fp) && fgets(memberInfo, sizeof(memberInfo), fp))//���Ͽ� �о���� ������ �ִ� ����
	{
		//strtok : ���� �������� �޾ƿ� ���ڿ��� �ڸ���.
		token = strtok(memberInfo, "	");
		member[i].userid = atoi(token); //char���� int������ �ٲ㼭(atoi) member[i].userid�� �ִ´�
		token = strtok(NULL, "	"); //strtok�� ������ �� ��ū�� ������(���й��ڰ� �ִ� ��)�� NULL�� �����صд�. �� ��������, ���� �Ǳ����� �� �ϳ��� ��ū���� ����
		strcpy(member[i].name, token); //��ū�� ����ü �ش� ĭ�� �����سֱ�
		token = strtok(NULL, "	");
		strcpy(member[i].address, token);
		token = strtok(NULL, "	");
		token[strlen(token) - 1] = '\0';
		strcpy(member[i].phone, token);

		//ȸ�� ����Ҷ� �й��� ���� ū �й� ���� ��ȣ�� �ڵ������ϱ� ���� ���Ͽ��� �Է¹޾ƿö� üũ�ؼ� �����صд�. 
		if (nowMemberNum < member[i].userid)
			nowMemberNum = member[i].userid;
		i++;
	}

	curMemberNum = i;
	nowMemberNum++;
	fclose(fp);//���� �ݱ�
}

void showMenu(void)
{
	system("cls");
	char choice;

	prettyMenuPrint();//�޴�����Ʈ

	choice = getche(); //getche() : �ѱ��ڸ� �Է¹޾�, ȭ�鿡 �Է¹��� ���ڸ� �����ش�.
	Beep(rand() % 200 + 300, 80);
	
	switch (choice)
	{
	case '1'://ȸ������Ʈ �����ֱ�
		printAll();
		break;
	case '2'://ȸ�����
		addNewMember();
		break;
	case '3'://ȸ���˻�
		searchMember(0);
		break;
	case '4'://����
		searchMember(1);
		break;
	case '5'://����
		searchMember(2);
		break;
	case '6'://����
		saveData();
		break;
	case '7'://����
		exitProgram();
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

	printf("	���θ޴��� ���ư��÷��� ESC�� �����ּ��� : ");
	user_choice = getche();
	Beep(rand() % 200 + 300, 80);
	fflush(stdin);

	while (user_choice != ESC)
	{
		printf("\n\n	�ùٸ� ���� �Է����ּ���!\n");
		fflush(stdin);
		returnToMenu();
	}
	showMenu();
}

/*
1. ȸ���������� : printAll-printPage
*/
void printAll(void)
{
	char ch;
	int lastPageNum = curMemberNum % 17 == 0 ? curMemberNum / 17 : (curMemberNum / 17) + 1;
	int curPageNum = 1; //���� �������� �� ó������ 1��

	printPage(curPageNum, lastPageNum);//ó������ 1��(curPageNum�� �ʱⰪ 1) ����Ʈ

	while (1)
	{
		ch = getch();
		Beep(rand() % 200 + 300, 80);

		if (ch == LEFT)//����
		{
			if (curPageNum == 1) continue;//���� 1�������� ������ ���������� ����
			printPage(--curPageNum, lastPageNum);
		}
		else if (ch == RIGHT)//����
		{
			if (curPageNum == lastPageNum) continue;//���� �������������� ������ ���������� ���� 
			printPage(++curPageNum, lastPageNum);
		}
		else if (ch == ESC)//���θ޴���
		{
			showMenu();
		}
	}
}

void printPage(int curPageNum, int lastPageNum)
{
	system("cls");
	int start, end; //�� �������� ���� �л� ����� ���۰� ��
	int i, j = 0;

	start = (curPageNum - 1) * 17;
	
	end = start + 17;
	if (curPageNum == lastPageNum) end = curMemberNum; //���� �������������̸� end�� �� �����

	printListIndex();//�й�-�̸�-�ּ�-��ȭ��ȣ

	for (i = start; i < end; i++)
	{
		gotoxy(5, 5 + j); 
		printf("��%6d  ��%7s ��%-25s ��%10s ��", member[i].userid, member[i].name, member[i].address, member[i].phone);
		j++;
	}
	gotoxy(5, j + 5); printf("������������������������������������������������������������������");
	CYAN; gotoxy(5, 23); printf("   <����������            ���θ޴���(ESC)            ����������>");
}

/*
2. ȸ������ϱ� : addNewMember
*/
void addNewMember(void)
{
	unsigned int i;
	char buf[100];//�Է¹޴� ������ �ϴ� ���� �迭�� �ְ�, �����Է����� Ȯ���Ѵ�.
	int fineInput;//�����Է»������� üũ���ֱ� ���� ����. fineInput=1�̸� ���� �Է� ����
	char ch;

	system("cls");
	printAddIndex();//������ ����ϰ�, ��� �������� ���θ� ���´�

	ch = getche();
	fflush(stdin);
	while (1)
	{
		if (ch == ESC)	showMenu();
		break;
	}

	gotoxy(18, 8); CLEAR_LINE;
	gotoxy(18, 9); CLEAR_LINE;

	// ���ο� �л������� �Է¹޴´�. �ԷµǴ� ���� �ƹ��͵� ������ �Է°��� ���������� �Է��� �䱸�Ѵ�.
	// ���۰���ŭ�� ���� �ȿ� ������ Ȯ��. ������ ���ۿ� ���� �� ���� ū ���� �Է��ϸ� �ٽ��Է¹޴´�.

	member[curMemberNum].userid = nowMemberNum++;
	BLACK;
	gotoxy(24, 10); printf("��    �� : %d\n", member[curMemberNum].userid); //�й��� �ڵ�����

	gotoxy(24, 12); printf("��    �� : ");
	while (1)
	{
		fgets(buf, sizeof(buf), stdin);//fgets�� �־��� ũ�� �̻����� �Է��ϸ�, ũ�⸸ŭ �ް� ���� �Է��� �׳� ������ �ִ�.
		fflush(stdin);//���� �Է����� ���� ����ؼ� ���� ������
		fineInput = 0; //�ʱ�ȭ

		//��ư ������ �ԷµǾ���, ���� ũ�⸦ ����� ������ -> �ϴ� ����ü �ش� ĭ�� �����سֱ�
		if (buf[0] != '\n' && strlen(buf) < 10)
		{
			buf[strlen(buf) - 1] = 0;
			strcpy(member[curMemberNum].name, buf);
			fineInput = 1; //�ϴ� �����Է�.
		}

		// �ѱ��Է� Ȯ��
		for (i = 0; i < strlen(member[curMemberNum].name); i++)
		{
			if (member[curMemberNum].name[i] >= '0' && member[curMemberNum].name[i] <= '127')
			{
				fineInput = 0;//�ѱ��� �ƴ� ���� member[curMemberNum].name �迭�� ��ҿ� ������ chk���� 0�� �ִ´�(=�����Է¾ƴ�)
				break;
			}
		}

		if (fineInput) break; //���������� chk���� 0�� �ƴϸ�(�����Է� �����̸�) while���� �������� �ּҸ� �Է¹޴´�
		//�ƴϸ� �ٽ� �Է��϶�� �޽��� ����� while ���ѷ���...
		CYAN; gotoxy(0, 13); CLEAR_LINE;
		gotoxy(24, 13); printf("�ùٸ� �̸��� �Է����ּ���!");
		BLACK; gotoxy(24, 12); CLEAR_LINE;
		gotoxy(24, 12); printf("��    �� : ");
	}

	BLACK;
	gotoxy(0, 13); CLEAR_LINE;
	gotoxy(24, 14); printf("��    �� : ");
	while (1)
	{
		fgets(buf, sizeof(buf), stdin);
		fflush(stdin);

		if (buf[0] != '\n'&&strlen(buf) < 25)
		{
			buf[strlen(buf) - 1] = 0;
			strcpy(member[curMemberNum].address, buf);
			break;
		}
		CYAN; gotoxy(0, 15); CLEAR_LINE;
		gotoxy(24, 15); printf("�ּҸ� �Է����ּ���!");
		BLACK; gotoxy(0, 14); CLEAR_LINE;
		gotoxy(24, 14); printf("��    �� : ");
	}
	gotoxy(0, 15); CLEAR_LINE;

	BLACK;
	gotoxy(24, 16); printf("000-0000-0000�������� �Է����ּ���\n");
	gotoxy(24, 17); printf("��ȭ��ȣ : ");
	while (1)
	{
		fgets(buf, sizeof(buf), stdin);
		fflush(stdin);

		if (buf[0] != '\n'&&strlen(buf) <= 14)
		{
			buf[strlen(buf) - 1] = 0;
			strcpy(member[curMemberNum].phone, buf);
			break;
		}
		CYAN; gotoxy(0, 18); CLEAR_LINE;
		gotoxy(24, 18); printf("��ȭ��ȣ�� �Է����ּ���!");
		BLACK; gotoxy(0, 17); CLEAR_LINE;
		gotoxy(24, 17); printf("��ȭ��ȣ : ");
	}
	phoneFormCheck(curMemberNum,18);

	curMemberNum++;// ���� ����� �� ��� �� ++
	CYAN; gotoxy(30, 21); printf("�� �� �� �� !");
	getch();
	showMenu();
}

/*
�����Լ� phoneFormCheck
��ȭ��ȣ�� �ùٸ� �������� �ԷµǾ����� Ȯ���Ѵ� 
�Է� : memberId, �����޽����� ����� ��ġ�� y��ǥ
*/
void phoneFormCheck(int memberId, int y_position) 
{
	unsigned int i;

	while (1)
	{
		// ����, - �� �Էµ� �� �ֵ��� �Ѵ�
		for (i = 0; i < strlen(member[memberId].phone) - 1; i++)
		{
			if (!(member[memberId].phone[i] >= '0' && member[memberId].phone[i] <= '9')
				&& member[memberId].phone[i] != '-')
				break;
		}

		// (1) -�� ����ġ�� �ִ��� Ȯ�� : ����ġ�� ������ break;
		// (2) �ùٸ� �������� �ԷµǾ����� Ȯ�� : �ùٸ��� break 
		if (!(member[memberId].phone[3] != '-' || member[memberId].phone[8] != '-')
			&& i == strlen(member[memberId].phone) - 1)
			break;

		//��������� break���� ���� ������ �Է°����� �ٽ� �Է¿䱸
		CYAN;gotoxy(0, y_position); CLEAR_LINE;
		gotoxy(24, y_position); printf("���Ŀ� ���߾� �Է����ּ���!");
		BLACK;gotoxy(0, y_position - 1); CLEAR_LINE;
		gotoxy(24, y_position-1); printf("��ȭ��ȣ : ");
		fgets(member[memberId].phone, sizeof(member[memberId].phone), stdin); fflush(stdin);
	}
}

/*
3. ȸ���˻��ϱ� : searchMember

�Ű����� fromwhere : ���θ޴����� �ٷ� �˻����� �°Ͱ�, ����/���� �Լ����� ȣ���� ��쿡 �˻� ���� �����۾� �ٸ���
fromwhere == 0 : ���θ޴�-�˻�. �˻� ���� �˻��� ����޴� ���
fromwhere == 1 : ���θ޴�-����. �˻� ���� edit�Լ� ȣ��
fromwhere == 2 : ���θ޴�-����. �˻� ���� delete�Լ� ȣ��
*/
void searchMember(int fromwhere)
{
	system("cls");
	char choice;
	int i, j, sameCount = 0;
	int searchmemberid;//����ڰ� ã���� �ϴ� �й�
	char searchName[20];//����ڰ� ã���� �ϴ� �̸�
	char searchPhone[14];//����ڰ� ã���� �ϴ� ��ȭ��ȣ
	int result;//���ڿ� ���Լ� strcmp�� ����� ����

	int sameName[100];//�����̸��̸� id�� �����ص� �迭

	printSearchIndex();

	choice = getche();
	fflush(stdin);
	Beep(rand() % 200 + 300, 80);

	CYAN;
	switch (choice)
	{
	case '1':
		gotoxy(20, 13); printf("ã���� �й� : ");
		scanf("%d", &searchmemberid);

		for (i = 0; i < curMemberNum; i++)
		{
			if (searchmemberid == member[i].userid)
			{
				gotoxy(0, 16); printCertainMember(i);
				break;
			}
		}
		break;

	case '2':
		gotoxy(20, 13); printf("ã���� �̸� : "); BLACK;
		fgets(searchName, sizeof(searchName), stdin);
		searchName[strlen(searchName) - 1] = '\0';
		//fgets�� ������ ����Ű('\n')���� �Է¹޾Ƽ� '�̸�\n'�������� �����⶧���� �������� �ι��ڷ� �ٲ㼭 �������ش�

		while (1)
		{
			//�̸��� �ƹ��͵� �Է����� �ʰ� ���͸� ���� ���(������ �������� \0���� �ٲ����ϱ� üũ�Ҷ��� \0���� üũ) 
			//�ٽ� �Է¹ޱ�
			if (searchName[0] == '\0')
			{
				gotoxy(20, 14); printf("�̸��� �Է����ּ��� : ");
				fgets(searchName, sizeof(searchName), stdin);
				searchName[strlen(searchName) - 1] = '\0';
			}
			else break;
		}

		//�̸� �Է��� ���� ����
		for (j = 0; j < curMemberNum; j++)
		{
			result = strcmp(searchName, member[j].name);

			//��ü ����Ʈ�� �� ���鼭 result�� 0�ΰ� ���� ������ sameCount�� �ø��� 
			if (result == 0)
			{
				sameName[sameCount] = j;
				sameCount++;
			}
		}

		//�˻��ϴ� �̸��� ��ġ�ϴ� �����Ͱ� 2�� �̻��� ���(���������� �ִ� ���)
		if (sameCount > 1) sameNameDifferent(sameName,fromwhere,sameCount);
		else if (sameCount == 1){
			i = sameName[0];
			gotoxy(0, 16); printCertainMember(i); //�������� ������
		}
		else{
			CYAN;
			gotoxy(29, 20); printf("�׷� �л� �����ϴ�");
			getch();
			showMenu();
		}
		break;

	case '3':
		gotoxy(18, 13); printf("000-0000-0000 ���Ŀ� ���߾� �Է����ּ���\n");
		gotoxy(18, 14); printf("ã���� ��ȭ��ȣ : ");
		fgets(searchPhone, sizeof(searchPhone), stdin);
		fflush(stdin);

		//�Է¹��� ��ȭ��ȣ ����üũ : ����ü�� ���� ���̶� phoneFormCheck�Լ��� ���� Id�� ���, ���� üũ
		while (1)
		{
			// ����, - �� �Էµ� �� �ֵ��� �Ѵ� : ����, - �� �ƴϸ� break(���Ŀ� ���߾� �ٽ��Է� �䱸)
			for (i = 0; i < (signed int)strlen(searchPhone) - 1; i++)
			{
				if (!(searchPhone[i] >= '0' && searchPhone[i] <= '9') && searchPhone[i] != '-')
					break;
			}

			// (1) -�� ����ġ�� �ִ��� Ȯ�� : ����ġ�� ������ break;
			// (2) �ùٸ� �������� �ԷµǾ����� Ȯ�� : �ùٸ��� break 
			if (!(searchPhone[3] != '-' || searchPhone[8] != '-') && i == strlen(searchPhone) - 1)
				break;

			BLACK;
			gotoxy(0, 15); CLEAR_LINE;
			gotoxy(18, 15); printf("���Ŀ� ���߾� �Է����ּ���!");
			CYAN;
			gotoxy(0, 14); CLEAR_LINE;
			gotoxy(18, 14); printf("ã���� ��ȭ��ȣ : ");
			fgets(searchPhone, sizeof(searchPhone), stdin);
			fflush(stdin);
		}

		for (i = 0; i < curMemberNum; i++)
		{
			result = strcmp(searchPhone, member[i].phone);
			if (result == 0)
			{
				gotoxy(0, 16); printCertainMember(i);
				break;
			}
		}
		break;

	case ESC://�޴��� ���ư���
		showMenu();
		break;

	default:
		searchMember(fromwhere);
		break;
	}

	//switch������ �������� ����(�й�, �ּҰ˻� �ش�)���� i�� �������� ���� �ٸ� �۾� ����
	CYAN;	
	if (i==curMemberNum)
	{
		gotoxy(29, 20); printf("�׷� �л� �����ϴ�"); 
		getch();
		showMenu();
	}
	else
	{
		BLACK;
		switch (fromwhere)
		{
		case 0: //���θ޴�-�˻�
			searchSubmenu(i);
			break;
		case 1: //���θ޴�-����
			gotoxy(20, 21); printf("����Ͻ÷��� �ƹ� Ű�� �����ּ��� :-)");
			getch();
			editMember(i);
			break;
		case 2: //���θ޴�-����
			gotoxy(20, 21); printf("����Ͻ÷��� �ƹ� Ű�� �����ּ��� :-)");
			getch();
			deleteMember(i);
			break;
		default:
			break;
		}
	}
}

/*
3-0 sameName : �������� ó�� �Լ�
�������� �߿� ���� �۾��� ������ ����� id�� ����
*/
void sameNameDifferent(int *sameName[], int fromwhere, int sameCount)
{
	int i;
	int option = 0;//�������ο��� ���� ��. ���������� ������ 0

	for (i = 0; i < sameCount; i++)
	{
		gotoxy(0, 16 + i); printf("   [%d]", i + 1); printCertainMember(sameName[i]);
	}
	gotoxy(20, 20); printf("������ �����Ͻðڽ��ϱ�? : ");
	do{
		option = getche();
		option = option - '0'; //option�� ���ڷ�.
		option=option-1;
		if (option<0 || option>9)
		{
			option = getche();
		}
	} while (!(option >= 0 && option < sameCount)); 

	BLACK;
	switch (fromwhere)
	{
	case 0: //���θ޴�-�˻�
		searchSubmenu(sameName[option]);
		break;
	case 1: //���θ޴�-����
		gotoxy(20, 21); printf("����Ͻ÷��� �ƹ� Ű�� �����ּ��� :-)");
		getch();
		editMember(sameName[option]);
		break;
	case 2: //���θ޴�-����
		gotoxy(20, 21); printf("����Ͻ÷��� �ƹ� Ű�� �����ּ��� :-)");
		getch();
		deleteMember(sameName[option]);
		break;
	default:
		break;
	}
}

/*
3-1 �˻��� ������ �۾� ���� : searchSubmenu
*/
void searchSubmenu(int memberIdx)
{
	char selectWhatToDo;

	CYAN; gotoxy(20, 21); printf("1 �����ϱ�  2 �����ϱ�  ESC ���θ޴���\n");
	BLACK; gotoxy(20, 22); printf("������ �� �۾��� �������ּ��� : ");
	selectWhatToDo = getche();
	Beep(rand() % 200 + 300, 80);

	switch (selectWhatToDo)
	{
	case '1'://�����ϱ�
		deleteMember(memberIdx);
		break;
	case '2'://�����ϱ�
		editMember(memberIdx);
		break;
	case ESC://���θ޴���
		showMenu();
		break;
	default://�� ��찡 �ƴ� ���̸� searchSubmenu �ٽ� ȣ��
		searchSubmenu(memberIdx);
		break;
	}
}

//�˻������ ���� ��� �� ��� ������ ���
void printCertainMember(int memberNum)
{
	BLACK;	
	printf("\t��%6d  ��%7s ��%-25s ��%10s ��\n",
		member[memberNum].userid, member[memberNum].name, member[memberNum].address, member[memberNum].phone);
}

/*
4. ȸ�������ϱ� : editMember
*/
void editMember(int memberIdx)
{
	char datachoice;
	char buf[100];

	int fineInput;
	int i;

	system("cls");

	printEditIndex();
	//�Ѿ�� �����͸� �ϴ� ����ؼ� �����ش�.
	gotoxy(0, 8); printCertainMember(memberIdx);

	gotoxy(54, 16); datachoice = getche();
	Beep(rand() % 200 + 300, 80);

	BLACK;
	switch (datachoice)
	{
	case '1'://�̸�
		gotoxy(20, 18); printf("���ο� �̸��� �Է��ϼ��� : ");

		while (1)
		{
			fgets(buf, sizeof(buf), stdin);//�ϴ� ���ۿ� �Է��� �޴´�
			fflush(stdin);
			fineInput = 0;

			while (1)//�Է°��� �ƹ��͵� ������ �ٽ��Է� �䱸
			{
				if (buf[0] == '\n')
				{
					fineInput = 0;
					CYAN; gotoxy(0, 19); CLEAR_LINE;
					gotoxy(20, 19); printf("�̸��� �Է��ϼ���!");
					BLACK; gotoxy(0, 18); CLEAR_LINE;
					gotoxy(20, 18); printf("���ο� �̸��� �Է��ϼ��� : ");
					fgets(buf, sizeof(buf), stdin);
				}
				else break;
			}

			if (buf[0] != '\n' && strlen(buf) < 10)
			{
				buf[strlen(buf) - 1] = 0;
				strcpy(member[memberIdx].name, buf);
				fineInput = 1;
			}

			// �ѱ��Է� Ȯ��
			for (i = 0; i < (signed)strlen(member[memberIdx].name); i++)
			{
				if (member[memberIdx].name[i] >= '0' && member[memberIdx].name[i] <= '127')
				{
					fineInput = 0;//�ѱ��� �ƴ� ���� member[curMemberNum].name �迭�� ��ҿ� ������ fineInput���� 0�� �ִ´�(�����Է¾ƴ�)
					break;
				}
			}

			//���������� fineInput���� 0�� �ƴϸ�(�����Է� �����̸�) while���� �������� �ּҸ� �Է¹޴´�
			if (fineInput) 
				break;

			CYAN; gotoxy(0, 19); CLEAR_LINE;
			gotoxy(20, 19); printf("�ùٸ� �̸��� �Է����ּ���!");
			BLACK; gotoxy(0, 18); CLEAR_LINE;
			gotoxy(20, 18); printf("���ο� �̸��� �Է��ϼ��� : ");
		}
		break;

	case '2'://�ּ�
		gotoxy(20, 18); printf("���ο� �ּ��� �Է��ϼ��� : ");
		while (1)
		{
			fgets(buf, sizeof(buf), stdin);
			fflush(stdin);

			if (buf[0] != '\n'&&strlen(buf) <= 80)
			{
				buf[strlen(buf) - 1] = 0;
				strcpy(member[memberIdx].address, buf);
				break;
			}
			CYAN; gotoxy(0, 19); CLEAR_LINE;
			gotoxy(20, 19); printf("�ּҸ� �Է����ּ���!");
			BLACK; gotoxy(0, 18); CLEAR_LINE;
			gotoxy(20, 18); printf("���ο� �ּ��� �Է��ϼ��� : ");
		}
		break;

	case '3'://��ȭ��ȣ

		gotoxy(20, 18); printf("���ο� ��ȭ��ȣ�� �Է��ϼ��� : ");
		while (1)
		{
			fgets(buf, sizeof(buf), stdin);
			fflush(stdin);

			if (buf[0] != '\n'&&strlen(buf) <= 14)//NULL���� �ƴϰ�, ���ۼ��� �Ѿ�� ������ �ϴ� �ش��ϴ� ����� ��ȣĭ�� �Է¹��� ������ �����سִ´�.
			{
				buf[strlen(buf) - 1] = 0;
				strcpy(member[memberIdx].phone, buf);
				break;
			}
			CYAN; gotoxy(0, 19); CLEAR_LINE;
			gotoxy(20, 19); printf("��ȭ��ȣ�� �Է����ּ���!");
			BLACK; gotoxy(0, 18); CLEAR_LINE;
			gotoxy(20, 18); printf("���ο� ��ȭ��ȣ�� �Է��ϼ��� : ");
		}
		phoneFormCheck(memberIdx,19);
		break;

	case ESC://�޴���
		showMenu();
	default:
		editMember(memberIdx);
		break;
	}

	CYAN;
	gotoxy(20, 21); printf("�л������� �����Ǿ����ϴ�!");
	getch();
	showMenu();
}

/*
5. ȸ�������ϱ� : deleteMember
*/
void deleteMember(int memberIdx)
{
	int i;
	char user_choice;
	system("cls");

	printDeleteIndex(); //������ ����ϰ�, �������θ� �����.

	user_choice = getch();
	Beep(rand() % 200 + 300, 80);

	if (user_choice == 'y')
	{
		for (i = memberIdx; i < curMemberNum; i++)
		{
			member[i] = member[i + 1];
		}
		curMemberNum--;
		CYAN; gotoxy(30, 14); printf("�����Ǿ����ϴ�!");
	}
	else if (user_choice == 'n')
	{
		showMenu();
	}
	else
	{
		deleteMember(memberIdx);
	}
	getch();
	showMenu();
}

/*
6. �����ϱ� : saveData
*/
void saveData(void)
{
	system("cls");
	char user_input;
	int i = 0;

	printSaveIndex();

	FILE* fp = fopen("data.txt", "wt");

	if (fp == NULL)
	{
		puts("file open error"); return;//������ ���� �������� ������ ������ �����޽��� ��� �� ����(����������)
	}

	//������ ó���� �ε��� ����
	fprintf(fp, "ȸ�� ���̵�	ȸ���̸�	ȸ���ּ�	�ڵ��� ��ȣ\n");

	//����ü�� �ҷ��ͼ� ���Ͽ� ���� ����
	while (i < curMemberNum){
		fprintf(fp, "%d\t%s\t%s\t%s\n", member[i].userid, member[i].name, member[i].address, member[i].phone);
		i++;
	}

	fclose(fp);//�� ���� ���� �ݱ�

	user_input = getche();
	Beep(rand() % 200 + 300, 80);

	if (user_input == ESC) showMenu();
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

	printExitIndex();
	user_input = getche();//����� �Է��� �޴´�. 
	Beep(rand() % 200 + 300, 80);

	if (user_input == 'y') saveData();//����ڰ� y�� �Է�(���� ���� �����ϰ�ʹ�)�ϸ� ���������� ��ȯ
	else if (user_input == 'n') byebyeMessage();
	else exitProgram();
}