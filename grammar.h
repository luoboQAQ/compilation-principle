#ifndef GRAMMER_H
#define GRAMMER_H

#include "conditional.h"
#include "my_structs.h"
#include "operation.h"
#include "parser.h"
using namespace std;

class GrammarAnalysis {
private:
    class Parser *parser;
    class OperationAnalysis *operation;
    class ConditionalAnalyzer *conditional;

    void program();

public:
    GrammarAnalysis();
    ~GrammarAnalysis();
    void analyse();
};

#endif