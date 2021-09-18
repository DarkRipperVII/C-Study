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
*����������βλ��;
*Ϊʲô�½��ṹList? ---> ����Ҫ��main()�ڶ�head���и�ֵ; ���ں�������չ
***/

void add(List* list, int num);				//Ϊ���������Ԫ��
int search(List list, int search_num);		//��������Ѱ���ض�ֵ��Ѱ�ҵ�ʱ����1�����򷵻�0
void delete(List* list, int delete_num);		//ɾ���ض�ֵ���ڵĵ�Ԫ
void clear(List* list);						//�ͷ���������
void printlist(List list);					//��ӡ�������б��������ֵ

int main(int argc, const char* argv[])
{
	//The main function is used to test.

	Node* head = NULL;
	Node* tail = NULL;
	List list = { head,tail };

	int num = 0;
	while (-1 != num)		//����������-1��ʾ�������
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

	if (list->head)		//��list���п�ָ����
	{
		list->tail->next = p;	//����һ������ĩ��������p
		list->tail = p;		//����tailָ���λ��
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
		printf("�ҵ���\n");
		return 1;
	}
	else
	{
		for (p; p; p = p->next)			//��������
		{
			if (p->value == search_num)
			{
				printf("�ҵ���\n");
				return 1;
			}
		}
	}

	printf("û�ҵ�\n");
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

		for (p; p; p = p->next)		//Ϊ�˵���tail�����б���
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
		for (p = list->head; p; p = p->next)			//Ϊʲôһģһ���Ķ���ֻ�����ﱨwarning����		�ر��ؿ�VS������Ϊʲô�ֲ����ˣ�		Ϊʲô�ֿ�ʼ���ˣ�
		{
			if (p && p->next->value == delete_num)		//��ǰ�鿴�¸���Ԫ��ֵ����Ϊ�ǵ�������
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
