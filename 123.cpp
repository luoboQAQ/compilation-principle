#include <fstream>
#include <iostream>
#include <set>
#include <stack>
#include <string>
#include <unordered_map>
using namespace std;

const string PREFIX = "D:\\Code\\C++\\CP\\code\\";

const int MAX_NUM = 300;

int LRTable[][9] =
    {{3, -1, -1, -1, -1, 2, -1, -1, 1},
     {-1, 4, 5, 6, 7, -1, -1, -2, -1},
     {3, -1, -1, -1, -1, 2, -1, -1, 8},
     {-1, 106, 106, 106, 106, -1, 106, 106, -1},
     {3, -1, -1, -1, -1, 2, -1, -1, 9},
     {3, -1, -1, -1, -1, 2, -1, -1, 10},
     {3, -1, -1, -1, -1, 2, -1, -1, 11},
     {3, -1, -1, -1, -1, 2, -1, -1, 12},
     {-1, 4, 5, 6, 7, -1, 13, -1, -1},
     {-1, 101, 101, 6, 7, -1, 101, 101, -1},
     {-1, 102, 102, 6, 7, -1, 102, 102, -1},
     {-1, 103, 103, 103, 103, -1, 103, 103, -1},
     {-1, 104, 104, 104, 104, -1, 104, 104, -1},
     {-1, 105, 105, 105, 105, -1, 105, 105, -1}};
int action2[][11] =
    {{1, -1, 4, -1, 5, -1, -1, -1, 13, 7, 8},
     {-1, 2, -1, 101, -1, 101, 101, 101, -1, -1, -1},
     {3, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
     {-1, -1, -1, 102, -1, 102, 102, 102, -1, -1, -1},
     {1, -1, 4, -1, 5, -1, -1, -1, 11, 7, 8},
     {1, -1, 4, -1, 5, -1, -1, -1, 6, 7, 8},
     {-1, -1, -1, 104, -1, 104, 104, 104, -1, -1, -1},
     {1, -1, 4, -1, 5, -1, -1, -1, 14, 7, 8},
     {1, -1, 4, -1, 5, -1, -1, -1, 15, 7, 8},
     {105, -1, 105, -1, 105, -1, -1, -1, -1, -1, -1},
     {107, -1, 107, -1, 107, -1, -1, -1, -1, -1, -1},
     {-1, -1, -1, 12, -1, 9, 10, -1, -1, -1, -1},
     {-1, -1, -1, 103, -1, 103, 103, 103, -1, -1, -1},
     {-1, -1, -1, -1, -1, 9, 10, -2, -1, -1, -1},
     {-1, -1, -1, 106, -1, 106, 106, 106, -1, -1, -1},
     {-1, -1, -1, 108, -1, 9, 108, 108, -1, -1, -1}};
struct
{
    string symbol;
    string code;
} propertyTable[MAX_NUM];  // 储存关键字的表
struct
{
    string name;
    string cat;
    string type;
    int value;
} signTable[1150];  //储存字符串变量的表
struct
{
    string sign;
    int code;
} symbolTable[MAX_NUM];  //储存单词表
struct
{
    string op;
    string arg1;
    string arg2;
    string result;
} quadTable[MAX_NUM];  //储存四元式的表
struct
{
    string lable;
    string op;
    string arg1;
    string arg2;
} comTable[MAX_NUM];  // 储存汇编程序表
int propertyTableSize = 0, signTableSize = 0, symbolTableSize = 0;
int Flag, tempIndex = 1, quadIndex = 1, NXQ = 1, sym1, symbolIndex = 0, Temp, bracket, E_TC, E_FC, Schain;
bool ifFlag, whileFlag, doFlag;
int comIndex;

void Create()  // 把关键字表中的symbol 和 code输入到propertytable结构体中
{
    int i = 0;
    ifstream fin(PREFIX + "keyword.txt");
    if (!fin.is_open()) {
        cout << "无法找到关键字表" << endl;
        return;
    }
    while (!fin.eof()) {
        fin >> propertyTable[i].symbol >> propertyTable[i].code;
        i++;
        propertyTableSize++;
    }
    fin.close();
}

int findstring(int x) {
    int i;
    for (i = 0; atoi(symbolTable[i].sign.c_str()) != x; i++)
        ;
    return i;
}

bool findcreate(string &p, bool type) {
    int i;
    for (i = 0; i < signTableSize; i++) {
        if (signTable[i].name == p) {
            symbolTable[symbolTableSize].sign = p;
            symbolTable[symbolTableSize++].code = 1;
            return 0;
        }
    }
    //字符串常量表中没有单词p,就把p存储到字符串常量表和单词表中
    if (i == signTableSize && type) {
        symbolTable[symbolTableSize].sign = p;
        symbolTable[symbolTableSize++].code = 1;
        signTable[signTableSize++].name = p;
    }
    if (!type) {
        cout << p << "未定义!" << endl;
        return false;
    }
    return true;
}

void find(string &p, bool type) {
    int i;
    if (p[0] >= '0' && p[0] <= '9')  //整数
    {
        symbolTable[symbolTableSize].sign = p;
        symbolTable[symbolTableSize++].code = 2;
    } else {
        for (i = 0; i < propertyTableSize; i++) {
            if (propertyTable[i].symbol == p) {
                symbolTable[symbolTableSize].sign = p;
                symbolTable[symbolTableSize++].code = atoi(propertyTable[i].code.c_str());
                break;
            }
        }
        if (i == propertyTableSize) {
            if (isalpha(p[0])) {
                //如果符合就是字符串常量
                findcreate(p, type);
            } else if (p[0] >= 32) {
                symbolTable[symbolTableSize].sign = p;
                symbolTable[symbolTableSize++].code = 0;
            }
        }
    }
}

void Test(string &code) {
    bool type = true;
    int k;
    string word;
    string::iterator p = code.begin();
    while (p < code.end()) {
        if (isalpha(*p)) {
            // 判断单词是否为字符串
            word.clear();
            word += *p;
            p++;
            while (isalnum(*p) || *p == '_') {
                word += *p;
                p++;
            }
            if (word == "int" || word == "float" || word == "char")
                // 为1代表int float char 类型的字符串变量
                type = true;
            find(word, type);
        } else if (*p >= '0' && *p <= '9') {
            //判断单词是否为整数
            word.clear();
            word += *p;
            p++;
            while (*p >= '0' && *p <= '9') {
                word += *p;
                p++;
            }
            find(word, type);
        } else if (*p == '<' || *p == '>' || *p == '=' || *p == '!' || *p == '&' || *p == '|') {
            word.clear();
            word += *p;
            p++;
            if (*(p - 1) == '&' && *p == '&') {
                word += *p;
                p++;
            } else if (*(p - 1) == '|' && *p == '|') {
                word += *p;
                p++;
            } else if (*p == '=') {
                word += *p;
                p++;
            }
            find(word, type);
        } else if (*p == ' ') {
            p++;
        } else {
            word.clear();
            word += *p;
            if (word == ";") {
                type = false;
            }
            p++;
            find(word, type);
        }
    }
}

int precede1(int a) {
    int i;
    int PAT[] = {'i', 3, 4, 5, 6, 17, 18, '#', 'E'};
    i = 0;
    while (PAT[i] != a && i <= 8) {
        i++;
    }
    if (i == 9) {
        i = 7;
    }
    return i;
}

// 查变量的符号表入口地址
int entry(string p) {
    int i;
    for (i = 0; i < signTableSize; i++) {
        if (signTable[i].name == p) {
            return i;
        }
    }
    if (p == "T") {
        i = 1000 + tempIndex;
        tempIndex++;
    } else {
        i = atoi(p.c_str()) + 10000;
    }
    return i;
}

int newtemp(char op, int E1_place, int E2_place) {
    int temp, temp1, temp2;
    string T = "T" + to_string(tempIndex);
    if (E1_place >= 10000) {
        temp1 = E1_place - 10000;
    } else {
        temp1 = signTable[E1_place].value;
    }
    if (E2_place >= 10000) {
        temp2 = E2_place - 10000;
    } else {
        temp2 = signTable[E2_place].value;
    }
    if (op == '+') {
        temp = temp1 + temp2;
    }
    if (op == '*') {
        temp = temp1 * temp2;
    }
    if (op == '-') {
        temp = temp1 - temp2;
    }
    if (op == '/') {
        if (temp2 != 0) {
            temp = temp1 / temp2;
        }
    }
    signTable[1000 + tempIndex].name = T;
    signTable[1000 + tempIndex].value = temp;
    return 1000 + tempIndex;
}

void gen(string op, int arg1, int arg2, string result)  // 产生四元式
{
    quadTable[quadIndex].op = op;
    if (arg1 >= 10000) {
        quadTable[quadIndex].arg1 = symbolTable[findstring(arg1 - 10000)].sign;
    } else if (arg1 == -1) {
        quadTable[quadIndex].arg1 = "-";
    } else {
        quadTable[quadIndex].arg1 = signTable[arg1].name;
    }
    if (arg2 >= 10000) {
        quadTable[quadIndex].arg2 = symbolTable[findstring(arg2 - 10000)].sign;
    } else if (arg2 == -1) {
        quadTable[quadIndex].arg2 = "-";
    } else {
        quadTable[quadIndex].arg2 = signTable[arg2].name;
    }
    if (result == "T") {
        quadTable[quadIndex].result = "T" + to_string(tempIndex);
    } else {
        quadTable[quadIndex].result = result;
    }
    quadIndex++;
    NXQ = quadIndex;
}

bool E() {
    int sym, acc, t, j, E1_place, E2_place, x, l;
    stack<int> s1, s2, s3;
    s1.emplace(0);
    //压入#
    s2.emplace(24);
    s3.emplace('@');
    Flag = 0;
    sym1 = symbolTable[symbolIndex++].code;
    if (sym1 == 1 || sym1 == 2) {
        sym = 'i';
    } else {
        sym = sym1;
    }
    acc = false;
    while (!acc) {
        l = s1.top();
        j = precede1(sym);
        t = LRTable[l][j];
        if (t == -1) {
            cout << "错误：四则运算语法错误" << endl;
            return false;
        }
        if (t == -2) {
            acc = true;
        }
        if (t >= 0 && t < 100) {
            s1.emplace(t);
            s2.emplace(sym);
            if (sym == 'i') {
                s3.emplace(entry(symbolTable[symbolIndex - 1].sign));
            } else {
                s3.emplace('@');
            }
            sym1 = symbolTable[symbolIndex++].code;
            if (sym1 == 1 || sym1 == 2) {
                sym = 'i';
            } else {
                sym = sym1;
            }
        }
        if (t >= 100 && t <= 200) {
            char op = 0;
            switch (t) {
            case 101:
                op = '+';
                break;

            case 102:
                op = '-';
                break;

            case 103:
                op = '*';
                break;

            case 104:
                op = '/';
                break;

            case 105:
                s1.pop();
                s1.pop();
                s1.pop();
                s2.pop();
                s2.pop();
                s2.pop();
                s3.pop();
                Temp = s3.top();
                s3.pop();
                s3.pop();
                t = s1.top();
                s2.emplace('E');
                j = precede1('E');
                x = LRTable[t][j];
                s1.emplace(x);
                s3.emplace(Temp);
                break;

            case 106:
                s1.pop();
                s2.pop();
                s2.emplace('E');
                Temp = s3.top();
                t = s1.top();
                j = precede1('E');
                x = LRTable[t][j];
                s1.emplace(x);
                Flag++;
            }
            if (op) {
                s1.pop();
                s1.pop();
                s1.pop();
                s2.pop();
                s2.pop();
                s2.pop();
                E2_place = s3.top();
                s3.pop();
                s3.pop();
                E1_place = s3.top();
                Temp = newtemp(op, E1_place, E2_place);
                s3.pop();
                t = s1.top();
                s2.emplace('E');
                j = precede1('E');
                x = LRTable[t][j];
                s1.emplace(x);
                string op1(1, op);
                gen(op1, E1_place, E2_place, "T");
                tempIndex++;
                s3.emplace(Temp);
            }
        }
    }
    return true;
}

int precede2(int a) {
    int i;
    int PAT[] = {'i', 'r', 17, 18, 34, 14, 15, '#', 'E', 'A', 'O'};
    i = 0;
    if (a >= 7 && a <= 12) {
        return 1;
    }
    while (PAT[i] != a && i <= 10) {
        i++;
    }
    if (i == 2) {
        bracket++;
    }
    if (i == 3) {
        bracket--;
    }
    if (bracket == -1 || i == 11) {
        i = 7;
        bracket = 0;
    }
    return i;
}

void Backpatch(int p, int t) {
    int Q;
    string q;
    Q = p;
    while (Q != 0) {
        q = quadTable[Q].result;
        quadTable[Q].result = to_string(t);
        Q = atoi(q.c_str());
    }
}

int Merg(int p1, int p2) {
    int p;
    if (p1 > p2) {
        return p1;
    }
    if (p2 == 0) {
        return p1;
    } else {
        p = p2;
        while (quadTable[p].result != "0") {
            p = atoi(quadTable[p].result.c_str());
        }
        quadTable[p].result = to_string(p1);
        return p2;
    }
}

bool EB() {
    int sym, acc, t, j, temp, E1_place, E2_place, x, l, op;
    int E_temp, EA_FC, EO_TC, NXQ_temp = 0;
    string tempstring;
    stack<int> s1, s2, s3;
    s1.emplace(0);
    s2.emplace(24);
    s3.emplace('@');
    sym1 = symbolTable[symbolIndex++].code;
    if (sym1 == 1 || sym1 == 2) {
        tempstring = symbolTable[symbolIndex - 1].sign.c_str();
        sym1 = symbolTable[symbolIndex].code;
        if (sym1 >= 3 && sym1 <= 6 || sym1 == 16) {
            NXQ_temp = NXQ;
            if (sym1 == 16) {
                symbolIndex++;
                if (E()) {
                    temp = entry(tempstring);
                    gen("=", 1000 + tempIndex - 1, -1, signTable[temp].name);
                    symbolIndex--;
                } else
                    ;
            } else {
                tempstring = "T";
                symbolIndex--;
                E();
                tempIndex--;
                symbolIndex--;
            }
        }
        sym = 'i';
    } else {
        sym = sym1;
    }
    acc = false;
    while (!acc) {
        l = s1.top();
        j = precede2(sym);
        t = action2[l][j];
        if (t == -1) {
            cout << "错误：条件语句语法错误" << endl;
            return false;
        }
        if (t == -2) {
            acc = true;
        }
        if (t >= 0 && t < 100) {
            s1.emplace(t);
            s2.emplace(sym);
            if (sym == 'i') {
                s3.emplace(entry(tempstring));
            } else {
                s3.emplace('@');
            }
            sym1 = symbolTable[symbolIndex++].code;
            if (sym1 == 1 || sym1 == 2) {
                tempstring = symbolTable[symbolIndex - 1].sign.c_str();
                sym1 = symbolTable[symbolIndex].code;
                if (sym1 >= 3 && sym1 <= 6 || sym1 == 16) {
                    NXQ_temp = NXQ;
                    if (sym1 == 16) {
                        symbolIndex++;
                        if (E()) {
                            temp = entry(tempstring);
                            gen("=", 1000 + tempIndex - 1, -1, signTable[temp].name);
                            symbolIndex--;
                        }
                    } else {
                        tempstring = "T";
                        symbolIndex--;
                        E();
                        tempIndex--;
                        symbolIndex--;
                    }
                }
                sym = 'i';
            } else {
                sym = sym1;
            }
        }
        if (t >= 100 && t <= 200)
            switch (t) {
            case 101: {
                s1.pop();
                s2.pop();
                E1_place = s3.top();
                t = s1.top();
                s2.emplace('E');
                j = precede2('E');
                x = action2[t][j];
                s1.emplace(x);
                E_TC = NXQ;
                E_FC = NXQ + 1;
                gen("jnz", E1_place, -1, "0");
                gen("j", -1, -1, "0");
                break;
            }
            case 102: {
                s1.pop();
                s1.pop();
                s1.pop();
                s2.pop();
                op = s2.top();
                s2.pop();
                s2.pop();
                E2_place = s3.top();
                s3.pop();
                s3.pop();
                E1_place = s3.top();
                s3.pop();
                t = s1.top();
                s2.emplace('E');
                j = precede2('E');
                x = action2[t][j];
                s1.emplace(x);
                E_TC = NXQ;
                E_FC = NXQ + 1;
                if (op == 7) {
                    gen("j<", E1_place, E2_place, "0");
                }
                if (op == 8) {
                    gen("j<=", E1_place, E2_place, "0");
                }
                if (op == 9) {
                    gen("j==", E1_place, E2_place, "0");
                }
                if (op == 10) {
                    gen("j!=", E1_place, E2_place, "0");
                }
                if (op == 11) {
                    gen("j>", E1_place, E2_place, "0");
                }
                if (op == 12) {
                    gen("j>=", E1_place, E2_place, "0");
                }
                gen("j", -1, -1, "0");
                s3.emplace('@');
                break;
            }
            case 103: {
                s1.pop();
                s1.pop();
                s1.pop();
                s2.pop();
                s2.pop();
                s2.pop();
                s3.pop();
                temp = s3.top();
                s3.pop();
                s3.pop();
                t = s1.top();
                s2.emplace('E');
                j = precede2('E');
                x = action2[t][j];
                s1.emplace(x);
                s3.emplace(temp);
                break;
            }
            case 104: {
                s1.pop();
                s1.pop();
                s2.pop();
                s2.pop();
                s3.pop();
                s3.pop();
                t = s1.top();
                s2.emplace('E');
                j = precede2('E');
                x = action2[t][j];
                s1.emplace(x);
                E_temp = E_FC;
                E_FC = E_TC;
                E_TC = E_temp;
                s3.emplace('@');
                break;
            }
            case 105: {
                s1.pop();
                s1.pop();
                s2.pop();
                s2.pop();
                s3.pop();
                s3.pop();
                t = s1.top();
                s2.emplace('A');
                j = precede2('A');
                x = action2[t][j];
                s1.emplace(x);
                if (NXQ_temp > 1) {
                    Backpatch(E_TC, NXQ_temp);
                    NXQ_temp = 0;
                } else {
                    Backpatch(E_TC, NXQ);
                }
                EA_FC = E_FC;
                s3.emplace('@');
                break;
            }
            case 106: {
                s1.pop();
                s1.pop();
                s2.pop();
                s2.pop();
                s3.pop();
                s3.pop();
                t = s1.top();
                s2.emplace('E');
                j = precede2('E');
                x = action2[t][j];
                s1.emplace(x);
                E_FC = Merg(EA_FC, E_FC);
                s3.emplace('@');
                break;
            }
            case 107: {
                s1.pop();
                s1.pop();
                s2.pop();
                s2.pop();
                s3.pop();
                s3.pop();
                t = s1.top();
                s2.emplace('O');
                j = precede2('O');
                x = action2[t][j];
                s1.emplace(x);
                if (NXQ_temp > 1) {
                    Backpatch(E_FC, NXQ_temp);
                    NXQ_temp = 0;
                } else {
                    Backpatch(E_FC, NXQ);
                }
                EO_TC = E_TC;
                s3.emplace('@');
                break;
            }
            case 108: {
                s1.pop();
                s1.pop();
                s2.pop();
                s2.pop();
                s3.pop();
                s3.pop();
                t = s1.top();
                s2.emplace('E');
                j = precede2('E');
                x = action2[t][j];
                s1.emplace(x);
                E_TC = Merg(EO_TC, E_TC);
                s3.emplace('@');
                break;
            }
            }
    }
    return true;
}

void Program() {
    int temp, q, ffc, Tchain;
    char s_q[10];
    string tempstring;
    sym1 = symbolTable[symbolIndex++].code;
    if (sym1 >= 27 && sym1 <= 29) {
        sym1 = symbolTable[symbolIndex++].code;
        while (sym1 != 24) {
            //;
            if (sym1 == 1) {
                sym1 = symbolTable[symbolIndex++].code;
                if (sym1 == 16)
                    //=
                    Program();
                else if (sym1 == 25)
                    //,
                    sym1 = symbolTable[symbolIndex++].code;
                else if (sym1 == 24)
                    //;
                    break;
                else
                    cout << "错误的变量定义" << endl;

            } else
                cout << "错误的变量定义" << endl;
        }
    } else if (sym1 == 1) {
        tempstring = symbolTable[symbolIndex - 1].sign.c_str();
        sym1 = symbolTable[symbolIndex++].code;
        if (sym1 == 16) {
            Schain = 0;
            if (E()) {
                temp = entry(tempstring);
                if (Flag == 1) {
                    gen("=", Temp, -1, signTable[temp].name);
                } else {
                    gen("=", 1000 + tempIndex - 1, -1, signTable[temp].name);
                }
            }
            if (sym1 != 24)
                cout << "赋值语句缺少;" << endl;
        } else
            cout << "赋值语句缺少=" << endl;
    } else if (sym1 == 30) {
        // if
        sym1 = symbolTable[symbolIndex++].code;
        if (sym1 == 17) {
            ifFlag = true;
            EB();
            if (sym1 == 18) {
                Backpatch(E_TC, NXQ);
                ffc = E_FC;
                Program();
                sym1 = symbolTable[symbolIndex++].code;
                if (sym1 == 31) {
                    q = NXQ;
                    gen("j", -1, -1, "0");
                    Backpatch(ffc, NXQ);
                    E_FC = q;
                    Tchain = Merg(Schain, q);
                    Program();
                    Schain = Merg(Tchain, Schain);
                } else {
                    symbolIndex--;
                    Schain = Merg(ffc, Schain);
                }
            } else
                cout << "if语句缺少右括号" << endl;
        } else
            cout << "if语句缺少左括号" << endl;
    } else if (sym1 == 32) {
        // while
        sym1 = symbolTable[symbolIndex++].code;
        if (sym1 == 17) {
            q = NXQ;
            EB();
            if (sym1 == 18) {
                whileFlag = true;
                Backpatch(E_TC, NXQ);
                ffc = E_FC;
                Program();
                Backpatch(Schain, NXQ);
                if (q < 10) {
                    s_q[0] = q + '0';
                    s_q[1] = '\0';
                } else {
                    s_q[0] = q / 10 + '0';
                    s_q[1] = q % 10 + '0';
                    s_q[2] = '\0';
                }
                gen("j", -1, -1, s_q);
                Schain = ffc;
                E_FC = ffc;
            } else
                cout << "while语句缺少右括号" << endl;
        } else
            cout << "while语句缺少左括号" << endl;
    } else if (sym1 == 33) {
        // do
        q = NXQ;
        Program();
        Backpatch(Schain, NXQ);
        sym1 = symbolTable[symbolIndex++].code;
        if (sym1 == 32) {
            sym1 = symbolTable[symbolIndex++].code;
            if (sym1 == 17) {
                EB();
                if (sym1 == 18) {
                    doFlag = true;
                    Backpatch(E_TC, q);
                    Schain = E_FC;
                } else
                    cout << "do-while语句缺少右括号" << endl;
            } else
                cout << "do-while语句缺少左括号" << endl;
        }
    }
}

void Printquad() {
    int i;
    cout << "四元式如下：" << endl;
    for (i = 1; i < quadIndex; i++) {
        cout << '(' << i << "): ";
        cout << '(' << quadTable[i].op << "," << quadTable[i].arg1 << "," << quadTable[i].arg2 << "," << quadTable[i].result << ')' << endl;
    }
}

//四元式翻译成汇编
void quadtocom() {
    int i, j = 0, n, k;
    set<int> lTable;
    //把每个四元式要跳转的序号存入数组arr
    for (i = 1; i < quadIndex; i++) {
        if (isdigit(quadTable[i].result[0])) {
            int arrnum = atoi(quadTable[i].result.c_str());
            lTable.emplace(arrnum);
        }
    }
    unordered_map<int, int> lTableIndex;
    i = 1;
    for (int l : lTable) {
        lTableIndex[l] = i;
        i++;
    }
    i = 1;
    // 从第一个四元式翻译成汇编
    for (i = 1; i < quadIndex; i++) {
        if (lTable.count(i))
            comTable[comIndex].lable = "L" + to_string(lTableIndex[i]);
        if (quadTable[i].op == "jnz") {
            comTable[comIndex].op = "CMP";
            comTable[comIndex].arg1 = quadTable[i].arg1;
            comTable[comIndex].arg2 = "0";
            comIndex++;
            comTable[comIndex].lable = "";
            comTable[comIndex].op = "JNZ";
            comTable[comIndex].arg1 = "L" + to_string(lTableIndex[atoi(quadTable[i].result.c_str())]);
            comTable[comIndex].arg2 = "";
            comIndex++;
        } else if (quadTable[i].op == "j") {
            comTable[comIndex].op = "JMP";
            comTable[comIndex].arg1 = "L" + to_string(lTableIndex[atoi(quadTable[i].result.c_str())]);
            comTable[comIndex].arg2 = "";
            comIndex++;
        } else if (quadTable[i].op == "j>") {
            comTable[comIndex].op = "CMP";
            comTable[comIndex].arg1 = quadTable[i].arg1;
            comTable[comIndex].arg2 = quadTable[i].arg2;
            comIndex++;
            comTable[comIndex].lable = "";
            comTable[comIndex].op = "JA";
            comTable[comIndex].arg1 = "L" + to_string(lTableIndex[atoi(quadTable[i].result.c_str())]);
            comTable[comIndex].arg2 = "";
            comIndex++;
        } else if (quadTable[i].op == "j>=") {
            comTable[comIndex].op = "CMP";
            comTable[comIndex].arg1 = quadTable[i].arg1;
            comTable[comIndex].arg2 = quadTable[i].arg2;
            comIndex++;
            comTable[comIndex].lable = "";
            comTable[comIndex].op = "JAE";
            comTable[comIndex].arg1 = "L" + to_string(lTableIndex[atoi(quadTable[i].result.c_str())]);
            comTable[comIndex].arg2 = "";
            comIndex++;
        } else if (quadTable[i].op == "j<") {
            comTable[comIndex].op = "CMP";
            comTable[comIndex].arg1 = quadTable[i].arg1;
            comTable[comIndex].arg2 = quadTable[i].arg2;
            comIndex++;
            comTable[comIndex].lable = "";
            comTable[comIndex].op = "JB";
            comTable[comIndex].arg1 = "L" + to_string(lTableIndex[atoi(quadTable[i].result.c_str())]);
            comTable[comIndex].arg2 = "";
            comIndex++;
        } else if (quadTable[i].op == "j<=") {
            comTable[comIndex].op = "CMP";
            comTable[comIndex].arg1 = quadTable[i].arg1;
            comTable[comIndex].arg2 = quadTable[i].arg2;
            comIndex++;
            comTable[comIndex].lable = "";
            comTable[comIndex].op = "JBE";
            comTable[comIndex].arg1 = "L" + to_string(lTableIndex[atoi(quadTable[i].result.c_str())]);
            comTable[comIndex].arg2 = "";
            comIndex++;
        } else if (quadTable[i].op == "j==") {
            comTable[comIndex].op = "CMP";
            comTable[comIndex].arg1 = quadTable[i].arg1;
            comTable[comIndex].arg2 = quadTable[i].arg2;
            comIndex++;
            comTable[comIndex].lable = "";
            comTable[comIndex].op = "JE";
            comTable[comIndex].arg1 = "L" + to_string(lTableIndex[atoi(quadTable[i].result.c_str())]);
            comTable[comIndex].arg2 = "";
            comIndex++;
        } else if (quadTable[i].op == "j!=") {
            comTable[comIndex].op = "CMP";
            comTable[comIndex].arg1 = quadTable[i].arg1;
            comTable[comIndex].arg2 = quadTable[i].arg2;
            comIndex++;
            comTable[comIndex].lable = "";
            comTable[comIndex].op = "JNE";
            comTable[comIndex].arg1 = "L" + to_string(lTableIndex[atoi(quadTable[i].result.c_str())]);
            comTable[comIndex].arg2 = "";
            comIndex++;
        } else if (quadTable[i].op == "=") {
            comTable[comIndex].op = "MOV";
            comTable[comIndex].arg1 = "R0";
            comTable[comIndex].arg2 = quadTable[i].arg1;
            comIndex++;
            comTable[comIndex].lable = "";
            comTable[comIndex].op = "MOV";
            comTable[comIndex].arg1 = quadTable[i].result;
            comTable[comIndex].arg2 = "R0";
            comIndex++;
        } else if (quadTable[i].op == "+") {
            comTable[comIndex].op = "MOV";
            comTable[comIndex].arg1 = "R0";
            comTable[comIndex].arg2 = quadTable[i].arg1;
            comIndex++;
            comTable[comIndex].lable = "";
            comTable[comIndex].op = "MOV";
            comTable[comIndex].arg1 = "R1";
            comTable[comIndex].arg2 = quadTable[i].arg2;
            comIndex++;
            comTable[comIndex].lable = "";
            comTable[comIndex].op = "ADD";
            comTable[comIndex].arg1 = "R1";
            comTable[comIndex].arg2 = "R0";
            comIndex++;
            comTable[comIndex].lable = "";
            comTable[comIndex].op = "MOV";
            comTable[comIndex].arg1 = quadTable[i].result;
            comTable[comIndex].arg2 = "R1";
            comIndex++;
        } else if (quadTable[i].op == "-") {
            comTable[comIndex].op = "MOV";
            comTable[comIndex].arg1 = "R0";
            comTable[comIndex].arg2 = quadTable[i].arg1;
            comIndex++;
            comTable[comIndex].lable = "";
            comTable[comIndex].op = "MOV";
            comTable[comIndex].arg1 = "R1";
            comTable[comIndex].arg2 = quadTable[i].arg2;
            comIndex++;
            comTable[comIndex].lable = "";
            comTable[comIndex].op = "SUB";
            comTable[comIndex].arg1 = "R1";
            comTable[comIndex].arg2 = "R0";
            comIndex++;
            comTable[comIndex].lable = "";
            comTable[comIndex].op = "MOV";
            comTable[comIndex].arg1 = quadTable[i].result;
            comTable[comIndex].arg2 = "R1";
            comIndex++;
        } else if (quadTable[i].op == "*") {
            comTable[comIndex].op = "MOV";
            comTable[comIndex].arg1 = "AL";
            comTable[comIndex].arg2 = quadTable[i].arg1;
            comIndex++;
            comTable[comIndex].lable = "";
            comTable[comIndex].op = "MUL";
            comTable[comIndex].arg1 = quadTable[i].arg2;
            comTable[comIndex].arg2 = "";
            comIndex++;
            comTable[comIndex].lable = "";
            comTable[comIndex].op = "MOV";
            comTable[comIndex].arg1 = quadTable[i].result;
            comTable[comIndex].arg2 = "AX";
            comIndex++;
        } else if (quadTable[i].op == "/") {
            comTable[comIndex].op = "MOV";
            comTable[comIndex].arg1 = "AX";
            comTable[comIndex].arg2 = quadTable[i].arg1;
            comIndex++;
            comTable[comIndex].lable = "";
            comTable[comIndex].op = "DIV";
            comTable[comIndex].arg1 = quadTable[i].arg2;
            comTable[comIndex].arg2 = "";
            comIndex++;
            comTable[comIndex].lable = "";
            comTable[comIndex].op = "MOV";
            comTable[comIndex].arg1 = quadTable[i].result;
            comTable[comIndex].arg2 = "AL";
            comIndex++;
        }
    }
}

void printcom() {
    int i;
    for (i = 0; i < comIndex; i++) {
        if (!comTable[i].lable.empty())
            cout << comTable[i].lable << ": " << comTable[i].op << " " << comTable[i].arg1;
        else
            cout << "    " << comTable[i].op << " " << comTable[i].arg1;
        if (!comTable[i].arg2.empty())
            cout << "," << comTable[i].arg2;
        cout << endl;
    }
}

void Finput() {
    string file;
    ifstream fin;
    cout << "请输入文件名称：";
    cin >> file;
    fin.open(PREFIX + file);
    if (!fin.is_open()) {
        cout << "无法打开文件" << endl;
        system("pause");
        return;
    }
    // C语言程序文本字符串
    string code((std::istreambuf_iterator<char>(fin)), std::istreambuf_iterator<char>());
    fin.close();
    cout << "C语言代码如下: " << endl;
    cout << code << endl;
    // 对程序进行词法分析
    Test(code);
    while (symbolIndex < symbolTableSize) {
        Program();
        if (ifFlag || whileFlag || doFlag) {
            Backpatch(E_FC, NXQ);
            ifFlag = false;
            whileFlag = false;
            doFlag = false;
        }
    }
    Printquad();
    quadtocom();
    printcom();
}

int main() {
    Create();  //把关键字表中的symbol 和 code输入到propertytable结构体中
    Finput();
}