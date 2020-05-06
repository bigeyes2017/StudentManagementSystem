#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <iomanip>
#include <string.h>
using namespace std;

typedef char CH20[20];

struct Student
{
	char name[20];
	char id[20];
	int nScore;
	struct Student* pnext;

	Student(char _n[20], char _id[20], int _sco) {
		strcpy(name, _n);
		strcpy(id, _id);
		nScore = _sco;
		pnext = NULL;	//每次都要初始化为NULL
	}
};

Student* pHead, * pEnd, *del_pHead,*del_pEnd;

Student* makeNode(char name[20], char id[20], int nScore);
void addStu(char name[20], char id[20], int nScore);//1
void addStuToHead(char name[20], char id[20], int nScore);//11
//111:查找+删除，一个函数只实现一个功能。
Student* search(char* id);
void insert(Student* p, Student *newStu);
void addStuToSpecLocal(Student* pre_p, char name[20], char id[20], int nScore);

void show1Stu(Student* pre_p);
void saveStuToFile();


void deleteStu(Student* p);
//恢复删除节点:插+取+加入
void delInsert(Student* p);
void resumeStu();

void destoryStu();//0
void showStus(); //9
void showOrder();//10

void showOrder() {
	printf("***本学生管理系统实现的功能有：************\n");
	printf("*  1.增加一个学生信息.                 ****\n");
	printf("*  11.增加一个学生信息（头部添加）.    ****\n");
	printf("*  111.增加一个学生信息（指定位置添加）****\n");
	printf("*  2.输入学号得到一个学生信息		   ****\n");
	printf("*  3.输入学号修改一个学生分数信息	   ****\n");
	printf("*  4.保存学生信息至文件				   ****\n");
	printf("*  5.从文件读取学生信息				   ****\n");
	printf("*  6.输入学号删除指定学生信息		   ****\n");
	printf("*  7.恢复删除学生的信息				   ****\n");
	printf("*  9.显示所有学生信息.                 ****\n");
	printf("*  0.退出.			   ****\n");
	printf("*******************************************\n");
}

Student* makeNode(char name[20], char id[20], int nScore) {
	if (NULL == name || NULL == id || nScore < 0) {
		printf("输入的数据错误\n");
		return NULL;
	}
	return new Student(name, id, nScore);
}

void addStu(char name[20], char id[20], int nScore) {
	Student* newStu = makeNode(name,id,nScore);
	if (NULL == newStu)return;

	if (NULL == pHead) {
		pHead = newStu;
	}
	else
	{
		pEnd->pnext = newStu;
	}
	pEnd = newStu;
}

void addStuToHead(char name[20], char id[20], int nScore) {
	Student* newStu = makeNode(name, id, nScore);
	if (NULL == newStu)return;

	if (NULL == pHead) {
		pEnd = newStu;
	}
	else
	{
		newStu->pnext = pHead;
	}
	pHead = newStu;
}

Student* search(char* id) {
	if (NULL == id) {
		printf("未输入id\n");
		return NULL;
	}

	Student* p = pHead;
	while (NULL != p && strcmp(p->id, id) != 0)
	{
		p = p->pnext;
	}
	if (NULL == p){
		printf("未找到学号为%s的学生\n", id);
		return NULL;
	}
	return	p;
}
void insert(Student* p, Student* newStu) {
	if (NULL == p) {
		printf("无法插入\n");	
		//delete newStu;
		return;
	}
	else if(p == pEnd)
	{
		pEnd->pnext = newStu;
		pEnd = newStu;
	}
	else
	{
		//也可以两步解决：先连后断。
		Student* q = p->pnext;
		newStu->pnext = q;
		p->pnext = newStu;
	}
}

void addStuToSpecLocal(Student* pre_p, char name[20], char id[20], int nScore) {
	Student* newStu = makeNode(name, id, nScore);
	if (NULL == newStu)return;

	insert(pre_p, newStu);
}


void show1Stu(Student* p) {
	printf("%s %s %d\n", p->id, p->name, p->nScore);
}

void saveStuToFile() {
	if (NULL == pHead) {
		return;
	}
	//打开文件
	FILE * pf = NULL;
	if ((pf = fopen("StudentInfo.txt", "wt+")) == NULL) {
		printf("文件打开失败\n");
		return;
	}
	//操作文件
	Student* p = pHead;
	while ( NULL != p)//写入缓冲区
	{	
		int a = fprintf(pf, "学号: %s 姓名: %s 成绩: %d\n",
			p->id, p->name, p->nScore);
		if (a < 0) {
			printf("文件写入失败\n");
			fclose(pf);
			return;
		}
		p = p -> pnext;
	}
	//关闭文件：写入文件
	fclose(pf);
	printf("文件写入成功\n");
}

void readStuFromFILE() {
	FILE* pf = NULL;
	if ((pf = fopen("StudentInfo.txt", "r")) == NULL) {
		printf("文件打开失败\n");
		return;
	}
	while (true)
	{
		//读出
		CH20 name = { 0 }, id = { 0 },temp;
		int nScore = 0;

		int a =fscanf(pf, "%s%s%s%s%s%d",temp,id , temp, name, temp, &nScore);
		if (0 == a ) {
			printf("文件读取失败\n");
			fclose(pf);
			return;
		}
		else if (EOF == a)
			//正常结束，判断条件用feof(pf)是一样的。
		{
			break;
		}
		//添加
		addStu(name, id, nScore);		
	}

	//关闭文件:成功返回0
	fclose(pf);
	printf("文件读取成功\n");
}

void deleteStu(Student* p) {
	if (pHead == p) {
		if (pEnd==p)	//特殊考虑：一个节点
		{
			pHead = pEnd = NULL;
		}
		else {			//有多个节点
			pHead = pHead->pnext;
		}
	}
	else {//需要找到先前节点
		Student* q = pHead;
		while (true)	//找到p的前一个
		{
			if (p == q->pnext)break;

			q = q->pnext;
		}
		if (NULL == p->pnext) {
			q->pnext = NULL;	
			pEnd = q;	//与pend有关。
		}
		else
		{
			q->pnext = p->pnext;
		}
	}
	delInsert(p);
}
void delInsert(Student* p) {
	if (NULL == del_pHead) {
		del_pEnd = p;		
	}
	else {
		p->pnext = del_pHead;
	}
	del_pHead = p;
}
void resumeStu() {
	if (NULL != del_pHead) {
		Student* p = del_pHead;

//删除del_pHead
		if (del_pEnd == del_pHead) {
			del_pEnd = del_pHead = NULL;
		}
		else
		{
			del_pHead = del_pHead->pnext;
		}
//加入正常链表末尾
		p->pnext = NULL;	//切记：否则粘起来了两个链

		if (NULL == pHead) {
			pHead = p;
		}
		else
		{
			pEnd->pnext = p;
		}
		pEnd = p;
	}
}
void destoryStu() {
	if (NULL != pHead) {
		pEnd = pHead->pnext;
		while (NULL != pHead)
		{
			delete pHead;

			pHead = pEnd;
			if (NULL != pEnd)	//此处注意
				pEnd = pEnd->pnext;
		}
	}
	if (NULL != del_pHead) {
		del_pEnd = del_pHead->pnext;
		while (NULL!=del_pHead)
		{
			delete del_pHead;

			del_pHead = del_pEnd;
			if(NULL!= del_pEnd)
				del_pEnd = del_pEnd->pnext;
		}

	}
}

void showStus() {
	if (NULL == pHead) {
		printf(" 链表是空的\n");
		return;
	}
	Student* p = pHead;
	
	while (NULL!=p)
	{
		printf("%s %s %d\n", p->id,p->name,p->nScore);

		p = p->pnext;
	}
}



