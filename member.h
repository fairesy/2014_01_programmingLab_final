#ifndef __MEMBER_H__
#define __MEMBER_H__

typedef struct student_node{
	int userid;
	char name[20];
	char address[80];
	char phone[14];
}student;


void readMemberData(void);
void showMenu(void);
void returnToMenu(void);
void viewAllMember(void);
void addNewMember(void);
void deleteMember(void);
void editMember(void);
void searchMember(void);
int saveData(void);
int exitProgram(void);
void gotoxy(int x, int y);
void memoryExtension();


#endif // !__MEMBER_H__
