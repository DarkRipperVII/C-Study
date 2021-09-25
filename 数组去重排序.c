#include <stdio.h>
#include <stdlib.h>

const int INIT_NUM = 999;          //初始化数组用

int Sort(const int* p1, int* p2, int N);        //去重，并按小到大排序，要求输入原数组大小
void Print(int* p, int N);          //输出数组及其大小，N其实可以不给

int main(int argc, const char* argv[])
{
    int N = 0, num = 0;
    scanf_s("%d", &N);
    int* buffer = (int*)malloc(sizeof(int) * (N + 1));
    int* array = (int*)malloc(sizeof(int) * (N + 1));

    for (int i = 0; i < N; i++)
    {
        scanf_s("%d", &buffer[i]);
        array[i] = INIT_NUM;
    }

    int cnt = Sort(buffer, array, N);
    Print(array, cnt);

    return 0;
}

int Sort(const int* p1, int* p2, int N)
{
    int j = 0, cnt = 0;
    for (int i = 0; i < N; i++)
    {
        j = 0;
        while (p1[i] > p2[j])
        {
            j++;
        }

        if (p1[i] < p2[j])
        {
            for (int k = N - 2; k >= j; k--)        //从尾部遍历数组，将值整体往后移动一位
            {
                p2[k + 1] = p2[k];
            }

            p2[j] = p1[i];
            cnt++;
            continue;       //将这个符合要求的数插入后就短路，不执行下面的语句
        }

        if (p1[i] != p2[j])         //最大的数置于尾部
        {
            p2[j + 1] = p1[i];
        }
    }

    return cnt;
}

void Print(int* p, int N)
{
    printf("%d\n", N);
    printf("%d", p[0]);
    for (int i = 1; INIT_NUM != p[i]; i++)
    {
        printf(" %d", p[i]);
    }
}