#ifndef LEXICAL_H
#define LEXICAL_H

#include <fstream>
#include <iostream>

#include "my_structs.h"
using namespace std;

class LexicalAnalysis {
private:
    /**
     * @brief 将字符串p存入字符串常量表和单词表中
     *
     * @param p 要保存的字符串
     * @param type 字符串前是否存在类型声明
     * @return bool 是否成功
     */
    bool findcreate(string &p, bool type);

    /**
     * @brief 向单词表中添加程序分析出的单词
     *
     * @param p 要分析的字符串
     * @param type 字符串前是否存在类型声明
     */
    void addSymbol(string &p, bool type);

public:
    /**
     * @brief 把关键字表中的symbol和code输入到propertytable结构体中
     *
     * @param local  文件所在位置
     */
    void loadProperty(string fileName);

    /**
     * @brief 对代码进行词法分析
     *
     * @param code 代码字符串
     */
    void analyse(string &code);
};

#endif