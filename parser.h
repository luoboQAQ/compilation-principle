#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <vector>

#include "my_structs.h"
using namespace std;

class Parser {
private:
    //当前临时变量的下标
    int index = 0;
    //临时变量表
    vector<int> signTableTemp;
    vector<word> *symbol;
    vector<sign> *signtable;
    vector<quad> *quadtable;

public:
    Parser();

    Parser(vector<word> *symbol, vector<sign> *signtable, vector<quad> *quadtable);

    int findstring(int x);

    // 查变量的符号表入口地址
    int entry(string &p);

    int newtemp(char op, int E1_place, int E2_place);

    // 产生四元式
    void gen(string op, int arg1, int arg2, string result);

    void gen(char op, int arg1, int arg2, string result);
};

#endif