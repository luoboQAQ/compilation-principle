#include "grammar.h"

GrammarAnalysis::~GrammarAnalysis() {
    delete parser;
    delete operation;
}

GrammarAnalysis::GrammarAnalysis(vector<word> *symbol, vector<sign> *signtable) {
    this->parser = new Parser(symbol, signtable, &quadtable);
    this->operation = new OperationAnalysis(parser, symbol);
    this->symbol = symbol;
    this->signtable = signtable;
}

bool GrammarAnalysis::program() {
    operation->sentenceAnalysis();
    return true;
}

void GrammarAnalysis::printQuadTable() {
    for (int i = 0; i < (int)quadtable.size(); i++)
        cout << '(' << quadtable[i].op << "," << quadtable[i].arg1 << "," << quadtable[i].arg2 << "," << quadtable[i].result << ')' << endl;
};