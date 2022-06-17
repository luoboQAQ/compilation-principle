#ifndef MY_STRUCTS_H
#define MY_STRUCTS_H

#include <string>
using namespace std;

//关键字
struct property {
    string symbol;
    string code;
};
//关键字表
extern property propertyTable[300];

//字符串变量
struct sign {
    string name;
    string cat;
    string type;
    int value;
};
//字符串变量表
extern sign signTable[1150];

//单词
struct sym {
    string sign;
    int code;
};
//单词表
extern sym symbolTable[300];

//四元式
struct quad {
    string op;
    string arg1;
    string arg2;
    string result;
};
//四元式表
extern quad quadTable[300];

//汇编代码
struct com {
    string lable;
    string op;
    string arg1;
    string arg2;
};
//汇编代码表
extern com comTable[300];

extern int propertyTableSize, signTableSize, symbolTableSize;
extern int Flag, tempIndex, quadIndex, NXQ, sym1, symbolIndex, Temp, bracket, E_TC, E_FC, Schain;
extern bool ifFlag, whileFlag, doFlag;
extern int comIndex;

#endif