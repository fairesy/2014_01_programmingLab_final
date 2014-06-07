#ifndef __MEMBER_H__
#define __MEMBER_H__

typedef struct student_node{
	int userid;
	char name[10];
	char address[80];
	char phone[14];
}student;


void readMemberData(void);
void showMenu(void);
void returnToMenu(void);

void printAll(void);
void printPage(int curPageNum, int lastPageNum);

void addNewMember(void);
void phoneFormCheck(int memberId);

void deleteMember(int memberIdx);
void editMember(int memberIdx);

void searchMember(void);
void printCertainMember(int memberNum);
void searchSubmenu(int memberIdx);


void saveData(void);
void exitProgram(void);

void gotoxy(int x, int y);
void memoryExtension();
void textcolor(unsigned short color);


#endif // !__MEMBER_H__
