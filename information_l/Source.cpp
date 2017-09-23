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
int  Setting(NodePtr *ppNode, const char*password)//ע���˻�������
{
	NodePtr pCurNode = *ppNode;
	NodePtr pNode = *ppNode;
	int choose = 0;
	int Admin = 1;
	char name[10];
	printf("\t\t\t���ע���µ��˺ź����룬������1\n");
	printf("\t\t\t\t");
	scanf("%d", &choose);
	if (choose == 1)
	{
		while (pNode != NULL)
		{
			if (pNode->account_number == name)
			{
				printf("\t\t����û�����Ϣ�Ѿ�����!\n");
				return -1;
			}
			pNode = pNode->next;
		}
		if (pCurNode == 0) //��Ϊ�յ����������ڵ�λ��Ϊ�գ�
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
			printf("\t\t-----------ע������ǰ���˺ź�����-----------\n");
			printf("\t\t------------------ע���˺�Ϊ----------------\n");
			printf("\t\t\t\t");
			scanf("%s", name);
			printf("\t\t------------------ע������Ϊ----------------\n");
			printf("\t\t\t\t");
			scanf("%s", password);
			printf("\t\t------------------ע�����------------------\n");
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
			printf("\t\t����û�����Ϣ�Ѿ�����!\n");
			return -1;
		}
		pNode = pNode->next;
	}
	if (pCurNode == 0) //��Ϊ�յ����������ڵ�λ��Ϊ�գ�
	{
		*ppNode = (NodePtr)malloc(sizeof(Node));
		memset(*ppNode, 0, sizeof(Node));
		pCurNode = *ppNode;
	}
	else
	{
		Node* pNewNode = (Node*)malloc(sizeof(Node));
		memset(pNewNode, 0, sizeof(Node));
		while (pCurNode->next != 0)//��β������
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
int deleteData(NodePtr *ppNode, const char* data)//ɾ���û���Ϣ
{
	if (ppNode == 0 || *ppNode == 0)
	{
		printf("\t\t\tû��Ҫɾ�����˻���Ϣ !\n");
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
			printf("\t\t\tɾ���ɹ�\n");
			return 0;
		}
		preNode = pNode;
		pNode = pNode->next;
	}
	printf("\t\t\tû��Ҫɾ�����˻���Ϣ !\n");
	return 0;
}
Node* UpData(NodePtr fptr)//�����û���Ϣ
{
	int acctNum;
	char name;
	double transaction;
	NodePtr fpptr = fptr;
	printf("\t\t������Ҫ���µ��û����� ( 1 - 100 ): ");
	scanf("%d", &acctNum);
	while (fpptr != NULL)
	{
		if (fpptr->acctNum == acctNum)
		{
			fputs("\t\tinput** �ͻ����**����**��ַ**�ֻ�����**���:\n", stdout);
			printf("\t\t%-6d%-10s%-10s%-8ld%10.2f\n\n", fpptr->acctNum, fpptr->name, fpptr->address, fpptr->number, fpptr->balance);
			printf("\t\t�������� ( + ) ���� ȡ��( - ): ");
			scanf("%lf", &transaction);
			fpptr->balance += transaction;
			fputs("\t\t�û�����**����**��ַ**�ֻ�����**���:\n", stdout);
			printf("\t\t%-6d%-10s%-10s%-8ld%10.2f\n", fpptr->acctNum, fpptr->name, fpptr->address, fpptr->number, fpptr->balance);
			return fpptr;
		}
		fpptr = fpptr->next;
	}
	if (fpptr == NULL || fpptr->acctNum != acctNum)
	{
		printf("\t\t�û�����Ϊ #%d ����Ϣû���ҵ�.\n", acctNum);
		return 0;
	}
}
NodePtr findData(NodePtr *list, const char* name)//�����û���Ϣ
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
void printNodeInfo(const NodePtr pNode)//��ʾ�û���Ϣ
{
	if (pNode)
	{
		printf("\t\tѰ�ҵ�����Ϣ��:\n");
		fputs("\t\t������** �ͻ����**����**��ַ**�ֻ�����**���:\n", stdout);
		printf("\t\t%d\t%s\t%s\t%ld\t%lf\n", pNode->acctNum, pNode->name, pNode->address, pNode->number, pNode->balance);
	}
}
void Modify(NodePtr fptr)//�޸��û���Ϣ
{
	char name[10] = { '0' };
	long int number = 1;
	char address[20] = { '0' };
	NodePtr fpptr = fptr;
	printf("\t\t\t����Ҫ�޸��˵����֣�\n");
	printf("\t\t\t\t");
	scanf("%s", &name);
	int ret = (int)findData(&fpptr, name);//�ҵ�Ҫ�޸���Ϣ����ϵ��  
	if (ret != 0)
	{
		printf("\t\t\t�������޸ĺ�ĵ�ַ��\n");
		printf("\t\t\t\t");
		scanf("%s", &fpptr->address);
		printf("\t\t\t�������޸ĺ���ֻ��ţ�\n");
		printf("\t\t\t\t");
		scanf("%ld", &fpptr->number);
		printf("\t\t\t�޸���Ϣ�ɹ���\n");
	}
	else
		printf("\t\t\t�޸���Ϣʧ�ܣ�\n");
}
/*void textFile(NodePtr header)//�����ı�������
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
int Login()//����Ա�˺������¼
{
	char account_number[10];
	char password[10];
	char s_name[10] = "111";/*����Ա��ʼ����*/
	char s_password[10] = "666";
	for (int i = 1; i <= 3; i++)
	{
		printf("\t\t------------------�������˺�----------------\n");
		printf("\t\t\t\t");
		scanf("%s", account_number);
		if (strcmp(s_name, account_number) == 0)
		{
			printf("\t\t------------------����������----------------\n");
			printf("\t\t\t\t");
			scanf("%s", &password);
			if (strcmp(s_password, password) == 0)
			{
				printf("\t\t------------------��¼�ɹ�------------------\n");
				return 1;
			}
			else
			{
				printf("\t\t------------------��¼ʧ��------------------\n");
			}
		}
	}
	printf("\t\t-----------�Ѿ��������δ�����Ϣ�����Ժ�����-----------");
	void SysTitle();
	return -1;
}
int _Login(NodePtr *ppNode)//�û��˺������¼
{
	char account_number[10];
	char password[10];
	char s_name[10];
	char s_password[10];
	NodePtr fptr = *ppNode;
	for (int i = 1; i <= 3; i++)
	{
		printf("\t\t------------------�������˺�----------------\n");
		printf("\t\t\t\t\t");
		scanf("%s", &s_name);
		while (fptr)
		{
			if (strcmp(fptr->account_number, s_name) == 0)
			{
				printf("\t\t------------------����������----------------\n");
				printf("\t\t\t\t\t");
				scanf("%s", &s_password);
				if (strcmp(fptr->password, s_password) == 0)
				{
					printf("\t\t------------------��¼�ɹ�------------------\n");
					return 1;
				}
				else
				{
					printf("\t\t------------------��¼ʧ��------------------\n");
				}
				break;
			}
			fptr = fptr->next;
		}
		if (fptr == NULL)
		{
			printf("\t\t\t\t���û�������\n");
		}
	}
	printf("\t\t------�Ѿ��������δ�����Ϣ�����Ժ�����--------");
	void SysTitle();
	return -1;
}
void processList(NodePtr list)//��ʾ���������
{
	//�����������������
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
void SysTitle()//��ʼ����
{
	printf("\n \n"
		"\t\t\t_____________________________\n"
		"\t\t\t*                           *\n"
		"\t\t\t*         ��ӭʹ��          *\n"
		"\t\t\t*                           *\n"
		"\t\t\t*      �û���Ϣ����ϵͳ     *\n"
		"\t\t\t*                           *\n"
		"\t\t\t*****************************\n");
}
char AdminenterChoice(void)//����Ա���˵�
{
	char  menuChoice[256];
	system("cls");
	printf("\t\t\t_____________________________\n"
		"\t\t\t                             \n"
		"\t\t\t*********����Ա���˵�********\n"
		"\t\t\t_____________________________\n"
		"\t\t\t*                           *\n"
		"\t\t\t*      1.�������û���Ϣ     *\n"
		"\t\t\t*      2.ɾ���û���Ϣ       *\n"
		"\t\t\t*      3.�����û���Ϣ       *\n"
		"\t\t\t*      4.�����û���Ϣ       *\n"
		"\t\t\t*      5.�����û���Ϣ       *\n"
		"\t\t\t*      6.�޸��û���Ϣ       *\n"
		"\t\t\t*      7.��ʾ�û���Ϣ       *\n"
		"\t\t\t*      8.ע���û���Ϣ       *\n"
		"\t\t\t*      9.�˳�ϵͳ           *\n"
		"\t\t\t*                           *\n"
		"\t\t\t*****************************\n"
		"\t\t\t                             \n"
		"\t\t\t------��������Ҫѡ��Ĺ���---\n");
	printf("\t\t\t\t\t\n");
	printf("\t\t\t\t");
	scanf("%s", &menuChoice);
	if (menuChoice[0]> '0' && menuChoice[0] < '9'&&strlen(menuChoice) == 1)
	{
		return menuChoice[0];
	}
}
char UserenterChoice(void)//�û����˵�
{
	char menuChoice[256];
	system("cls");
	printf("\t\t\t_____________________________\n"
		"\t\t\t                             \n"
		"\t\t\t**********�û����˵�*********\n"
		"\t\t\t_____________________________\n"
		"\t\t\t*                           *\n"
		"\t\t\t*      1.�����û���Ϣ       *\n"
		"\t\t\t*      2.�޸��û���Ϣ       *\n"
		"\t\t\t*      3.�����û���Ϣ       *\n"
		"\t\t\t*      4.ע���û���Ϣ       *\n"
		"\t\t\t*      5.�˳�ϵͳ           *\n"
		"\t\t\t*                           *\n"
		"\t\t\t*****************************\n"
		"\t\t\t                             \n"
		"\t\t\t----��������Ҫѡ��Ĺ���-----\n");
	printf("\t\t\t\t\t");
	scanf("%s", &menuChoice);
	if (menuChoice[0]> '0' && menuChoice[0] < '6'&&strlen(menuChoice) == 1)
	{
		return menuChoice[0];
	}
}
void SysTail()//��������
{
	//system("cls");
	printf("\n \n"
		"\t\t\t_____________________________\n"
		"\t\t\t*                           *\n"
		"\t\t\t*          ллʹ��         *\n"
		"\t\t\t*                           *\n"
		"\t\t\t*      �û���Ϣ����ϵͳ     *\n"
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
	if (mysql_real_connect(con, argv[1], argv[2], argv[3] , NULL, 0, NULL, 0) == NULL)//��������
	{
		fprintf(stderr, "%s\n", mysql_error(con));
		mysql_close(con);
		exit(1);
	}
	if (mysql_query(con, "CREATE DATABASE information"))//�������ݿ�
	{
		fprintf(stderr, "%s\n", mysql_error(con));
		mysql_close(con);
		exit(1);
	}
	mysql_close(con);
}
void  readFile_information(NodePtr* list)//������
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
void  textFile_Persons(NodePtr header)//�������е�����д�뵽���ݿ���
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

	if (mysql_query(con, "DROP TABLE IF EXISTS Persons"))//����
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
    Create_information(argc, argv);//�������ݿ�
	SysTitle();
	NodePtr header = 0;
	readFile_information(&header);//��ȡ��Ϣ
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
	if ((cfPtr = fopen("credit.dat", "r+")) == NULL)//�ж��ļ��ǲ����Ѿ����ڣ���������w+��������r+
	{
		cfPtr = fopen("credit.dat", "w+");
	}
	int flag = 1;
	while (flag)
	{
		printf("\n");
		printf("\t\t\t����ϵͳ����Ա���û����ǹ���Ա(0\\1)��\n");
		printf("\t\t\t        ���������ֽ���ѡ��\n");
		printf("\t\t\t\t");
		scanf("%d", &choose);
		if (choose == 0 || choose == 1)
		{
			flag = 0;
			break;
		}
		printf("\t\t\t       �����������������\n");
	}
	while (choose != 2)
	{
		if (choose == Admin)
		{
			if (Login() == 1)//����Ա�˺������¼
			{
				if ((cfPtr = fopen("credit.dat", "r+")) != NULL)
				{
					int flag = 1;
					while (flag)
					{
						char choice = AdminenterChoice();//����Ա����
						switch (choice)
						{
						case '1':
						{
							FLAG_NODE = 1;
							fputs("\t\t����** �ͻ����**����**��ַ**�ֻ�����**���:\n", stdout);
							memset(name, 0, 256);
							printf("\t\t\t\t");
							scanf("%d%s%s%ld%lf", &acctNum, &name, &address, &number, &balance);
							insertData(&header, name, address, acctNum, number, balance);
							system("pause");
						}
						break;
						case '2':
						{
							fputs("\t\t\t����Ҫɾ�����û�����:\n", stdout);
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
							fputs("\t\t����ҪѰ�ҵ��û�����:\n", stdout);
							memset(name, 0, 256);
							printf("\t\t\t\t\t");
							scanf("%s", &name);
							if (pNode = findData(&header, name))
							{
								printNodeInfo(pNode);
							}
							else
							{
								printf("\t\t%s �û�����Ϣû���ҵ�!\n", name);
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
							fputs("\t\t\t�û���Ϣ������Ϊ:\n", stdout);
							fputs("\t\t\t�û����*����*��ַ*�ֻ�����*���\n", stdout);
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
								printf("\t\t\t����ϵͳ����Ա���û����ǹ���Ա(0\\1)��\n");
								printf("\t\t\t        ���������ֽ���ѡ��\n");
								printf("\t\t\t\t");
								scanf("%d", &choose);
								if (choose == 0 || choose == 1)
								{
									flag = 0;
									break;
								}
								printf("\t\t\t       �����������������\n");
							}
						}
						}
						if (choice < '0' || choice > '9')
						{
							printf("\t\t\t\t�������!\n");
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
					printf("\t\t\t����ϵͳ����Ա���û����ǹ���Ա(0\\1)��\n");
					printf("\t\t\t        ���������ֽ���ѡ��\n");
					printf("\t\t\t\t");
					scanf("%d", &choose);
					if (choose == 0 || choose == 1)
					{
						flag = 0;
						break;
					}
					printf("\t\t\t       �����������������\n");
					system("pause");
				}
			}
		}
		else
		{
			if (_Login(&header) == 1)//�û��˺������¼
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
							fputs("\t\t����ҪѰ�ҵ��û�����:\n", stdout);
							memset(name, 0, 256);
							printf("\t\t\t\t\t");
							scanf("%s", &name);
							if (pNode = findData(&header, name))
							{
								printNodeInfo(pNode);
							}
							else
							{
								printf("\t\t%s �û�����Ϣû���ҵ�!\n", name);
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
								printf("\t\t\t����ϵͳ����Ա���û����ǹ���Ա(0\\1)��\n");
								printf("\t\t\t        ���������ֽ���ѡ��\n");
								printf("\t\t\t\t");
								scanf("%d", &choose);
								if (choose == 0 || choose == 1)
								{
									flag = 0;
									break;
								}
								printf("\t\t\t       �����������������\n");
							}
						}
						if (choice < '0' || choice > '5')
						{
							printf("\t\t\t\t�������!\n");
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
					printf("\t\t\t����ϵͳ����Ա���û����ǹ���Ա(0\\1)��\n");
					printf("\t\t\t        ���������ֽ���ѡ��\n");
					printf("\t\t\t\t");
					scanf("%d", &choose);
					if (choose == 0 || choose == 1)
					{
						flag = 0;
						break;
					}
					printf("\t\t\t       �����������������\n");
					system("pause");
				}
			}
		}
	}

	return 0;
}

