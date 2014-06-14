#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <conio.h>
#include "member_140613.h"
#pragma warning(disable:4996)

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

#define BLACK textcolor(7)
#define CYAN textcolor(3)
#define CYAN_BACKGROUND textcolor(55) 

//프로그램 시작할 때 안녕 메시지
void helloMessage(void)
{
	system("title 신영's MEMBERSHIP"); //콘솔창의 이름 설정
	CYAN_BACKGROUND;
	gotoxy(0, 11); printf("                               NICE TO MEET YOU!                                ");
	getch(); 
	BLACK;
}

//메뉴 예쁘게 출력
void prettyMenuPrint(void)
{
	int i;
	char* menu[] = { "1  회 원 보 기", "2  회 원 등 록", "3  회 원 검 색", "4  회 원 수 정",
		"5  회 원 삭 제", "6  저 장 하 기", "7  종 료 하 기" };

	CYAN_BACKGROUND;
	gotoxy(15, 3); printf("                  ");
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

	CYAN;
	gotoxy(22, 9); printf("  안녕 반가워요");
	gotoxy(22, 11); printf("■■■     ■■■");
	gotoxy(22, 12); printf("        ■       ");
	gotoxy(22, 13); printf("        ■       ");
	gotoxy(22, 14); printf(" ■           ■ ");
	gotoxy(22, 15); printf("   ■■■■■■  ");

	//메뉴목록 출력
	BLACK;
	for (i = 0; i < 7; i++)
	{
		gotoxy(45, 9 + i); puts(menu[i]);
	}

	gotoxy(26, 18); printf("원하는 작업을 선택해주세요  ");

}

void printListIndex(void)
{
	CYAN_BACKGROUND;
	gotoxy(5, 1); printf("┌────┬────┬─────────────┬───────┐");
	gotoxy(5, 2); printf("│  학번  │  이름  │  주소                    │  전화번호    │");
	gotoxy(5, 3); printf("└────┴────┴─────────────┴───────┘");
	BLACK;
	gotoxy(5, 4); printf("┌────┬────┬─────────────┬───────┐");
}

void printAddIndex(void)
{
	CYAN_BACKGROUND;
	gotoxy(18, 4); printf(" ┌─────────────────┐ \n");
	gotoxy(18, 5); printf(" │     새로운 학생을 등록합니다     │ \n");
	gotoxy(18, 6); printf(" └─────────────────┘ \n");
	BLACK;
	gotoxy(18, 8); printf("메인메뉴로 돌아가시려면 ESC을 눌러주세요");
	gotoxy(18, 9); printf("다른 키를 누르면 등록을 진행합니다 : ");
}

void printSearchIndex(void)
{
	CYAN_BACKGROUND;
	gotoxy(18, 2); printf(" ┌─────────────────┐ \n");
	gotoxy(18, 3); printf(" │       학생정보를 검색합니다      │ \n");
	gotoxy(18, 4); printf(" └─────────────────┘ \n");
	BLACK;
	gotoxy(20, 6); printf("1 학번으로 찾기\n");
	gotoxy(20, 7); printf("2 이름으로 찾기\n");
	gotoxy(20, 8); printf("3 전화번호로 찾기\n");
	gotoxy(20, 9); printf("ESC 메인메뉴로 돌아가기\n");

	gotoxy(20, 11); printf("원하는 작업을 선택해주세요 : ");
}

void printDeleteIndex(void)
{
	CYAN_BACKGROUND;
	gotoxy(18, 4); printf(" ┌─────────────────┐ \n");
	gotoxy(18, 5); printf(" │       학생정보를 삭제합니다      │ \n");
	gotoxy(18, 6); printf(" └─────────────────┘ \n");
	
	BLACK;
	gotoxy(22, 10); printf("정말로 삭제할거에요? (y/n) : ");
}

void printEditIndex(void)
{
	CYAN_BACKGROUND;
	gotoxy(18, 4); printf(" ┌─────────────────┐ \n");
	gotoxy(18, 5); printf(" │       학생정보를 수정합니다      │ \n");
	gotoxy(18, 6); printf(" └─────────────────┘ \n");

	CYAN;
	gotoxy(32, 11); printf("1 이    름");
	gotoxy(32, 12); printf("2 주    소");
	gotoxy(32, 13); printf("3 전화번호");

	BLACK;
	gotoxy(20, 15); printf("수정하실 데이터를 선택해주세요");
	gotoxy(20, 16); printf("ESC을 누르면 메뉴로 돌아갑니다 : ");
}

void printSaveIndex(void)
{
	CYAN_BACKGROUND;
	gotoxy(18, 7); printf(" ┌─────────────────┐ \n");
	gotoxy(18, 8); printf(" │  모든 변경사항을 저장합니다 :^)  │ \n");
	gotoxy(18, 9); printf(" └─────────────────┘ \n");
	
	BLACK;
	gotoxy(19, 13); printf("메인메뉴로 돌아가시려면 ESC을 눌러주세요\n");
	gotoxy(19, 14); printf("다른값을 누르면 종료화면으로 갑니다 : ");
}

void printExitIndex(void)
{
	CYAN_BACKGROUND;
	gotoxy(18, 7); printf(" ┌─────────────────┐ \n");
	gotoxy(18, 8); printf(" │   종료하기 전에 저장하시겠어요?  │ \n");
	gotoxy(18, 9); printf(" └─────────────────┘ \n");

	BLACK;
	gotoxy(30, 12); printf("y/n :  ");
}

//바이바이
void byebyeMessage(void)
{
	system("cls");
	CYAN;	
	gotoxy(31, 7); printf("안녕 또 만나요!");
	gotoxy(30, 9); printf("■■■     ■■■");
	gotoxy(30, 10); printf("        ■       ");
	gotoxy(30, 11); printf("        ■       ");
	gotoxy(30, 12); printf(" ■           ■ ");
	gotoxy(30, 13); printf("   ■■■■■■  ");
	BLACK;
	gotoxy(18, 17); exit(0);
}