#ifndef COMPILE_H
#define COMPILE_H
#include <fstream>
#include <iostream>

#include "lexical.h"
using namespace std;

class Complier {
private:
    //单词表
    vector<word> symbol;
    //字符串变量表
    vector<sign> signtable;
    class LexicalAnalysis *lexical;
    string code;
    const string prefix = "D:\\Code\\C++\\CompilationPrinciple\\";

public:
    Complier();
    ~Complier();
    bool loadCode();
    //打印单词表
    void printSymbol();
    bool complie();
};

#endif