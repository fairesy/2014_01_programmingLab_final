#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "member.h"
#pragma warning(disable:4996)

#define MAX_SIZE 50

static int curMemberNum;
static int nowMemberNum;
static student member[MAX_SIZE];

int main(void){
	readMemberData();
	showMenu();
	return 0;
}
/*
showMenu : 메인메뉴화면을 보여준다.
*/
void showMenu(void)
{
	system("cls");
	char choice;
	int i;

	char* menu[] = { "1  회 원 보 기", "2  회 원 등 록", "3  회 원 삭 제",
		"4  회 원 수 정", "5  회 원 검 색", "6  저 장 하 기", "7  종 료 하 기" };

	gotoxy(17, 1); printf("┌─────────────────────┐\n");
	gotoxy(17, 2); printf("│                                          │\n");
	gotoxy(17, 3); printf("│         회 원 관 리 프 로 그 램          │\n");
	gotoxy(17, 4); printf("│                                          │\n");
	gotoxy(17, 5); printf("└─────────────────────┘\n");


	for (i = 0; i < 7; i++)
	{
		gotoxy(32, 8 + i); puts(menu[i]);
	}

	gotoxy(17, 16); printf("원하는 작업을 선택해주세요  ");
	choice = getch();
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
returnToMenu : 메인메뉴로 돌아간다
*/
void returnToMenu(void)
{
	char user_choice;

	printf("	메인메뉴로 돌아가시려면 0을 눌러주세요 : "); scanf("%c", &user_choice);
	fflush(stdin);
	while (user_choice!='0')
	{
		printf("\n	올바른 값을 입력해주세요!\n");
		fflush(stdin);
		returnToMenu();
	}
	showMenu();
}

/*
readMemberData : 파일을 불러온다. 
*/
void readMemberData(void)
{
	curMemberNum = 0;
	nowMemberNum = 0; //현재 멤버의 학번
	char memberInfo[120];//파일에서 읽어들인 한 줄을 저장해둘 공간
	char* token;
	int i = 0;

	FILE* fp;
	fp = fopen("data.txt", "rt");

	if (fp == NULL)
	{
		puts("file open error"); return -1;
	}

	fgets(memberInfo, sizeof(memberInfo), fp);//file의 첫줄은 학생정보가 아니라 학번/이름같은 분류기준이므로 구조체에 넣지 않음

	while (!feof(fp) && fgets(memberInfo, sizeof(memberInfo), fp))//파일에 읽어들일 내용이 있는 동안
	{
		token = strtok(memberInfo, "	");//탭을 기준으로 문자열을 자른다
		member[i].userid = atoi(token);
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
memoryExtension : 메모리가 꽉 차면 메모리를 확장한다. 
*/
void memoryExtension(void)
{
#define MAX_SIZE = MAX_SIZE * 2;
}

/*
1. 회원정보보기 : viewAllMember
data.txt 파일을 불러와서 각 줄을 tap을 기준으로 잘라서 구조체에 집어넣는다.
구조체 단위로 출력한다.
*/

void viewAllMember(void)
{
	system("cls");
	int i; 

	gotoxy(5, 1); printf("┌────┬────┬─────────────┬───────┐\n");
	gotoxy(5, 2); printf("│  학번  │  이름  │  주소                    │  전화번호    │\n");
	gotoxy(5, 3); printf("└────┴────┴─────────────┴───────┘\n");

	for (i = 0; i<curMemberNum ; i++){
		gotoxy(5, 4 + i); printf("│%6d  │%7s │%-25s │%10s",
			member[i].userid, member[i].name, member[i].address, member[i].phone);
	}
	gotoxy(5, 4 + curMemberNum); printf("└────┴────┴─────────────┴───────┘\n");

	printf("\n");
	fflush(stdin); 
	returnToMenu();

}

/*
2. 회원등록하기 : addNewMember
수정할 버그사항 : 
이름형식(숫자 안됨).
전화번호 형식.

*/
void addNewMember(void)
{
	int i;

	system("cls");
	int user_choice;
	member[curMemberNum].userid = nowMemberNum++;

	gotoxy(18, 4); printf(" ┌─────────────────┐\n");
	gotoxy(18, 5); printf(" │     새로운 학생을 등록합니다     │\n");
	gotoxy(18, 6); printf(" └─────────────────┘\n");

	// 새로운 학생정보를 입력받는다. 입력되는 값이 아무것도 없으면 입력값이 있을때까지 입력을 요구한다.
	// 버퍼값만큼의 범위 안에 들어가는지 확인

	printf("			학    번 : %d\n", member[curMemberNum].userid); 
	fflush(stdin);

	char buf[80];
	int chk;

	printf("\n			이    름 : ");
	while (1)
	{
		fgets(buf, sizeof(buf), stdin);
		chk = 0;
		
		if (buf[0]!='\n' && strlen(buf) < 20)
		{
			buf[strlen(buf)-1] = 0;
			strcpy(member[curMemberNum].name, buf);
			fflush(stdin);
			chk = 1;
		}

		// 한글입력 확인
		for (i = 0; i < strlen(member[curMemberNum].name); i++)
		{
			if (member[curMemberNum].name[i] >= '0' && member[curMemberNum].name[i] <= '127')
			{
				chk = 0;
				break;
			}
		}

		if (chk)
			break;

		printf("			이름을 입력해주세요 :");
	}

	
	printf("\n			주    소 : "); 
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
		printf("			주소를 입력해주세요 :"); 
	}
	
	printf("\n			000-0000-0000형식으로 입력해주세요\n");
	printf("			전화번호 : "); 
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
		printf("			전화번호를 입력해주세요 :"); 
	}
	
	while (1)
	{
		// 숫자, - 만 입력될 수 있도록 한다
		for (i = 0; i < strlen(member[curMemberNum].phone)-1; i++)
		{
			if (!(member[curMemberNum].phone[i] >= '0' && member[curMemberNum].phone[i] <= '9') 
				&& member[curMemberNum].phone[i] != '-')
				break;
		}

		// (1) -이 제위치에 있는지 확인 : 제위치에 있으면 break;
		// (2) 올바른 형식으로 입력되었는지 확인 : 올바르면 break 
		if (!(member[curMemberNum].phone[3] != '-' || member[curMemberNum].phone[8] != '-') 
			&& i == strlen(member[curMemberNum].phone) - 1)
			break;

		printf("			형식에 맞추어 입력해주세요 : "); gets(member[curMemberNum].phone); fflush(stdin);
	}
	curMemberNum++;
	showMenu();
}

/*
3. 회원삭제하기 : deleteMember
*/
void deleteMember(void)
{

}
/*
4. 회원수정하기 : editMember
*/
void editMember(void)
{

}
/*
5. 회원검색하기 : searchMember
*/
void searchMember(void)
{

}
/*
6. 저장하기 : saveData
수정할 버그 :
회원 등록 후 저장하기 수행까지 마치고 프로그램을 종료했는데, 다시 프로그램을 실행하면 파일에 추가사항이 남아있지 않음
*/
int saveData(void)
{
	char user_input;

	system("cls");
	int i=0;
	gotoxy(18, 7); printf(" ┌─────────────────┐\n");
	gotoxy(18, 8); printf(" │  모든 변경사항을 저장합니다 :^)  │\n");
	gotoxy(18, 9); printf(" └─────────────────┘\n");

	FILE* fp = fopen("data.txt", "wt");

	fprintf(fp, "회원 아이디	회원이름	회원주소	핸드폰 번호\n");
	
	while (i<curMemberNum){
		fprintf(fp, "%d\t%s\t%s\t%s\n", member[i].userid, member[i].name, member[i].address, member[i].phone);
		i++;
	}

	fclose(fp);

	gotoxy(19, 13); printf("메인메뉴로 돌아가시려면 0을 눌러주세요\n");
	gotoxy(19, 14); printf("다른값을 누르면 종료됩니다 : "); scanf_s(" %c", &user_input,1);

	if (user_input == '0')
	{
	showMenu();
	}
	else
	{
	gotoxy(19, 16); return 0;
	}
	
}

/*
7. 종료하기 : exitProgram
*/
int exitProgram(void)
{
	system("cls");//화면전환
	char user_input;//사용자가 저장여부를 원하는지 확인하기 위해 입력받는 값(yes/no)
	gotoxy(18, 7); printf(" ┌─────────────────┐\n");
	gotoxy(18, 8); printf(" │   종료하기 전에 저장하시겠어요?  │\n");
	gotoxy(18, 9); printf(" └─────────────────┘\n");
	gotoxy(32, 11); printf("y/n :  "); scanf(" %c", &user_input);//사용자 입력을 받는다.

	if (user_input == 'y') saveData();//사용자가 y를 입력(종료 전에 저장하고싶다)하면 저장기능으로 전환
	else if (user_input == 'n')
	{
		gotoxy(20, 13); return 0;
	}
	else
	{
		exitProgram();
	}
}

/*
gotoxy : UI구현을 위한 좌표 설정함수
매개변수 : x,y좌표
*/
void gotoxy(int x, int y)
{
	COORD CursorPosition = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), CursorPosition);
}
