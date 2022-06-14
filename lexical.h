#ifndef LEXICAL_H
#define LEXICAL_H

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "my_structs.h"
using namespace std;

/**
 * @brief 词法分析程序
 *
 */
class LexicalAnalysis {
private:
    //关键字表
    vector<property> propertytable;
    //单词表
    vector<word>* symbol;
    //字符串变量表
    vector<sign>* signtable;

    /**
     * @brief 将字符串p存入字符串常量表和单词表中
     *
     * @param p 要保存的字符串
     * @param type 字符串前是否存在类型声明
     * @return bool 是否成功
     */
    bool findcreate(string& p, bool type);
    /**
     * @brief 向单词表中添加程序分析出的单词
     *
     * @param p 要分析的字符串
     * @param type 字符串前是否存在类型声明
     */
    void find(string& p, bool type);

public:
    LexicalAnalysis(){};
    LexicalAnalysis(vector<word>* sy, vector<sign>* si);
    LexicalAnalysis(string local, vector<word>* sy, vector<sign>* si);

    /**
     * @brief 把关键字表中的symbol和code输入到propertytable结构体中
     *
     * @param local  文件所在位置
     */
    void loadProperty(string local);

    /**
     * @brief 对代码进行词法分析
     *
     * @param code 代码字符串
     */
    void test(string& code);
};

#endif