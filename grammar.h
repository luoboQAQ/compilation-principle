#ifndef GRAMMER_H
#define GRAMMER_H

#include "conditional.h"
#include "my_structs.h"
#include "operation.h"
#include "parser.h"
using namespace std;

//语法分析类
class GrammarAnalysis {
private:
    // 四元式工具类
    class Parser *parser;
    //四则运算语法分析类
    class OperationAnalysis *operation;
    //条件语句语法分析类
    class ConditionalAnalyzer *conditional;

    //递归下降语法分析
    void program();

public:
    GrammarAnalysis();
    ~GrammarAnalysis();
    //对代码进行语法分析
    void analyse();
};

#endif