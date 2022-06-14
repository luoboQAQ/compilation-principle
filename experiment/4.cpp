#include <stdlib.h>

#include <fstream>
#include <iostream>
#include <string>
using namespace std;

#define MAX 100
//����������ĸ���
int sum = 0;
//����������ʽ���ַ��ĸ���
int m = 0;
//��ʱ�������ַ�
char JG = 'A';
//�������ʽ
string str;
//�����ŵı�־
int token = 0;

//���ļ���������е�ֵ
void change(int e) {
    int f = e + 2;
    char ch = str[f];
    if (ch >= 'A' && ch <= 'Z') {
        for (int l = 0; l < m + 10; l++) {
            if (str[l] == ch)
                str[l] = JG;
        }
    }

    if (str[e] >= 'A' && str[e] <= 'Z') {
        for (int i = 0; i < m; i++) {
            if (str[i] == str[e])
                str[i] = JG;
        }
    }
}

void chengchuchuli(int i, int m) {
    i++;
    for (; i <= m - 1; i++)  //�����˳�����
    {
        if (str[i] == '*' || str[i] == '/') {
            cout << "(" << str[i] << "  " << str[i - 1] << "  " << str[i + 1] << "  " << JG << ")" << endl;
            change(i - 1);
            str[i - 1] = str[i] = str[i + 1] = JG;
            sum--;
            JG++;
        }
    }
}

void jiajianchuli(int j, int m) {
    j++;
    for (; j <= m - 1; j++)  //�����Ӽ�����
    {
        if (str[j] == '+' || str[j] == '-') {
            cout << "(" << str[j] << "  " << str[j - 1] << "  " << str[j + 1] << "  " << JG << ")" << endl;
            change(j - 1);
            str[j - 1] = str[j] = str[j + 1] = JG;
            sum--;
            JG++;
        }
    }
}

/*ɨ��һ����ļ��ж������ʽ*/
void scan(FILE *fin) {
    int p[MAX];
    char ch = 'a';
    int c = -1, q = 0;
    while (ch != EOF) {
        ch = getc(fin);

        while (ch == ' ' || ch == '\n' || ch == '\t') ch = getc(fin);  //�����ո�ͻ��з�

        str[m++] = ch;

        if (ch == '=' || ch == '+' || ch == '-' || ch == '*' || ch == '/')
            sum++;

        else if (ch == '(') {
            p[++c] = m - 1;

        } else if (ch == ')') {
            q = m - 1;
            chengchuchuli(p[c], q);  //�������Ŵ�����������
            jiajianchuli(p[c], q);
            JG--;
            str[p[c]] = str[m - 1] = JG;
            c--;
            JG++;
        }
    }
}

/*�Ա����ǽ��д��������������Ԫʽ*/
void siyuanshi() {
    for (int i = 0; i <= m - 1; i++)  //�����˳�����
    {
        if (str[i] == '*' || str[i] == '/') {
            cout << "(" << str[i] << "  " << str[i - 1] << "  " << str[i + 1] << "  " << JG << ")" << endl;
            change(i - 1);
            str[i - 1] = str[i] = str[i + 1] = JG;
            sum--;
            JG++;
        }
    }

    for (int j = 0; j <= m - 1; j++)  //�����Ӽ�����
    {
        if (str[j] == '+' || str[j] == '-') {
            cout << "(" << str[j] << "  " << str[j - 1] << "  " << str[j + 1] << "  " << JG << ")" << endl;
            change(j - 1);
            str[j - 1] = str[j] = str[j + 1] = JG;
            sum--;
            JG++;
        }
    }

    for (int k = 0; k <= m - 1; k++)  //������ֵ����
    {
        if (str[k] == '=') {
            JG--;
            cout << "(" << str[k] << "  " << str[k + 1] << "  "
                 << "  "
                 << " " << str[k - 1] << ")" << endl;
            sum--;
            change(k + 1);
            str[k - 1] = JG;
        }
    }
}

int main() {
    str.resize(100);
    //������������ļ���
    string in;
    FILE *fin;
    cout << "������������ڵ��ļ���:";
    cin >> in;
    cout << endl;
    if ((fin = fopen(in.c_str(), "r")) == NULL)  //�ж������ļ����Ƿ���ȷ
    {
        cout << endl
             << "Error!" << endl;
    }
    cout << "The result:" << endl;

    scan(fin);  //���ú������ļ��ж������ʽ

    /********����������Ԫʽ�ĺ���********/
    siyuanshi();

    /*********�ж��Ƿ�ɹ�**********/
    if (sum == 0)
        cout << "Success!" << endl;
    else
        cout << "Error!" << endl;

    //�ر��ļ�
    fclose(fin);
    system("pause");
    return 0;
}