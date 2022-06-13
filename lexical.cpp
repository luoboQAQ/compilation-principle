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

/**
 * @brief 词法分析程序
 *
 */
class LexicalAnalysis {
private:
    //关键字
    struct property {
        string symbol;
        string code;
    };
    //关键字表
    vector<property> propertytable;

    /**
     * @brief 将字符串p存入字符串常量表和单词表中
     *
     * @param p 要保存的字符串
     * @param type 字符串前是否存在类型声明
     * @return bool 是否成功
     */
    bool findcreate(string& p, bool type) {
        int i;
        for (i = 0; i < (int)signtable.size(); i++) {
            if (signtable[i].name == p) {
                symbol.emplace_back(word(p, 1));
                return true;
            }
        }
        // 字符串常量表中没有单词p,就把p存储到字符串常量表和单词表中
        if (i == (int)signtable.size() && type) {
            symbol.emplace_back(word(p, 1));
            signtable.emplace_back(sign(p));
        }
        if (!type) {
            cout << p << "未定义!" << endl;
            return false;
        }
        return true;
    }
    /**
     * @brief 向单词表中添加程序分析出的单词
     *
     * @param p 要分析的字符串
     * @param type 字符串前是否存在类型声明
     */
    void find(string& p, bool type) {
        int i;
        //整数
        if (p[0] >= '0' && p[0] <= '9') {
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
                    findcreate(p, type);
                else if (p[0] >= 32)
                    symbol.emplace_back(word(p, p[0]));
            }
        }
    }

public:
    //单词表
    vector<word> symbol;
    //字符串变量表
    vector<sign> signtable;
    /**
     * @brief 把关键字表中的symbol和code输入到propertytable结构体中
     *
     * @param prefix  文件所在位置,调试用,默认为空
     */
    void loadProperty(string prefix = "") {
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

    /**
     * @brief 对代码进行词法分析
     *
     * @param code 代码字符串
     */
    void test(string& code) {
        bool type = true;
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

    //打印单词表
    void printSymbol() {
        for (int i = 0; i < (int)symbol.size(); i++)
            cout << symbol[i].sign << " " << symbol[i].code << endl;
    }
};

int main(int argc, char* argv[]) {
    string prefix;
    if (argc >= 2)
        prefix = argv[1];
    LexicalAnalysis la;
    la.loadProperty(prefix);
    // 文件名称字符串
    string file;
    ifstream fin;
    cout << "请输入文件名称：";
    cin >> file;
    fin.open(prefix + file);
    if (!fin.is_open()) {
        cout << "无法打开文件" << endl;
        system("pause");
        return 1;
    }
    // C语言程序文本字符串
    string code((std::istreambuf_iterator<char>(fin)), std::istreambuf_iterator<char>());
    fin.close();
    cout << "C语言程序文本为:" << endl;
    cout << code << endl;
    // 对程序进行词法分析
    la.test(code);
    cout << "词法分析结果为：" << endl;
    la.printSymbol();
    system("pause");
    return 0;
}