#ifndef COMBUILDER_H
#define COMBUILDER_H

#include <iostream>
#include <set>
#include <unordered_map>

#include "my_structs.h"
using namespace std;

//汇编程序生成类
class ComBuilder {
private:
    //打印变量段
    void printVariables();

    //打印堆栈段
    void printStacks();

    //打印代码段
    void printCode();

public:
    //将四元式转换成汇编代码
    void build();

    //打印汇编代码
    void printCom();
};

#endif