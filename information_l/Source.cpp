#include <stdio.h>
#include<cstdlib>
#include<cstring>
#include<cstdio>
#include"information.h"
#include<conio.h>
#include<stdlib.h>
#include<string.h>
#include <my_global.h>
#include <mysql.h>
#define MAX 256
int FLAG_NODE;
bool isEmpty(NodePtr list)
{
	return list == 0;
}
int  Setting(NodePtr *ppNode, const char*password)//注册账户和密码
{
	NodePtr pCurNode = *ppNode;
	NodePtr pNode = *ppNode;
	int choose = 0;
	int Admin = 1;
	char name[10];
	printf("\t\t\t如果注册新的账号和密码，请输入1\n");
	printf("\t\t\t\t");
	scanf("%d", &choose);
	if (choose == 1)
	{
		while (pNode != NULL)
		{
			if (pNode->account_number == name)
			{
				printf("\t\t这个用户的信息已经存在!\n");
				return -1;
			}
			pNode = pNode->next;
		}
		if (pCurNode == 0) //表为空的情况（插入节点位置为空）
		{
			*ppNode = (NodePtr)malloc(sizeof(Node));
			memset(*ppNode, 0, sizeof(Node));
			pCurNode = *ppNode;
		}
		else
		{
			Node* pNewNode = (Node*)malloc(sizeof(Node));
			memset(pNewNode, 0, sizeof(Node));
			pNewNode->next = pCurNode->next;
			pCurNode->next = pNewNode;
			pCurNode = pNewNode;
		}
		if (choose == 1)
		{
			printf("\t\t-----------注册您当前用账号和密码-----------\n");
			printf("\t\t------------------注册账号为----------------\n");
			printf("\t\t\t\t");
			scanf("%s", name);
			printf("\t\t------------------注册密码为----------------\n");
			printf("\t\t\t\t");
			scanf("%s", password);
			printf("\t\t------------------注册完毕------------------\n");
			strcpy(pCurNode->account_number, name);
			strcpy(pCurNode->password, password);
		}
	}
	else
	{
		return -1;
	}
}
int insertData(NodePtr *ppNode, const char* name, const char* address, int  acctNum, long int number, double balance)
{
	NodePtr pCurNode = *ppNode;
	NodePtr pNode = *ppNode;
	while (pNode != NULL && FLAG_NODE == 1)
	{
		if (pNode->acctNum == acctNum)
		{
			printf("\t\t这个用户的信息已经存在!\n");
			return -1;
		}
		pNode = pNode->next;
	}
	if (pCurNode == 0) //表为空的情况（插入节点位置为空）
	{
		*ppNode = (NodePtr)malloc(sizeof(Node));
		memset(*ppNode, 0, sizeof(Node));
		pCurNode = *ppNode;
	}
	else
	{
		Node* pNewNode = (Node*)malloc(sizeof(Node));
		memset(pNewNode, 0, sizeof(Node));
		while (pCurNode->next != 0)//从尾部插入
		{
			pCurNode = pCurNode->next;
		}
		pCurNode->next = pNewNode;
		pNewNode->next = 0;
		pCurNode = pNewNode;
	}
	pCurNode->acctNum = acctNum;
	strcpy(pCurNode->name, name);
	pCurNode->number = number;
	strcpy(pCurNode->address, address);
	pCurNode->balance = balance;
	return 0;
}
int deleteData(NodePtr *ppNode, const char* data)//删除用户信息
{
	if (ppNode == 0 || *ppNode == 0)
	{
		printf("\t\t\t没有要删除的账户信息 !\n");
		return -1;
	}
	NodePtr pNode = *ppNode;
	NodePtr preNode = 0;
	while (pNode != 0)
	{
		if (strcmp(pNode->name, data) == 0)
		{
			if (preNode == 0)
			{
				*ppNode = (*ppNode)->next;
			}
			else
			{
				preNode->next = pNode->next;
			}
			free(pNode);
			printf("\t\t\t删除成功\n");
			return 0;
		}
		preNode = pNode;
		pNode = pNode->next;
	}
	printf("\t\t\t没有要删除的账户信息 !\n");
	return 0;
}
Node* UpData(NodePtr fptr)//更新用户信息
{
	int acctNum;
	char name;
	double transaction;
	NodePtr fpptr = fptr;
	printf("\t\t输入需要更新的用户编码 ( 1 - 100 ): ");
	scanf("%d", &acctNum);
	while (fpptr != NULL)
	{
		if (fpptr->acctNum == acctNum)
		{
			fputs("\t\tinput** 客户编号**姓名**地址**手机号码**余额:\n", stdout);
			printf("\t\t%-6d%-10s%-10s%-8ld%10.2f\n\n", fpptr->acctNum, fpptr->name, fpptr->address, fpptr->number, fpptr->balance);
			printf("\t\t请输入存款 ( + ) 或者 取款( - ): ");
			scanf("%lf", &transaction);
			fpptr->balance += transaction;
			fputs("\t\t用户编码**姓名**地址**手机号码**余额:\n", stdout);
			printf("\t\t%-6d%-10s%-10s%-8ld%10.2f\n", fpptr->acctNum, fpptr->name, fpptr->address, fpptr->number, fpptr->balance);
			return fpptr;
		}
		fpptr = fpptr->next;
	}
	if (fpptr == NULL || fpptr->acctNum != acctNum)
	{
		printf("\t\t用户编码为 #%d 的信息没有找到.\n", acctNum);
		return 0;
	}
}
NodePtr findData(NodePtr *list, const char* name)//查找用户信息
{
	if (list == 0 || *list == 0)
	{
		return 0;
	}
	NodePtr plist = *list;
	while (list != 0 && plist->name != 0 && plist != 0)
	{
		if (strcmp(plist->name, name) == 0)
		{
			return plist;
		}
		plist = plist->next;
	}
	return 0;
}
void printNodeInfo(const NodePtr pNode)//显示用户信息
{
	if (pNode)
	{
		printf("\t\t寻找到的信息是:\n");
		fputs("\t\t请输入** 客户编号**姓名**地址**手机号码**余额:\n", stdout);
		printf("\t\t%d\t%s\t%s\t%ld\t%lf\n", pNode->acctNum, pNode->name, pNode->address, pNode->number, pNode->balance);
	}
}
void Modify(NodePtr fptr)//修改用户信息
{
	char name[10] = { '0' };
	long int number = 1;
	char address[20] = { '0' };
	NodePtr fpptr = fptr;
	printf("\t\t\t输入要修改人的名字：\n");
	printf("\t\t\t\t");
	scanf("%s", &name);
	int ret = (int)findData(&fpptr, name);//找到要修改信息的联系人  
	if (ret != 0)
	{
		printf("\t\t\t请输入修改后的地址：\n");
		printf("\t\t\t\t");
		scanf("%s", &fpptr->address);
		printf("\t\t\t请输入修改后的手机号：\n");
		printf("\t\t\t\t");
		scanf("%ld", &fpptr->number);
		printf("\t\t\t修改信息成功！\n");
	}
	else
		printf("\t\t\t修改信息失败！\n");
}
/*void textFile(NodePtr header)//保存文本的作用
{
	FILE *writePtr;
	int num = 100;
	NodePtr temp = header;
	if ((writePtr = fopen("accounts.dat", "w+")) == NULL)
		printf("File could not be opened.\n");
	else
	{
		int count = 0;
		while (temp != NULL)
		{
			fseek(writePtr, count*sizeof(Node), SEEK_SET);
			fwrite(temp, sizeof(Node), 1, writePtr);
			temp = temp->next;
			count++;
		}
		fclose(writePtr);
	}
}*/
/*void  readFile(NodePtr* list)
{
	FILE *readPtr = fopen("accounts.dat", "r+");
	Node *curnode = (NodePtr)malloc(sizeof(Node));
	memset(curnode, 0, sizeof(Node));
	fseek(readPtr, 0, SEEK_SET);
	int i = 0;
	while (feof(readPtr) == 0)
	{
		fseek(readPtr, i*sizeof(Node), SEEK_SET);
		int ret = fread(curnode, sizeof(Node), 1, readPtr);
		if (curnode->acctNum == 0)
			continue;
		if (ret != 1)
			break;
		insertData(list, curnode->name, curnode->address, curnode->acctNum, curnode->number, curnode->balance);
		i++;
	}
	fclose(readPtr);
}*/
int Login()//管理员账号密码登录
{
	char account_number[10];
	char password[10];
	char s_name[10] = "111";/*管理员初始密码*/
	char s_password[10] = "666";
	for (int i = 1; i <= 3; i++)
	{
		printf("\t\t------------------请输入账号----------------\n");
		printf("\t\t\t\t");
		scanf("%s", account_number);
		if (strcmp(s_name, account_number) == 0)
		{
			printf("\t\t------------------请输入密码----------------\n");
			printf("\t\t\t\t");
			scanf("%s", &password);
			if (strcmp(s_password, password) == 0)
			{
				printf("\t\t------------------登录成功------------------\n");
				return 1;
			}
			else
			{
				printf("\t\t------------------登录失败------------------\n");
			}
		}
	}
	printf("\t\t-----------已经输入三次错误信息，请稍后再试-----------");
	void SysTitle();
	return -1;
}
int _Login(NodePtr *ppNode)//用户账号密码登录
{
	char account_number[10];
	char password[10];
	char s_name[10];
	char s_password[10];
	NodePtr fptr = *ppNode;
	for (int i = 1; i <= 3; i++)
	{
		printf("\t\t------------------请输入账号----------------\n");
		printf("\t\t\t\t\t");
		scanf("%s", &s_name);
		while (fptr)
		{
			if (strcmp(fptr->account_number, s_name) == 0)
			{
				printf("\t\t------------------请输入密码----------------\n");
				printf("\t\t\t\t\t");
				scanf("%s", &s_password);
				if (strcmp(fptr->password, s_password) == 0)
				{
					printf("\t\t------------------登录成功------------------\n");
					return 1;
				}
				else
				{
					printf("\t\t------------------登录失败------------------\n");
				}
				break;
			}
			fptr = fptr->next;
		}
		if (fptr == NULL)
		{
			printf("\t\t\t\t该用户不存在\n");
		}
	}
	printf("\t\t------已经输入三次错误信息，请稍后再试--------");
	void SysTitle();
	return -1;
}
void processList(NodePtr list)//显示存入的内容
{
	//遍历单链表，输出数据
	Node* pNode = list;
	while (pNode != 0)
	{
		if (pNode->acctNum != 0)
		{
			printf("\t\t\t%d\t%s\t%s\t%ld\t%lf\n", pNode->acctNum, pNode->name, pNode->address, pNode->number, pNode->balance);
		}
		pNode = pNode->next;
	}
	fputs("\n", stdout);
}
void SysTitle()//开始界面
{
	printf("\n \n"
		"\t\t\t_____________________________\n"
		"\t\t\t*                           *\n"
		"\t\t\t*         欢迎使用          *\n"
		"\t\t\t*                           *\n"
		"\t\t\t*      用户信息管理系统     *\n"
		"\t\t\t*                           *\n"
		"\t\t\t*****************************\n");
}
char AdminenterChoice(void)//管理员主菜单
{
	char  menuChoice[256];
	system("cls");
	printf("\t\t\t_____________________________\n"
		"\t\t\t                             \n"
		"\t\t\t*********管理员主菜单********\n"
		"\t\t\t_____________________________\n"
		"\t\t\t*                           *\n"
		"\t\t\t*      1.创建新用户信息     *\n"
		"\t\t\t*      2.删除用户信息       *\n"
		"\t\t\t*      3.更新用户信息       *\n"
		"\t\t\t*      4.查找用户信息       *\n"
		"\t\t\t*      5.保存用户信息       *\n"
		"\t\t\t*      6.修改用户信息       *\n"
		"\t\t\t*      7.显示用户信息       *\n"
		"\t\t\t*      8.注册用户信息       *\n"
		"\t\t\t*      9.退出系统           *\n"
		"\t\t\t*                           *\n"
		"\t\t\t*****************************\n"
		"\t\t\t                             \n"
		"\t\t\t------请输入你要选择的功能---\n");
	printf("\t\t\t\t\t\n");
	printf("\t\t\t\t");
	scanf("%s", &menuChoice);
	if (menuChoice[0]> '0' && menuChoice[0] < '9'&&strlen(menuChoice) == 1)
	{
		return menuChoice[0];
	}
}
char UserenterChoice(void)//用户主菜单
{
	char menuChoice[256];
	system("cls");
	printf("\t\t\t_____________________________\n"
		"\t\t\t                             \n"
		"\t\t\t**********用户主菜单*********\n"
		"\t\t\t_____________________________\n"
		"\t\t\t*                           *\n"
		"\t\t\t*      1.查找用户信息       *\n"
		"\t\t\t*      2.修改用户信息       *\n"
		"\t\t\t*      3.保存用户信息       *\n"
		"\t\t\t*      4.注册用户信息       *\n"
		"\t\t\t*      5.退出系统           *\n"
		"\t\t\t*                           *\n"
		"\t\t\t*****************************\n"
		"\t\t\t                             \n"
		"\t\t\t----请输入你要选择的功能-----\n");
	printf("\t\t\t\t\t");
	scanf("%s", &menuChoice);
	if (menuChoice[0]> '0' && menuChoice[0] < '6'&&strlen(menuChoice) == 1)
	{
		return menuChoice[0];
	}
}
void SysTail()//结束界面
{
	//system("cls");
	printf("\n \n"
		"\t\t\t_____________________________\n"
		"\t\t\t*                           *\n"
		"\t\t\t*          谢谢使用         *\n"
		"\t\t\t*                           *\n"
		"\t\t\t*      用户信息管理系统     *\n"
		"\t\t\t*                           *\n"
		"\t\t\t*                           *\n"
		"\t\t\t*****************************\n");
}
void finish_with_error(MYSQL *con)
{
	fprintf(stderr, "%s\n", mysql_error(con));
	mysql_close(con);
	exit(1);
}
void  Create_information(int argc, char **argv)
{
	MYSQL *con = mysql_init(NULL);
	if (con == NULL)
	{
		fprintf(stderr, "%s\n", mysql_error(con));
		exit(1);
	}
	argv[1] = "127.0.0.1";
	argv[2] = "root";
	argv[3] = "123";
	if (mysql_real_connect(con, argv[1], argv[2], argv[3] , NULL, 0, NULL, 0) == NULL)//建立连接
	{
		fprintf(stderr, "%s\n", mysql_error(con));
		mysql_close(con);
		exit(1);
	}
	if (mysql_query(con, "CREATE DATABASE information"))//创建数据库
	{
		fprintf(stderr, "%s\n", mysql_error(con));
		mysql_close(con);
		exit(1);
	}
	mysql_close(con);
}
void  readFile_information(NodePtr* list)//读数据
{
	MYSQL *con = mysql_init(NULL);
	Node data = { 0 };
	if (con == NULL)
	{
		fprintf(stderr, "mysql_init() failed\n");
		exit(1);
	}

	if (mysql_real_connect(con, "127.0.0.1", "root", "123", "information", 0, NULL, 0) == NULL)
	{
		finish_with_error(con);
	}

	if (mysql_query(con, "SELECT * FROM Persons LIMIT 3"))
	{
		finish_with_error(con);
	}

	MYSQL_RES *result = mysql_store_result(con);

	if (result == NULL)
	{
		finish_with_error(con);
	}

	//int num_fields = mysql_num_fields(result);
	int num_fields = 5;
	MYSQL_ROW row;
	MYSQL_FIELD *field;

	while ((row = mysql_fetch_row(result)))
	{
		for (int i = 0; i < num_fields; i++)
		{
			switch (i)
			{
			case 0:
				data.acctNum = atoi(row[i]);
				break;
			case 1:
				strcpy(data.name, row[i]);
				break;
			case 2:
				strcpy(data.address, row[i]);
				break;
			case 3:
				data.number = atoi(row[i]);
				break;
			case 4:
				data.balance = atof(row[i]);
				break;
			default:
				break;
			}
		}
		insertData(list, data.name, data.address, data.acctNum, data.number, data.balance);
	}

	printf("\n");
	mysql_free_result(result);
	mysql_close(con);

}
void  textFile_Persons(NodePtr header)//将链表中的数据写入到数据库中
{
	Node *curnode = (NodePtr)malloc(sizeof(Node));
	memset(curnode, 0, sizeof(Node));
	curnode = header;
	MYSQL *con = mysql_init(NULL);
	/*argv[1] = "127.0.0.1";
	argv[2] = "root";
	argv[3] = "123";*/
	if (con == NULL)
	{
		fprintf(stderr, "%s\n", mysql_error(con));
		exit(1);
	}
	if (mysql_real_connect(con, "127.0.0.1", "root", "123","information", 0, NULL, 0) == NULL)
	{
		finish_with_error(con);
	}

	if (mysql_query(con, "DROP TABLE IF EXISTS Persons"))//建表
	{
		finish_with_error(con);
	}

	if (mysql_query(con, "CREATE TABLE Persons(AcctNum INT, Name TEXT,Address TEXT,Number INT, Balance INT)"))
	{
		finish_with_error(con);
	}
	//char cache[50] = { 0 };
	char * cache = (char*)malloc(MAX);
	memset(cache, 0, MAX);
	while (curnode != 0)
	{
		sprintf(cache, "INSERT INTO Persons VALUES('%d','%s','%s','%d','%lf')",
			curnode->acctNum, curnode->name, curnode->address, curnode->number, curnode->balance);
		if (mysql_query(con, cache))
		{
			finish_with_error(con);
		}
		curnode = curnode->next;
	}
	free(cache);
	mysql_close(con);

}
int main(int argc, char **argv)
{ 
    Create_information(argc, argv);//创建数据库
	SysTitle();
	NodePtr header = 0;
	readFile_information(&header);//读取信息
	Node* pCurNode = header;
	NodePtr pNode = 0;
	int acctNum = 1;
	char menuChoice[256];
	char name[256];
	char address[100] = { 0 };
	double balance = 1.0;
	long int number = 1;
	char password[256];
	Node information = { 0 };
	FILE *cfPtr;
	char choice;
	int Admin = 1;
	int choose = 0;
	if ((cfPtr = fopen("credit.dat", "r+")) == NULL)//判断文件是不是已经存在，不存在用w+，存在用r+
	{
		cfPtr = fopen("credit.dat", "w+");
	}
	int flag = 1;
	while (flag)
	{
		printf("\n");
		printf("\t\t\t操作系统的人员是用户还是管理员(0\\1)？\n");
		printf("\t\t\t        请输入数字进行选择\n");
		printf("\t\t\t\t");
		scanf("%d", &choose);
		if (choose == 0 || choose == 1)
		{
			flag = 0;
			break;
		}
		printf("\t\t\t       输入错误，请重新输入\n");
	}
	while (choose != 2)
	{
		if (choose == Admin)
		{
			if (Login() == 1)//管理员账号密码登录
			{
				if ((cfPtr = fopen("credit.dat", "r+")) != NULL)
				{
					int flag = 1;
					while (flag)
					{
						char choice = AdminenterChoice();//管理员界面
						switch (choice)
						{
						case '1':
						{
							FLAG_NODE = 1;
							fputs("\t\t输入** 客户编号**姓名**地址**手机号码**余额:\n", stdout);
							memset(name, 0, 256);
							printf("\t\t\t\t");
							scanf("%d%s%s%ld%lf", &acctNum, &name, &address, &number, &balance);
							insertData(&header, name, address, acctNum, number, balance);
							system("pause");
						}
						break;
						case '2':
						{
							fputs("\t\t\t输入要删除的用户姓名:\n", stdout);
							memset(name, 0, 256);
							printf("\t\t\t\t\t");
							scanf("%s", &name);
							deleteData(&header, name);
							system("pause");
						}
						break;
						case '3':
						{
							UpData(header);
							system("pause");
						}
						break;
						case '4':
						{
							fputs("\t\t输入要寻找的用户姓名:\n", stdout);
							memset(name, 0, 256);
							printf("\t\t\t\t\t");
							scanf("%s", &name);
							if (pNode = findData(&header, name))
							{
								printNodeInfo(pNode);
							}
							else
							{
								printf("\t\t%s 用户的信息没有找到!\n", name);
							}
							system("pause");
						}
						break;
						case '5':
						{
							textFile_Persons(header);
							system("pause");
						}
						break;
						case '6':
						{
							Modify(header);
							system("pause");
						}
						break;
						case '7':
						{
							fputs("\t\t\t用户信息的内容为:\n", stdout);
							fputs("\t\t\t用户编号*姓名*地址*手机号码*余额\n", stdout);
							processList(header);
							system("pause");
						}
						break;
						case '8':
						{
							Setting(&header, password);
							system("pause");
						}
						break;
						case '9':
						{
							SysTail();
							system("pause");
							flag = 0;
							int Admin = 1;
							int flag = 1;
							while (flag)
							{
								system("cls");
								SysTitle();
								printf("\n");
								printf("\t\t\t操作系统的人员是用户还是管理员(0\\1)？\n");
								printf("\t\t\t        请输入数字进行选择\n");
								printf("\t\t\t\t");
								scanf("%d", &choose);
								if (choose == 0 || choose == 1)
								{
									flag = 0;
									break;
								}
								printf("\t\t\t       输入错误，请重新输入\n");
							}
						}
						}
						if (choice < '0' || choice > '9')
						{
							printf("\t\t\t\t输入错误!\n");
							system("pause");
						}
					}
				}
			}
			else
			{
				SysTail();
				system("pause");
				int flag = 1;
				while (flag)
				{
					system("cls");
					SysTitle();
					printf("\n");
					printf("\t\t\t操作系统的人员是用户还是管理员(0\\1)？\n");
					printf("\t\t\t        请输入数字进行选择\n");
					printf("\t\t\t\t");
					scanf("%d", &choose);
					if (choose == 0 || choose == 1)
					{
						flag = 0;
						break;
					}
					printf("\t\t\t       输入错误，请重新输入\n");
					system("pause");
				}
			}
		}
		else
		{
			if (_Login(&header) == 1)//用户账号密码登录
			{
				if ((cfPtr = fopen("credit.dat", "r+")) != NULL)
				{
					Node client;
					fread(&client, sizeof(Node), 1, cfPtr);
					fseek(cfPtr, sizeof(Node), SEEK_CUR);
					int flag = 1;
					while (flag)
					{
						int choice = UserenterChoice();
						switch (choice)
						{
						case '1':
						{
							fputs("\t\t输入要寻找的用户姓名:\n", stdout);
							memset(name, 0, 256);
							printf("\t\t\t\t\t");
							scanf("%s", &name);
							if (pNode = findData(&header, name))
							{
								printNodeInfo(pNode);
							}
							else
							{
								printf("\t\t%s 用户的信息没有找到!\n", name);
							}
							system("pause");
						}
						break;

						case '2':
						{
							Modify(header);
							system("pause");
						}
						break;
						case '3':
						{
							textFile_Persons(header);
							system("pause");
						}
						break;

						case '4':
						{
							Setting(&header, password);
							system("pause");
						}
						break;
						case '5':
							SysTail();
							system("pause");
							flag = 0;
							int flag = 1;
							while (flag)
							{
								system("cls");
								SysTitle();
								printf("\n");
								printf("\t\t\t操作系统的人员是用户还是管理员(0\\1)？\n");
								printf("\t\t\t        请输入数字进行选择\n");
								printf("\t\t\t\t");
								scanf("%d", &choose);
								if (choose == 0 || choose == 1)
								{
									flag = 0;
									break;
								}
								printf("\t\t\t       输入错误，请重新输入\n");
							}
						}
						if (choice < '0' || choice > '5')
						{
							printf("\t\t\t\t输入错误!\n");
							system("pause");
						}
					}
				}
				fclose(cfPtr);
			}
			else
			{
				SysTail();
				int flag = 1;
				while (flag)
				{
					printf("\n");
					printf("\t\t\t操作系统的人员是用户还是管理员(0\\1)？\n");
					printf("\t\t\t        请输入数字进行选择\n");
					printf("\t\t\t\t");
					scanf("%d", &choose);
					if (choose == 0 || choose == 1)
					{
						flag = 0;
						break;
					}
					printf("\t\t\t       输入错误，请重新输入\n");
					system("pause");
				}
			}
		}
	}

	return 0;
}

