#include "lexical.h"

bool LexicalAnalysis::findcreate(string& p, bool type) {
    int i;
    for (i = 0; i < (int)signtable->size(); i++) {
        if (signtable->at(i).name == p) {
            symbol->emplace_back(word(p, 1));
            return true;
        }
    }
    // 字符串常量表中没有单词p,就把p存储到字符串常量表和单词表中
    if (i == (int)signtable->size() && type) {
        symbol->emplace_back(word(p, 1));
        signtable->emplace_back(sign(p));
    }
    if (!type) {
        cout << p << "未定义!" << endl;
        return false;
    }
    return true;
}

void LexicalAnalysis::find(string& p, bool type) {
    int i;
    //整数
    if (p[0] >= '0' && p[0] <= '9') {
        symbol->emplace_back(word(p, 2));
    } else {
        for (i = 0; i < (int)propertytable.size(); i++) {
            if (propertytable[i].symbol == p) {
                symbol->emplace_back(word(p, atoi(propertytable[i].code.c_str())));
                break;
            }
        }
        if (i == (int)propertytable.size()) {
            //如果符合就是字符串常量
            if (isalpha(p[0]))
                findcreate(p, type);
            else if (p[0] >= 32)
                symbol->emplace_back(word(p, p[0]));
        }
    }
}

void LexicalAnalysis::loadProperty(string local) {
    ifstream fin(local);
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

void LexicalAnalysis::test(string& code) {
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

LexicalAnalysis::LexicalAnalysis(vector<word>* sy, vector<sign>* si) {
    symbol = sy;
    signtable = si;
}

LexicalAnalysis::LexicalAnalysis(string local, vector<word>* sy, vector<sign>* si) {
    loadProperty(local);
    symbol = sy;
    signtable = si;
}