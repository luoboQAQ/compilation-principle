//预测分析程序
#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>
using namespace std;

//用来存储用户输入的字符串，最长为20个字符
string inputString;
//使用vector模拟栈
vector<char> stack;
//用来存放5个终结符
const unordered_set<char> VT = {'i', '+', '*', '(', ')'};
//用来存放预测分析表M[A,a]中的一条产生式
string chanShengShi;
//用来存放用户输入串的第一个元素的下标，如果a匹配产生式，则每次firstCharIntex 自增 1
int firstCharIndex = 0;

/*
    若预测分析表M[A,a]中存在产生式，
    则将该产生式赋给字符数组chanShengShi，并返回 1，
    若M[A,a]中无定义产生式则返回 0
*/
bool M(char A, char a) {
    if (A == 'E' && a == 'i') {
        chanShengShi = "Te$";
        return true;
    }
    if (A == 'E' && a == '(') {
        chanShengShi = "Te$";
        return true;
    }
    if (A == 'e' && a == '+') {
        chanShengShi = "+Te$";
        return true;
    }
    if (A == 'e' && a == ')') {
        chanShengShi = "$";
        return true;
    }
    if (A == 'e' && a == '#') {
        chanShengShi = "$";
        return true;
    }
    if (A == 'T' && a == 'i') {
        chanShengShi = "Ft$";
        return true;
    }
    if (A == 'T' && a == '(') {
        chanShengShi = "Ft$";
        return true;
    }
    if (A == 't' && a == '+') {
        chanShengShi = "$";
        return true;
    }
    if (A == 't' && a == '*') {
        chanShengShi = "*Ft$";
        return true;
    }
    if (A == 't' && a == ')') {
        chanShengShi = "$";
        return true;
    }
    if (A == 't' && a == '#') {
        chanShengShi = "$";
        return true;
    }
    if (A == 'F' && a == 'i') {
        chanShengShi = "i$";
        return true;
    }
    if (A == 'F' && a == '(') {
        chanShengShi = "(E)$";
        return true;
    } else
        return false;
}

//打印栈内元素
void printStack() {
    for (int i = 1; i < (int)stack.size(); i++)
        cout << stack[i];
    cout << "\t\t";
}

//打印用户输入串
void printinputString() {
    for (int i = firstCharIndex; i < (int)inputString.size() && inputString[i] != '#'; i++)
        cout << inputString[i];
    cout << "\t\t";
}

/*
    进行输入串的预测分析的主功能函数，
    若输入串满足文法则返回 1，不满足则返回0
*/
bool yuCeFenXi() {
    // X变量存储每次弹出的栈顶元素
    char X;
    // a变量存储用户输入串的第一个元素
    char a;
    //该变量记录语法分析的步骤数
    int counter = 1;

    cout << "本程序支持的文法为：" << endl;
    cout << "E->Te" << endl;
    cout << "e->+Te | $" << endl;
    cout << "T->Ft" << endl;
    cout << "t->*Ft | $" << endl;
    cout << "F->(E) | i" << endl;
    cout << "请输入一个字符串，以#结束：" << endl;
    cin >> inputString;

    stack.emplace_back('#');
    stack.emplace_back('E');

    cout << "步骤\t\t栈内\t\t输入串\t\t动作" << endl;
    while (1) {
        cout << counter << "\t\t";
        printStack();
        X = stack.back();
        stack.pop_back();
        printinputString();
        //在终结符集合VT中查找变量X的值
        if (!VT.count(X)) {
            if (X == '#') {
                //栈已经弹空，语法分析结果正确
                cout << endl;
                cout << "识别成功" << endl;
                return true;
            } else {
                a = inputString[firstCharIndex];
                //查看预测分析表M[A,a]是否存在产生式，存在返回1，不存在返回0
                if (M(X, a) == 1) {
                    //'$'为产生式的结束符,找出该产生式的最后一个元素的下标
                    for (int i = chanShengShi.find('$') - 1; i >= 0; i--)
                        stack.emplace_back(chanShengShi[i]);
                    cout << "推导";
                } else {
                    cout << "预测分析表M[A,a]不存在产生式，识别失败" << endl;
                    return false;
                }
            }
        } else {
            //终结符
            if (X == inputString[firstCharIndex]) {
                //匹配
                firstCharIndex++;
                cout << "匹配";
            } else {
                cout << "匹配错误，识别失败" << endl;
                return false;
            }
        }
        counter++;
        cout << endl;
    }
}

int main() {
    yuCeFenXi();
    system("pause");
    return 0;
}