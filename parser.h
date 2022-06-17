#ifndef PARSER_H
#define PARSER_H

#include "my_structs.h"
using namespace std;

//四元式工具类
class Parser {
public:
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
     * @brief 回填过程
     *
     * @param p 开始回填的链首
     * @param t 回填的四元式下标
     */
    void Backpatch(int p, int t);

    /**
     * @brief 并链
     *
     * @param p1 第一条链首
     * @param p2 第二条链首
     * @return int 合并完成后的链首
     */
    int Merg(int p1, int p2);
};

#endif