#ifndef COMPILE_H
#define COMPILE_H
#include <fstream>
#include <iostream>

#include "coder.h"
#include "grammar.h"
#include "lexical.h"
using namespace std;

class Complier {
private:
    //单词表
    vector<word> symbol;
    //字符串变量表
    vector<sign> signtable;
    //四元式表
    vector<quad> quadtable;
    class LexicalAnalysis *lexical;
    class GrammarAnalysis *grammar;
    class Coder *coder;
    string code;
    const string prefix = "D:\\Code\\C++\\CompilationPrinciple\\";

public:
    Complier();
    ~Complier();
    bool loadCode();
    //打印单词表
    void printSymbol();
    void printQuadTable();
    bool complie();
};

#endif