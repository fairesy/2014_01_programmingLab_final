#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <conio.h>
#include "member.h"
#pragma warning(disable:4996)

#define MAX_SIZE 50

static int curMemberNum; //현재 저장된 총 멤버 수
static int nowMemberNum; //학번 자동생성을 위해 가장 큰 학번 저장
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
	system("title 신영's MEMBERSHIP"); //콘솔창의 이름 설정
	char choice;
	int i;

	char* menu[] = { "1  회 원 보 기", "2  회 원 등 록", "3  회 원 검 색", "4  저 장 하 기", "5  종 료 하 기" };

	//예쁜 화면.......ㅎ.....
	textcolor(55);
	gotoxy(15, 4); printf(" 회원관리프로그램 ");
	gotoxy(15, 5); printf("                                                  ");
	gotoxy(15, 6); printf(" "); gotoxy(64, 6); printf(" ");
	gotoxy(15, 7); printf(" "); gotoxy(64, 7); printf(" ");
	gotoxy(15, 8); printf(" "); gotoxy(64, 8); printf(" ");
	gotoxy(15, 9); printf(" "); gotoxy(64, 9); printf(" ");
	gotoxy(15, 10); printf(" "); gotoxy(64, 10); printf(" ");
	gotoxy(15, 11); printf(" "); gotoxy(64, 11); printf(" ");
	gotoxy(15, 12); printf(" "); gotoxy(64, 12); printf(" ");
	gotoxy(15, 13); printf(" "); gotoxy(64, 13); printf(" ");
	gotoxy(15, 14); printf(" "); gotoxy(64, 14); printf(" ");
	gotoxy(15, 15); printf(" "); gotoxy(64, 15); printf(" ");
	gotoxy(15, 16); printf(" "); gotoxy(64, 16); printf(" ");
	gotoxy(15, 17); printf(" "); gotoxy(64, 17); printf(" ");
	gotoxy(15, 18); printf(" "); gotoxy(64, 18); printf(" ");
	gotoxy(15, 19); printf(" "); gotoxy(64, 19); printf(" ");
	gotoxy(15, 20); printf("                                                  ");
	gotoxy(47, 21); printf(" 2014_1_shinyoung ");

	textcolor(3);
	gotoxy(22, 8); printf("  안녕 반가워요");
	gotoxy(22, 10); printf("■■■     ■■■");
	gotoxy(22, 11); printf("        ■       ");
	gotoxy(22, 12); printf("        ■       ");
	gotoxy(22, 13); printf(" ■           ■ ");
	gotoxy(22, 14); printf("   ■■■■■■  ");

	//메뉴목록 출력
	textcolor(7);
	for (i = 0; i < 5; i++)
	{
		gotoxy(45, 10 + i); puts(menu[i]); 
	}

	gotoxy(26, 18); printf("원하는 작업을 선택해주세요  ");
	choice = getche(); //getche() : 한글자만 입력받아, 화면에 입력받은 글자를 보여준다.
	Beep(rand() % 200 + 300, 80);
	switch (choice)
	{
	case '1':
		printAll();
		break;
	case '2':
		addNewMember();
		break;
	case '3':
		searchMember();
		break;
	case '4':
		saveData();
		break;
	case '5':
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
	Beep(rand() % 200 + 300, 80);
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

/*
memoryExtension : 메모리가 꽉 차면 메모리를 2배로 확장한다. 
*/
void memoryExtension(void)
{
#define MAX_SIZE = MAX_SIZE * 2;
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

		if (ch == 'b')//이전
		{
			if (curPageNum == 1) continue;//현재 1페이지에 있으면 이전페이지 없음
			printPage(--curPageNum, lastPageNum);
		}
		else if (ch == 'n')//다음
		{
			if (curPageNum == lastPageNum) continue;//현재 마지막페이지에 있으면 다음페이지 없음 
			printPage(++curPageNum, lastPageNum);
		}
		else if (ch == '0')//메인메뉴로
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
	
	if (curPageNum == lastPageNum)
	{
		end = curMemberNum;
	}

	textcolor(55);
	gotoxy(5, 1); printf("┌────┬────┬─────────────┬───────┐");
	gotoxy(5, 2); printf("│  학번  │  이름  │  주소                    │  전화번호    │");
	gotoxy(5, 3); printf("└────┴────┴─────────────┴───────┘");
	textcolor(7);

	gotoxy(5, 4); printf("┌────┬────┬─────────────┬───────┐");
	for (i = start; i < end; i++)
	{
		gotoxy(5, 5+j); printf("│%6d  │%7s │%-25s │%10s │",
			member[i].userid, member[i].name, member[i].address, member[i].phone);
		j++;
	}
	gotoxy(5, j+5); printf("└────┴────┴─────────────┴───────┘");
	textcolor(3);
	gotoxy(5, 23); printf("   <이전페이지(b)          메인메뉴로(0)          (n)다음페이지>");

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

	textcolor(55);
	gotoxy(18, 4); printf(" ┌─────────────────┐ \n");
	gotoxy(18, 5); printf(" │     새로운 학생을 등록합니다     │ \n");
	gotoxy(18, 6); printf(" └─────────────────┘ \n");
	textcolor(7); printf("\n");

	// 새로운 학생정보를 입력받는다. 입력되는 값이 아무것도 없으면 입력값이 있을때까지 입력을 요구한다.
	// 버퍼값만큼의 범위 안에 들어가는지 확인. 지정된 버퍼에 넣을 수 없는 큰 값을 입력하면 다시입력받는다.
	
	member[curMemberNum].userid = nowMemberNum++;
	textcolor(7);
	printf("			학    번 : %d\n", member[curMemberNum].userid); //학번은 자동생성
	fflush(stdin);

	printf("\n			이    름 : ");
	while (1)
	{
		fgets(buf, sizeof(buf), stdin);
		chk = 0; //정상입력상태인지 체크해주기 위한 변수 chk. chk=1이면 정상 입력 상태

		//여하간 뭔가가 입력되었고, 버퍼 크기를 벗어나지 않으면 -> 일단 구조체 해당 칸에 복사해넣기
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
				chk = 0;//한글이 아닌 값이 member[curMemberNum].name 배열의 요소에 들어오면 chk값에 0을 넣는다(=정상입력아님)
				break; 
			}
		}

		if (chk) //최종적으로 chk값이 0이 아니면(정상입력 상태이면) while문을 빠져나가 주소를 입력받는다
			break;

		//아니면 다시 입력하라는 메시지 출력후 while 무한루프...
		textcolor(3);
		printf("		  올바른 이름을 입력해주세요 :");
	}
	
	textcolor(7);
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
		textcolor(3);
		printf("		  주소를 입력해주세요 :"); 
	}
	
	textcolor(7);
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
		textcolor(3);
		printf("		  전화번호를 입력해주세요 :"); 
	}
	phoneFormCheck(curMemberNum);

	curMemberNum++;// 현재 저장된 총 멤버 수 ++
	showMenu();
}

void phoneFormCheck(int memberId) //전화번호를 올바른 형식으로 입력하도록 한다 
{
	int i;

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
		textcolor(3);
		printf("		  형식에 맞추어 입력해주세요 : "); 
		fgets(member[memberId].phone, sizeof(member[memberId].phone), stdin); fflush(stdin);
	}
}

/*
3. 회원삭제하기 : deleteMember
*/
void deleteMember(int memberIdx)
{
	int i;
	char user_choice;

	system("cls");
	textcolor(55);
	gotoxy(18, 4); printf(" ┌─────────────────┐ \n");
	gotoxy(18, 5); printf(" │       학생정보를 삭제합니다      │ \n");
	gotoxy(18, 6); printf(" └─────────────────┘ \n");
	textcolor(7);

	gotoxy(22, 10); printf("정말로 삭제할거에요? (y/n) : ");
	user_choice = getche();
	if (user_choice == 'y')
	{
		for (i = memberIdx; i < curMemberNum; i++)
		{
			member[i] = member[i + 1];
		}
		curMemberNum--;
		textcolor(3);
		gotoxy(30, 14); printf("삭제되었습니다!");
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
4. 회원수정하기 : editMember
*/
void editMember(int memberIdx)
{
	char datachoice;
	int newid;
	char buf[80];
	char newname[10];
	char newaddress[80];
	char phone[14];

	int chk = 0;
	int i;

	system("cls");
	textcolor(55);
	gotoxy(18, 4); printf(" ┌─────────────────┐ \n");
	gotoxy(18, 5); printf(" │       학생정보를 수정합니다      │ \n");
	gotoxy(18, 6); printf(" └─────────────────┘ \n");
	textcolor(7);

	gotoxy(3, 8); printCertainMember(memberIdx);
	gotoxy(32, 11); printf("1 이    름");
	gotoxy(32, 12); printf("2 주    소");
	gotoxy(32, 13); printf("3 전화번호");
	gotoxy(20, 15); printf("수정하실 데이터를 선택해주세요");
	gotoxy(20, 16); printf("0을 누르면 메뉴로 돌아갑니다 : ");
	datachoice = getche();
	printf("\n\n");

	textcolor(3);
	switch (datachoice)
	{
	case '1'://이름
		printf("\t\t    새로운 이름을 입력하세요 : ");

		while (1)
		{
			fgets(buf, sizeof(buf), stdin);//일단 버퍼에 입력을 받는다
			chk = 0; //정상입력상태인지 체크해주기 위한 변수 chk. chk=1이면 정상 입력 상태

			if (buf[0] != '\n' && strlen(buf) < 10)
			{
				buf[strlen(buf) - 1] = 0;
				strcpy(member[memberIdx].name, buf);
				fflush(stdin);
				chk = 1;
			}

			// 한글입력 확인
			for (i = 0; i < strlen(member[memberIdx].name); i++)
			{
				if (member[memberIdx].name[i] >= '0' && member[memberIdx].name[i] <= '127')
				{
					chk = 0;//한글이 아닌 값이 member[curMemberNum].name 배열의 요소에 들어오면 chk값에 0을 넣는다(정상입력아님)
					break;
				}
			}

			if (chk) //최종적으로 chk값이 0이 아니면(정상입력 상태이면) while문을 빠져나가 주소를 입력받는다
				break;

			printf("			올바른 이름을 입력해주세요 :");
		}

		break;

	case '2'://주소
		printf("\t\t    새로운 주소을 입력하세요 : ");
		while (1)
		{
			fgets(buf, sizeof(buf), stdin);
			if (buf[0] != '\n'&&strlen(buf) <= 80)
			{
				buf[strlen(buf) - 1] = 0;
				strcpy(member[memberIdx].address, buf);
				fflush(stdin);
				break;
			}
			printf("			주소를 입력해주세요 :");
		}
		break;


	case '3'://전화번호

		printf("\t\t    새로운 전화번호를 입력하세요 : ");

		while (1)
		{
			fgets(buf, sizeof(buf), stdin);
			if (buf[0] != '\n'&&strlen(buf) <= 14)//NULL값이 아니고, 버퍼수를 넘어서지 않으면 일단 해당하는 멤버의 번호칸에 입력받은 정보를 복사해넣는다.
			{
				buf[strlen(buf) - 1] = 0;
				strcpy(member[memberIdx].phone, buf);
				fflush(stdin);
				break;
			}
			printf("			전화번호를 입력해주세요 :");
		}
		phoneFormCheck(memberIdx);

		break;

	case '0'://메뉴로
		showMenu();
	default:
		editMember(memberIdx);
		break;
	}
	textcolor(7);
	printf("\n\t\t\t학생정보가 수정되었습니다!");
	getch();
	showMenu();
}

/*
5. 회원검색하기 : searchMember
*/

void searchMember(void)
{
	system("cls");
	char choice;
	int i;
	int searchmemberid;//사용자가 찾고자 하는 학번
	char searchName[20];//사용자가 찾고자 하는 이름
	char searchPhone[14];//사용자가 찾고자 하는 전화번호
	int result;//문자열 비교함수 strcmp의 결과값 저장

	textcolor(55);
	gotoxy(18, 4); printf(" ┌─────────────────┐ \n");
	gotoxy(18, 5); printf(" │       학생정보를 검색합니다      │ \n");
	gotoxy(18, 6); printf(" └─────────────────┘ \n");
	
	textcolor(7);
	gotoxy(20, 8); printf("1 학번으로 찾기\n");
	gotoxy(20, 9); printf("2 이름으로 찾기\n");
	gotoxy(20, 10); printf("3 전화번호로 찾기\n");
	gotoxy(20, 11); printf("4 메인메뉴로 돌아가기\n");

	gotoxy(20, 13); printf("원하는 작업을 선택해주세요 : ");
	choice = getche();
	Beep(rand() % 200 + 300, 80);

	printf("\n\n");
	textcolor(3);
	switch (choice)
	{
	case '1':
		printf("		    찾으실 학번 : "); 
		scanf("%d", &searchmemberid);

		for (i = 0; i < curMemberNum; i++)
		{
			if (searchmemberid==member[i].userid)
			{
				printCertainMember(i);
				break;
			}
		}

		break;

	case '2':
		printf("		    찾으실 이름 : "); 
		fgets(searchName, sizeof(searchName), stdin);
		searchName[strlen(searchName) - 1] = '\0'; 
		//fgets로 받을때 엔터키('\n')까지 입력받아서 '이름\n'형식으로 들어오기때문에 마지막을 널문자로 바꿔서 저장해준다

		for (i = 0; i < curMemberNum; i++)
		{
			result = strcmp(searchName, member[i].name);
			if (result == 0) 
			{
				printCertainMember(i);
				break;
			}
		}
		break;

	case '3':
		printf("		    000-0000-0000 형식에 맞추어 입력해주세요\n");
		printf("		    찾으실 전화번호 : "); 
		fgets(searchPhone, sizeof(searchPhone), stdin);
		fflush(stdin);
		
		//입력받은 전화번호 형식체크 : 구조체에 들어가기 전이라 phoneFormCheck함수에 넣을 Id가 없어서, 따로 체크
		while (1)
		{
			// 숫자, - 만 입력될 수 있도록 한다 : 숫자, - 가 아니면 break(형식에 맞추어 다시입력 요구)
			for (i = 0; i < strlen(searchPhone) - 1; i++)
			{
				if (!(searchPhone[i] >= '0' && searchPhone[i] <= '9') && searchPhone[i] != '-')
					break;
			}

			// (1) -이 제위치에 있는지 확인 : 제위치에 있으면 break;
			// (2) 올바른 형식으로 입력되었는지 확인 : 올바르면 break 
			if (!(searchPhone[3] != '-' || searchPhone[8] != '-')&& i == strlen(searchPhone) - 1)
				break;

			textcolor(3);
			printf("		  형식에 맞추어 입력해주세요 : ");
			fgets(searchPhone, sizeof(searchPhone), stdin);
			fflush(stdin);
		}

		for (i = 0; i < curMemberNum; i++)
		{
			result = strcmp(searchPhone,member[i].phone);
			if (result == 0)
			{
				printCertainMember(i);
				break;
			}
		}
		break;

	case '4'://메뉴로 돌아가기
		showMenu();
		break;

	default:
		searchMember();
		break;
	}

	//switch문에서 빠져나온 상태에서 i가 뭐인지에 따라 다른 작업 수행
	textcolor(7);
	if (i == curMemberNum){
		printf("\n		    그런 학생 없습니다");
		getch();
		showMenu();
	}
	else
	{
		searchSubmenu(i);
	}
}

/*
5-1 검색한 다음의 작업 결정 : searchSubmenu
*/
void searchSubmenu(int memberIdx)
{
	char selectWhatToDo;

	textcolor(3);
	gotoxy(10, 19);
	printf("\n\t\t   1 삭제하기  2 수정하기  3 메인메뉴로\n\n");
	textcolor(7);
	printf("\t\t    다음에 할 작업을 선택해주세요 : ");
	selectWhatToDo = getche();

	switch (selectWhatToDo)
	{
	case '1'://삭제하기
		deleteMember(memberIdx);
		break;
	case '2'://수정하기
		editMember(memberIdx);
		break;
	case '3'://메인메뉴로
		showMenu();
		break;
	default://1-3이 아닌 값이면 searchSubmenu 다시 호출
		gotoxy(10, 18);
		searchSubmenu(memberIdx);
		break;
	}
}

//검색대상이 있을 경우 그 멤버 정보를 출력
void printCertainMember(int memberNum)
{
	textcolor(7);
	printf("\n\t│%6d  │%7s │%-25s │%10s │\n\n",
		member[memberNum].userid, member[memberNum].name, member[memberNum].address, member[memberNum].phone);
}

/*
6. 저장하기 : saveData
*/
void saveData(void)
{
	char user_input;
	int i = 0;

	system("cls");
	textcolor(55);
	gotoxy(18, 7); printf(" ┌─────────────────┐ \n");
	gotoxy(18, 8); printf(" │  모든 변경사항을 저장합니다 :^)  │ \n");
	gotoxy(18, 9); printf(" └─────────────────┘ \n");
	textcolor(7);

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
	textcolor(55);
	gotoxy(18, 7); printf(" ┌─────────────────┐ \n");
	gotoxy(18, 8); printf(" │   종료하기 전에 저장하시겠어요?  │ \n");
	gotoxy(18, 9); printf(" └─────────────────┘ \n");
	textcolor(7);
	gotoxy(30, 12); printf("y/n :  ");
	user_input = getche();//사용자 입력을 받는다. getche() : 한글자만 입력받고, 입력받은 문자를 화면에 보여준다.
	Beep(rand() % 200 + 300, 80);

	if (user_input == 'y') saveData();//사용자가 y를 입력(종료 전에 저장하고싶다)하면 저장기능으로 전환
	else if (user_input == 'n')//사용자가 n을 입력하면 그대로 종료
	{
		//바이바이
		system("cls");
		textcolor(3);
		gotoxy(31, 7); printf("안녕 또 만나요!");
		gotoxy(30, 9); printf("■■■     ■■■");
		gotoxy(30, 10); printf("        ■       ");
		gotoxy(30, 11); printf("        ■       ");
		gotoxy(30, 12); printf(" ■           ■ ");
		gotoxy(30, 13); printf("   ■■■■■■  ");
		textcolor(7);
		gotoxy(18, 17); exit(0);
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

/*
textcolor : 텍스트에 색을 설정해주는 함수
매개변수 : 색 번호
*/
void textcolor(unsigned short color)
{
	HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hcon, color);
}