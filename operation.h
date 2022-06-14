#ifndef OPERATION_H
#define OPERATION_H

#include <iostream>
#include <stack>

#include "parser.h"
using namespace std;

class OperationAnalysis {
private:
    // LR分析表
    const int LRTable[14][9] = {
        {3, -1, -1, -1, -1, 2, -1, -1, 1},
        {-1, 4, 5, 6, 7, -1, -1, -2, -1},
        {3, -1, -1, -1, -1, 2, -1, -1, 8},
        {-1, 106, 106, 106, 106, -1, 106, 106, -1},
        {3, -1, -1, -1, -1, 2, -1, -1, 9},
        {3, -1, -1, -1, -1, 2, -1, -1, 10},
        {3, -1, -1, -1, -1, 2, -1, -1, 11},
        {3, -1, -1, -1, -1, 2, -1, -1, 12},
        {-1, 4, 5, 6, 7, -1, 13, -1, -1},
        {-1, 101, 101, 6, 7, -1, 101, 101, -1},
        {-1, 102, 102, 6, 7, -1, 102, 102, -1},
        {-1, 103, 103, 103, 103, -1, 103, 103, -1},
        {-1, 104, 104, 104, 104, -1, 104, 104, -1},
        {-1, 105, 105, 105, 105, -1, 105, 105, -1}};
    Parser* parser;
    vector<word>* symbol;

    /**
     * @brief 获得LR分析表表头的下标
     *
     * @param a 单词序号
     * @return int LR分析表表头的下标
     */
    int getLRIndex(int a);

public:
    OperationAnalysis(){};

    OperationAnalysis(Parser* parser, vector<word>* symbol);

    /**
     * @brief 对代码进行LR语法分析并生成四元式
     *
     * @return 是否分析成功
     */
    bool sentenceAnalysis();
};

#endif