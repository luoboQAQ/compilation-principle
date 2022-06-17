#ifndef COMPILER_H
#define COMPILER_H

#include <iostream>

#include "grammar.h"
#include "lexical.h"
#include "my_structs.h"
using namespace std;

property propertyTable[300];
sign signTable[1150];
sym symbolTable[300];
quad quadTable[300];
com comTable[300];
int propertyTableSize = 0, signTableSize = 0, symbolTableSize = 0;
int Flag, tempIndex = 1, quadIndex = 1, NXQ = 1, sym1, symbolIndex = 0, Temp, bracket, E_TC, E_FC, Schain;
bool ifFlag, whileFlag, doFlag;

class Compiler {
private:
    class LexicalAnalysis lexical;
    class GrammarAnalysis grammar;

public:
    void init(string filename);

    void compile(string& code);

    void printSymbol();

    void printQuad();
};

#endif