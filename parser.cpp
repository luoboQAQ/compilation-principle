#include "parser.h"

Parser::Parser(vector<word> *symbol, vector<sign> *signtable, vector<quad> *quadtable, int *temp_index) {
    this->symbol = symbol;
    this->signtable = signtable;
    this->quadtable = quadtable;
    this->temp_index = temp_index;
}

int Parser::findstring(int x) {
    int i;
    for (i = 0; i < (int)symbol->size(); i++)
        if (atoi(symbol->at(i).sign.c_str()) == x)
            break;
    return i;
};

int Parser::entry(string &p) {
    int i;
    for (i = 0; i < (int)signtable->size(); i++) {
        if (signtable->at(i).name == p) {
            return i;
        }
    }
    if (p == "T") {
        i = 1000 + *temp_index;
        (*temp_index)++;
    } else {
        i = stoi(p.c_str()) + 10000;
    }
    return i;
};
int Parser::newtemp(char op, int E1_place, int E2_place) {
    int temp, temp1, temp2;
    string T = 'T' + to_string(*temp_index);
    if (E1_place >= 10000)
        temp1 = E1_place - 10000;
    else if (E1_place >= 1000)
        temp1 = signTableTemp[E1_place - 1000];
    else
        temp1 = signtable->at(E1_place).value;
    if (E2_place >= 10000)
        temp2 = E2_place - 10000;
    else if (E2_place >= 1000)
        temp2 = signTableTemp[E2_place - 1000];
    else
        temp2 = signtable->at(E2_place).value;
    if (op == '+')
        temp = temp1 + temp2;
    else if (op == '*')
        temp = temp1 * temp2;
    else if (op == '-')
        temp = temp1 - temp2;
    else if (op == '/') {
        if (temp2 != 0)
            temp = temp1 / temp2;
    }
    signTableTemp.emplace_back(temp);
    return 1000 + *temp_index;
}
void Parser::gen(string op, int arg1, int arg2, string result) {
    quad q;
    q.op = op;
    if (arg1 >= 10000)
        q.arg1 = symbol->at(findstring(arg1 - 10000)).sign;
    else if (arg1 == -1)
        q.arg1 = "-";
    else if (arg1 >= 1000)
        q.arg1 = "T" + to_string(arg1 - 1000);
    else
        q.arg1 = signtable->at(arg1).name;
    if (arg2 >= 10000)
        q.arg2 = symbol->at(findstring(arg2 - 10000)).sign;
    else if (arg2 == -1)
        q.arg2 = "-";
    else if (arg2 >= 1000)
        q.arg2 = "T" + to_string(arg2 - 1000);
    else
        q.arg2 = signtable->at(arg2).name;
    if (result == "T") {
        q.result = "T" + to_string(*temp_index);
    } else {
        q.result = result;
    }
    quadtable->emplace_back(q);
    (*temp_index)++;
    // NXQ = quad_i;
}

void Parser::gen(char op, int arg1, int arg2, string result) {
    string op1(1, op);
    gen(op1, arg1, arg2, result);
}