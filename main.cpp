
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
		printf("������ָ�10�鿴ָ���");
		int nIndex;		scanf("%d", &nIndex);


		Student* pre_p = NULL, *p = NULL;
		CH20 name = { 0 }, id = { 0 }, preid = { 0 }, 
			tempId{ 0 }, tempName{ 0 };
		int nScore = 0,tempScore =0;

		switch (nIndex)
		{
		case 1:
			printf("����������,ѧ�ţ��ɼ� ��");
			scanf("%s%s%d", name, id, &nScore);

			addStu(name, id, nScore);
			break;
		case 11:
			printf("����������,ѧ�ţ��ɼ� ��");
			scanf("%s%s%d", name, id, &nScore);

			addStuToHead(name, id, nScore);
			break;
		case 111:
			printf("�������ĸ�id֮��");
			scanf("%s", preid);
			pre_p = search(preid);
			if (NULL == pre_p)continue;

			printf("����������,ѧ�ţ��ɼ� ��");
			scanf("%s%s%d", name, id, &nScore);
			addStuToSpecLocal(pre_p , name, id, nScore);
			break;
		case 2:	
			printf("��������ҵ�ѧ�ţ�");
			scanf("%s", id);
			p = search(id);

			if(NULL!=p) show1Stu(p);

			break;

		case 3:
			printf("������Ҫ�޸ķ�����ѧ�ţ�");
			scanf("%s", id);
			p = search(id);

			if (NULL != p) {
				printf("�����·�����");
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
			printf("������Ҫɾ����ѧ�ţ�");
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
			printf("����ָ���ȷ\n");
			break;
		}

	}	
	destoryStu();
	return 0;
}