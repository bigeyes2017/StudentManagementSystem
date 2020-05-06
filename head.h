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
		pnext = NULL;	//ÿ�ζ�Ҫ��ʼ��ΪNULL
	}
};

Student* pHead, * pEnd, *del_pHead,*del_pEnd;

Student* makeNode(char name[20], char id[20], int nScore);
void addStu(char name[20], char id[20], int nScore);//1
void addStuToHead(char name[20], char id[20], int nScore);//11
//111:����+ɾ����һ������ֻʵ��һ�����ܡ�
Student* search(char* id);
void insert(Student* p, Student *newStu);
void addStuToSpecLocal(Student* pre_p, char name[20], char id[20], int nScore);

void show1Stu(Student* pre_p);
void saveStuToFile();


void deleteStu(Student* p);
//�ָ�ɾ���ڵ�:��+ȡ+����
void delInsert(Student* p);
void resumeStu();

void destoryStu();//0
void showStus(); //9
void showOrder();//10

void showOrder() {
	printf("***��ѧ������ϵͳʵ�ֵĹ����У�************\n");
	printf("*  1.����һ��ѧ����Ϣ.                 ****\n");
	printf("*  11.����һ��ѧ����Ϣ��ͷ����ӣ�.    ****\n");
	printf("*  111.����һ��ѧ����Ϣ��ָ��λ����ӣ�****\n");
	printf("*  2.����ѧ�ŵõ�һ��ѧ����Ϣ		   ****\n");
	printf("*  3.����ѧ���޸�һ��ѧ��������Ϣ	   ****\n");
	printf("*  4.����ѧ����Ϣ���ļ�				   ****\n");
	printf("*  5.���ļ���ȡѧ����Ϣ				   ****\n");
	printf("*  6.����ѧ��ɾ��ָ��ѧ����Ϣ		   ****\n");
	printf("*  7.�ָ�ɾ��ѧ������Ϣ				   ****\n");
	printf("*  9.��ʾ����ѧ����Ϣ.                 ****\n");
	printf("*  0.�˳�.			   ****\n");
	printf("*******************************************\n");
}

Student* makeNode(char name[20], char id[20], int nScore) {
	if (NULL == name || NULL == id || nScore < 0) {
		printf("��������ݴ���\n");
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
		printf("δ����id\n");
		return NULL;
	}

	Student* p = pHead;
	while (NULL != p && strcmp(p->id, id) != 0)
	{
		p = p->pnext;
	}
	if (NULL == p){
		printf("δ�ҵ�ѧ��Ϊ%s��ѧ��\n", id);
		return NULL;
	}
	return	p;
}
void insert(Student* p, Student* newStu) {
	if (NULL == p) {
		printf("�޷�����\n");	
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
		//Ҳ�������������������ϡ�
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
	//���ļ�
	FILE * pf = NULL;
	if ((pf = fopen("StudentInfo.txt", "wt+")) == NULL) {
		printf("�ļ���ʧ��\n");
		return;
	}
	//�����ļ�
	Student* p = pHead;
	while ( NULL != p)//д�뻺����
	{	
		int a = fprintf(pf, "ѧ��: %s ����: %s �ɼ�: %d\n",
			p->id, p->name, p->nScore);
		if (a < 0) {
			printf("�ļ�д��ʧ��\n");
			fclose(pf);
			return;
		}
		p = p -> pnext;
	}
	//�ر��ļ���д���ļ�
	fclose(pf);
	printf("�ļ�д��ɹ�\n");
}

void readStuFromFILE() {
	FILE* pf = NULL;
	if ((pf = fopen("StudentInfo.txt", "r")) == NULL) {
		printf("�ļ���ʧ��\n");
		return;
	}
	while (true)
	{
		//����
		CH20 name = { 0 }, id = { 0 },temp;
		int nScore = 0;

		int a =fscanf(pf, "%s%s%s%s%s%d",temp,id , temp, name, temp, &nScore);
		if (0 == a ) {
			printf("�ļ���ȡʧ��\n");
			fclose(pf);
			return;
		}
		else if (EOF == a)
			//�����������ж�������feof(pf)��һ���ġ�
		{
			break;
		}
		//���
		addStu(name, id, nScore);		
	}

	//�ر��ļ�:�ɹ�����0
	fclose(pf);
	printf("�ļ���ȡ�ɹ�\n");
}

void deleteStu(Student* p) {
	if (pHead == p) {
		if (pEnd==p)	//���⿼�ǣ�һ���ڵ�
		{
			pHead = pEnd = NULL;
		}
		else {			//�ж���ڵ�
			pHead = pHead->pnext;
		}
	}
	else {//��Ҫ�ҵ���ǰ�ڵ�
		Student* q = pHead;
		while (true)	//�ҵ�p��ǰһ��
		{
			if (p == q->pnext)break;

			q = q->pnext;
		}
		if (NULL == p->pnext) {
			q->pnext = NULL;	
			pEnd = q;	//��pend�йء�
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

//ɾ��del_pHead
		if (del_pEnd == del_pHead) {
			del_pEnd = del_pHead = NULL;
		}
		else
		{
			del_pHead = del_pHead->pnext;
		}
//������������ĩβ
		p->pnext = NULL;	//�мǣ�����ճ������������

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
			if (NULL != pEnd)	//�˴�ע��
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
		printf(" �����ǿյ�\n");
		return;
	}
	Student* p = pHead;
	
	while (NULL!=p)
	{
		printf("%s %s %d\n", p->id,p->name,p->nScore);

		p = p->pnext;
	}
}



