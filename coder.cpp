#include "coder.h"

void Coder::quadtocode() {
    int i, j = 0, n, k;
    set<int> lTable;
    //把每个四元式要跳转的序号存入LTable
    for (i = 0; i < (int)quadtable->size(); i++) {
        if (isdigit((*quadtable)[i].result[0])) {
            int arrnum = atoi((*quadtable)[i].result.c_str());
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
    for (quad &q : *quadtable) {
        Com com;
        if (lTable.count(i)) {
            com.lable = "L" + to_string(lTableIndex[i]);
        }
        if (q.op == "=") {
            com.op = "MOV";
            com.arg1 = "AL";
            com.arg2 = q.arg1;
            comTable.emplace_back(com);
            comTable.emplace_back(Com("", "MOV", q.result, "AL"));
        } else if (q.op == "+") {
            com.op = "MOV";
            com.arg1 = "AL";
            com.arg2 = q.arg1;
            comTable.emplace_back(com);
            comTable.emplace_back(Com("", "MOV", "BL", q.arg2));
            comTable.emplace_back(Com("", "ADD", "BL", "AL"));
            comTable.emplace_back(Com("", "MOV", q.result, "BL"));
        } else if (q.op == "-") {
            com.op = "MOV";
            com.arg1 = "AL";
            com.arg2 = q.arg1;
            comTable.emplace_back(com);
            comTable.emplace_back(Com("", "MOV", "BL", q.arg2));
            comTable.emplace_back(Com("", "ADD", "BL", "AL"));
            comTable.emplace_back(Com("", "MOV", q.result, "BL"));
        } else if (q.op == "*") {
            com.op = "MOV";
            com.arg1 = "AL";
            com.arg2 = q.arg1;
            comTable.emplace_back(com);
            comTable.emplace_back(Com("", "MUL", q.arg2, ""));
            comTable.emplace_back(Com("", "MOV", q.result, "AX"));
        } else if (q.op == "/") {
            com.op = "MOV";
            com.arg1 = "AX";
            com.arg2 = q.arg1;
            comTable.emplace_back(com);
            comTable.emplace_back(Com("", "DIV", q.arg2, ""));
            comTable.emplace_back(Com("", "MOV", q.result, "AL"));
        }
        i++;
    }
}

void Coder::printCode() {
    for (Com &com : comTable) {
        if (!com.lable.empty())
            cout << com.lable << ": " << com.op << " " << com.arg1;
        else
            cout << "    " << com.op << " " << com.arg1;
        if (!com.arg2.empty())
            cout << "," << com.arg2;
        cout << endl;
    }
}