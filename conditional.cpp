#include "conditional.h"

ConditionalAnalyzer::ConditionalAnalyzer(Parser* parser, OperationAnalysis* operation,
                                         vector<word>* symbol, vector<sign>* signtable, int* symbol_index, int* temp_index,
                                         int* sym, int* sym1, int* NXQ, int* E_TC, int* E_FC) {
    this->parser = parser;
    this->operation = operation;
    this->symbol = symbol;
    this->signtable = signtable;
    this->symbol_index = symbol_index;
    this->temp_index = temp_index;
    this->sym = sym;
    this->sym1 = sym1;
    this->NXQ = NXQ;
    this->E_TC = E_TC;
    this->E_FC = E_FC;
}

int ConditionalAnalyzer::getLRIndex(int a) {
    int PAT[] = {'i', 'r', 17, 18, 34, 14, 15, '#', 'E', 'A', 'O'};
    if (a >= 7 && a <= 12)
        return 1;
    int i;
    for (i = 0; i <= 10; i++)
        if (PAT[i] == a)
            break;
    if (i == 2)
        bracket++;
    else if (i == 3)
        bracket--;
    if (bracket == -1 || i == 11) {
        i = 7;
        bracket = 0;
    }
    return i;
}

void ConditionalAnalyzer::operAnalyze(string& tempstring, int& NXQ_temp) {
    *sym1 = (*symbol)[(*symbol_index)++].code;
    if (*sym1 == 1 || *sym1 == 2) {
        tempstring = (*symbol)[(*symbol_index) - 1].sign;
        *sym1 = (*symbol)[(*symbol_index)].code;
        if (*sym1 >= 3 && *sym1 <= 6 || *sym1 == 16) {
            NXQ_temp = *NXQ;
            if (*sym1 == 16) {
                (*symbol_index)++;
                if (operation->sentenceAnalysis()) {
                    parser->gen("=", 1000 + *temp_index - 1, -1, (*signtable)[parser->entry(tempstring)].name);
                    (*symbol_index)--;
                }
            } else {
                tempstring = "T";
                (*symbol_index)--;
                operation->sentenceAnalysis();
                (*temp_index)--;
                (*symbol_index)--;
            }
        }
        *sym = 'i';
    } else
        *sym = *sym1;
}

bool ConditionalAnalyzer::analyze() {
    stack<int> s1, s2, s3;
    string tempstring;
    int NXQ_temp = 0;
    int EA_FC, EO_TC;
    int E1_place, E2_place;
    int op;
    int temp;
    s1.emplace(0);
    s2.emplace(24);
    s3.emplace('@');
    operAnalyze(tempstring, NXQ_temp);
    bool acc = false;
    while (!acc) {
        int action = LRTable[s1.top()][getLRIndex(*sym)];
        if (action == -1) {
            cout << "Ìõ¼þÓï¾ä·ÖÎö´íÎó" << endl;
            return false;
        } else if (action == -2)
            acc = true;
        else if (action >= 0 && action < 100) {
            s1.emplace(action);
            s3.emplace(*sym);
            if (*sym == 'i')
                s3.emplace(parser->entry(tempstring));
            else
                s3.emplace('@');
            operAnalyze(tempstring, NXQ_temp);
        } else if (action >= 100 && action <= 200) {
            switch (action) {
            case 101:
                s1.pop();
                s2.pop();
                E1_place = s3.top();
                action = s1.top();
                s2.emplace('E');
                s1.emplace(LRTable[action][getLRIndex('E')]);
                *E_TC = *NXQ;
                *E_FC = *NXQ + 1;
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
                action = s1.top();
                s2.emplace('E');
                s1.emplace(LRTable[action][getLRIndex('E')]);
                *E_TC = *NXQ;
                *E_FC = *NXQ + 1;
                if (op == 7)
                    parser->gen("j<", E1_place, E2_place, "0");
                else if (op == 8)
                    parser->gen("j<=", E1_place, E2_place, "0");
                else if (op == 9)
                    parser->gen("j==", E1_place, E2_place, "0");
                else if (op == 10)
                    parser->gen("j!=", E1_place, E2_place, "0");
                else if (op == 11)
                    parser->gen("j>", E1_place, E2_place, "0");
                else if (op == 12)
                    parser->gen("j>=", E1_place, E2_place, "0");
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
                s3.emplace('E');
                action = s1.top();
                s1.emplace(LRTable[action][getLRIndex('E')]);
                s3.emplace(temp);
                break;
            case 104:
                s1.pop();
                s1.pop();
                s2.pop();
                s2.pop();
                s3.pop();
                s3.pop();
                s2.emplace('E');
                action = s1.top();
                s1.emplace(LRTable[action][getLRIndex('E')]);
                swap(*E_FC, *E_TC);
                s3.emplace('@');
                break;
            case 105:
                s1.pop();
                s1.pop();
                s2.pop();
                s2.pop();
                s3.pop();
                s3.pop();
                s2.emplace('A');
                action = s1.top();
                s1.emplace(LRTable[action][getLRIndex('A')]);
                if (NXQ_temp > 1) {
                    parser->backPatch(*E_TC, NXQ_temp);
                    NXQ_temp = 0;
                } else
                    parser->backPatch(*E_TC, *NXQ);
                EA_FC = *E_FC;
                s3.emplace('@');
                break;
            case 106:
                s1.pop();
                s1.pop();
                s2.pop();
                s2.pop();
                s3.pop();
                s3.pop();
                s2.emplace('E');
                action = s1.top();
                s1.emplace(LRTable[action][getLRIndex('E')]);
                *E_FC = parser->merg(EA_FC, *E_FC);
                s3.emplace('@');
                break;
            case 107:
                s1.pop();
                s1.pop();
                s2.pop();
                s2.pop();
                s3.pop();
                s3.pop();
                s2.emplace('O');
                action = s1.top();
                s1.emplace(LRTable[action][getLRIndex('O')]);
                if (NXQ_temp > 1) {
                    parser->backPatch(*E_TC, NXQ_temp);
                    NXQ_temp = 0;
                } else
                    parser->backPatch(*E_TC, *NXQ);
                EO_TC = *E_TC;
                s3.emplace('@');
                break;
            case 108:
                s1.pop();
                s1.pop();
                s2.pop();
                s2.pop();
                s3.pop();
                s3.pop();
                s2.emplace('E');
                action = s1.top();
                s1.emplace(LRTable[action][getLRIndex('E')]);
                *E_TC = parser->merg(EO_TC, *E_TC);
                s3.emplace('@');
                break;
            }
        }
    }
    return true;
}