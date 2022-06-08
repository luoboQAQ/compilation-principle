#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10
#define ERROR 0
#define OK 1
//********************************************栈模块
typedef struct SqStack1  //运算数栈
{
    int *base;
    int *top;
    int stacksize;
} SqStack1;
typedef struct SqStack2  //运算符栈
{
    char *base;
    char *top;
    int stacksize;
} SqStack2;
void IntInitStack(SqStack1 *S) {
    S->base = (int *)malloc(STACK_INIT_SIZE * sizeof(int));
    if (!S->base)
        exit(ERROR);
    S->top = S->base;
    S->stacksize = STACK_INIT_SIZE;
}
void CharInitStack(SqStack2 *S) {
    S->base = (char *)malloc(STACK_INIT_SIZE * sizeof(char));
    if (!S->base)
        exit(ERROR);
    S->top = S->base;
    S->stacksize = STACK_INIT_SIZE;
}
int IntGetTop(SqStack1 *S)  //取栈顶元素
{
    int e;
    if ((*S).top == (*S).base)
        return 0;
    e = *((*S).top - 1);
    return e;
}
char CharGetTop(SqStack2 *S)  //取栈顶元素
{
    char e;
    if ((*S).top == (*S).base)
        return 0;
    e = *((*S).top - 1);
    return e;
}
int IntPush(SqStack1 *S, int e) {
    *(*S).top++ = e;
    return OK;
}
int CharPush(SqStack2 *S, char e) {
    *(*S).top++ = e;
    return OK;
}

int IntPop(SqStack1 *S) {
    int e;
    if ((*S).top == (*S).base)
        return 0;
    e = *--(*S).top;
    return e;
}
int CharPop(SqStack2 *S) {
    char e;
    if ((*S).top == (*S).base)
        return 0;
    e = *--(*S).top;
    return e;
}
//——————————————————*******************运算模块
char Precede(char a, char b)  //运算优先级判断
{
    int i, j;
    char Table[8][8] = {
        ' ',
        '+',
        '-',
        '*',
        '/',
        '(',
        ')',
        '#',
        '+',
        '>',
        '>',
        '<',
        '<',
        '<',
        '>',
        '>',
        '-',
        '>',
        '>',
        '<',
        '<',
        '<',
        '>',
        '>',
        '*',
        '>',
        '>',
        '>',
        '>',
        '<',
        '>',
        '>',
        '/',
        '>',
        '>',
        '>',
        '>',
        '<',
        '>',
        '>',
        '(',
        '<',
        '<',
        '<',
        '<',
        '<',
        '=',
        ' ',
        ')',
        '>',
        '>',
        '>',
        '>',
        ' ',
        '>',
        '>',
        '#',
        '<',
        '<',
        '<',
        '<',
        '<',
        ' ',
        '=',
    };  //优先级表格
    for (i = 0; i < 8; i++)
        if (Table[0][i] == a)  //纵坐标寻找
            break;
    for (j = 0; j < 8; j++)  //横坐标寻找
        if (Table[j][0] == b)
            break;
    return Table[j][i];
}
int Operate(int a, char theta, int b)  //计算表达式值：主要是将大的表达式转化成小的表达式进行逐步求值
{
    int c;
    if (theta == '+')
        c = a + b;
    else if (theta == '-')
        c = a - b;
    else if (theta == '*')
        c = a * b;
    else
        c = a / b;
    return c;
}  // Operate
int In(char c)  //判断c是否为操作符
{
    if (c == '(' || c == '+' || c == '-' || c == '*' || c == '/' || c == ')' || c == '#' || c == '^')
        return 1;  //如果是操作符返回1
    else
        return 0;  //不是，返回0
}
int result(SqStack1 *OPND, SqStack2 *OPTR)  //求值
{
    char a = 0;
    char theta;
    int b, c, number = 0;
    IntInitStack(OPND);
    CharInitStack(OPTR);
    CharPush(OPTR, '#');
    a = getchar();
    while (a != '#' || CharGetTop(OPTR) != '#') {
        printf("输入字符：%c    ", a);
        if (!In(a))  //不是运算符则进栈
        {
            number = 0;
            while (!In(a)) {
                number = number * 10 + (a - 48);  //处理多位整数	z=10*x+y
                a = getchar();
            }
            IntPush(OPND, number);
            printf("主要操作：Push(OPND,%d)       ", number);
        } else
            switch (Precede(a, CharGetTop(OPTR))) {
            case '<':
                CharPush(OPTR, a);
                a = getchar();
                printf("主要操作：Push(OPTR,%c)       ", a);
                break;
            case '=':
                CharPop(OPTR);
                a = getchar();
                printf("主要操作：Pop(OPTR,%c)        ", a);
                break;
            case '>':
                theta = CharPop(OPTR);
                c = IntPop(OPND);
                b = IntPop(OPND);
                IntPush(OPND, Operate(b, theta, c));
                printf("主要操作：Operate(%d,%c,%d)     ", b, theta, c);
                break;
            }
        printf("OPND栈：%d  OPTR栈：%c\n", IntGetTop(OPND), CharGetTop(OPTR));
    }
    printf("\n结果:%d.\n", IntGetTop(OPND));  //打印输出表达式值
    return OK;
}
//————————————————————————主程序模块
main()  //主函数，使用自定义函数完成功能
{
    SqStack1 s1, *OPND;
    SqStack2 s2, *OPTR;
    OPND = &s1;
    OPTR = &s2;
    printf("请输入算数表达式并以'#'结尾.\n");
    printf("算数表达式:");
    result(OPND, OPTR);
    system("pause");
}
