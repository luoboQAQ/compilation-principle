#include "combuilder.h"

void ComBuilder::build() {
    int i, j = 0, n, k;
    set<int> lTable;
    //把每个四元式要跳转的序号存入数组arr
    for (i = 1; i < quadIndex; i++) {
        if (isdigit(quadTable[i].result[0])) {
            int arrnum = atoi(quadTable[i].result.c_str());
            lTable.emplace(arrnum);
        }
    }
    unordered_map<int, int> lTableIndex;
    i = 1;
    for (int l : lTable) {
        lTableIndex[l] = i;
        i++;
    }
    i = 1;
    // 从第一个四元式翻译成汇编
    for (i = 1; i < quadIndex; i++) {
        if (lTable.count(i))
            comTable[comIndex].lable = "L" + to_string(lTableIndex[i]);
        if (quadTable[i].op == "jnz") {
            comTable[comIndex].op = "CMP";
            comTable[comIndex].arg1 = quadTable[i].arg1;
            comTable[comIndex].arg2 = "0";
            comIndex++;
            comTable[comIndex].lable = "";
            comTable[comIndex].op = "JNZ";
            comTable[comIndex].arg1 = "L" + to_string(lTableIndex[atoi(quadTable[i].result.c_str())]);
            comTable[comIndex].arg2 = "";
            comIndex++;
        } else if (quadTable[i].op == "j") {
            comTable[comIndex].op = "JMP";
            comTable[comIndex].arg1 = "L" + to_string(lTableIndex[atoi(quadTable[i].result.c_str())]);
            comTable[comIndex].arg2 = "";
            comIndex++;
        } else if (quadTable[i].op == "j>") {
            comTable[comIndex].op = "CMP";
            comTable[comIndex].arg1 = quadTable[i].arg1;
            comTable[comIndex].arg2 = quadTable[i].arg2;
            comIndex++;
            comTable[comIndex].lable = "";
            comTable[comIndex].op = "JA";
            comTable[comIndex].arg1 = "L" + to_string(lTableIndex[atoi(quadTable[i].result.c_str())]);
            comTable[comIndex].arg2 = "";
            comIndex++;
        } else if (quadTable[i].op == "j>=") {
            comTable[comIndex].op = "CMP";
            comTable[comIndex].arg1 = quadTable[i].arg1;
            comTable[comIndex].arg2 = quadTable[i].arg2;
            comIndex++;
            comTable[comIndex].lable = "";
            comTable[comIndex].op = "JAE";
            comTable[comIndex].arg1 = "L" + to_string(lTableIndex[atoi(quadTable[i].result.c_str())]);
            comTable[comIndex].arg2 = "";
            comIndex++;
        } else if (quadTable[i].op == "j<") {
            comTable[comIndex].op = "CMP";
            comTable[comIndex].arg1 = quadTable[i].arg1;
            comTable[comIndex].arg2 = quadTable[i].arg2;
            comIndex++;
            comTable[comIndex].lable = "";
            comTable[comIndex].op = "JB";
            comTable[comIndex].arg1 = "L" + to_string(lTableIndex[atoi(quadTable[i].result.c_str())]);
            comTable[comIndex].arg2 = "";
            comIndex++;
        } else if (quadTable[i].op == "j<=") {
            comTable[comIndex].op = "CMP";
            comTable[comIndex].arg1 = quadTable[i].arg1;
            comTable[comIndex].arg2 = quadTable[i].arg2;
            comIndex++;
            comTable[comIndex].lable = "";
            comTable[comIndex].op = "JBE";
            comTable[comIndex].arg1 = "L" + to_string(lTableIndex[atoi(quadTable[i].result.c_str())]);
            comTable[comIndex].arg2 = "";
            comIndex++;
        } else if (quadTable[i].op == "j==") {
            comTable[comIndex].op = "CMP";
            comTable[comIndex].arg1 = quadTable[i].arg1;
            comTable[comIndex].arg2 = quadTable[i].arg2;
            comIndex++;
            comTable[comIndex].lable = "";
            comTable[comIndex].op = "JE";
            comTable[comIndex].arg1 = "L" + to_string(lTableIndex[atoi(quadTable[i].result.c_str())]);
            comTable[comIndex].arg2 = "";
            comIndex++;
        } else if (quadTable[i].op == "j!=") {
            comTable[comIndex].op = "CMP";
            comTable[comIndex].arg1 = quadTable[i].arg1;
            comTable[comIndex].arg2 = quadTable[i].arg2;
            comIndex++;
            comTable[comIndex].lable = "";
            comTable[comIndex].op = "JNE";
            comTable[comIndex].arg1 = "L" + to_string(lTableIndex[atoi(quadTable[i].result.c_str())]);
            comTable[comIndex].arg2 = "";
            comIndex++;
        } else if (quadTable[i].op == "=") {
            comTable[comIndex].op = "MOV";
            comTable[comIndex].arg1 = "AL";
            comTable[comIndex].arg2 = quadTable[i].arg1;
            comIndex++;
            comTable[comIndex].lable = "";
            comTable[comIndex].op = "MOV";
            comTable[comIndex].arg1 = quadTable[i].result;
            comTable[comIndex].arg2 = "AL";
            comIndex++;
        } else if (quadTable[i].op == "+") {
            comTable[comIndex].op = "MOV";
            comTable[comIndex].arg1 = "AL";
            comTable[comIndex].arg2 = quadTable[i].arg1;
            comIndex++;
            comTable[comIndex].lable = "";
            comTable[comIndex].op = "MOV";
            comTable[comIndex].arg1 = "BL";
            comTable[comIndex].arg2 = quadTable[i].arg2;
            comIndex++;
            comTable[comIndex].lable = "";
            comTable[comIndex].op = "ADD";
            comTable[comIndex].arg1 = "BL";
            comTable[comIndex].arg2 = "AL";
            comIndex++;
            comTable[comIndex].lable = "";
            comTable[comIndex].op = "MOV";
            comTable[comIndex].arg1 = quadTable[i].result;
            comTable[comIndex].arg2 = "BL";
            comIndex++;
        } else if (quadTable[i].op == "-") {
            comTable[comIndex].op = "MOV";
            comTable[comIndex].arg1 = "AL";
            comTable[comIndex].arg2 = quadTable[i].arg1;
            comIndex++;
            comTable[comIndex].lable = "";
            comTable[comIndex].op = "MOV";
            comTable[comIndex].arg1 = "BL";
            comTable[comIndex].arg2 = quadTable[i].arg2;
            comIndex++;
            comTable[comIndex].lable = "";
            comTable[comIndex].op = "SUB";
            comTable[comIndex].arg1 = "BL";
            comTable[comIndex].arg2 = "AL";
            comIndex++;
            comTable[comIndex].lable = "";
            comTable[comIndex].op = "MOV";
            comTable[comIndex].arg1 = quadTable[i].result;
            comTable[comIndex].arg2 = "BL";
            comIndex++;
        } else if (quadTable[i].op == "*") {
            comTable[comIndex].op = "MOV";
            comTable[comIndex].arg1 = "AL";
            comTable[comIndex].arg2 = quadTable[i].arg1;
            comIndex++;
            comTable[comIndex].lable = "";
            comTable[comIndex].op = "MUL";
            comTable[comIndex].arg1 = quadTable[i].arg2;
            comTable[comIndex].arg2 = "";
            comIndex++;
            comTable[comIndex].lable = "";
            comTable[comIndex].op = "MOV";
            comTable[comIndex].arg1 = quadTable[i].result;
            comTable[comIndex].arg2 = "AX";
            comIndex++;
        } else if (quadTable[i].op == "/") {
            comTable[comIndex].op = "MOV";
            comTable[comIndex].arg1 = "AX";
            comTable[comIndex].arg2 = quadTable[i].arg1;
            comIndex++;
            comTable[comIndex].lable = "";
            comTable[comIndex].op = "DIV";
            comTable[comIndex].arg1 = quadTable[i].arg2;
            comTable[comIndex].arg2 = "";
            comIndex++;
            comTable[comIndex].lable = "";
            comTable[comIndex].op = "MOV";
            comTable[comIndex].arg1 = quadTable[i].result;
            comTable[comIndex].arg2 = "AL";
            comIndex++;
        }
    }
}