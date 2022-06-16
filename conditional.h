#ifndef CONDITIONAL_H
#define CONDITIONAL_H

#include <stack>

#include "grammar.h"
#include "my_structs.h"
#include "operation.h"
#include "parser.h"
using namespace std;

class ConditionalAnalyzer {
private:
    // LR·ÖÎö±í
    const int LRTable[16][11] =
        {{1, -1, 4, -1, 5, -1, -1, -1, 13, 7, 8},
         {-1, 2, -1, 101, -1, 101, 101, 101, -1, -1, -1},
         {3, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
         {-1, -1, -1, 102, -1, 102, 102, 102, -1, -1, -1},
         {1, -1, 4, -1, 5, -1, -1, -1, 11, 7, 8},
         {1, -1, 4, -1, 5, -1, -1, -1, 6, 7, 8},
         {-1, -1, -1, 104, -1, 104, 104, 104, -1, -1, -1},
         {1, -1, 4, -1, 5, -1, -1, -1, 14, 7, 8},
         {1, -1, 4, -1, 5, -1, -1, -1, 15, 7, 8},
         {105, -1, 105, -1, 105, -1, -1, -1, -1, -1, -1},
         {107, -1, 107, -1, 107, -1, -1, -1, -1, -1, -1},
         {-1, -1, -1, 12, -1, 9, 10, -1, -1, -1, -1},
         {-1, -1, -1, 103, -1, 103, 103, 103, -1, -1, -1},
         {-1, -1, -1, -1, -1, 9, 10, -2, -1, -1, -1},
         {-1, -1, -1, 106, -1, 106, 106, 106, -1, -1, -1},
         {-1, -1, -1, 108, -1, 9, 108, 108, -1, -1, -1}};
    Parser* parser;
    OperationAnalysis* operation;
    vector<word>* symbol;
    vector<sign>* signtable;
    int* symbol_index;
    int* temp_index;
    int *sym, *sym1;
    int* NXQ;
    int *E_TC, *E_FC;
    int bracket = 0;

    int getLRIndex(int a);

    void operAnalyze(string& tempstring, int& NXQ_temp);

public:
    ConditionalAnalyzer(){};
    ConditionalAnalyzer(Parser* parser, OperationAnalysis* operation,
                        vector<word>* symbol, vector<sign>* signtable, int* symbol_index, int* temp_index,
                        int* sym, int* sym1, int* NXQ, int* E_TC, int* E_FC);
    bool analyze();
};

#endif