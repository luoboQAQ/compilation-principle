#ifndef GRAMMER_H
#define GRAMMER_H

#include "conditional.h"
#include "my_structs.h"
#include "operation.h"
#include "parser.h"
using namespace std;

// �﷨������
class GrammarAnalysis {
private:
    //��Ԫʽ������
    class Parser *parser;
    //���������﷨������
    class OperationAnalysis *operation;
    class ConditionalAnalyzer *conditional;
    vector<word> *symbol;
    vector<sign> *signtable;
    vector<quad> *quadtable;
    int symbol_index = 0;
    int temp_index = 0;
    int sym = 0;
    int Flag = 0;
    int Temp = 0;
    int NXQ = 1;
    int E_TC = 0;
    int E_FC = 0;

    // �﷨����
    bool program();

public:
    GrammarAnalysis(){};
    ~GrammarAnalysis();
    GrammarAnalysis(vector<word> *symbol, vector<sign> *signtable, vector<quad> *quadtable);
    //ʹ�õݹ��½��������﷨
    bool analysis();
};

#endif