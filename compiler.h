#ifndef COMPILER_H
#define COMPILER_H

#include <iostream>

#include "combuilder.h"
#include "grammar.h"
#include "lexical.h"
#include "my_structs.h"
using namespace std;

property propertyTable[300];
sign signTable[1150];
sym symbolTable[300];
quad quadTable[300];
com comTable[300];
int propertyTableSize = 0, signTableSize = 0, symbolTableSize = 0;
int Flag, tempIndex = 1, quadIndex = 1, NXQ = 1, sym1, symbolIndex = 0, Temp, bracket, E_TC, E_FC, Schain;
bool ifFlag, whileFlag, doFlag;
int comIndex;

//汇编器类
class Compiler {
private:
    //词法分析类
    class LexicalAnalysis lexical;
    //语法分析类
    class GrammarAnalysis grammar;
    //汇编生成类
    class ComBuilder comBuilder;

public:
    /**
     * @brief 初始化编译器
     *
     * @param filename 关键字文件所在位置
     */
    void init(string filename);

    /**
     * @brief 将代码进行编译
     *
     * @param code 要编译的代码
     */
    void compile(string& code);

    //打印符号表
    void printSymbol();

    //打印四元式
    void printQuad();

    //打印汇编代码
    void printCom();
};

#endif