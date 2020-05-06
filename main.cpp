
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "head.h"

using namespace std;


int main() {
	bool flag = true;
	pHead =pEnd =del_pHead=del_pEnd= NULL;

	showOrder();

	while (flag)
	{
		printf("请输入指令（10查看指令）：");
		int nIndex;		scanf("%d", &nIndex);


		Student* pre_p = NULL, *p = NULL;
		CH20 name = { 0 }, id = { 0 }, preid = { 0 }, 
			tempId{ 0 }, tempName{ 0 };
		int nScore = 0,tempScore =0;

		switch (nIndex)
		{
		case 1:
			printf("请输入姓名,学号，成绩 ：");
			scanf("%s%s%d", name, id, &nScore);

			addStu(name, id, nScore);
			break;
		case 11:
			printf("请输入姓名,学号，成绩 ：");
			scanf("%s%s%d", name, id, &nScore);

			addStuToHead(name, id, nScore);
			break;
		case 111:
			printf("插入在哪个id之后：");
			scanf("%s", preid);
			pre_p = search(preid);
			if (NULL == pre_p)continue;

			printf("请输入姓名,学号，成绩 ：");
			scanf("%s%s%d", name, id, &nScore);
			addStuToSpecLocal(pre_p , name, id, nScore);
			break;
		case 2:	
			printf("请输入查找的学号：");
			scanf("%s", id);
			p = search(id);

			if(NULL!=p) show1Stu(p);

			break;

		case 3:
			printf("请输入要修改分数的学号：");
			scanf("%s", id);
			p = search(id);

			if (NULL != p) {
				printf("输入新分数：");
				scanf("%d", &tempScore);
				p->nScore = tempScore;
			}

			break;
		case 4:
			saveStuToFile();
			break;
		case 5:
			readStuFromFILE();
			break;
		case 6:
			printf("请输入要删除的学号：");
			scanf("%s", id);
			p = search(id);

			if (NULL != p) deleteStu(p);

			break;
		case 7:
			resumeStu();
			break;
		case 9:
			showStus();
			break;
		case 10:
			showOrder();
			break;
		case 0:
			flag = false;
			break;
		default:
			printf("输入指令不正确\n");
			break;
		}

	}	
	destoryStu();
	return 0;
}