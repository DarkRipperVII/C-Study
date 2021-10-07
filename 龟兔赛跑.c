/*
***
话说这个世界上有各种各样的兔子和乌龟，但是研究发现，所有的兔子和乌龟都有一个共同的特点——喜欢赛跑。于是世界上各个角落都不断在发生着乌龟和兔子的比赛，小华对此很感兴趣，
于是决定研究不同兔子和乌龟的赛跑。他发现，兔子虽然跑比乌龟快，但它们有众所周知的毛病——骄傲且懒惰，于是在与乌龟的比赛中，一旦任一秒结束后兔子发现自己领先t米或以上，
它们就会停下来休息s秒。对于不同的兔子，t，s的数值是不同的，但是所有的乌龟却是一致——它们不到终点决不停止。

小华发现只要在每场比赛开始后记录下兔子和乌龟的数据——兔子的速度v1（表示每秒兔子能跑v1米），乌龟的速度v2，以及兔子对应的t，s值，以及赛道的长度l，就能预测出比赛的结果
但是小华很懒，不想通过手工计算推测出比赛的结果，于是他找到了你——众所周知的编程高手——请求帮助，请你写一个程序，对于输入的一场比赛的数据v1，v2，t，s，l，预测该场比赛的结果。
***
*/

#include <stdio.h>

int judge(int v1, int v2, int t, int s, int l);     //判断并输出比赛结果

int main()
{
    int v1 = 0, v2 = 0, t = 0, s = 0, l = 0;        //题目中，t的变量名具有迷惑性
    scanf_s("%d %d %d %d %d", &v1, &v2, &t, &s, &l);

    judge(v1, v2, t, s, l);

    return 0;
}

int judge(int v1, int v2, int t, int s, int l)
{
    int turtle_l = 0, rabbit_l = 0, t_now = 0;
    
    while ((l != turtle_l) && (l != rabbit_l))          //判断标准：双方有没有其中一个到了终点？
    {
        if ((rabbit_l - turtle_l) >= t)         //判断双方距离。想想为什么不用abs()求绝对值？
        {
            for (int i = 0; (i < s) && (l != turtle_l); i++)
            {
                turtle_l += v2;
                t_now++;
            }
            //turtle_l += v2 * s;           想想这里这么写为什么在有些情况下是不对的？
            //t_now += s;
        }
        else
        {
            turtle_l += v2;
            rabbit_l += v1;
            t_now++;
        }
    }

    if ((l == turtle_l) && (l == rabbit_l))
    {
        printf("D\n%d", t_now);
    }
    else if (l == turtle_l)
    {
        printf("T\n%d", t_now);
    }
    else if (l == rabbit_l)
    {
        printf("R\n%d", t_now);
    }

    return 0;
}