#include <stdio.h>
#include <stdlib.h>

int Flag(int flag, int x);          //处理array状态
void MaxArraySum(const int* array, int N);

int main(int argc, const char* argv[])
{
    int K = 0;
    scanf_s("%d", &K);

    int* array = (int*)malloc(sizeof(int) * (K + 1));
    for (int i = 0; i < K; i++)
    {
        scanf_s("%d", &array[i]);
    }

    MaxArraySum(array, K);

    free(array);
    return 0;
}

int Flag(int flag, int x)
{
    if (1 == flag || -2 == flag)       //已经是存在0与负数或存在正数的状态时，不用处理
    {
        return flag;
    }
    else if ((0 == flag && x < 0) || (-1 == flag && 0 == x))        //同时存在0与负数时返回-2
    {
        return -2;
    }

    if (x > 0)      //处理第一次及只有0或负数时进入的数据
    {
        return 1;
    }
    if (x < 0)      
    {
        return -1;
    }

    return 0;
}

void MaxArraySum(const int* array, int N)
{
    int MaxSum = 0, ThisSum = 0;
    int FirstNum = array[0], BufferFirst = array[0], LastNum = array[N - 1];
    int flag = -99;

    for (int i = 0; i < N; i++)
    {
        ThisSum += array[i];
        flag = Flag(flag, array[i]);          //判断array状态：-2：存在0与负数 -1：只存在负数  0：只存在0  1：存在正数（最高优先级）

        if (ThisSum < 0 && i + 1 < N)         //ThisSum < 0 时，不可能再让后面的数列和增加，故舍去
        {
            ThisSum = 0;
            BufferFirst = array[i + 1];       //BufferFirst用于暂存可能的第一位数字
        }
        else if (ThisSum > MaxSum)
        {
            MaxSum = ThisSum;
            FirstNum = BufferFirst;
            LastNum = array[i];
        }
    }

    if (-2 == flag)
    {
        MaxSum = 0;
        FirstNum = 0;
        LastNum = 0;
    }

    printf("%d %d %d", MaxSum, FirstNum, LastNum);
}