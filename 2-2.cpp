//递归下降分析程序
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
char a[80];
char sym;
int i = 0;

void E();
void E1();
void T();
void T1();
void F();
void input();
void Scaner();
void Error();

void input() {
    puts("输入需要分析的字符串（以#键结尾）:");
    cin >> a;
}

void Scaner() {
    sym = a[i];
    i++;
}

void Error() {
    cout << "Error" << endl;
    exit(0);
}

main() {
    while (1) {
        input();
        Scaner();
        E();
        if (sym == '#')
            printf("此字符串是该文法的字符串!\n");
        else
            printf("Error!\n");
        i = 0;
    }
}

void E() {
    T();
    E1();
}

void E1() {
    if (sym == '+') {
        Scaner();
        T();
        E1();
    } else if ((sym != ')') && (sym != '#'))
        Error();
}

void T() {
    F();
    T1();
}

void T1() {
    if (sym == '*') {
        Scaner();
        F();
        T1();
    } else if ((sym != '+' && sym != ')') && sym != '#')
        Error();
}

void F() {
    if (sym == '(') {
        Scaner();
        E();
        if (sym == ')')
            Scaner();
        else
            Error();
    } else if (sym == 'i')
        Scaner();
    else
        Error();
}
