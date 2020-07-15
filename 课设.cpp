#define  _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct teacher
{
	char num[10];//教师工号
	char depart[20];//部门名称
	int basepay;//基本工资
	int meritpay;//绩效工资
	int jobpay;//职务工资
	int cutpay;//扣款
	int finalpay;//实发工资
};
struct node
{
	struct teacher data;
	struct node* next;
};
struct node* createlist()//创建链表
{
	struct node* headnode = (struct node*)malloc(sizeof(struct node));
	//表头：对数据域data不做初始化
	headnode->next = NULL;
	return headnode;
}
struct node* list = createlist();
struct node* createnode(struct teacher data)//创建结点
{
	struct node* newnode = (struct node*)malloc(sizeof(struct node));
	newnode->data = data;
	newnode->data.finalpay = newnode->data.basepay + newnode->data.meritpay + newnode->data.jobpay - newnode->data.cutpay;
	newnode->next = NULL;
	return newnode;
}
void sort(struct node*headnode)//对链表数据进行排序（实发工资）
{
	struct node* p = headnode->next;
	struct node* q = headnode->next;
	struct teacher teacher1;
	for (; p->next; p = p->next) { // 确定比较次数

		for (q = headnode->next; q->next; q = q->next) {
			if (q->data.finalpay > q->next->data.finalpay) {

				teacher1= q->data;
				q->data = q->next->data;
				q->next->data = teacher1;
			}
		}

	}
}
void printlist(struct node* headnode)//打印单链表
{
	struct node* pmove = headnode->next;
	printf("教师工号\t部门名称\t基本工资\t绩效工资\t职务工资\t扣款\t实发工资\n");
	sort(headnode);
	pmove = headnode->next;
	while (pmove!=NULL)
	{
		printf("%s\t\t%s\t%d\t\t%d\t\t%d\t\t%d\t%d\n", pmove->data.num, pmove->data.depart, pmove->data.basepay, pmove->data.meritpay, pmove->data.jobpay, pmove->data.cutpay, pmove->data.finalpay );
		pmove = pmove->next;
	}
	printf("\n");
}
void insertnode(struct node* headnode, struct teacher data)//插入结点(头插法)
{
	struct node* newnode = createnode(data);
	newnode->next = headnode->next;
	headnode->next = newnode;
}
void deleatnode1(struct node* headnode, char* depart)//批量删除信息
{
	struct node* posnode = headnode->next;
	struct node* frontnode = headnode;
	int flag=0;
	if (posnode == NULL)
	{
		printf("【数据为空，无法删除】\n");
		return;
	}
	printf("%s", depart);
	system("pause");
	while(posnode!=NULL)
	{
		if (strcmp(posnode->data.depart, depart) == 0)
		{
			frontnode->next = posnode->next;
			free(posnode);
			flag++;
			posnode = frontnode->next;
		}
		else
		{
			frontnode = posnode;
			posnode = frontnode->next;
		}
	}
	if (flag == 0)
	{
		printf("未找到%s教师信息",depart);
	}
	else
	{
		printf("%s教师信息删除成功", depart);
	}
}
void deleatnode(struct node* headnode,char*num)//删除结点
{
	struct node* posnode = headnode->next;
	struct node* frontnode = headnode;
	if (posnode == NULL)
	{
		printf("【数据为空，无法删除】\n");
		return;
	}
	while (strcmp(posnode->data.num,num))
	{
		frontnode = posnode;
		posnode = frontnode->next;
		if (posnode == NULL)
		{
			printf("【未找到指定位置，无法删除】\n");
			return;
		}
	}
	frontnode->next = posnode->next;
	free(posnode);
	printf("【指定信息删除成功】\n");
}
void searchnode1(struct node* headnode, char* depart)//链表查找(部门名称查找)
{
	struct node* pmove = headnode->next;
	int num = 0;
	if (pmove == NULL)
	{
		printf("【链表为空，无法查找】\n");
		return;
	}
	for (pmove = headnode->next; pmove != NULL; pmove = pmove->next)
	{
		if (strcmp(pmove->data.depart, depart) == 0)
		{
			if (num == 0)
			{
				printf("教师工号\t部门名称\t基本工资\t绩效工资\t职务工资\t扣款\t实发工资\n");
				num++;
			}
			printf("%s\t\t%s\t%d\t\t%d\t\t%d\t\t%d\t%d\n", pmove->data.num, pmove->data.depart, pmove->data.basepay, pmove->data.meritpay, pmove->data.jobpay, pmove->data.cutpay, pmove->data.finalpay);
		}
	}
	if (num==0)
	{
		printf("【没有找到相关信息】");
	}
}
void searchnode(struct node* headnode, char* num)//链表查找(工号查找)
{
	struct node* pmove = headnode->next;
	if (pmove == NULL)
	{
		printf("【链表为空，无法查找】\n");
		return;
	}
	while (strcmp(pmove->data.num, num))
	{
		pmove = pmove->next;
		if (pmove == NULL)
			break;
	}
	if (pmove)
	{
		printf("教师工号\t部门名称\t基本工资\t绩效工资\t职务工资\t扣款\t实发工资\n");
		printf("%s\t\t%s\t%d\t\t%d\t\t%d\t\t%d\t%d\n", pmove->data.num, pmove->data.depart, pmove->data.basepay, pmove->data.meritpay, pmove->data.jobpay, pmove->data.cutpay, pmove->data.finalpay);
		return;
	}
	else
	{
		printf("【没有找到相关信息】\n");
		return;
	}
}
void changenode(struct node* headnode, char* num)
{
	struct node* pmove = headnode->next;
	if (pmove == NULL)
	{
		printf("【链表为空，不可修改】\n");
		return;
	}
	while (strcmp(pmove->data.num, num))
	{
		pmove = pmove->next;
		if (pmove == NULL)
			break;
	}
	if (pmove)
	{
		printf("请输入修改信息\n");
		scanf("%s%s%d%d%d%d", pmove->data.num, pmove->data.depart, &pmove->data.basepay, &pmove->data.meritpay, &pmove->data.jobpay, &pmove->data.cutpay);
		printf("【修改信息成功】\n");
		return;
	}
	else
	{
		printf("【无相关信息，无法修改】\n");
		return;
	}
}
void upbasepay(struct node*headnode, char*depart, int up)
{
	int flag = 0;
	struct node* movenode = headnode->next;
	while (movenode != NULL)
	{
		if (strcmp(movenode->data.depart, depart) == 0)
		{
			movenode->data.basepay = movenode->data.basepay + up;
			flag++;
		}
		movenode = movenode->next;
	}
	if (flag == 0)
	{
		printf("未找到相关部门信息！\n");
	}
	else
	{
		printf("%s %d名教师基本工资修改完毕。\n",depart,flag);
	}
}
void upjobpay(struct node* headnode, int merit, int up)
{
	int flag = 0;
	struct node* movenode = headnode->next;
	while (movenode != NULL)
	{
		if (movenode->data.meritpay > merit|| movenode->data.meritpay == merit)
		{
			movenode->data.jobpay= movenode->data.jobpay + up;
			flag++;
		}
		movenode = movenode->next;
	}
	if (flag == 0)
	{
		printf("绩效工资涨薪标准过高，未能找到符合数据 ！\n");
	}
	else
	{
		printf("已为%d名优秀教师提高职务工资.\n", flag);
	}
}
void writeExcel(struct node *headnode,char* num)//生成指定教师工资报表
{
	FILE* fp = NULL;
	struct node* movenode=headnode->next;
	fp = fopen("D:\\test.xls", "w");
	while (movenode != NULL)
	{
		if (strcmp(movenode->data.num, num) == 0)
		{
			fprintf(fp, "教师工号\t部门名称\t基本工资\t绩效工资\t职务工资\t扣款\t实发工资\n");
			fprintf(fp, "%s\t%s\t%d\t%d\t%d\t%d\t%d", movenode->data.num, movenode->data.depart, movenode->data.basepay, movenode->data.meritpay, movenode->data.jobpay, movenode->data.cutpay, movenode->data.finalpay);
		}
		movenode = movenode->next;
	}
	printf("工资报表生成成功！\n");
	fclose(fp);
}
void writeExcel1(struct node* headnode, char* depart)//生成指定部门工资报表
{
	FILE* fp = NULL;
	int flag=0;
	struct node* movenode = headnode->next;
	fp = fopen("D:\\test.xls", "w");
	while (movenode != NULL)
	{
		if (strcmp(movenode->data.depart, depart) == 0)
		{
			if (flag == 0)
			{
				fprintf(fp, "教师工号\t部门名称\t基本工资\t绩效工资\t职务工资\t扣款\t实发工资\n");
				fprintf(fp, "%s\t%s\t%d\t%d\t%d\t%d\t%d\n", movenode->data.num, movenode->data.depart, movenode->data.basepay, movenode->data.meritpay, movenode->data.jobpay, movenode->data.cutpay, movenode->data.finalpay);
				flag++;
			}
			else
			{
				fprintf(fp, "%s\t%s\t%d\t%d\t%d\t%d\t%d\n", movenode->data.num, movenode->data.depart, movenode->data.basepay, movenode->data.meritpay, movenode->data.jobpay, movenode->data.cutpay, movenode->data.finalpay);
			}
		}
		movenode = movenode->next;
	}
	printf("%s工资报表生成成功！\n",depart);
	fclose(fp);
}
void writeExcel2(struct node* headnode)//打印所有教师工资报表
{
	FILE* fp = NULL;
	int flag = 0;
	struct node* movenode = headnode->next;
	fp = fopen("D:\\test.xls", "w");
	while (movenode != NULL)
	{
			if (flag == 0)
			{
				fprintf(fp, "教师工号\t部门名称\t基本工资\t绩效工资\t职务工资\t扣款\t实发工资\n");
				fprintf(fp, "%s\t%s\t%d\t%d\t%d\t%d\t%d\n", movenode->data.num, movenode->data.depart, movenode->data.basepay, movenode->data.meritpay, movenode->data.jobpay, movenode->data.cutpay, movenode->data.finalpay);
				flag++;
			}
			else
			{
				fprintf(fp, "%s\t%s\t%d\t%d\t%d\t%d\t%d\n", movenode->data.num, movenode->data.depart, movenode->data.basepay, movenode->data.meritpay, movenode->data.jobpay, movenode->data.cutpay, movenode->data.finalpay);
			}
		movenode = movenode->next;
	}
	printf("全部教师工资报表生成成功！\n" );
	fclose(fp);
}
//文件读操作
void readfile(struct node* headnode, char* filename)
{
	//打开文件
	FILE* fp;
	struct teacher data;
	fp = fopen(filename, "r");
	//读文件
	while (!feof(fp))
	{
		fscanf(fp, "%s\t%s\t%d\t%d\t%d\t%d\n", data.num, data.depart, &data.basepay, &data.meritpay, &data.jobpay, &data.cutpay);
		insertnode(list, data);
	}
	/*while (fscanf(fp, "%s\t%s\t%d\t%d\t%d\t%d\n", data.num, data.depart, &data.basepay, &data.meritpay, &data.jobpay, &data.cutpay));
	{
		insertnode(list, data);
	}*/
	//关闭文件
	fclose(fp);
}
//文件写操作
void writefile(struct node* headnode, char* filename)
{
	FILE* fp;
	fp = fopen(filename, "w");
	struct node* pmove = headnode->next;
	while (pmove!=NULL)
	{
		fprintf(fp, "%s %s %d %d %d %d %d\n", pmove->data.num, pmove->data.depart, pmove->data.basepay, pmove->data.meritpay, pmove->data.jobpay, pmove->data.cutpay, pmove->data.finalpay);
		pmove = pmove->next;
	}
	fclose(fp);
}
void menu()//菜单函数
{
	printf("-------------教师工资管理系统-----------------\n");
	printf("\t\t0.退出系统\n");
	printf("\t\t1.录入信息\n");
	printf("\t\t2.浏览信息\n");
	printf("\t\t3.查找信息\n");
	printf("\t\t4.删除信息\n");
	printf("\t\t5.修改信息\n");
	printf("\t\t6.批量处理\n");
	printf("\t\t7.打印报表\n");
	printf("----------------------------------------------\n");
}
//struct node* list = createlist();
void keydown()//用户交互函数
{
	int up;//工资涨幅
	int merit;//评优绩效工资标准
	int choice;//定义功能编号
	int choice1;//定义批量处理内容
	int choice2;//定义批量修改方式
	int search;//定义查找方式
	char bbnum[20],bbdepart[20];//定义打印报表教师编号、报表打印部门
	char pldepart[20];//定义批量处理的部门
	char searchnum[20],searchdepart[20],changenum[20];//定义查找的工号、查找的部门、欲修改的教师工号
	printf("请输入功能编号：\n");
	struct teacher data;
	scanf("%d", &choice);
	switch (choice)
	{
	case 0:
		printf("【系统正常退出，欢迎您下次使用】\n");
			system("pause");
			exit(0);
		break;
	case 1:
		printf("\t\t【欢迎来到录入信息模块】\n");
		printf("请输入教师信息：\n");
		scanf("%s%s%d%d%d%d", data.num, data.depart, &data.basepay, &data.meritpay, &data.jobpay, &data.cutpay);
		insertnode(list, data);
		break;
	case 2:
		printf("\t\t【欢迎来到信息浏览模块】\n");
		printlist(list);
		break;
	case 3:
		printf("\t\t【欢迎来到信息查找模块】\n");
		printf("【请选择查找方式】\n");
		printf("1.教师工号查找\t2.所属部门查找\n");
		scanf("%d", &search);
		switch (search)
		{
		case 1:
			printf("请输入所要查找的教师工号：\n");
				scanf("%s",searchnum);
				searchnode(list, searchnum);
			break;
		case 2:
			printf("请输入所要查找的部门名称：\n");
			scanf("%s", searchdepart);
			searchnode1(list, searchdepart);
			break;
		default :
			printf("【输入选择编号有误，请重新输入】\n");
			system("pause");
			break;
		}
		break;
	case 4:
		printf("\t\t【欢迎来到信息删除模块】\n");
		printf("请输入删除的教师工号:\n");
		scanf("%s", data.num);
		deleatnode(list, data.num);
		break;
	case 5:
		printf("\t\t【欢迎来到信息修改模块】\n");
		printf("请输入欲修改的教师工号\n");
		scanf("%s", changenum);
		changenode(list, changenum);
		break;
	case 6:
		printf("--------[批量处理模块]--------\n");
		printf("\t1.批量浏览信息\n\t2.批量删除信息\n\t3.批量修改信息\n");
		printf("------------------------------\n");
		printf("请输入功能编号: \n");
		scanf("%d", &choice1);
		switch (choice1)
		{
		case 1:
			printf("\t\t【批量浏览信息】\n");
			printf("请输入所要浏览的部门：\n");
			scanf("%s", pldepart);
			searchnode1(list, pldepart);
			break;
		case 2:
			printf("\t\t【批量删除信息】\n");
			printf("请选择所要删除的部门 \n");
				scanf("%s", pldepart);
			deleatnode1(list, pldepart);
			break;
		case 3:
			printf("\t\t【批量修改信息】\n");
			printf("请选择修改方式：\n");
			printf("1.按部门进行修改  2.按绩效工资进行修改 \n");
			printf("请输入功能编号： \n");
			scanf("%d", &choice2);
			switch (choice2)
			{
			case 1:
				printf("请输入部门名称：\n");
				scanf("%s", pldepart );
				printf("部门基本工资涨幅：\n");
				scanf("%d", &up);
				 upbasepay(list, pldepart, up);
				break;
			case 2:
				printf("请输入评优绩效工资标准： \n");
				scanf("%d", &merit);
				printf("请输入职务工资涨幅： \n");
				scanf("%d", &up);
				upjobpay(list, merit, up);
				break; 
			default:
				printf("【输入选择编号有误，请重新输入】\n");
				system("pause");
				break;
			}
			break;
		}
		break;
	case 7:
		printf("--------[报表打印模块]--------\n");
		printf("\t1.指定教师报表打印\n\t2.指定部门报表打印\n\t3.全部信息报表打印\n");
		printf("------------------------------\n");
		printf("请输入功能编号: \n");
		scanf("%d", &choice1);
		switch (choice1)
		{
		case 1:
			printf("请输入教师工号： \n");
			scanf("%s", bbnum);
			writeExcel(list, bbnum);
			break;
		case 2:
			printf("请输入部门名称： \n");
			scanf("%s", bbdepart);
			writeExcel1(list, bbdepart);
			break;
		case 3:
			writeExcel2(list);
			break;
		default:
			printf("【输入功能编号有误，请重新输入】\n");
			system("pause");
			break;
		}
		printf("请输入教师工号： \n");
		scanf("%s", bbnum);
		writeExcel(list,bbnum);
		break;
	default:
		printf("【输入功能编号有误，请重新输入】\n");
		system("pause");
		break;
	}
	writefile(list, "2.txt");
}
int main()
{
	readfile(list,"1.txt");
	while (1)
	{
     menu();
	 keydown();
	 system("pause");
	 system("cls");//清屏
	}
	system("pause");
	return 0;
}