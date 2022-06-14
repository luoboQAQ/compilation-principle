#include "operation.h"

OperationAnalysis::OperationAnalysis(Parser* parser, vector<word>* symbol) {
    this->parser = parser;
    this->symbol = symbol;
}

int OperationAnalysis::getLRIndex(int a) {
    int PAT[9] = {'i', 3, 4, 5, 6, 17, 18, '#', 'E'};
    for (int i = 0; i < 9; i++) {
        if (a == PAT[i])
            return i;
    }
    return 7;
}

bool OperationAnalysis::sentenceAnalysis() {
    //当前分析词法下标
    int index = 0;
    int E1_place, E2_place;
    stack<int> s1, s2;
    stack<int> s3;
    s1.emplace(0);
    //压入#
    s2.emplace(24);
    s3.emplace('@');
    //读入的单词序号
    int sym = symbol->at(index++).code;
    if (sym == 1 || sym == 2)
        sym = 'i';
    //是否分析成功
    bool acc = false;
    while (!acc) {
        int action = LRTable[s1.top()][getLRIndex(sym)];
        if (action == -1) {
            cout << "错误：语法分析失败" << endl;
            return false;
        } else if (action == -2)
            acc = true;
        else if (action >= 0 && action < 100) {
            //移进操作
            s1.emplace(action);
            s2.emplace(sym);
            if (sym == 'i')
                s3.emplace(parser->entry(symbol->at(index - 1).sign));
            else
                s3.emplace('@');
            sym = (*symbol)[index++].code;
            if (sym == 1 || sym == 2)
                sym = 'i';
        } else if (action >= 100 && action < 200) {
            char op = 0;
            //规约操作
            switch (action) {
            //规约:E -> E + E
            case 101:
                op = '+';
                break;
            //规约:E -> E - E
            case 102:
                op = '-';
                break;
            //规约:E -> E * E
            case 103:
                op = '*';
                break;
            //规约:E -> E / E
            case 104:
                op = '/';
                break;
            //规约:E -> (E)
            case 105: {
                s1.pop();
                s1.pop();
                s1.pop();
                s2.pop();
                s2.pop();
                s2.pop();
                s2.emplace('E');
                s3.pop();
                int temp = s3.top();
                s3.pop();
                s3.pop();
                action = s1.top();
                s1.emplace(LRTable[action][getLRIndex('E')]);
                s3.emplace(temp);
                break;
            }
            //规约:E -> i
            case 106:
                s1.pop();
                s2.pop();
                s2.emplace('E');
                action = s1.top();
                s1.emplace(LRTable[action][getLRIndex('E')]);
                break;
            }
            if (op) {
                s1.pop();
                s1.pop();
                s1.pop();
                s2.pop();
                s2.pop();
                s2.pop();
                s2.emplace('E');
                E2_place = s3.top();
                s3.pop();
                s3.pop();
                E1_place = s3.top();
                s3.pop();
                s3.emplace(parser->newtemp(op, E1_place, E2_place));
                parser->gen(op, E1_place, E2_place, "T");
                action = s1.top();
                s1.emplace(LRTable[action][getLRIndex('E')]);
            }
        }
    }
    return true;
}