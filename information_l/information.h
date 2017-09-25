#pragma once
#ifndef _INFORMATION_h_
#define _INFORMATION_h_
#include <stdbool.h>
extern int FLAG_NODE;
typedef struct _Node
{
	char account_number[256];
	char name[256];
	int acctNum;
	long int number;
	char address[100];
	double balance;
	char password[256];
	struct _Node* next;
}Node, *NodePtr;
/*typedef struct _Password
{
	char account_number[256];
	char password[256];
}Password,*PasswordPtr;*/
bool isEmpty(NodePtr list);
int insertData(NodePtr *ppNode, const char* name, const char* address, int  acctNum, long int number, double balance);
int deleteData(NodePtr *ppNode, const char* data);
Node* UpData(NodePtr fptr);
NodePtr findData(NodePtr *list, const char* name);
void printNodeInfo(const NodePtr pNode);
void Modify(NodePtr fptr);
void processList(NodePtr list);
char UserenterChoice(void);
char AdminenterChoice(void);
int  Setting(NodePtr *ppNode, const char*password);
void SysTitle();
void SysTail();
int Login();
int _Login(NodePtr *ppNode);
int information(int argc, char **argv);
int read(int argc, char **argv);
int write(int argc, char **argv);
int Persons(int argc, char **argv);
void  Create_information(int argc, char **argv);
void  readFile_information(NodePtr* list);
void  textFile_Persons(NodePtr header);
#endif