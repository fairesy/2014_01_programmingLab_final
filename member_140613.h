#ifndef __MEMBER_140613_H__
#define __MEMBER_140613_H__

//학생정보를 저장하기 위한 구조체 student 선언. 학번,이름,주소,전화번호 저장.
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
void phoneFormCheck(int memberId, int y_position);

void deleteMember(int memberIdx);
void editMember(int memberIdx);

void searchMember(int fromwhere);
void printCertainMember(int memberNum);
void searchSubmenu(int memberIdx);
void sameNameDifferent(int *sameName[],int fromwhere,int sameCount);

void saveData(void);
void exitProgram(void);

void memoryExtension();
void gotoxy(int x, int y);
void textcolor(unsigned short color);

extern void helloMessage(void);
extern void prettyMenuPrint(void);
extern void printListIndex(void);
extern void printAddIndex(void);
extern void printSearchIndex(void);
extern void printDeleteIndex(void);
extern void printEditIndex(void);
extern void printSaveIndex(void);
extern void printExitIndex(void);
extern void byebyeMessage(void);

#endif