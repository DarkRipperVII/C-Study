#include <stdio.h>
#include <stdlib.h>

typedef struct _node
{
	int value;
	struct _node* next;
}Node;

typedef struct
{
	Node* head;
	Node* tail;
}List;
/***
*储存链表首尾位置;
*为什么新建结构List? ---> 不需要在main()内对head进行赋值; 利于后续的拓展
***/

void add(List* list, int num);				//为链表添加新元素
int search(List list, int search_num);		//在链表中寻找特定值，寻找到时返回1，否则返回0
void delete(List* list, int delete_num);		//删除特定值所在的单元
void clear(List* list);						//释放整个链表
void printlist(List list);					//打印出整个列表所储存的值

int main(int argc, const char* argv[])
{
	//The main function is used to test.

	Node* head = NULL;
	Node* tail = NULL;
	List list = { head,tail };

	int num = 0;
	while (-1 != num)		//惯例，输入-1表示输入结束
	{
		scanf_s("%d", &num);
		if (-1 != num)
		{
			add(&list, num);
		}
	}

	int search_num = 0;
	scanf_s("%d", &search_num);
	search(list,search_num);

	int delete_num = 0;
	scanf_s("%d", &delete_num);
	delete(&list, delete_num);

	printlist(list);

	return 0;
}

void add(List* list, int num)
{
	Node* p = (Node*)malloc(sizeof(Node));
	if (p)
	{
		p->value = num;
		p->next = NULL;
	}

	if (list->head)		//对list进行空指针检测
	{
		list->tail->next = p;	//将上一个链表末端链接至p
		list->tail = p;		//更新tail指向的位置
	}
	else
	{
		list->head = p;
		list->tail = p;
	}
}

int search(List list, int search_num)
{
	Node* p = list.head;

	if (p->value == search_num)
	{
		printf("找到了\n");
		return 1;
	}
	else
	{
		for (p; p; p = p->next)			//遍历链表
		{
			if (p->value == search_num)
			{
				printf("找到了\n");
				return 1;
			}
		}
	}

	printf("没找到\n");
	return 0;
}

void delete(List* list, int delete_num)
{
	Node* p = list->head;
	Node* q = list->tail;

	if (p->value == delete_num)
	{
		Node* buffer = p;
		list->head = list->head->next;
		free(buffer);
	}
	else if (q->value == delete_num)
	{
		Node* buffer = q;

		for (p; p; p = p->next)		//为了调整tail而进行遍历
		{
			if (p->next == q)
			{
				break;
			}
		}
		
		free(buffer);

		list->tail = p;
	}
	else
	{
		for (p = list->head; p; p = p->next)			//为什么一模一样的东西只有这里报warning啊！		关闭重开VS后：现在为什么又不报了？		为什么又开始报了？
		{
			if (p && p->next->value == delete_num)		//提前查看下个单元的值（因为是单向链表）
			{
				p->next = p->next->next;
				free(p->next);
			}
		}
	}
}

void clear(List* list)
{
	if (list->head)
	{
		Node* q = list->head;
		Node* p = list->head;
		for (p; p; q = p)
		{
			p = p->next;
			free(q);
		}
	}
}

void printlist(List list)
{
	Node* p = list.head;
	if (p)
	{
		 while(p != list.tail)
		{
			printf("%d ", p->value);
			p = p->next;
		 }

		 printf("%d", list.tail->value);
	}
}
