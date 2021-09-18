#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int change(char p);	
//change()将十六进制数（char类型）的每一位转换为对应的十进制数（int类型）。注意：此函数并不能完整地将十六进制数转换为十进制数

int check(char* p);
//check()用于比对校验码,并找出处于定位状态的语句，同时返回语句p中“时间”的起始位置(int型）

void timeget(char* p, char* q, int i);
//get_time()用于获取符合标准的语句p的“时间”，并写入给定的q数组中。其中，i是check()返回的值

int main()
{
	char input[200] = { 0 }, output[9] = { 0 };
	int check_ret = 0;

	do
	{
		scanf_s("%s", input,199);
		check_ret = check(input);

		if (-1 == check_ret)		//返回-1表明检索到"END"语句
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
		ret = (p - 16) + 10;		//16为A-F到1-6的ASCII码的距离
	}
	
	return ret;
}

int check(char* p)
{
	if (strstr(p, "END") != NULL)	//防止"END"进入
	{
		return 1;
	}

	int i = 1, count = 0, checksum = 0, realsum = 0, time_locate = 0;

	if (strstr(p, "$GPRMC") != NULL)		//检测字段1
	{
		checksum = p[1];

		for (i = 1; p[i + 1] != '*'; i++)
		{
			
			if (p[i] == ',')
			{
				count++;		//count用于记录','的出现次数

				if (count == 1)		//获取字段2开始的位置
				{
					time_locate = i + 1;
				}

				if (count == 3 && p[i - 1] == 'A')	//检测定位状态
				{
					continue;
				}
				else if(count == 3)
				{
					return 0;	//不符合要求就不再取待校验值了
				}
			}
			
			checksum ^= p[i + 1];	//取待校验值
		}
	}
	else
	{
		return 0;
	}
	
	//此时符合要求的p[i]指向‘*'的前一位

	realsum = change(p[i + 2]) * 16 + change(p[i + 3]);
	if (checksum == realsum)		//核对校验值
	{
		return time_locate;
	}

	return 0;
}

void timeget(char* p,char* ret,int i)
{
	int n = 0;
	int hour = 0, min = 0, sec = 0;

	hour = (p[i] - '0') * 10 + p[i + 1] - '0' + 8;	//北京时间为UTC+8。此处用到“字符±字符=整数”的方法
	min = (p[i + 2] - '0') * 10 + p[i + 3] - '0';
	sec = (p[i + 4] - '0') * 10 + p[i + 5] - '0';
	
	if (hour > 24)
	{
		hour -= 24;
	}

	sprintf_s(ret,9, "%d:%d:%d", hour, min, sec);	//利用指针修改output的值
}