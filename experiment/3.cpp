#include <iostream>
#include <stack>
#include <vector>
using namespace std;

class IntStack : public stack<int> {
public:
    int myPop() {
        if (this->empty())
            return 0;
        int value = this->top();
        this->pop();
        return value;
    };
    int getTop() {
        if (this->empty())
            return 0;
        return this->top();
    };
};

class CharStack : public stack<char> {
public:
    char myPop() {
        if (this->empty())
            return 0;
        char value = this->top();
        this->pop();
        return value;
    };
    char getTop() {
        if (this->empty())
            return 0;
        return this->top();
    };
};

class PrioFunct {
private:
    vector<int> f, g;
    vector<char> title;
    int getIndex(char a) {
        for (int i = 0; i < (int)title.size(); i++) {
            if (title[i] == a)
                return i;
        }
        return 0;
    }

public:
    bool build(vector<vector<char>>& table) {
        int n = table.size();
        if (n == 0)
            return false;
        f.resize(n + 1);
        g.resize(n + 1);
        for (int i = 0; i <= n; i++) {
            f[i] = 1;
            g[i] = 1;
        }
        title = table[0];
        bool isChanged = true;
        bool isValid = false;
        int end = 2 * n + 1;
        while (isChanged && !isValid) {
            isChanged = false;
            for (int i = 1; i < n; i++)
                for (int j = 1; j < n; j++) {
                    switch (table[i][j]) {
                    case '>':
                        if (f[i] <= g[j]) {
                            f[i] = g[j] + 1;
                            isChanged = true;
                        }
                        break;
                    case '<':
                        if (f[i] >= g[j]) {
                            g[j] = f[i] + 1;
                            isChanged = true;
                        }
                        break;
                    case '=':
                        if (f[i] != g[j]) {
                            f[i] = g[j] = max(f[i], g[j]);
                            isChanged = true;
                        }
                        break;
                    }
                    if (f[i] >= end || g[j] >= end)
                        isValid = true;
                }
        }
        if (isValid)
            return false;
#ifdef MY_DEBUG
        cout << "优先函数如下：" << endl;
        cout << "f: ";
        for (int i = 1; i < n; i++)
            cout << f[i] << " ";
        cout << endl;
        cout << "g: ";
        for (int i = 1; i < n; i++)
            cout << g[i] << " ";
        cout << endl;
#endif
        return true;
    }

    char precede(char a, char b) {
        int i = getIndex(b);
        int j = getIndex(a);
        if (f[i] < g[j])
            return '<';
        else if (f[i] > g[j])
            return '>';
        else
            return '=';
    }
};

//优先级表格
vector<vector<char>> Table = {
    {' ', '+', '-', '*', '/', '(', ')', '#'},
    {'+', '>', '>', '<', '<', '<', '>', '>'},
    {'-', '>', '>', '<', '<', '<', '>', '>'},
    {'*', '>', '>', '>', '>', '<', '>', '>'},
    {'/', '>', '>', '>', '>', '<', '>', '>'},
    {'(', '<', '<', '<', '<', '<', '=', ' '},
    {')', '>', '>', '>', '>', ' ', '>', '>'},
    {'#', '<', '<', '<', '<', '<', ' ', '='}};

//运算优先级判断
char Precede(char a, char b) {
    int i, j;
    //纵坐标寻找
    for (i = 0; i < 8; i++)
        if (Table[0][i] == a)
            break;
    //横坐标寻找
    for (j = 0; j < 8; j++)
        if (Table[j][0] == b)
            break;
    return Table[j][i];
}
//计算表达式值：主要是将大的表达式转化成小的表达式进行逐步求值
int Operate(int a, char theta, int b) {
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
}

//判断c是否为操作符
bool In(char c) {
    if (c == '(' || c == '+' || c == '-' || c == '*' || c == '/' || c == ')' || c == '#' || c == '^')
        return true;
    else
        return false;
}

//求值
int result() {
    IntStack opnd;
    CharStack optr;
    char a = 0;
    char theta;
    int b, c, number = 0;
    optr.emplace('#');
    a = getchar();
    while (a != '#' || optr.getTop() != '#') {
        cout << "输入字符：" << a << "    ";
        if (!In(a)) {
            //不是运算符则进栈
            number = 0;
            while (!In(a)) {
                number = number * 10 + (a - 48);
                a = getchar();
            }
            opnd.emplace(number);
            cout << "主要操作:Push(OPND," << number << ")       " << endl;
        } else
            switch (Precede(a, optr.getTop())) {
            case '<':
                optr.emplace(a);
                a = getchar();
                cout << "主要操作:Push(OPTR," << a << ")       " << endl;
                break;
            case '=':
                optr.myPop();
                a = getchar();
                cout << "主要操作:Pop(OPTR," << a << ")       " << endl;
                break;
            case '>':
                theta = optr.myPop();
                c = opnd.myPop();
                b = opnd.myPop();
                opnd.emplace(Operate(b, theta, c));
                printf("主要操作:Operate(%d,%c,%d)     \n", b, theta, c);
                break;
            }
        cout << "OPND栈:" << opnd.getTop() << "  OPTR栈:" << optr.getTop() << endl;
    }
    //打印输出表达式值
    printf("\n结果:%d.\n", opnd.getTop());
    return 0;
}

int resultByFunc() {
    IntStack opnd;
    CharStack optr;
    PrioFunct pf;
    pf.build(Table);
    char a = 0;
    char theta;
    int b, c, number = 0;
    optr.emplace('#');
    a = getchar();
    while (a != '#' || optr.getTop() != '#') {
        cout << "输入字符：" << a << "    ";
        if (!In(a)) {
            //不是运算符则进栈
            number = 0;
            while (!In(a)) {
                number = number * 10 + (a - 48);
                a = getchar();
            }
            opnd.emplace(number);
            cout << "主要操作:Push(OPND," << number << ")       " << endl;
        } else
            switch (pf.precede(a, optr.getTop())) {
            case '<':
                optr.emplace(a);
                a = getchar();
                cout << "主要操作:Push(OPTR," << a << ")       " << endl;
                break;
            case '=':
                optr.myPop();
                a = getchar();
                cout << "主要操作:Pop(OPTR," << a << ")       " << endl;
                break;
            case '>':
                theta = optr.myPop();
                c = opnd.myPop();
                b = opnd.myPop();
                opnd.emplace(Operate(b, theta, c));
                printf("主要操作:Operate(%d,%c,%d)     \n", b, theta, c);
                break;
            }
        cout << "OPND栈:" << opnd.getTop() << "  OPTR栈:" << optr.getTop() << endl;
    }
    //打印输出表达式值
    printf("\n结果:%d.\n", opnd.getTop());
    return 0;
}

int main() {
    cout << "[使用优先表]请输入算数表达式并以'#'结尾" << endl;
    result();
    //滤掉回车
    getchar();

    cout << "[使用优先函数]请输入算数表达式并以'#'结尾" << endl;
    resultByFunc();
    system("pause");
    return 0;
}
