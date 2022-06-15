#ifndef CODER_H
#define CODER_H

#include <iostream>
#include <set>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;
#include "my_structs.h"

//汇编生成类
class Coder {
private:
    vector<quad> *quadtable;

    //汇编语句
    struct Com {
        string lable;
        string op;
        string arg1;
        string arg2;
        Com(){};
        Com(string l, string o, string a1, string a2) : lable(l), op(o), arg1(a1), arg2(a2){};
    };
    //汇编语句表
    vector<Com> comTable;

public:
    Coder(){};

    Coder(vector<quad> *t) : quadtable(t){};

    //将四元式转成汇编代码
    void quadtocode();

    //打印汇编代码
    void printCode();
};

#endif