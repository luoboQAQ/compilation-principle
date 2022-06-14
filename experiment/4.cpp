#include <stdlib.h>

#include <fstream>
#include <iostream>
#include <string>
using namespace std;

#define MAX 100
//计算运算符的个数
int sum = 0;
//标记输入表达式中字符的个数
int m = 0;
//临时变量的字符
char JG = 'A';
//输入表达式
string str;
//左括号的标志
int token = 0;

//更改计算后数组中的值
void change(int e) {
    int f = e + 2;
    char ch = str[f];
    if (ch >= 'A' && ch <= 'Z') {
        for (int l = 0; l < m + 10; l++) {
            if (str[l] == ch)
                str[l] = JG;
        }
    }

    if (str[e] >= 'A' && str[e] <= 'Z') {
        for (int i = 0; i < m; i++) {
            if (str[i] == str[e])
                str[i] = JG;
        }
    }
}

void chengchuchuli(int i, int m) {
    i++;
    for (; i <= m - 1; i++)  //处理乘除运算
    {
        if (str[i] == '*' || str[i] == '/') {
            cout << "(" << str[i] << "  " << str[i - 1] << "  " << str[i + 1] << "  " << JG << ")" << endl;
            change(i - 1);
            str[i - 1] = str[i] = str[i + 1] = JG;
            sum--;
            JG++;
        }
    }
}

void jiajianchuli(int j, int m) {
    j++;
    for (; j <= m - 1; j++)  //处理加减运算
    {
        if (str[j] == '+' || str[j] == '-') {
            cout << "(" << str[j] << "  " << str[j - 1] << "  " << str[j + 1] << "  " << JG << ")" << endl;
            change(j - 1);
            str[j - 1] = str[j] = str[j + 1] = JG;
            sum--;
            JG++;
        }
    }
}

/*扫描一遍从文件中读入表达式*/
void scan(FILE *fin) {
    int p[MAX];
    char ch = 'a';
    int c = -1, q = 0;
    while (ch != EOF) {
        ch = getc(fin);

        while (ch == ' ' || ch == '\n' || ch == '\t') ch = getc(fin);  //消除空格和换行符

        str[m++] = ch;

        if (ch == '=' || ch == '+' || ch == '-' || ch == '*' || ch == '/')
            sum++;

        else if (ch == '(') {
            p[++c] = m - 1;

        } else if (ch == ')') {
            q = m - 1;
            chengchuchuli(p[c], q);  //从左括号处理到又括号
            jiajianchuli(p[c], q);
            JG--;
            str[p[c]] = str[m - 1] = JG;
            c--;
            JG++;
        }
    }
}

/*对表达是进行处理并输出部分四元式*/
void siyuanshi() {
    for (int i = 0; i <= m - 1; i++)  //处理乘除运算
    {
        if (str[i] == '*' || str[i] == '/') {
            cout << "(" << str[i] << "  " << str[i - 1] << "  " << str[i + 1] << "  " << JG << ")" << endl;
            change(i - 1);
            str[i - 1] = str[i] = str[i + 1] = JG;
            sum--;
            JG++;
        }
    }

    for (int j = 0; j <= m - 1; j++)  //处理加减运算
    {
        if (str[j] == '+' || str[j] == '-') {
            cout << "(" << str[j] << "  " << str[j - 1] << "  " << str[j + 1] << "  " << JG << ")" << endl;
            change(j - 1);
            str[j - 1] = str[j] = str[j + 1] = JG;
            sum--;
            JG++;
        }
    }

    for (int k = 0; k <= m - 1; k++)  //处理赋值运算
    {
        if (str[k] == '=') {
            JG--;
            cout << "(" << str[k] << "  " << str[k + 1] << "  "
                 << "  "
                 << " " << str[k - 1] << ")" << endl;
            sum--;
            change(k + 1);
            str[k - 1] = JG;
        }
    }
}

int main() {
    str.resize(100);
    //接收输入输出文件名
    string in;
    FILE *fin;
    cout << "请输入代码所在的文件名:";
    cin >> in;
    cout << endl;
    if ((fin = fopen(in.c_str(), "r")) == NULL)  //判断输入文件名是否正确
    {
        cout << endl
             << "Error!" << endl;
    }
    cout << "The result:" << endl;

    scan(fin);  //调用函数从文件中读入表达式

    /********调用生成四元式的函数********/
    siyuanshi();

    /*********判断是否成功**********/
    if (sum == 0)
        cout << "Success!" << endl;
    else
        cout << "Error!" << endl;

    //关闭文件
    fclose(fin);
    system("pause");
    return 0;
}
