#include "grammar.h"

GrammarAnalysis::~GrammarAnalysis() {
    delete parser;
    delete operation;
}

GrammarAnalysis::GrammarAnalysis(vector<word> *symbol, vector<sign> *signtable) {
    this->parser = new Parser(symbol, signtable, &quadtable, &temp_index);
    this->operation = new OperationAnalysis(parser, symbol, &symbol_index, &sym, &Flag, &Temp);
    this->symbol = symbol;
    this->signtable = signtable;
}

bool GrammarAnalysis::program() {
    int temp, q, ffc, Tchain;
    string s_q;
    string tempstring;
    sym = (*symbol)[symbol_index++].code;
    if (sym >= 27 && sym <= 29) {
        sym = (*symbol)[symbol_index++].code;
        //;
        while (sym != 24) {
            if (sym == 1) {
                sym = (*symbol)[symbol_index++].code;
                //=
                if (sym == 16)
                    program();
                //,
                else if (sym == 25)
                    sym = (*symbol)[symbol_index++].code;
                //;
                else if (sym == 24)
                    break;
                else
                    cout << "���󣺱����������!" << endl;
            } else {
                cout << "���󣺱����������!" << endl;
            }
        }
    } else if (sym == 1) {
        tempstring = (*symbol)[symbol_index - 1].sign;
        sym = (*symbol)[symbol_index++].code;
        if (sym == 16) {
            // Schain=0;
            if (operation->sentenceAnalysis()) {
                temp = parser->entry(tempstring);
                if (Flag == 1)
                    parser->gen("=", Temp, -1, (*signtable)[temp].name);
                else
                    parser->gen("=", 1000 + temp_index - 1, -1, (*signtable)[temp].name);
            }
            if (sym != 24)
                cout << "����ȱ��;��!" << endl;
        } else
            cout << "����ȱ��=��!" << endl;
    }
    return true;
}

bool GrammarAnalysis::analysis() {
    while (symbol_index < (int)symbol->size()) {
        program();
    }
    return true;
}

void GrammarAnalysis::printQuadTable() {
    for (int i = 0; i < (int)quadtable.size(); i++)
        cout << '(' << quadtable[i].op << "," << quadtable[i].arg1 << "," << quadtable[i].arg2 << "," << quadtable[i].result << ')' << endl;
};