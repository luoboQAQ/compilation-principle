#include "parser.h"

int Parser::findstring(int x) {
    int i;
    for (i = 0; i < symbolTableSize; i++)
        if (atoi(symbolTable[i].sign.c_str()) == x)
            break;
    return i;
}

int Parser::entry(string &p) {
    int i;
    for (i = 0; i < signTableSize; i++) {
        if (signTable[i].name == p) {
            return i;
        }
    }
    if (p == "T") {
        i = 1000 + tempIndex;
        tempIndex++;
    } else {
        i = atoi(p.c_str()) + 10000;
    }
    return i;
}

int Parser::newtemp(char op, int E1_place, int E2_place) {
    int temp, temp1, temp2;
    string T = "T" + to_string(tempIndex);
    if (E1_place >= 10000) {
        temp1 = E1_place - 10000;
    } else {
        temp1 = signTable[E1_place].value;
    }
    if (E2_place >= 10000) {
        temp2 = E2_place - 10000;
    } else {
        temp2 = signTable[E2_place].value;
    }
    if (op == '+') {
        temp = temp1 + temp2;
    }
    if (op == '*') {
        temp = temp1 * temp2;
    }
    if (op == '-') {
        temp = temp1 - temp2;
    }
    if (op == '/') {
        if (temp2 != 0) {
            temp = temp1 / temp2;
        }
    }
    signTable[1000 + tempIndex].name = T;
    signTable[1000 + tempIndex].value = temp;
    return 1000 + tempIndex;
}

void Parser::gen(string op, int arg1, int arg2, string result) {
    quadTable[quadIndex].op = op;
    if (arg1 >= 10000) {
        quadTable[quadIndex].arg1 = symbolTable[findstring(arg1 - 10000)].sign;
    } else if (arg1 == -1) {
        quadTable[quadIndex].arg1 = "-";
    } else {
        quadTable[quadIndex].arg1 = signTable[arg1].name;
    }
    if (arg2 >= 10000) {
        quadTable[quadIndex].arg2 = symbolTable[findstring(arg2 - 10000)].sign;
    } else if (arg2 == -1) {
        quadTable[quadIndex].arg2 = "-";
    } else {
        quadTable[quadIndex].arg2 = signTable[arg2].name;
    }
    if (result == "T") {
        quadTable[quadIndex].result = "T" + to_string(tempIndex);
    } else {
        quadTable[quadIndex].result = result;
    }
    quadIndex++;
    NXQ = quadIndex;
}

void Parser::Backpatch(int p, int t) {
    int Q;
    string q;
    Q = p;
    while (Q != 0) {
        q = quadTable[Q].result;
        quadTable[Q].result = to_string(t);
        Q = atoi(q.c_str());
    }
}

int Parser::Merg(int p1, int p2) {
    int p;
    if (p1 > p2) {
        return p1;
    }
    if (p2 == 0) {
        return p1;
    } else {
        p = p2;
        while (quadTable[p].result != "0") {
            p = atoi(quadTable[p].result.c_str());
        }
        quadTable[p].result = to_string(p1);
        return p2;
    }
}