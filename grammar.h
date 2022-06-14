#ifndef GRAMMER_H
#define GRAMMER_H

#include "my_structs.h"
#include "operation.h"
#include "parser.h"
using namespace std;

class GrammarAnalysis {
private:
    class Parser *parser;
    class OperationAnalysis *operation;
    vector<word> *symbol;
    vector<sign> *signtable;
    vector<quad> quadtable;

public:
    GrammarAnalysis(){};
    ~GrammarAnalysis();
    GrammarAnalysis(vector<word> *symbol, vector<sign> *signtable);

    bool program();

    void printQuadTable();
};

#endif