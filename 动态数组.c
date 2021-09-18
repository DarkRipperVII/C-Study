#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
	int* array;
	int size;
	int num_checkpoint;
}Array;

const int BLOCK_SIZE = 20;

Array* array_create(int init_size);				//������̬����
void array_free(Array* a);						//�ͷŶ�̬����ռ�
int array_size(Array* a);						//���������С����װ���������ݣ�
/*
int* array_at(Array* a, int index);				//�������飨���ڱ�array_set��array_getȡ����
*/
int array_set(Array* a, int num);				//����������루������NULLָ��ģ����Զ�Ϊ�����1��BLOCK��С�Ŀռ䣩
int array_get(const Array* a, int index);		//��ȡ��������,���Ҳ���������NULLָ����Խ�����
void array_inflate(Array* a);		//ʵ�ֶ�̬����ı仯

int main(int argc, const char* argv[])
{
	//The main function is used to test.
	
	Array* x = array_create(10);

	int cnt = 0;
	int num = 0;
	while (-1 != num)
	{
		scanf_s("%d", &num);
		if (-1 != num)
		{
			array_set(x, num);
		}
	}

	printf("%d\n",array_get(x, 12));
	printf("%d\n",array_size(x));
	
	array_free(x);

	return 0;
}

Array* array_create(int init_size)
{
	Array* a = (Array*)malloc(sizeof(Array));
	
	if (a)
	{
		a->array = (int*)malloc(sizeof(int) * init_size);
		a->size = init_size;		//��ʼ��С
		a->num_checkpoint = 0;
	}
	else
	{
		return NULL;
	}
	
	return a;
}

void array_free(Array* a)
{
	free(a->array);
	free(a);
}

int array_size(Array* a)
{
	if (a)
	{
		return a->size;
	}

	return -1;
}

/*
***
int* array_at(Array* a, int index)
{
	if (a && index >= (a->size))
	{
		int more_size = (index / BLOCK_SIZE + 1) * BLOCK_SIZE - (a->size);	//���indexλ�ڵڼ���BLOCK��
		array_inflate(a, more_size);
	}
	
	return &(a->array[index]);
}
***
*/

int array_set(Array* a, int num)
{
	if (NULL == a)
	{
		a = array_create(BLOCK_SIZE);		//����������һ��NULLָ�루����δ��ȷ����Array�����������Զ�Ϊ�䴴��һ������
	}

	if (a->num_checkpoint >= a->size - 1)
	{
		array_inflate(a);
	}
	
	a->num_checkpoint++;
	a->array[a->num_checkpoint] = num;

	return a->num_checkpoint;
}

int array_get(const Array * a, int index)
{
	if (a && index <= a->num_checkpoint)
	{
		return a->array[index];
	}
	else if (a && index >= a->num_checkpoint)
	{
		printf("�Ƿ�����");
		return 0;
	}
	else
	{
		printf("��ȡ����ʱ������������");
		return 0;
	}
}

void array_inflate(Array* a)
{
	int* p = (int*)malloc(sizeof(int) * (a->size + BLOCK_SIZE));

	if (p && a)		//��ֹmalloc����NULL
	{
		memcpy(p, a->array, a->size + 1);

		free(a->array);

		a->array = p;
		a->size = a->size + BLOCK_SIZE;
	}
	else
	{
		printf("error");
	}
}