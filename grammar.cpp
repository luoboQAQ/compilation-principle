#include "grammar.h"

GrammarAnalysis::GrammarAnalysis() {
    parser = new Parser();
    operation = new OperationAnalysis(parser);
    conditional = new ConditionalAnalyzer(parser, operation);
}

GrammarAnalysis::~GrammarAnalysis() {
    delete parser;
    delete operation;
    delete conditional;
}

void GrammarAnalysis::program() {
    int temp, q, ffc, Tchain;
    string tempstring;
    sym1 = symbolTable[symbolIndex++].code;
    if (sym1 >= 27 && sym1 <= 29) {
        sym1 = symbolTable[symbolIndex++].code;
        while (sym1 != 24) {
            //;
            if (sym1 == 1) {
                sym1 = symbolTable[symbolIndex++].code;
                if (sym1 == 16)
                    //=
                    program();
                else if (sym1 == 25)
                    //,
                    sym1 = symbolTable[symbolIndex++].code;
                else if (sym1 == 24)
                    //;
                    break;
                else
                    cout << "´íÎóµÄ±äÁ¿¶¨Òå" << endl;

            } else
                cout << "´íÎóµÄ±äÁ¿¶¨Òå" << endl;
        }
    } else if (sym1 == 1) {
        tempstring = symbolTable[symbolIndex - 1].sign.c_str();
        sym1 = symbolTable[symbolIndex++].code;
        if (sym1 == 16) {
            Schain = 0;
            if (operation->analyse()) {
                temp = parser->entry(tempstring);
                if (Flag == 1) {
                    parser->gen("=", Temp, -1, signTable[temp].name);
                } else {
                    parser->gen("=", 1000 + tempIndex - 1, -1, signTable[temp].name);
                }
            }
            if (sym1 != 24)
                cout << "¸³ÖµÓï¾äÈ±ÉÙ;" << endl;
        } else
            cout << "¸³ÖµÓï¾äÈ±ÉÙ=" << endl;
    } else if (sym1 == 30) {
        // if
        sym1 = symbolTable[symbolIndex++].code;
        if (sym1 == 17) {
            ifFlag = true;
            conditional->analyse();
            if (sym1 == 18) {
                parser->Backpatch(E_TC, NXQ);
                ffc = E_FC;
                program();
                sym1 = symbolTable[symbolIndex++].code;
                if (sym1 == 31) {
                    q = NXQ;
                    parser->gen("j", -1, -1, "0");
                    parser->Backpatch(ffc, NXQ);
                    E_FC = q;
                    Tchain = parser->Merg(Schain, q);
                    program();
                    Schain = parser->Merg(Tchain, Schain);
                } else {
                    symbolIndex--;
                    Schain = parser->Merg(ffc, Schain);
                }
            } else
                cout << "ifÓï¾äÈ±ÉÙÓÒÀ¨ºÅ" << endl;
        } else
            cout << "ifÓï¾äÈ±ÉÙ×óÀ¨ºÅ" << endl;
    } else if (sym1 == 32) {
        // while
        sym1 = symbolTable[symbolIndex++].code;
        if (sym1 == 17) {
            q = NXQ;
            conditional->analyse();
            if (sym1 == 18) {
                whileFlag = true;
                parser->Backpatch(E_TC, NXQ);
                ffc = E_FC;
                program();
                parser->Backpatch(Schain, NXQ);
                parser->gen("j", -1, -1, to_string(q));
                Schain = ffc;
                E_FC = ffc;
            } else
                cout << "whileÓï¾äÈ±ÉÙÓÒÀ¨ºÅ" << endl;
        } else
            cout << "whileÓï¾äÈ±ÉÙ×óÀ¨ºÅ" << endl;
    } else if (sym1 == 33) {
        // do
        q = NXQ;
        program();
        parser->Backpatch(Schain, NXQ);
        sym1 = symbolTable[symbolIndex++].code;
        if (sym1 == 32) {
            sym1 = symbolTable[symbolIndex++].code;
            if (sym1 == 17) {
                conditional->analyse();
                if (sym1 == 18) {
                    doFlag = true;
                    parser->Backpatch(E_TC, q);
                    Schain = E_FC;
                } else
                    cout << "do-whileÓï¾äÈ±ÉÙÓÒÀ¨ºÅ" << endl;
            } else
                cout << "do-whileÓï¾äÈ±ÉÙ×óÀ¨ºÅ" << endl;
        }
    }
}

void GrammarAnalysis::analyse() {
    while (symbolIndex < symbolTableSize) {
        program();
        if (ifFlag || whileFlag || doFlag) {
            parser->Backpatch(E_FC, NXQ);
            ifFlag = false;
            whileFlag = false;
            doFlag = false;
        }
    }
}