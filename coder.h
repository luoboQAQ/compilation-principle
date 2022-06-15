#ifndef CODER_H
#define CODER_H

#include <iostream>
#include <set>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;
#include "my_structs.h"

class Coder {
private:
    vector<quad> *quadtable;
    struct L {
        int i;
        string li;
        L(){};
        L(int a, string i) : i(a), li(i){};
    };
    //    vector<L> LTable;

    //ª„±‡”Ôæ‰
    struct Com {
        string lable;
        string op;
        string arg1;
        string arg2;
        Com(){};
        Com(string l, string o, string a1, string a2) : lable(l), op(o), arg1(a1), arg2(a2){};
    };
    //ª„±‡”Ôæ‰±Ì
    vector<Com> comTable;

public:
    Coder(){};

    Coder(vector<quad> *t) : quadtable(t){};

    void quadtocode();

    void printCode();
};

#endif