//递归下降分析程序
#include <iostream>
#include <string>
using namespace std;

string code;
char sym;
int i;

void E();
void E1();
void T();
void T1();
void F();
void Scaner();
void Error();

void Scaner() {
    sym = code[i];
    i++;
}

void Error() {
    cout << "Error" << endl;
    system("pause");
    exit(0);
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

int main() {
    while (1) {
        i = 0;
        cout << "输入需要分析的字符串（以#键结尾）:";
        cin >> code;
        Scaner();
        E();
        if (sym == '#')
            cout << "此字符串是该文法的字符串!" << endl;
        else
            cout << "Error!" << endl;
    }
    return 0;
}
