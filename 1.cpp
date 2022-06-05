//词法分析程序
#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
using namespace std;

const int NUMBER = 300;
const int STRING_LENGTH = 4000;
const int LENGTH = 40;

//储存单词表
struct
{
    char sign[10];
    int code;
} symbol[NUMBER];

// 储存关键字的表
struct
{
    char symbol[30];
    char code[5];
} propertytable[NUMBER];

//储存字符串变量的表
struct
{
    char name[10];
    char cat[10];
    char type[10];
    int value;
} signtable[1150];

int propertytable_count = 0, signtable_count = 0, symbol_count = 0, type = 1;

//把数字字符串转化为整数
int changestring(char *p) {
    int i, num = 0;
    for (i = 0; p[i] != '\0'; i++) {
        num = num * 10 + p[i] - '0';
    }
    return num;
}

int findcreate(char *p) {
    int i;
    for (i = 0; i < signtable_count; i++) {
        if (strcmp(signtable[i].name, p) == 0) {
            strcpy(symbol[symbol_count].sign, p);
            symbol[symbol_count++].code = 1;
            return 0;
        }
    }
    if (i == signtable_count && type)  // 表示字符串常量表中没有单词p,就把p存储到字符串常量表和单词表中
    {
        strcpy(symbol[symbol_count].sign, p);
        symbol[symbol_count++].code = 1;
        strcpy(signtable[signtable_count++].name, p);
    }
    if (type == 0) {
        printf("%snot defined\n", p);
    }
    return 0;
}

void find(char *p) {
    int i, num = 0;
    if (*p >= '0' && *p <= '9')  //整数
    {
        for (i = 0; p[i] != '\0'; i++) {
            num = num * 10 + p[i] - '0';
            symbol[symbol_count].sign[i] = p[i];
        }
        symbol[symbol_count].sign[i] = '\0';
        symbol[symbol_count++].code = 2;
    } else {
        for (i = 0; i < propertytable_count; i++) {
            if (strcmp(propertytable[i].symbol, p) == 0) {
                strcpy(symbol[symbol_count].sign, p);
                symbol[symbol_count++].code = changestring(propertytable[i].code);
                break;
            }
        }
        if (i == propertytable_count) {
            if (*p >= 'A' && *p <= 'Z' || *p >= 'a' && *p <= 'z')  //如果符合就是字符串常量
            {
                findcreate(p);
            } else if (*p >= 32) {
                strcpy(symbol[symbol_count].sign, p);
                symbol[symbol_count++].code = 0;
            }
        }
    }
}

void Test(char *p) {
    int k;
    char word[30];
    while (*p != '\0') {
        if (*p >= 'A' && *p <= 'Z' || *p >= 'a' && *p <= 'z')  // 判断单词是否为字符串
        {
            k = 0;
            word[k++] = *p;
            p++;
            while (*p >= 'A' && *p <= 'Z' || *p >= 'a' && *p <= 'z' || *p >= '0' && *p <= '9' || *p == '_') {
                word[k++] = *p;
                p++;
            }
            word[k] = '\0';
            if (strcmp(word, "int") == 0 || strcmp(word, "float") == 0 || strcmp(word, "char") == 0) {
                type = 1;  // 为1代表int float char 类型的字符串变量
            }
            find(word);
        } else if (*p >= '0' && *p <= '9')  //判断单词是否为整数
        {
            k = 0;
            word[k++] = *p;
            p++;
            while (*p >= '0' && *p <= '9') {
                word[k++] = *p;
                p++;
            }
            word[k] = '\0';
            find(word);
        } else if (*p == '<' || *p == '>' || *p == '=' || *p == '!' || *p == '&' || *p == '|') {
            k = 0;
            word[k++] = *p;
            p++;
            if (*(p - 1) == '&') {
                if (*p == '&') {
                    word[k++] = *p;
                    p++;
                }
            } else if (*(p - 1) == '|') {
                if (*p == '|') {
                    word[k++] = *p;
                    p++;
                }
            } else {
                if (*p == '=') {
                    word[k++] = *p;
                    p++;
                }
            }
            word[k] = '\0';
            find(word);
        } else if (*p == ' ') {
            p++;
        } else {
            k = 0;
            word[k++] = *p;
            word[k] = '\0';
            if (strcmp(word, ";") == 0) {
                type = 0;
            }
            p++;
            find(word);
        }
    }
}

// 把关键字表中的symbol 和 code输入到propertytable结构体中
void Create() {
    int i = 0;
    FILE *fp;
    if ((fp = fopen("D:\\Code\\C++\\CompilationPrinciple\\keyword.txt", "r")) == NULL) {
        printf("keyword.txt not found");
        return;
    }
    while (!feof(fp)) {
        fscanf(fp, "%s %s", propertytable[i++].symbol, propertytable[i].code);
        propertytable_count++;
    }
    fclose(fp);  // 关闭文件
}

void Finput() {
    int i = 0;
    char ch;
    char string[STRING_LENGTH];  // C语言程序文本字符串
    char file[LENGTH];           // 文件名称字符串
    FILE *fp;
    printf("input filename:");
    scanf("%s", file);
    if ((fp = fopen(file, "rb")) == NULL) {
        printf("file not found");
        return;
    }
    ch = fgetc(fp);
    while (ch != EOF)  // 判断程序是否读完
    {
        string[i++] = ch;
        ch = fgetc(fp);
    }
    string[i] = '\0';  // 作为程序字符串结尾标识
    printf("c program is :\n");
    printf("%s\n", string);
    Test(string);  // 对程序进行词法分析
}

int main() {
    Create();
    Finput();
    system("pause");
    return 0;
}