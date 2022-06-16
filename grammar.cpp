#include "grammar.h"

GrammarAnalysis::~GrammarAnalysis() {
    delete parser;
    delete operation;
}

GrammarAnalysis::GrammarAnalysis(vector<word> *symbol, vector<sign> *signtable, vector<quad> *quadtable) {
    this->parser = new Parser(symbol, signtable, quadtable, &temp_index, &NXQ);
    this->operation = new OperationAnalysis(parser, symbol, &symbol_index, &sym, &sym1, &Flag, &Temp);
    this->conditional = new ConditionalAnalyzer(parser, operation, symbol, signtable, &symbol_index, &temp_index, &sym, &sym1, &NXQ, &E_TC, &E_FC);
    this->symbol = symbol;
    this->signtable = signtable;
    this->quadtable = quadtable;
}

bool GrammarAnalysis::program() {
    int temp, q, ffc, Tchain;
    string s_q;
    string tempstring;
    sym1 = (*symbol)[symbol_index++].code;
    if (sym1 >= 27 && sym1 <= 29) {
        sym1 = (*symbol)[symbol_index++].code;
        //;
        while (sym1 != 24) {
            if (sym1 == 1) {
                sym1 = (*symbol)[symbol_index++].code;
                //=
                if (sym1 == 16)
                    program();
                //,
                else if (sym1 == 25)
                    sym1 = (*symbol)[symbol_index++].code;
                //;
                else if (sym1 == 24)
                    break;
                else
                    cout << "´íÎó£º±äÁ¿¶¨Òå´íÎó!" << endl;
            } else {
                cout << "´íÎó£º±äÁ¿¶¨Òå´íÎó!" << endl;
            }
        }
    } else if (sym1 == 1) {
        tempstring = (*symbol)[symbol_index - 1].sign;
        sym1 = (*symbol)[symbol_index++].code;
        if (sym1 == 16) {
            Schain = 0;
            if (operation->sentenceAnalysis()) {
                temp = parser->entry(tempstring);
                if (Flag == 1)
                    parser->gen("=", Temp, -1, (*signtable)[temp].name);
                else
                    parser->gen("=", 1000 + temp_index - 1, -1, (*signtable)[temp].name);
            }
            if (sym1 != 24)
                cout << "´íÎó£ºÈ±ÉÙ;ºÅ!" << endl;
        } else
            cout << "´íÎó£ºÈ±ÉÙ=ºÅ!" << endl;
    } else if (sym1 == 30) {
        // if
        sym1 = (*symbol)[symbol_index++].code;
        if (sym1 == 17) {
            ifFlag = true;
            conditional->analyze();
            if (sym1 == 18) {
                parser->backPatch(E_TC, NXQ);
                ffc = E_FC;
                operation->sentenceAnalysis();
                sym1 = (*symbol)[symbol_index++].code;
                if (sym1 == 31) {
                    q = NXQ;
                    parser->gen("j", -1, -1, "0");
                    parser->backPatch(ffc, NXQ);
                    E_FC = q;
                    Tchain = parser->merg(Schain, q);
                    operation->sentenceAnalysis();
                    Schain = parser->merg(Tchain, Schain);
                } else {
                    symbol_index--;
                    Schain = parser->merg(ffc, Schain);
                }
            } else
                cout << "ifÓï¾äÈ±ÉÙÓÒÀ¨ºÅ" << endl;
        } else
            cout << "ifÓï¾äÈ±ÉÙ×óÀ¨ºÅ" << endl;
    } else if (sym1 == 32) {
        // while
        sym1 = (*symbol)[symbol_index++].code;
        if (sym1 == 17) {
            q = NXQ;
            conditional->analyze();
            if (sym1 == 18) {
                whileFlag = true;
                parser->backPatch(E_TC, NXQ);
                ffc = E_FC;
                operation->sentenceAnalysis();
                parser->backPatch(Schain, NXQ);
                s_q = to_string(q);
                parser->gen("j", -1, -1, s_q);
                Schain = ffc;
                E_FC = ffc;
            } else
                cout << "whileÓï¾äÈ±ÉÙÓÒÀ¨ºÅ" << endl;
        } else
            cout << "whileÓï¾äÈ±ÉÙ×óÀ¨ºÅ" << endl;
    } else if (sym1 == 33) {
        // do
        q = NXQ;
        operation->sentenceAnalysis();
        parser->backPatch(Schain, NXQ);
        sym1 = (*symbol)[symbol_index++].code;
        if (sym1 == 32) {
            sym1 = (*symbol)[symbol_index++].code;
            if (sym1 == 17) {
                conditional->analyze();
                if (sym1 == 18) {
                    doFlag = true;
                    parser->backPatch(E_TC, q);
                    Schain = E_FC;
                } else
                    cout << "do-whileÓï¾äÈ±ÉÙÓÒÀ¨ºÅ" << endl;
            } else
                cout << "do-whileÓï¾äÈ±ÉÙ×óÀ¨ºÅ" << endl;
        }
    }
    return true;
}

bool GrammarAnalysis::analysis() {
    quadtable->emplace_back(quad());
    while (symbol_index < (int)symbol->size()) {
        program();
        if (ifFlag || whileFlag || doFlag) {
            parser->backPatch(E_FC, NXQ);
            ifFlag = false;
            whileFlag = false;
            doFlag = false;
        }
    }
    return true;
}