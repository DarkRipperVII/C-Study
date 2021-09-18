#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int change(char p);	
//change()��ʮ����������char���ͣ���ÿһλת��Ϊ��Ӧ��ʮ��������int���ͣ���ע�⣺�˺��������������ؽ�ʮ��������ת��Ϊʮ������

int check(char* p);
//check()���ڱȶ�У����,���ҳ����ڶ�λ״̬����䣬ͬʱ�������p�С�ʱ�䡱����ʼλ��(int�ͣ�

void timeget(char* p, char* q, int i);
//get_time()���ڻ�ȡ���ϱ�׼�����p�ġ�ʱ�䡱����д�������q�����С����У�i��check()���ص�ֵ

int main()
{
	char input[200] = { 0 }, output[9] = { 0 };
	int check_ret = 0;

	do
	{
		scanf_s("%s", input,199);
		check_ret = check(input);

		if (-1 == check_ret)		//����-1����������"END"���
		{
			printf("%s", output);
			return 0;
		}
		else if (0 != check_ret)
		{
			timeget(input, output, check_ret);
		}
	} while (1);

	return 1;
}

int change(char p)
{
	int ret = 0;

	if ('0' <= p && p <= '9')
	{
		ret = p - '0';
	}
	if ('A' <= p && p <= 'Z')
	{
		ret = (p - 16) + 10;		//16ΪA-F��1-6��ASCII��ľ���
	}
	
	return ret;
}

int check(char* p)
{
	if (strstr(p, "END") != NULL)	//��ֹ"END"����
	{
		return 1;
	}

	int i = 1, count = 0, checksum = 0, realsum = 0, time_locate = 0;

	if (strstr(p, "$GPRMC") != NULL)		//����ֶ�1
	{
		checksum = p[1];

		for (i = 1; p[i + 1] != '*'; i++)
		{
			
			if (p[i] == ',')
			{
				count++;		//count���ڼ�¼','�ĳ��ִ���

				if (count == 1)		//��ȡ�ֶ�2��ʼ��λ��
				{
					time_locate = i + 1;
				}

				if (count == 3 && p[i - 1] == 'A')	//��ⶨλ״̬
				{
					continue;
				}
				else if(count == 3)
				{
					return 0;	//������Ҫ��Ͳ���ȡ��У��ֵ��
				}
			}
			
			checksum ^= p[i + 1];	//ȡ��У��ֵ
		}
	}
	else
	{
		return 0;
	}
	
	//��ʱ����Ҫ���p[i]ָ��*'��ǰһλ

	realsum = change(p[i + 2]) * 16 + change(p[i + 3]);
	if (checksum == realsum)		//�˶�У��ֵ
	{
		return time_locate;
	}

	return 0;
}

void timeget(char* p,char* ret,int i)
{
	int n = 0;
	int hour = 0, min = 0, sec = 0;

	hour = (p[i] - '0') * 10 + p[i + 1] - '0' + 8;	//����ʱ��ΪUTC+8���˴��õ����ַ����ַ�=�������ķ���
	min = (p[i + 2] - '0') * 10 + p[i + 3] - '0';
	sec = (p[i + 4] - '0') * 10 + p[i + 5] - '0';
	
	if (hour > 24)
	{
		hour -= 24;
	}

	sprintf_s(ret,9, "%d:%d:%d", hour, min, sec);	//����ָ���޸�output��ֵ
}