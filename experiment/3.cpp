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
        cout << "??????????????" << endl;
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

//??????????
vector<vector<char>> Table = {
    {' ', '+', '-', '*', '/', '(', ')', '#'},
    {'+', '>', '>', '<', '<', '<', '>', '>'},
    {'-', '>', '>', '<', '<', '<', '>', '>'},
    {'*', '>', '>', '>', '>', '<', '>', '>'},
    {'/', '>', '>', '>', '>', '<', '>', '>'},
    {'(', '<', '<', '<', '<', '<', '=', ' '},
    {')', '>', '>', '>', '>', ' ', '>', '>'},
    {'#', '<', '<', '<', '<', '<', ' ', '='}};

//??????????????
char Precede(char a, char b) {
    int i, j;
    //??????????
    for (i = 0; i < 8; i++)
        if (Table[0][i] == a)
            break;
    //??????????
    for (j = 0; j < 8; j++)
        if (Table[j][0] == b)
            break;
    return Table[j][i];
}
//????????????????????????????????????????????????????????????
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

//????c????????????
bool In(char c) {
    if (c == '(' || c == '+' || c == '-' || c == '*' || c == '/' || c == ')' || c == '#' || c == '^')
        return true;
    else
        return false;
}

//????
int result() {
    IntStack opnd;
    CharStack optr;
    char a = 0;
    char theta;
    int b, c, number = 0;
    optr.emplace('#');
    a = getchar();
    while (a != '#' || optr.getTop() != '#') {
        cout << "??????????" << a << "    ";
        if (!In(a)) {
            //????????????????
            number = 0;
            while (!In(a)) {
                number = number * 10 + (a - 48);
                a = getchar();
            }
            opnd.emplace(number);
            cout << "????????:Push(OPND," << number << ")       " << endl;
        } else
            switch (Precede(a, optr.getTop())) {
            case '<':
                optr.emplace(a);
                a = getchar();
                cout << "????????:Push(OPTR," << a << ")       " << endl;
                break;
            case '=':
                optr.myPop();
                a = getchar();
                cout << "????????:Pop(OPTR," << a << ")       " << endl;
                break;
            case '>':
                theta = optr.myPop();
                c = opnd.myPop();
                b = opnd.myPop();
                opnd.emplace(Operate(b, theta, c));
                printf("????????:Operate(%d,%c,%d)     \n", b, theta, c);
                break;
            }
        cout << "OPND??:" << opnd.getTop() << "  OPTR??:" << optr.getTop() << endl;
    }
    //????????????????
    printf("\n????:%d.\n", opnd.getTop());
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
        cout << "??????????" << a << "    ";
        if (!In(a)) {
            //????????????????
            number = 0;
            while (!In(a)) {
                number = number * 10 + (a - 48);
                a = getchar();
            }
            opnd.emplace(number);
            cout << "????????:Push(OPND," << number << ")       " << endl;
        } else
            switch (pf.precede(a, optr.getTop())) {
            case '<':
                optr.emplace(a);
                a = getchar();
                cout << "????????:Push(OPTR," << a << ")       " << endl;
                break;
            case '=':
                optr.myPop();
                a = getchar();
                cout << "????????:Pop(OPTR," << a << ")       " << endl;
                break;
            case '>':
                theta = optr.myPop();
                c = opnd.myPop();
                b = opnd.myPop();
                opnd.emplace(Operate(b, theta, c));
                printf("????????:Operate(%d,%c,%d)     \n", b, theta, c);
                break;
            }
        cout << "OPND??:" << opnd.getTop() << "  OPTR??:" << optr.getTop() << endl;
    }
    //????????????????
    printf("\n????:%d.\n", opnd.getTop());
    return 0;
}

int main() {
    cout << "[??????????]????????????????????'#'????" << endl;
    result();
    //????????
    getchar();

    cout << "[????????????]????????????????????'#'????" << endl;
    resultByFunc();
    system("pause");
    return 0;
}
