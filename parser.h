#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <vector>

#include "my_structs.h"
using namespace std;

/**
 * @brief 四元式分析类
 *
 */
class Parser {
private:
    //当前临时变量的下标
    int *temp_index;
    //临时变量表
    vector<int> signTableTemp;
    vector<word> *symbol;
    vector<sign> *signtable;
    vector<quad> *quadtable;

public:
    Parser();
    Parser(vector<word> *symbol, vector<sign> *signtable, vector<quad> *quadtable, int *temp_index);

    /**
     * @brief 查找单词在单词表中的下标
     *
     * @param x 单词
     * @return int 单词在单词表中的下标
     */
    int findstring(int x);

    /**
     * @brief 查变量的符号表入口地址
     *
     * @param p 待查的变量
     * @return int 变量的符号表入口地址\n
     *         >=1000表示是临时变量\n
     *         >=10000表示是常量
     */
    int entry(string &p);

    /**
     * @brief 产生一个新的临时变量
     *
     * @param op 运算符
     * @param E1_place 第一个操作数的符号表入口地址
     * @param E2_place 第二个操作数的符号表入口地址
     * @return int 新的临时变量的符号表入口地址
     */
    int newtemp(char op, int E1_place, int E2_place);

    /**
     * @brief 产生四元式并填入四元式表
     *
     * @param op 运算符
     * @param arg1 第一个操作数的符号表入口地址
     * @param arg2 第二个操作数的符号表入口地址
     * @param result 结果的符号表入口地址
     */
    void gen(string op, int arg1, int arg2, string result);

    /**
     * @brief 产生四元式并填入四元式表
     *
     * @param op 运算符
     * @param arg1 第一个操作数的符号表入口地址
     * @param arg2 第二个操作数的符号表入口地址
     * @param result 结果的符号表入口地址
     */
    void gen(char op, int arg1, int arg2, string result);
};

#endif