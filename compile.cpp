#include "compile.h"

Complier::Complier() {
    lexical = new LexicalAnalysis(prefix + "keyword.txt", &symbol, &signtable);
    grammar = new GrammarAnalysis(&symbol, &signtable, &quadtable);
    coder = new Coder(&quadtable);
}

Complier::~Complier() {
    delete lexical;
    delete grammar;
    delete coder;
}

bool Complier::loadCode() {
    string file;
    ifstream fin;
    cout << "请输入文件名称：";
    cin >> file;
    fin.open(prefix + file);
    if (!fin.is_open()) {
        cout << "无法打开文件" << endl;
        system("pause");
        return false;
    }
    // C语言程序文本字符串
    string c((std::istreambuf_iterator<char>(fin)), std::istreambuf_iterator<char>());
    code = c;
    fin.close();
    return true;
}

void Complier::printSymbol() {
    for (int i = 0; i < (int)symbol.size(); i++)
        cout << symbol[i].sign << " " << symbol[i].code << endl;
}

void Complier::printQuadTable() {
    for (int i = 0; i < (int)quadtable.size(); i++)
        cout << '(' << quadtable[i].op << "," << quadtable[i].arg1 << "," << quadtable[i].arg2 << "," << quadtable[i].result << ')' << endl;
}

bool Complier::complie() {
    if (!loadCode()) {
        cout << "文件打开失败！" << endl;
        return false;
    }
    cout << "C语言代码如下: " << endl;
    cout << code << endl;
    cout << "词法分析结果如下：" << endl;
    lexical->test(code);
    printSymbol();
    cout << "四元式如下：" << endl;
    grammar->analysis();
    printQuadTable();
    cout << "汇编代码如下：" << endl;
    coder->quadtocode();
    coder->printCode();
    return true;
}

int main(int argc, char *argv[]) {
    Complier c;
    c.complie();
    system("pause");
    return 0;
}