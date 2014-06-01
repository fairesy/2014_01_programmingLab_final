#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "member.h"
#pragma warning(disable:4996)

#define MAX_SIZE 50

static int curMemberNum; //현재 저장된 총 멤버 수
static int nowMemberNum;
static student member[MAX_SIZE];

int main(void){
	readMemberData(); //프로그램이 실행되면 파일을 로드한다
	showMenu(); //메뉴화면을 보여준다
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
		gotoxy(32, 8 + i); puts(menu[i]); //메뉴목록 출력
	}

	gotoxy(17, 16); printf("원하는 작업을 선택해주세요  ");
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
returnToMenu : 메인메뉴로 돌아간다
*/
void returnToMenu(void)
{
	char user_choice;

	printf("	메인메뉴로 돌아가시려면 0을 눌러주세요 : ");
	user_choice = getche();
	fflush(stdin);
			
	while (user_choice != '0')
	{
		printf("\n\n	올바른 값을 입력해주세요!\n");
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
	nowMemberNum = 0; 
	char memberInfo[120];//파일에서 읽어들인 한 줄을 저장해둘 공간
	char* token;
	int i = 0;

	FILE* fp;
	fp = fopen("data.txt", "rt");//파일을 읽기 모드로 연다

	if (fp == NULL)
	{
		puts("file open error"); return -1;
	}

	fgets(memberInfo, sizeof(memberInfo), fp);//file의 첫줄은 학생정보가 아니라 학번/이름같은 분류기준이므로 구조체에 넣지 않음

	while (!feof(fp) && fgets(memberInfo, sizeof(memberInfo), fp))//파일에 읽어들일 내용이 있는 동안
	{
		//strtok : 탭을 기준으로 받아온 문자열을 자른다.
		token = strtok(memberInfo, "	");
		member[i].userid = atoi(token); //char형을 int형으로 바꿔서(atoi) member[i].userid에 넣는다
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
memoryExtension : 메모리가 꽉 차면 메모리를 2배로 확장한다. 
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
		gotoxy(5, 4 + i); printf("│%6d  │%7s │%-25s │%10s │",
			member[i].userid, member[i].name, member[i].address, member[i].phone);
	}
	gotoxy(5, 4 + curMemberNum); printf("└────┴────┴─────────────┴───────┘\n");

	printf("\n");
	fflush(stdin); 
	returnToMenu();

}

/*
2. 회원등록하기 : addNewMember
*/
void addNewMember(void)
{
	int i;
	char buf[80];
	int chk;

	system("cls");

	gotoxy(18, 4); printf(" ┌─────────────────┐\n");
	gotoxy(18, 5); printf(" │     새로운 학생을 등록합니다     │\n");
	gotoxy(18, 6); printf(" └─────────────────┘\n");

	// 새로운 학생정보를 입력받는다. 입력되는 값이 아무것도 없으면 입력값이 있을때까지 입력을 요구한다.
	// 버퍼값만큼의 범위 안에 들어가는지 확인. 지정된 버퍼에 넣을 수 없는 큰 값을 입력하면 다시입력받는다.
	
	member[curMemberNum].userid = nowMemberNum++;
	printf("			학    번 : %d\n", member[curMemberNum].userid); //학번은 자동생성
	fflush(stdin);

	printf("\n			이    름 : ");
	while (1)
	{
		fgets(buf, sizeof(buf), stdin);
		chk = 0; //정상입력상태인지 체크해주기 위한 변수 chk. chk=1이면 정상 입력 상태
		
		if (buf[0]!='\n' && strlen(buf) < 10)
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
				chk = 0;//한글이 아닌 값이 member[curMemberNum].name 배열의 요소에 들어오면 chk값에 0을 넣는다(정상입력아님)
				break;
			}
		}

		if (chk) //최종적으로 chk값이 0이 아니면(정상입력 상태이면) while문을 빠져나가 주소를 입력받는다
			break;

		printf("			올바른 이름을 입력해주세요 :");
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
	curMemberNum++;// 현재 저장된 총 멤버 수 ++
	showMenu();
}

/*
3. 회원삭제하기 : deleteMember
*/
void deleteMember(void)
{
	gotoxy(18, 4); printf(" ┌─────────────────┐\n");
	gotoxy(18, 5); printf(" │       학생정보를 삭제합니다      │\n");
	gotoxy(18, 6); printf(" └─────────────────┘\n");

	returnToMenu();
}
/*
4. 회원수정하기 : editMember
*/
void editMember(void)
{
	gotoxy(18, 4); printf(" ┌─────────────────┐\n");
	gotoxy(18, 5); printf(" │       학생정보를 수정합니다      │\n");
	gotoxy(18, 6); printf(" └─────────────────┘\n");

	returnToMenu();
}
/*
5. 회원검색하기 : searchMember
*/
void searchMember(void)
{
	gotoxy(18, 4); printf(" ┌─────────────────┐\n");
	gotoxy(18, 5); printf(" │       학생정보를 검색합니다      │\n");
	gotoxy(18, 6); printf(" └─────────────────┘\n");

	returnToMenu();
}
/*
6. 저장하기 : saveData
*/
void saveData(void)
{
	char user_input;
	int i = 0;

	system("cls");
	gotoxy(18, 7); printf(" ┌─────────────────┐\n");
	gotoxy(18, 8); printf(" │  모든 변경사항을 저장합니다 :^)  │\n");
	gotoxy(18, 9); printf(" └─────────────────┘\n");

	FILE* fp = fopen("data.txt", "wt");

	if (fp == NULL)
	{
		puts("file open error"); return -1;//파일을 여는 과정에서 문제가 있으면 오류메시지 출력 후 -1 리턴(비정상종료)
	}

	fprintf(fp, "회원 아이디	회원이름	회원주소	핸드폰 번호\n");//파일의 처음에 인덱스 쓰기
	
	//구조체를 불러와서 파일에 쭉쭉 쓰기
	while (i<curMemberNum){
		fprintf(fp, "%d\t%s\t%s\t%s\n", member[i].userid, member[i].name, member[i].address, member[i].phone);
		i++;
	}

	fclose(fp);//다 쓰면 파일 닫기

	gotoxy(19, 13); printf("메인메뉴로 돌아가시려면 0을 눌러주세요\n");
	gotoxy(19, 14); printf("다른값을 누르면 종료화면으로 갑니다 : "); 
	user_input = getche();

	if (user_input == '0') showMenu(); 
	else
	{
		gotoxy(19, 16); exitProgram();
	}
	
}

/*
7. 종료하기 : exitProgram
*/
void exitProgram(void)
{
	system("cls");//화면전환
	char user_input;//사용자가 저장여부를 원하는지 확인하기 위해 입력받는 값(yes/no)
	gotoxy(18, 7); printf(" ┌─────────────────┐\n");
	gotoxy(18, 8); printf(" │   종료하기 전에 저장하시겠어요?  │\n");
	gotoxy(18, 9); printf(" └─────────────────┘\n");
	gotoxy(32, 11); printf("y/n :  ");
	user_input = getche();//사용자 입력을 받는다. getche() : 한글자만 입력받고, 입력받은 문자를 화면에 보여준다.

	if (user_input == 'y') saveData();//사용자가 y를 입력(종료 전에 저장하고싶다)하면 저장기능으로 전환
	else if (user_input == 'n')
	{
		gotoxy(20, 13); return 0;
	}
	else exitProgram();
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
