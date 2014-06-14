#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <conio.h>
#include "member_140613.h"
#pragma warning(disable:4996)

/*
gotoxy : UI������ ���� ��ǥ �����Լ�
�Ű����� : x,y��ǥ
*/
void gotoxy(int x, int y)
{
	COORD CursorPosition = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), CursorPosition);
}

/*
textcolor : �ؽ�Ʈ�� ���� �������ִ� �Լ�
�Ű����� : �� ��ȣ
*/
void textcolor(unsigned short color)
{
	HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hcon, color);
}

#define BLACK textcolor(7)
#define CYAN textcolor(3)
#define CYAN_BACKGROUND textcolor(55) 

//���α׷� ������ �� �ȳ� �޽���
void helloMessage(void)
{
	system("title �ſ�'s MEMBERSHIP"); //�ܼ�â�� �̸� ����
	CYAN_BACKGROUND;
	gotoxy(0, 11); printf("                               NICE TO MEET YOU!                                ");
	getch(); 
	BLACK;
}

//�޴� ���ڰ� ���
void prettyMenuPrint(void)
{
	int i;
	char* menu[] = { "1  ȸ �� �� ��", "2  ȸ �� �� ��", "3  ȸ �� �� ��", "4  ȸ �� �� ��",
		"5  ȸ �� �� ��", "6  �� �� �� ��", "7  �� �� �� ��" };

	CYAN_BACKGROUND;
	gotoxy(15, 3); printf("                  ");
	gotoxy(15, 4); printf(" ȸ���������α׷� ");
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
	gotoxy(22, 9); printf("  �ȳ� �ݰ�����");
	gotoxy(22, 11); printf("����     ����");
	gotoxy(22, 12); printf("        ��       ");
	gotoxy(22, 13); printf("        ��       ");
	gotoxy(22, 14); printf(" ��           �� ");
	gotoxy(22, 15); printf("   �������  ");

	//�޴���� ���
	BLACK;
	for (i = 0; i < 7; i++)
	{
		gotoxy(45, 9 + i); puts(menu[i]);
	}

	gotoxy(26, 18); printf("���ϴ� �۾��� �������ּ���  ");

}

void printListIndex(void)
{
	CYAN_BACKGROUND;
	gotoxy(5, 1); printf("������������������������������������������������������������������");
	gotoxy(5, 2); printf("��  �й�  ��  �̸�  ��  �ּ�                    ��  ��ȭ��ȣ    ��");
	gotoxy(5, 3); printf("������������������������������������������������������������������");
	BLACK;
	gotoxy(5, 4); printf("������������������������������������������������������������������");
}

void printAddIndex(void)
{
	CYAN_BACKGROUND;
	gotoxy(18, 4); printf(" �������������������������������������� \n");
	gotoxy(18, 5); printf(" ��     ���ο� �л��� ����մϴ�     �� \n");
	gotoxy(18, 6); printf(" �������������������������������������� \n");
	BLACK;
	gotoxy(18, 8); printf("���θ޴��� ���ư��÷��� ESC�� �����ּ���");
	gotoxy(18, 9); printf("�ٸ� Ű�� ������ ����� �����մϴ� : ");
}

void printSearchIndex(void)
{
	CYAN_BACKGROUND;
	gotoxy(18, 2); printf(" �������������������������������������� \n");
	gotoxy(18, 3); printf(" ��       �л������� �˻��մϴ�      �� \n");
	gotoxy(18, 4); printf(" �������������������������������������� \n");
	BLACK;
	gotoxy(20, 6); printf("1 �й����� ã��\n");
	gotoxy(20, 7); printf("2 �̸����� ã��\n");
	gotoxy(20, 8); printf("3 ��ȭ��ȣ�� ã��\n");
	gotoxy(20, 9); printf("ESC ���θ޴��� ���ư���\n");

	gotoxy(20, 11); printf("���ϴ� �۾��� �������ּ��� : ");
}

void printDeleteIndex(void)
{
	CYAN_BACKGROUND;
	gotoxy(18, 4); printf(" �������������������������������������� \n");
	gotoxy(18, 5); printf(" ��       �л������� �����մϴ�      �� \n");
	gotoxy(18, 6); printf(" �������������������������������������� \n");
	
	BLACK;
	gotoxy(22, 10); printf("������ �����Ұſ���? (y/n) : ");
}

void printEditIndex(void)
{
	CYAN_BACKGROUND;
	gotoxy(18, 4); printf(" �������������������������������������� \n");
	gotoxy(18, 5); printf(" ��       �л������� �����մϴ�      �� \n");
	gotoxy(18, 6); printf(" �������������������������������������� \n");

	CYAN;
	gotoxy(32, 11); printf("1 ��    ��");
	gotoxy(32, 12); printf("2 ��    ��");
	gotoxy(32, 13); printf("3 ��ȭ��ȣ");

	BLACK;
	gotoxy(20, 15); printf("�����Ͻ� �����͸� �������ּ���");
	gotoxy(20, 16); printf("ESC�� ������ �޴��� ���ư��ϴ� : ");
}

void printSaveIndex(void)
{
	CYAN_BACKGROUND;
	gotoxy(18, 7); printf(" �������������������������������������� \n");
	gotoxy(18, 8); printf(" ��  ��� ��������� �����մϴ� :^)  �� \n");
	gotoxy(18, 9); printf(" �������������������������������������� \n");
	
	BLACK;
	gotoxy(19, 13); printf("���θ޴��� ���ư��÷��� ESC�� �����ּ���\n");
	gotoxy(19, 14); printf("�ٸ����� ������ ����ȭ������ ���ϴ� : ");
}

void printExitIndex(void)
{
	CYAN_BACKGROUND;
	gotoxy(18, 7); printf(" �������������������������������������� \n");
	gotoxy(18, 8); printf(" ��   �����ϱ� ���� �����Ͻðھ��?  �� \n");
	gotoxy(18, 9); printf(" �������������������������������������� \n");

	BLACK;
	gotoxy(30, 12); printf("y/n :  ");
}

//���̹���
void byebyeMessage(void)
{
	system("cls");
	CYAN;	
	gotoxy(31, 7); printf("�ȳ� �� ������!");
	gotoxy(30, 9); printf("����     ����");
	gotoxy(30, 10); printf("        ��       ");
	gotoxy(30, 11); printf("        ��       ");
	gotoxy(30, 12); printf(" ��           �� ");
	gotoxy(30, 13); printf("   �������  ");
	BLACK;
	gotoxy(18, 17); exit(0);
}