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

Array* array_create(int init_size);				//创建动态数组
void array_free(Array* a);						//释放动态数组空间
int array_size(Array* a);						//返回数组大小（封装，保护数据）
/*
int* array_at(Array* a, int index);				//访问数组（现在被array_set与array_get取代）
*/
int array_set(Array* a, int num);				//对数组的输入（对输入NULL指针的，则自动为其分配1个BLOCK大小的空间）
int array_get(const Array* a, int index);		//读取数组内容,并且不允许输入NULL指针与越界访问
void array_inflate(Array* a);		//实现动态数组的变化

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
		a->size = init_size;		//初始大小
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
		int more_size = (index / BLOCK_SIZE + 1) * BLOCK_SIZE - (a->size);	//求出index位于第几个BLOCK中
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
		a = array_create(BLOCK_SIZE);		//如果传入的是一个NULL指针（涉嫌未正确创建Array变量），则自动为其创建一个变量
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
		printf("非法访问");
		return 0;
	}
	else
	{
		printf("读取输入时出错，请检查输入");
		return 0;
	}
}

void array_inflate(Array* a)
{
	int* p = (int*)malloc(sizeof(int) * (a->size + BLOCK_SIZE));

	if (p && a)		//防止malloc返回NULL
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