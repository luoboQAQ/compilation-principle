#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <vector>

#include "my_structs.h"
using namespace std;

/**
 * @brief ��Ԫʽ������
 *
 */
class Parser {
private:
    //��ǰ��ʱ�������±�
    int *temp_index;
    //��ʱ������
    vector<int> signTableTemp;
    vector<word> *symbol;
    vector<sign> *signtable;
    vector<quad> *quadtable;
    int *NXQ;

public:
    Parser();
    Parser(vector<word> *symbol, vector<sign> *signtable, vector<quad> *quadtable, int *temp_index, int *NXQ);

    /**
     * @brief ���ҵ����ڵ��ʱ��е��±�
     *
     * @param x ����
     * @return int �����ڵ��ʱ��е��±�
     */
    int findstring(int x);

    /**
     * @brief ������ķ��ű���ڵ�ַ
     *
     * @param p ����ı���
     * @return int �����ķ��ű���ڵ�ַ\n
     *         >=1000��ʾ����ʱ����\n
     *         >=10000��ʾ�ǳ���
     */
    int entry(string &p);

    /**
     * @brief ����һ���µ���ʱ����
     *
     * @param op �����
     * @param E1_place ��һ���������ķ��ű���ڵ�ַ
     * @param E2_place �ڶ����������ķ��ű���ڵ�ַ
     * @return int �µ���ʱ�����ķ��ű���ڵ�ַ
     */
    int newtemp(char op, int E1_place, int E2_place);

    /**
     * @brief ������Ԫʽ��������Ԫʽ��
     *
     * @param op �����
     * @param arg1 ��һ���������ķ��ű���ڵ�ַ
     * @param arg2 �ڶ����������ķ��ű���ڵ�ַ
     * @param result ����ķ��ű���ڵ�ַ
     */
    void gen(string op, int arg1, int arg2, string result);

    /**
     * @brief ������Ԫʽ��������Ԫʽ��
     *
     * @param op �����
     * @param arg1 ��һ���������ķ��ű���ڵ�ַ
     * @param arg2 �ڶ����������ķ��ű���ڵ�ַ
     * @param result ����ķ��ű���ڵ�ַ
     */
    void gen(char op, int arg1, int arg2, string result);

    void backPatch(int p, int t);

    int merg(int p1, int p2);
};

#endif