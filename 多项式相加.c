/*此程序将使用数组读取两个多项式的幂与系数，并以幂* 系数（若两个多项式有相同幂次，则两者相加）的方式表示多项式。
多项式输入的一头一尾将会是最高次幂（<100）与0次幂（即使0次幂的系数为0，也会被输入），其他次幂的系数若为0，则不予输入

#include <stdio.h>

int main()
{
	int i,j;	//i用于第一次遍历赋值，j用于第二次遍历输出
	int n, m;	//n，m用于存放用户输入的数字，并对数组a内部赋值
	int sum[200] = { 0 };	//sum数组存放系数，并将相同幂次的系数相加
	int break_count = 0;	//用于检测用户输入了多少次0次幂
	
	for (i = 0; i < sizeof(a[])/sizeof(a[0]) ; i++)
	{
		scanf_s("%d %d", &n, &m);
		//a[i][0] = n;
		//a[i][1] = m;

		sum[n] += m;

		if (n == 0)
		{
			break_count++;
		}
		
		if (break_count == 2)
		{
			break;
		}
	}
	
	int count = 0;	//调整输出格式使用
	for (j = 99; j >= 0; j--)	//此处遍历是否可以改进？ 另：此处可以继续使用"i"而无需额外变量"j"。
	{
		if (sum[j] != 0) 
		{
			count++;
			
			if(count>1)		//以下判断是为了调整输出格式
			{
				if(j == 0)
				{ 
					printf("+%d", sum[j]);
				}
				else if(j == 1)
				{
					printf("+%dx", sum[j]);
				}
				else
				{
					printf("+%dx%d", sum[j], j);
				}
			}
			
			else
			{
				printf("%dx%d", sum[j], j);		//第一项前不带加号
			}
		}
	}

	return 0;
}
*/