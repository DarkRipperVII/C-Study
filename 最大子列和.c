#include <stdio.h>
#include <stdlib.h>

int Flag(int flag, int x);          //����array״̬
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
    if (1 == flag || -2 == flag)       //�Ѿ��Ǵ���0�븺�������������״̬ʱ�����ô���
    {
        return flag;
    }
    else if ((0 == flag && x < 0) || (-1 == flag && 0 == x))        //ͬʱ����0�븺��ʱ����-2
    {
        return -2;
    }

    if (x > 0)      //�����һ�μ�ֻ��0����ʱ���������
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
        flag = Flag(flag, array[i]);          //�ж�array״̬��-2������0�븺�� -1��ֻ���ڸ���  0��ֻ����0  1������������������ȼ���

        if (ThisSum < 0 && i + 1 < N)         //ThisSum < 0 ʱ�����������ú�������к����ӣ�����ȥ
        {
            ThisSum = 0;
            BufferFirst = array[i + 1];       //BufferFirst�����ݴ���ܵĵ�һλ����
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