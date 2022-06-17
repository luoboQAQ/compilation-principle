#include "lexical.h"

bool LexicalAnalysis::findcreate(string &p, bool type) {
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
void LexicalAnalysis::addSymbol(string &p, bool type) {
    int i;
    if (isdigit(p[0])) {
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

void LexicalAnalysis::loadProperty(string fileName) {
    int i = 0;
    ifstream fin(fileName);
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

void LexicalAnalysis::analyse(string &code) {
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
            addSymbol(word, type);
        } else if (*p >= '0' && *p <= '9') {
            //判断单词是否为整数
            word.clear();
            word += *p;
            p++;
            while (*p >= '0' && *p <= '9') {
                word += *p;
                p++;
            }
            addSymbol(word, type);
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
            addSymbol(word, type);
        } else if (*p == ' ') {
            p++;
        } else {
            word.clear();
            word += *p;
            if (word == ";") {
                type = false;
            }
            p++;
            addSymbol(word, type);
        }
    }
}
