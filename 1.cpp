//词法分析程序
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

//单词
struct word {
    string sign;
    int code;

    word() : sign(""), code(0){};
    word(string s, int c) : sign(s), code(c){};
};
//单词表
vector<word> symbol;

//关键字
struct property {
    string symbol;
    string code;
};
//关键字表
vector<property> propertytable;

//字符串变量
struct sign {
    string name;
    string cat;
    string type;
    int value;

    sign() : name(""), cat(""), type(""), value(0){};
    sign(string n) : name(n), cat(""), type(""), value(0){};
    sign(string n, string c, string t, int v) : name(n), cat(c), type(t), value(v){};
};
//字符串变量表
vector<sign> signtable;

bool type = true;

int findcreate(string& p) {
    int i;
    for (i = 0; i < (int)signtable.size(); i++) {
        if (signtable[i].name == p) {
            symbol.emplace_back(word(p, 1));
            return 0;
        }
    }
    // 字符串常量表中没有单词p,就把p存储到字符串常量表和单词表中
    if (i == (int)signtable.size() && type) {
        symbol.emplace_back(word(p, 1));
        signtable.emplace_back(sign(p));
    }
    if (!type)
        cout << p << "未定义!" << endl;
    return 0;
}

void find(string& p) {
    int i;
    //整数
    if (p[0] >= '0' && p[0] <= '9') {
        // num = atoi(p.c_str());
        symbol.emplace_back(word(p, 2));
    } else {
        for (i = 0; i < (int)propertytable.size(); i++) {
            if (propertytable[i].symbol == p) {
                symbol.emplace_back(word(p, atoi(propertytable[i].code.c_str())));
                break;
            }
        }
        if (i == (int)propertytable.size()) {
            //如果符合就是字符串常量
            if (isalpha(p[0]))
                findcreate(p);
            else if (p[0] >= 32)
                symbol.emplace_back(word(p, p[0]));
        }
    }
}

void Test(string& code) {
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
            find(word);
        } else if (*p >= '0' && *p <= '9') {
            //判断单词是否为整数
            word.clear();
            word += *p;
            p++;
            while (*p >= '0' && *p <= '9') {
                word += *p;
                p++;
            }
            find(word);
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
            find(word);
        } else if (*p == ' ') {
            p++;
        } else {
            word.clear();
            word += *p;
            if (word == ";") {
                type = false;
            }
            p++;
            find(word);
        }
    }
}

string prefix;

// 把关键字表中的symbol和code输入到propertytable结构体中
void loadProperty() {
    ifstream fin(prefix + "keyword.txt");
    if (!fin.is_open()) {
        cout << "无法找到关键字表" << endl;
        return;
    }
    property p;
    while (!fin.eof()) {
        fin >> p.symbol >> p.code;
        propertytable.emplace_back(p);
    }
    // 关闭文件
    fin.close();
}

void Finput() {
    // 文件名称字符串
    string file;
    ifstream fin;
    cout << "请输入文件名称：";
    cin >> file;
    fin.open(prefix + file);
    if (!fin.is_open()) {
        cout << "无法打开文件" << endl;
        return;
    }
    // C语言程序文本字符串
    string code((std::istreambuf_iterator<char>(fin)), std::istreambuf_iterator<char>());
    fin.close();
    cout << "C语言程序文本为:" << endl;
    cout << code << endl;
    // 对程序进行词法分析
    Test(code);
}

int main(int argc, char* argv[]) {
    if (argc >= 2)
        prefix = argv[1];
    loadProperty();
    Finput();
    cout << "词法分析结果为：" << endl;
    for (int i = 0; i < (int)symbol.size(); i++) {
        cout << symbol[i].sign << " " << symbol[i].code << endl;
    }
    system("pause");
    return 0;
}