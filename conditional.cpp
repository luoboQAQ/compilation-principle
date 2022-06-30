#include "conditional.h"

int ConditionalAnalyzer::getLRIndex(int a) {
    int i;
    int PAT[] = {'i', 'r', 17, 18, 34, 14, 15, '#', 'E', 'A', 'O'};
    i = 0;
    if (a >= 7 && a <= 12) {
        return 1;
    }
    while (PAT[i] != a && i <= 10) {
        i++;
    }
    if (i == 2) {
        bracket++;
    }
    if (i == 3) {
        bracket--;
    }
    if (bracket == -1 || i == 11) {
        i = 7;
        bracket = 0;
    }
    return i;
}

bool ConditionalAnalyzer::analyse() {
    int sym, acc, t, j, temp, E1_place, E2_place, x, l, op;
    int E_temp, EA_FC, EO_TC, NXQ_temp = 0;
    string tempstring;
    stack<int> s1, s2, s3;
    s1.emplace(0);
    s2.emplace(24);
    s3.emplace('@');
    sym1 = symbolTable[symbolIndex++].code;
    if (sym1 == 1 || sym1 == 2) {
        tempstring = symbolTable[symbolIndex - 1].sign.c_str();
        sym1 = symbolTable[symbolIndex].code;
        if (sym1 >= 3 && sym1 <= 6 || sym1 == 16) {
            NXQ_temp = NXQ;
            if (sym1 == 16) {
                symbolIndex++;
                if (operation->analyse()) {
                    temp = parser->entry(tempstring);
                    parser->gen("=", 1000 + tempIndex - 1, -1, signTable[temp].name);
                    symbolIndex--;
                } else
                    ;
            } else {
                tempstring = "T";
                symbolIndex--;
                operation->analyse();
                tempIndex--;
                symbolIndex--;
            }
        }
        sym = 'i';
    } else {
        sym = sym1;
    }
    acc = false;
    while (!acc) {
        l = s1.top();
        j = getLRIndex(sym);
        t = LRTable[l][j];
        if (t == -1) {
            cout << "´íÎó£ºÌõ¼þÓï¾äÓï·¨´íÎó" << endl;
            return false;
        } else if (t == -2) {
            acc = true;
        } else if (t >= 0 && t < 100) {
            s1.emplace(t);
            s2.emplace(sym);
            if (sym == 'i') {
                s3.emplace(parser->entry(tempstring));
            } else {
                s3.emplace('@');
            }
            sym1 = symbolTable[symbolIndex++].code;
            if (sym1 == 1 || sym1 == 2) {
                tempstring = symbolTable[symbolIndex - 1].sign.c_str();
                sym1 = symbolTable[symbolIndex].code;
                if (sym1 >= 3 && sym1 <= 6 || sym1 == 16) {
                    NXQ_temp = NXQ;
                    if (sym1 == 16) {
                        symbolIndex++;
                        if (operation->analyse()) {
                            temp = parser->entry(tempstring);
                            parser->gen("=", 1000 + tempIndex - 1, -1, signTable[temp].name);
                            symbolIndex--;
                        }
                    } else {
                        tempstring = "T";
                        symbolIndex--;
                        operation->analyse();
                        tempIndex--;
                        symbolIndex--;
                    }
                }
                sym = 'i';
            } else {
                sym = sym1;
            }
        } else if (t >= 100 && t <= 200)
            switch (t) {
            case 101:
                s1.pop();
                s2.pop();
                E1_place = s3.top();
                t = s1.top();
                s2.emplace('E');
                j = getLRIndex('E');
                x = LRTable[t][j];
                s1.emplace(x);
                E_TC = NXQ;
                E_FC = NXQ + 1;
                parser->gen("jnz", E1_place, -1, "0");
                parser->gen("j", -1, -1, "0");
                break;
            case 102:
                s1.pop();
                s1.pop();
                s1.pop();
                s2.pop();
                op = s2.top();
                s2.pop();
                s2.pop();
                E2_place = s3.top();
                s3.pop();
                s3.pop();
                E1_place = s3.top();
                s3.pop();
                t = s1.top();
                s2.emplace('E');
                j = getLRIndex('E');
                x = LRTable[t][j];
                s1.emplace(x);
                E_TC = NXQ;
                E_FC = NXQ + 1;
                if (op == 7) {
                    parser->gen("j<", E1_place, E2_place, "0");
                } else if (op == 8) {
                    parser->gen("j<=", E1_place, E2_place, "0");
                } else if (op == 9) {
                    parser->gen("j==", E1_place, E2_place, "0");
                } else if (op == 10) {
                    parser->gen("j!=", E1_place, E2_place, "0");
                } else if (op == 11) {
                    parser->gen("j>", E1_place, E2_place, "0");
                } else if (op == 12) {
                    parser->gen("j>=", E1_place, E2_place, "0");
                }
                parser->gen("j", -1, -1, "0");
                s3.emplace('@');
                break;
            case 103:
                s1.pop();
                s1.pop();
                s1.pop();
                s2.pop();
                s2.pop();
                s2.pop();
                s3.pop();
                temp = s3.top();
                s3.pop();
                s3.pop();
                t = s1.top();
                s2.emplace('E');
                j = getLRIndex('E');
                x = LRTable[t][j];
                s1.emplace(x);
                s3.emplace(temp);
                break;
            case 104:
                s1.pop();
                s1.pop();
                s2.pop();
                s2.pop();
                s3.pop();
                s3.pop();
                t = s1.top();
                s2.emplace('E');
                j = getLRIndex('E');
                x = LRTable[t][j];
                s1.emplace(x);
                E_temp = E_FC;
                E_FC = E_TC;
                E_TC = E_temp;
                s3.emplace('@');
                break;
            case 105:
                s1.pop();
                s1.pop();
                s2.pop();
                s2.pop();
                s3.pop();
                s3.pop();
                t = s1.top();
                s2.emplace('A');
                j = getLRIndex('A');
                x = LRTable[t][j];
                s1.emplace(x);
                if (NXQ_temp > 1) {
                    parser->Backpatch(E_TC, NXQ_temp);
                    NXQ_temp = 0;
                } else {
                    parser->Backpatch(E_TC, NXQ);
                }
                EA_FC = E_FC;
                s3.emplace('@');
                break;
            case 106:
                s1.pop();
                s1.pop();
                s2.pop();
                s2.pop();
                s3.pop();
                s3.pop();
                t = s1.top();
                s2.emplace('E');
                j = getLRIndex('E');
                x = LRTable[t][j];
                s1.emplace(x);
                E_FC = parser->Merg(EA_FC, E_FC);
                s3.emplace('@');
                break;
            case 107:
                s1.pop();
                s1.pop();
                s2.pop();
                s2.pop();
                s3.pop();
                s3.pop();
                t = s1.top();
                s2.emplace('O');
                j = getLRIndex('O');
                x = LRTable[t][j];
                s1.emplace(x);
                if (NXQ_temp > 1) {
                    parser->Backpatch(E_FC, NXQ_temp);
                    NXQ_temp = 0;
                } else {
                    parser->Backpatch(E_FC, NXQ);
                }
                EO_TC = E_TC;
                s3.emplace('@');
                break;
            case 108:
                s1.pop();
                s1.pop();
                s2.pop();
                s2.pop();
                s3.pop();
                s3.pop();
                t = s1.top();
                s2.emplace('E');
                j = getLRIndex('E');
                x = LRTable[t][j];
                s1.emplace(x);
                E_TC = parser->Merg(EO_TC, E_TC);
                s3.emplace('@');
                break;
            }
    }
    return true;
}