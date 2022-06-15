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
    int symbol_index = 0;
    int temp_index = 0;
    int sym = 0;
    int Flag = 0;
    int Temp = 0;

public:
    GrammarAnalysis(){};
    ~GrammarAnalysis();
    GrammarAnalysis(vector<word> *symbol, vector<sign> *signtable);

    bool program();
    bool analysis();

    void printQuadTable();
};

#endif