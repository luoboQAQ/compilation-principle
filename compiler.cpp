#include "compiler.h"

void Compiler::init(string filename) {
    lexical.loadProperty(filename);
}

void Compiler::compile(string& code) {
    lexical.analyse(code);
    grammar.analyse();
}

void Compiler::printSymbol() {
    cout << "词法分析结果如下: " << endl;
    for (int i = 0; i < symbolTableSize; i++)
        cout << symbolTable[i].sign << " " << symbolTable[i].code << endl;
}

void Compiler::printQuad() {
    int i;
    cout << "四元式如下：" << endl;
    for (i = 1; i < quadIndex; i++) {
        cout << '(' << i << "): ";
        cout << '(' << quadTable[i].op << "," << quadTable[i].arg1 << "," << quadTable[i].arg2 << "," << quadTable[i].result << ')' << endl;
    }
}

int main(int argc, char* argv[]) {
    string prefix;
    prefix = "D:\\Code\\C++\\CP\\code\\";
    class Compiler compiler;
    compiler.init(prefix + "keyword.txt");
    string file;
    ifstream fin;
    cout << "请输入文件名称：";
    cin >> file;
    fin.open(prefix + file);
    if (!fin.is_open()) {
        cout << "无法打开文件" << endl;
        system("pause");
        return 1;
    }
    // C语言程序文本字符串
    string code((std::istreambuf_iterator<char>(fin)), std::istreambuf_iterator<char>());
    fin.close();
    cout << "C语言代码如下: " << endl;
    cout << code << endl;
    compiler.compile(code);
    // compiler.printSymbol();
    compiler.printQuad();
    system("pause");
    return 0;
}