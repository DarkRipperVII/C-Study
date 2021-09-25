#include <stdio.h>
#include <stdlib.h>

const int INIT_NUM = 999;          //��ʼ��������

int Sort(const int* p1, int* p2, int N);        //ȥ�أ�����С��������Ҫ������ԭ�����С
void Print(int* p, int N);          //������鼰���С��N��ʵ���Բ���

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
            for (int k = N - 2; k >= j; k--)        //��β���������飬��ֵ���������ƶ�һλ
            {
                p2[k + 1] = p2[k];
            }

            p2[j] = p1[i];
            cnt++;
            continue;       //���������Ҫ����������Ͷ�·����ִ����������
        }

        if (p1[i] != p2[j])         //����������β��
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