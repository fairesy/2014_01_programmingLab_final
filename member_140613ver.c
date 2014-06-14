
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

static int curMemberNum; //현재 저장된 총 멤버 수
static int nowMemberNum; //학번 자동생성을 위해 가장 큰 학번 저장
static student member[MAX_SIZE]; //구조체 배열 선언

int main(void)
{
	helloMessage();
	readMemberData();
	showMenu();
	return 0;
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
		puts("file open error"); return;
	}

	fgets(memberInfo, sizeof(memberInfo), fp);//file의 첫줄은 학생정보가 아니라 학번/이름같은 분류기준이므로 구조체에 넣지 않음

	while (!feof(fp) && fgets(memberInfo, sizeof(memberInfo), fp))//파일에 읽어들일 내용이 있는 동안
	{
		//strtok : 탭을 기준으로 받아온 문자열을 자른다.
		token = strtok(memberInfo, "	");
		member[i].userid = atoi(token); //char형을 int형으로 바꿔서(atoi) member[i].userid에 넣는다
		token = strtok(NULL, "	"); //strtok가 끝나면 그 토큰의 마지막(구분문자가 있던 곳)에 NULL을 리턴해둔다. 그 다음부터, 다음 탭까지를 또 하나의 토큰으로 끊기
		strcpy(member[i].name, token); //토큰을 구조체 해당 칸에 복사해넣기
		token = strtok(NULL, "	");
		strcpy(member[i].address, token);
		token = strtok(NULL, "	");
		token[strlen(token) - 1] = '\0';
		strcpy(member[i].phone, token);

		//회원 등록할때 학번을 가장 큰 학번 다음 번호로 자동생성하기 위해 파일에서 입력받아올때 체크해서 저장해둔다. 
		if (nowMemberNum < member[i].userid)
			nowMemberNum = member[i].userid;
		i++;
	}

	curMemberNum = i;
	nowMemberNum++;
	fclose(fp);//파일 닫기
}

void showMenu(void)
{
	system("cls");
	char choice;

	prettyMenuPrint();//메뉴프린트

	choice = getche(); //getche() : 한글자만 입력받아, 화면에 입력받은 글자를 보여준다.
	Beep(rand() % 200 + 300, 80);
	
	switch (choice)
	{
	case '1'://회원리스트 보여주기
		printAll();
		break;
	case '2'://회원등록
		addNewMember();
		break;
	case '3'://회원검색
		searchMember(0);
		break;
	case '4'://수정
		searchMember(1);
		break;
	case '5'://삭제
		searchMember(2);
		break;
	case '6'://저장
		saveData();
		break;
	case '7'://종료
		exitProgram();
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

	printf("	메인메뉴로 돌아가시려면 ESC을 눌러주세요 : ");
	user_choice = getche();
	Beep(rand() % 200 + 300, 80);
	fflush(stdin);

	while (user_choice != ESC)
	{
		printf("\n\n	올바른 값을 입력해주세요!\n");
		fflush(stdin);
		returnToMenu();
	}
	showMenu();
}

/*
1. 회원정보보기 : printAll-printPage
*/
void printAll(void)
{
	char ch;
	int lastPageNum = curMemberNum % 17 == 0 ? curMemberNum / 17 : (curMemberNum / 17) + 1;
	int curPageNum = 1; //현재 페이지는 맨 처음에는 1쪽

	printPage(curPageNum, lastPageNum);//처음에는 1쪽(curPageNum의 초기값 1) 프린트

	while (1)
	{
		ch = getch();
		Beep(rand() % 200 + 300, 80);

		if (ch == LEFT)//이전
		{
			if (curPageNum == 1) continue;//현재 1페이지에 있으면 이전페이지 없음
			printPage(--curPageNum, lastPageNum);
		}
		else if (ch == RIGHT)//다음
		{
			if (curPageNum == lastPageNum) continue;//현재 마지막페이지에 있으면 다음페이지 없음 
			printPage(++curPageNum, lastPageNum);
		}
		else if (ch == ESC)//메인메뉴로
		{
			showMenu();
		}
	}
}

void printPage(int curPageNum, int lastPageNum)
{
	system("cls");
	int start, end; //한 페이지에 들어가는 학생 목록의 시작과 끝
	int i, j = 0;

	start = (curPageNum - 1) * 17;
	
	end = start + 17;
	if (curPageNum == lastPageNum) end = curMemberNum; //현재 마지막페이지이면 end는 총 멤버수

	printListIndex();//학번-이름-주소-전화번호

	for (i = start; i < end; i++)
	{
		gotoxy(5, 5 + j); 
		printf("│%6d  │%7s │%-25s │%10s │", member[i].userid, member[i].name, member[i].address, member[i].phone);
		j++;
	}
	gotoxy(5, j + 5); printf("└────┴────┴─────────────┴───────┘");
	CYAN; gotoxy(5, 23); printf("   <이전페이지            메인메뉴로(ESC)            다음페이지>");
}

/*
2. 회원등록하기 : addNewMember
*/
void addNewMember(void)
{
	unsigned int i;
	char buf[100];//입력받는 내용은 일단 버퍼 배열에 넣고, 정상입력인지 확인한다.
	int fineInput;//정상입력상태인지 체크해주기 위한 변수. fineInput=1이면 정상 입력 상태
	char ch;

	system("cls");
	printAddIndex();//제목을 출력하고, 계속 진행할지 여부를 묻는다

	ch = getche();
	fflush(stdin);
	while (1)
	{
		if (ch == ESC)	showMenu();
		break;
	}

	gotoxy(18, 8); CLEAR_LINE;
	gotoxy(18, 9); CLEAR_LINE;

	// 새로운 학생정보를 입력받는다. 입력되는 값이 아무것도 없으면 입력값이 있을때까지 입력을 요구한다.
	// 버퍼값만큼의 범위 안에 들어가는지 확인. 지정된 버퍼에 넣을 수 없는 큰 값을 입력하면 다시입력받는다.

	member[curMemberNum].userid = nowMemberNum++;
	BLACK;
	gotoxy(24, 10); printf("학    번 : %d\n", member[curMemberNum].userid); //학번은 자동생성

	gotoxy(24, 12); printf("이    름 : ");
	while (1)
	{
		fgets(buf, sizeof(buf), stdin);//fgets는 주어진 크기 이상으로 입력하면, 크기만큼 받고 남은 입력은 그냥 가지고 있다.
		fflush(stdin);//남은 입력있을 때를 대비해서 버퍼 날리기
		fineInput = 0; //초기화

		//여튼 뭔가가 입력되었고, 버퍼 크기를 벗어나지 않으면 -> 일단 구조체 해당 칸에 복사해넣기
		if (buf[0] != '\n' && strlen(buf) < 10)
		{
			buf[strlen(buf) - 1] = 0;
			strcpy(member[curMemberNum].name, buf);
			fineInput = 1; //일단 정상입력.
		}

		// 한글입력 확인
		for (i = 0; i < strlen(member[curMemberNum].name); i++)
		{
			if (member[curMemberNum].name[i] >= '0' && member[curMemberNum].name[i] <= '127')
			{
				fineInput = 0;//한글이 아닌 값이 member[curMemberNum].name 배열의 요소에 들어오면 chk값에 0을 넣는다(=정상입력아님)
				break;
			}
		}

		if (fineInput) break; //최종적으로 chk값이 0이 아니면(정상입력 상태이면) while문을 빠져나가 주소를 입력받는다
		//아니면 다시 입력하라는 메시지 출력후 while 무한루프...
		CYAN; gotoxy(0, 13); CLEAR_LINE;
		gotoxy(24, 13); printf("올바른 이름을 입력해주세요!");
		BLACK; gotoxy(24, 12); CLEAR_LINE;
		gotoxy(24, 12); printf("이    름 : ");
	}

	BLACK;
	gotoxy(0, 13); CLEAR_LINE;
	gotoxy(24, 14); printf("주    소 : ");
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
		gotoxy(24, 15); printf("주소를 입력해주세요!");
		BLACK; gotoxy(0, 14); CLEAR_LINE;
		gotoxy(24, 14); printf("주    소 : ");
	}
	gotoxy(0, 15); CLEAR_LINE;

	BLACK;
	gotoxy(24, 16); printf("000-0000-0000형식으로 입력해주세요\n");
	gotoxy(24, 17); printf("전화번호 : ");
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
		gotoxy(24, 18); printf("전화번호를 입력해주세요!");
		BLACK; gotoxy(0, 17); CLEAR_LINE;
		gotoxy(24, 17); printf("전화번호 : ");
	}
	phoneFormCheck(curMemberNum,18);

	curMemberNum++;// 현재 저장된 총 멤버 수 ++
	CYAN; gotoxy(30, 21); printf("등 록 완 료 !");
	getch();
	showMenu();
}

/*
보조함수 phoneFormCheck
전화번호가 올바른 형식으로 입력되었는지 확인한다 
입력 : memberId, 오류메시지를 출력할 위치의 y좌표
*/
void phoneFormCheck(int memberId, int y_position) 
{
	unsigned int i;

	while (1)
	{
		// 숫자, - 만 입력될 수 있도록 한다
		for (i = 0; i < strlen(member[memberId].phone) - 1; i++)
		{
			if (!(member[memberId].phone[i] >= '0' && member[memberId].phone[i] <= '9')
				&& member[memberId].phone[i] != '-')
				break;
		}

		// (1) -이 제위치에 있는지 확인 : 제위치에 있으면 break;
		// (2) 올바른 형식으로 입력되었는지 확인 : 올바르면 break 
		if (!(member[memberId].phone[3] != '-' || member[memberId].phone[8] != '-')
			&& i == strlen(member[memberId].phone) - 1)
			break;

		//결과적으로 break하지 못한 불행한 입력값들은 다시 입력요구
		CYAN;gotoxy(0, y_position); CLEAR_LINE;
		gotoxy(24, y_position); printf("형식에 맞추어 입력해주세요!");
		BLACK;gotoxy(0, y_position - 1); CLEAR_LINE;
		gotoxy(24, y_position-1); printf("전화번호 : ");
		fgets(member[memberId].phone, sizeof(member[memberId].phone), stdin); fflush(stdin);
	}
}

/*
3. 회원검색하기 : searchMember

매개변수 fromwhere : 메인메뉴에서 바로 검색으로 온것과, 수정/삭제 함수에서 호출한 경우에 검색 이후 수행작업 다르게
fromwhere == 0 : 메인메뉴-검색. 검색 이후 검색의 서브메뉴 출력
fromwhere == 1 : 메인메뉴-수정. 검색 이후 edit함수 호출
fromwhere == 2 : 메인메뉴-삭제. 검색 이후 delete함수 호출
*/
void searchMember(int fromwhere)
{
	system("cls");
	char choice;
	int i, j, sameCount = 0;
	int searchmemberid;//사용자가 찾고자 하는 학번
	char searchName[20];//사용자가 찾고자 하는 이름
	char searchPhone[14];//사용자가 찾고자 하는 전화번호
	int result;//문자열 비교함수 strcmp의 결과값 저장

	int sameName[100];//같은이름이면 id를 저장해둘 배열

	printSearchIndex();

	choice = getche();
	fflush(stdin);
	Beep(rand() % 200 + 300, 80);

	CYAN;
	switch (choice)
	{
	case '1':
		gotoxy(20, 13); printf("찾으실 학번 : ");
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
		gotoxy(20, 13); printf("찾으실 이름 : "); BLACK;
		fgets(searchName, sizeof(searchName), stdin);
		searchName[strlen(searchName) - 1] = '\0';
		//fgets로 받을때 엔터키('\n')까지 입력받아서 '이름\n'형식으로 들어오기때문에 마지막을 널문자로 바꿔서 저장해준다

		while (1)
		{
			//이름에 아무것도 입력하지 않고 엔터만 쳤을 경우(받을때 마지막을 \0으로 바꿨으니까 체크할때는 \0으로 체크) 
			//다시 입력받기
			if (searchName[0] == '\0')
			{
				gotoxy(20, 14); printf("이름을 입력해주세요 : ");
				fgets(searchName, sizeof(searchName), stdin);
				searchName[strlen(searchName) - 1] = '\0';
			}
			else break;
		}

		//이름 입력이 들어온 상태
		for (j = 0; j < curMemberNum; j++)
		{
			result = strcmp(searchName, member[j].name);

			//전체 리스트를 쭉 돌면서 result가 0인게 있을 때마다 sameCount를 올린다 
			if (result == 0)
			{
				sameName[sameCount] = j;
				sameCount++;
			}
		}

		//검색하는 이름과 일치하는 데이터가 2개 이상일 경우(동명이인이 있는 경우)
		if (sameCount > 1) sameNameDifferent(sameName,fromwhere,sameCount);
		else if (sameCount == 1){
			i = sameName[0];
			gotoxy(0, 16); printCertainMember(i); //동명이인 없을때
		}
		else{
			CYAN;
			gotoxy(29, 20); printf("그런 학생 없습니다");
			getch();
			showMenu();
		}
		break;

	case '3':
		gotoxy(18, 13); printf("000-0000-0000 형식에 맞추어 입력해주세요\n");
		gotoxy(18, 14); printf("찾으실 전화번호 : ");
		fgets(searchPhone, sizeof(searchPhone), stdin);
		fflush(stdin);

		//입력받은 전화번호 형식체크 : 구조체에 들어가기 전이라 phoneFormCheck함수에 넣을 Id가 없어서, 따로 체크
		while (1)
		{
			// 숫자, - 만 입력될 수 있도록 한다 : 숫자, - 가 아니면 break(형식에 맞추어 다시입력 요구)
			for (i = 0; i < (signed int)strlen(searchPhone) - 1; i++)
			{
				if (!(searchPhone[i] >= '0' && searchPhone[i] <= '9') && searchPhone[i] != '-')
					break;
			}

			// (1) -이 제위치에 있는지 확인 : 제위치에 있으면 break;
			// (2) 올바른 형식으로 입력되었는지 확인 : 올바르면 break 
			if (!(searchPhone[3] != '-' || searchPhone[8] != '-') && i == strlen(searchPhone) - 1)
				break;

			BLACK;
			gotoxy(0, 15); CLEAR_LINE;
			gotoxy(18, 15); printf("형식에 맞추어 입력해주세요!");
			CYAN;
			gotoxy(0, 14); CLEAR_LINE;
			gotoxy(18, 14); printf("찾으실 전화번호 : ");
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

	case ESC://메뉴로 돌아가기
		showMenu();
		break;

	default:
		searchMember(fromwhere);
		break;
	}

	//switch문에서 빠져나온 상태(학번, 주소검색 해당)에서 i가 뭐인지에 따라 다른 작업 수행
	CYAN;	
	if (i==curMemberNum)
	{
		gotoxy(29, 20); printf("그런 학생 없습니다"); 
		getch();
		showMenu();
	}
	else
	{
		BLACK;
		switch (fromwhere)
		{
		case 0: //메인메뉴-검색
			searchSubmenu(i);
			break;
		case 1: //메인메뉴-수정
			gotoxy(20, 21); printf("계속하시려면 아무 키나 눌러주세요 :-)");
			getch();
			editMember(i);
			break;
		case 2: //메인메뉴-삭제
			gotoxy(20, 21); printf("계속하시려면 아무 키나 눌러주세요 :-)");
			getch();
			deleteMember(i);
			break;
		default:
			break;
		}
	}
}

/*
3-0 sameName : 동명이인 처리 함수
동명이인 중에 다음 작업을 수행할 대상의 id를 리턴
*/
void sameNameDifferent(int *sameName[], int fromwhere, int sameCount)
{
	int i;
	int option = 0;//동명이인에서 고르는 것. 동명이인이 없으면 0

	for (i = 0; i < sameCount; i++)
	{
		gotoxy(0, 16 + i); printf("   [%d]", i + 1); printCertainMember(sameName[i]);
	}
	gotoxy(20, 20); printf("누구를 선택하시겠습니까? : ");
	do{
		option = getche();
		option = option - '0'; //option을 숫자로.
		option=option-1;
		if (option<0 || option>9)
		{
			option = getche();
		}
	} while (!(option >= 0 && option < sameCount)); 

	BLACK;
	switch (fromwhere)
	{
	case 0: //메인메뉴-검색
		searchSubmenu(sameName[option]);
		break;
	case 1: //메인메뉴-수정
		gotoxy(20, 21); printf("계속하시려면 아무 키나 눌러주세요 :-)");
		getch();
		editMember(sameName[option]);
		break;
	case 2: //메인메뉴-삭제
		gotoxy(20, 21); printf("계속하시려면 아무 키나 눌러주세요 :-)");
		getch();
		deleteMember(sameName[option]);
		break;
	default:
		break;
	}
}

/*
3-1 검색한 다음의 작업 결정 : searchSubmenu
*/
void searchSubmenu(int memberIdx)
{
	char selectWhatToDo;

	CYAN; gotoxy(20, 21); printf("1 삭제하기  2 수정하기  ESC 메인메뉴로\n");
	BLACK; gotoxy(20, 22); printf("다음에 할 작업을 선택해주세요 : ");
	selectWhatToDo = getche();
	Beep(rand() % 200 + 300, 80);

	switch (selectWhatToDo)
	{
	case '1'://삭제하기
		deleteMember(memberIdx);
		break;
	case '2'://수정하기
		editMember(memberIdx);
		break;
	case ESC://메인메뉴로
		showMenu();
		break;
	default://세 경우가 아닌 값이면 searchSubmenu 다시 호출
		searchSubmenu(memberIdx);
		break;
	}
}

//검색대상이 있을 경우 그 멤버 정보를 출력
void printCertainMember(int memberNum)
{
	BLACK;	
	printf("\t│%6d  │%7s │%-25s │%10s │\n",
		member[memberNum].userid, member[memberNum].name, member[memberNum].address, member[memberNum].phone);
}

/*
4. 회원수정하기 : editMember
*/
void editMember(int memberIdx)
{
	char datachoice;
	char buf[100];

	int fineInput;
	int i;

	system("cls");

	printEditIndex();
	//넘어온 데이터를 일단 출력해서 보여준다.
	gotoxy(0, 8); printCertainMember(memberIdx);

	gotoxy(54, 16); datachoice = getche();
	Beep(rand() % 200 + 300, 80);

	BLACK;
	switch (datachoice)
	{
	case '1'://이름
		gotoxy(20, 18); printf("새로운 이름을 입력하세요 : ");

		while (1)
		{
			fgets(buf, sizeof(buf), stdin);//일단 버퍼에 입력을 받는다
			fflush(stdin);
			fineInput = 0;

			while (1)//입력값이 아무것도 없으면 다시입력 요구
			{
				if (buf[0] == '\n')
				{
					fineInput = 0;
					CYAN; gotoxy(0, 19); CLEAR_LINE;
					gotoxy(20, 19); printf("이름을 입력하세요!");
					BLACK; gotoxy(0, 18); CLEAR_LINE;
					gotoxy(20, 18); printf("새로운 이름을 입력하세요 : ");
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

			// 한글입력 확인
			for (i = 0; i < (signed)strlen(member[memberIdx].name); i++)
			{
				if (member[memberIdx].name[i] >= '0' && member[memberIdx].name[i] <= '127')
				{
					fineInput = 0;//한글이 아닌 값이 member[curMemberNum].name 배열의 요소에 들어오면 fineInput값에 0을 넣는다(정상입력아님)
					break;
				}
			}

			//최종적으로 fineInput값이 0이 아니면(정상입력 상태이면) while문을 빠져나가 주소를 입력받는다
			if (fineInput) 
				break;

			CYAN; gotoxy(0, 19); CLEAR_LINE;
			gotoxy(20, 19); printf("올바른 이름을 입력해주세요!");
			BLACK; gotoxy(0, 18); CLEAR_LINE;
			gotoxy(20, 18); printf("새로운 이름을 입력하세요 : ");
		}
		break;

	case '2'://주소
		gotoxy(20, 18); printf("새로운 주소을 입력하세요 : ");
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
			gotoxy(20, 19); printf("주소를 입력해주세요!");
			BLACK; gotoxy(0, 18); CLEAR_LINE;
			gotoxy(20, 18); printf("새로운 주소을 입력하세요 : ");
		}
		break;

	case '3'://전화번호

		gotoxy(20, 18); printf("새로운 전화번호를 입력하세요 : ");
		while (1)
		{
			fgets(buf, sizeof(buf), stdin);
			fflush(stdin);

			if (buf[0] != '\n'&&strlen(buf) <= 14)//NULL값이 아니고, 버퍼수를 넘어서지 않으면 일단 해당하는 멤버의 번호칸에 입력받은 정보를 복사해넣는다.
			{
				buf[strlen(buf) - 1] = 0;
				strcpy(member[memberIdx].phone, buf);
				break;
			}
			CYAN; gotoxy(0, 19); CLEAR_LINE;
			gotoxy(20, 19); printf("전화번호를 입력해주세요!");
			BLACK; gotoxy(0, 18); CLEAR_LINE;
			gotoxy(20, 18); printf("새로운 전화번호를 입력하세요 : ");
		}
		phoneFormCheck(memberIdx,19);
		break;

	case ESC://메뉴로
		showMenu();
	default:
		editMember(memberIdx);
		break;
	}

	CYAN;
	gotoxy(20, 21); printf("학생정보가 수정되었습니다!");
	getch();
	showMenu();
}

/*
5. 회원삭제하기 : deleteMember
*/
void deleteMember(int memberIdx)
{
	int i;
	char user_choice;
	system("cls");

	printDeleteIndex(); //제목을 출력하고, 삭제여부를 물어본다.

	user_choice = getch();
	Beep(rand() % 200 + 300, 80);

	if (user_choice == 'y')
	{
		for (i = memberIdx; i < curMemberNum; i++)
		{
			member[i] = member[i + 1];
		}
		curMemberNum--;
		CYAN; gotoxy(30, 14); printf("삭제되었습니다!");
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
6. 저장하기 : saveData
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
		puts("file open error"); return;//파일을 여는 과정에서 문제가 있으면 오류메시지 출력 후 리턴(비정상종료)
	}

	//파일의 처음에 인덱스 쓰기
	fprintf(fp, "회원 아이디	회원이름	회원주소	핸드폰 번호\n");

	//구조체를 불러와서 파일에 쭉쭉 쓰기
	while (i < curMemberNum){
		fprintf(fp, "%d\t%s\t%s\t%s\n", member[i].userid, member[i].name, member[i].address, member[i].phone);
		i++;
	}

	fclose(fp);//다 쓰면 파일 닫기

	user_input = getche();
	Beep(rand() % 200 + 300, 80);

	if (user_input == ESC) showMenu();
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

	printExitIndex();
	user_input = getche();//사용자 입력을 받는다. 
	Beep(rand() % 200 + 300, 80);

	if (user_input == 'y') saveData();//사용자가 y를 입력(종료 전에 저장하고싶다)하면 저장기능으로 전환
	else if (user_input == 'n') byebyeMessage();
	else exitProgram();
}