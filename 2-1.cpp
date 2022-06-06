//预测分析程序
#include <cstdio>
#include <cstring>
#include <iostream>

char inputString[13];                   /*用来存储用户输入的字符串，最长为20个字符*/
char stack[13];                         /*用来进行语法分析的栈结构*/
int base = 0;                           /*栈底指针*/
int top = 1;                            /*栈顶指针*/
char VT[5] = {'i', '+', '*', '(', ')'}; /*用来存放5个终结符*/
char chanShengShi[13];                  /*用来存放预测分析表M[A,a]中的一条产生式*/
int firstCharIntex = 0;                 /*如果a匹配产生式，则每次firstCharIntex 自增 1 */
                                        /*firstCharIntex用来存放用户输入串的第一个元素的下标*/
char pop();                             /*弹出栈顶元素*/

int push(char ch); /*向栈内添加一个元素，成功返回1，若栈已满则返回0*/

int search(char temp); /*查找非终结符集合VT中是否存在变量temp，存在返回1，不存在返回0*/

int M(char A, char a); /* 若预测分析表M[A,a]中存在产生式，
                          则将该产生式赋给字符数组chanShengShi[10]，并返回 1，
                          若M[A,a]中无定义产生式则返回 0
                        */

void init(); /*初始化数组inputString[10] 、栈 stack[10] 和 chanShengShi[10]*/

int yuCeFenXi();         /* 进行输入串的预测分析的主功能函数，
                            若输入串满足文法则返回 1，不满足则返回0
                          */
void printStack();       /*打印栈内元素    */
void printinputString(); /*打印用户输入串  */

/*进入主函数*/
main() {
    //  clrscr();
    yuCeFenXi(); /*调用语法预测分析函数*/
                 // getch();
}

/*函数的定义*/

int yuCeFenXi() {
    char X; /*X变量存储每次弹出的栈顶元素*/
    char a; /*a变量存储用户输入串的第一个元素*/
    int i;
    int counter = 1; /*该变量记录语法分析的步骤数*/

    init();                       /*初始化数组*/
    printf("wen fa  :     \n\n"); /*输出文法做为提示*/
    printf("E->Te        \n");
    printf("e->+Te | $    \n");
    printf("T->Ft    \n");
    printf("t->*Ft|$\n");
    printf("F ->(E)|i   \n");

    printf("input string ,'#' is a end sign  !!( i1+i2 ) \n "); /*提示用户输入将要测试的字符串*/
    scanf("%s", inputString);

    push('#');
    push('E');

    printf(" Counter-----Stack---------------Input string "); /*输出结果提示语句*/

    while (1) /*while循环为语法分析主功能语句块*/
    {
        printf(" ");
        printf("\n");
        printf("  %d", counter); /*输出分析步骤数*/
        printf("         ");     /*输出格式控制语句*/
        printStack();            /*输出当前栈内所有元素*/
        X = pop();               /*弹出栈顶元素赋给变量X*/
        printinputString();      /*输出当前用户输入的字符串*/
        if (search(X) == 0)      /*在终结符集合VT中查找变量X的值，存在返回 1，否则返回 0*/
        {
            if (X == '#') /*栈已经弹空，语法分析结果正确，返回 1*/
            {
                printf("success ... "); /*语法分析结束，输入字符串符合文法定义*/
                return 1;
            } else {
                a = inputString[firstCharIntex];
                if (M(X, a) == 1) /*查看预测分析表M[A,a]是否存在产生式，存在返回1，不存在返回0*/
                {
                    for (i = 0; i < 13; i++) /* '$'为产生式的结束符,for循环找出该产生式的最后一个元素的下标*/
                    {
                        if (chanShengShi[i] == '$')
                            break;
                    }
                    i--; /*因为 '$' 不是产生式，只是一个产生式的结束标志，所以i自减1*/

                    while (i >= 0) {
                        push(chanShengShi[i]); /*将当前产生式逆序压入栈内*/
                        i--;
                    }
                } else {
                    printf(" error(1) !!"); /*若预测分析表M[A,a]不存在产生式，说明语法错误*/
                    return 0;
                }
            }
        } else /*说明X为终结符*/
        {
            if (X == inputString[firstCharIntex]) /*如果X等于a,说明a匹配*/
            {
                firstCharIntex++; /*输入串的第一个元素被约去，下一个元素成为新的头元素*/
            } else {
                printf(" error(2) !! ");
                return 0;
            }
        }
        counter++;
    }
}

void init() {
    int i;
    for (i = 0; i < 13; i++) {
        inputString[i] = NULL;  /*初始化数组inputString[10] */
        stack[i] = NULL;        /*初始化栈stack[10]         */
        chanShengShi[i] = NULL; /*初始化数组chanShengShi[10]*/
    }
}

int M(char A, char a) /*文法定义因实际情况而定，该文法为课本例题的文法*/
{                     /*该函数模拟预测分析表中的二维数组              */
    if (A == 'E' && a == 'i') {
        strcpy(&chanShengShi[0], "Te$");
        return 1;
    }
    if (A == 'E' && a == '(') {
        strcpy(&chanShengShi[0], "Te$");
        return 1;
    }
    if (A == 'e' && a == '+') {
        strcpy(&chanShengShi[0], "+Te$");
        return 1;
    }
    if (A == 'e' && a == ')') {
        strcpy(&chanShengShi[0], "$");
        return 1;
    }
    if (A == 'e' && a == '#') {
        strcpy(&chanShengShi[0], "$");
        return 1;
    }
    if (A == 'T' && a == 'i') {
        strcpy(&chanShengShi[0], "Ft$");
        return 1;
    }
    if (A == 'T' && a == '(') {
        strcpy(&chanShengShi[0], "Ft$");
        return 1;
    }
    if (A == 't' && a == '+') {
        strcpy(&chanShengShi[0], "$");
        return 1;
    }
    if (A == 't' && a == '*') {
        strcpy(&chanShengShi[0], "*Ft$");
        return 1;
    }
    if (A == 't' && a == ')') {
        strcpy(&chanShengShi[0], "$");
        return 1;
    }
    if (A == 't' && a == '#') {
        strcpy(&chanShengShi[0], "$");
        return 1;
    }
    if (A == 'F' && a == 'i') {
        strcpy(&chanShengShi[0], "i$");
        return 1;
    }
    if (A == 'F' && a == '(') {
        strcpy(&chanShengShi[0], "(E)$");
        return 1;
    } else
        return 0; /*没有定义产生式则返回0*/
}

char pop() /*弹出栈顶元素，用topChar返回*/
{
    char topChar;
    topChar = stack[--top];
    return topChar;
}

int push(char ch) {
    if (top > 12) {
        printf(" error : stack overflow "); /*栈空间溢出*/
        return 0;
    } else {
        stack[top] = ch; /*给栈顶空间赋值*/
        top++;
        return 1;
    }
}

int search(char temp) {
    int i, flag = 0; /*flag变量做为标志，若找到temp则赋1，否则赋0*/
    for (i = 0; i < 5; i++) {
        if (temp == VT[i]) /*终结符集合中存在temp*/
        {
            flag = 1;
            break;
        }
    }

    if (flag == 1)
        return 1; /*flag==1说明已找到等于temp的元素*/
    else
        return 0;
}

void printStack() /*输出栈内内容*/
{
    int temp;
    for (temp = 1; temp < top; temp++) {
        printf("%c", stack[temp]);
    }
}

void printinputString() /*输出用户输入的字符串*/
{
    int temp = firstCharIntex;
    printf("                     "); /*该句控制输出格式*/
    do {
        printf("%c", inputString[temp]);
        temp++;
    } while (inputString[temp - 1] != '#');
    printf(" ");
}
