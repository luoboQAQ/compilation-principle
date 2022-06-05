#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#define length 40
#define string_length 4000
#define number 300
#define null 0
#define STACK_INIT_SIZE 50
int action1[][9]=
	{ { 3,-1,-1,-1,-1,2,-1,-1,1 },{ -1,4,5,6,7,-1,-1,-2,-1 },
    { 3,-1,-1,-1,-1,2,-1,-1,8 },{ -1,106,106,106,106,-1,106,106,-1 },
    { 3,-1,-1,-1,-1,2,-1,-1,9 },{ 3,-1,-1,-1,-1,2,-1,-1,10 },
    { 3,-1,-1,-1,-1,2,-1,-1,11 },{ 3,-1,-1,-1,-1,2,-1,-1,12 },
    { -1,4,5,6,7,-1,13,-1,-1 },{ -1,101,101,6,7,-1,101,101,-1 },
    { -1,102,102,6,7,-1,102,102,-1 },{ -1,103,103,103,103,-1,103,103,-1 },
    { -1,104,104,104,104,-1,104,104,-1 },{ -1,105,105,105,105,-1,105,105,-1 }
};
int action2[][11]=
	{{1,-1,4,-1,5,-1,-1,-1,13,7,8},
    { -1,2,-1,101,-1,101,101,101,-1,-1,-1},
    {3,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
    { -1,-1,-1,102,-1,102,102,102,-1,-1,-1},
    {1,-1,4,-1,5,-1,-1,-1,11,7,8},
    {1,-1,4,-1,5,-1,-1,-1,6,7,8},
    { -1,-1,-1,104,-1,104,104,104,-1,-1,-1},
    {1,-1,4,-1,5,-1,-1,-1,14,7,8},
    {1,-1,4,-1,5,-1,-1,-1,15,7,8},
    {105,-1,105,-1,105,-1,-1,-1,-1,-1,-1},
    {107,-1,107,-1,107,-1,-1,-1,-1,-1,-1},
    { -1,-1,-1,12,-1,9,10,-1,-1,-1,-1},
    { -1,-1,-1,103,-1,103,103,103,-1,-1,-1},
    { -1,-1,-1,-1,-1,9,10,-2,-1,-1,-1},
    { -1,-1,-1,106,-1,106,106,106,-1,-1,-1},
    { -1,-1,-1,108,-1,9,108,108,-1,-1,-1}
};
struct SqStack
{
    int *base;
    int *top;
    int stacksize;
} SqStack;
struct
{
    char symbol[30];
    char code[5];
} propertytable[number]; // 储存关键字的表
struct
{
    char name[10];
    char cat[10];
    char type[10];
    int value;
} signtable[1150]; //储存字符串变量的表
struct
{
    char sign[10];
    int code;
} symbol[number]; //储存单词表
struct
{
    char op[10];
    char arg1[10];
    char arg2[10];
    char result[10];
} quad[number]; //储存四元式的表
struct
{
    char lable[10];
    char op[10];
    char arg1[10];
    char arg2[10];
} com[number]; // 储存汇编程序表
struct
{
    int i;
    char li[10];
} L[number];
int propertytable_count=0,signtable_count=0,symbol_count=0,type=1;
int Flag,T_i=1,quad_i=1,NXQ=1,sym1,E_i=0,Temp,bracket,E_TC,E_FC,Schain;
int if_flag,while_flag,do_flag;
int L_i,c_i,com_i;

void InitStack(struct SqStack *S)
{
    S->base=(int *)malloc(STACK_INIT_SIZE * sizeof(char));
    S->top=S->base;
    S->stacksize=STACK_INIT_SIZE;
}

Push(struct SqStack *S,int e)
{
    *S->top++=e;
}

Pop(struct SqStack *S,int *e)
{
    if(S->top==S->base)
    {
        return 0;
    }
    --S->top;
    *e=*S->top;
    return 0;
}

char GetTop(struct SqStack *S)
{
    int e;
    if(S->top==S->base)
    {
        return 0;
    }
    e=*(S->top-1);
    return e;
}

void Create() // 把关键字表中的symbol 和 code输入到propertytable结构体中
{
    int i=0;
    FILE *fp;
    if ((fp=fopen("keyword.txt","r"))==null)
    {
        printf("keyword.txt not found");
        return;
    }
    while (!feof(fp))
    {
        fscanf(fp,"%s %s",propertytable[i++].symbol,propertytable[i].code);
        propertytable_count++;
    }
    fclose(fp); // 关闭文件
}

int changestring(char *p) //把数字字符串转化为整数
{
    int i,num=0;
    for(i=0; p[i]!='\0'; i++)
    {
        num=num*10+p[i]-'0';
    }
    return num;
}

int findstring(int x)
{
    int i;
    for(i=0; changestring(symbol[i].sign)!=x; i++);
    return i;
}

int findcreate(char *p)
{
    int i;
    for(i=0; i<signtable_count; i++)
    {
        if(strcmp(signtable[i].name,p)==0)
        {
            strcpy(symbol[symbol_count].sign,p);
            symbol[symbol_count++].code=1;
            return 0;
        }
    }
    if(i==signtable_count && type) // 表示字符串常量表中没有单词p,就把p存储到字符串常量表和单词表中
    {
        strcpy(symbol[symbol_count].sign,p);
        symbol[symbol_count++].code=1;
        strcpy(signtable[signtable_count++].name,p);
    }
    if(type==0)
    {
        printf("%snot defined\n",p);
    }
    return 0;
}

void find(char *p)
{
    int i,num=0;
    if(*p>='0'&& *p<='9') //整数
    {
        for(i=0; p[i]!='\0'; i++)
        {
            num=num*10+p[i]-'0';
            symbol[symbol_count].sign[i]=p[i];
        }
        symbol[symbol_count].sign[i]='\0';
        symbol[symbol_count++].code=2;
    }
    else
    {
        for(i=0; i<propertytable_count; i++)
        {
            if(strcmp(propertytable[i].symbol,p)==0)
            {
                strcpy(symbol[symbol_count].sign,p);
                symbol[symbol_count++].code=changestring(propertytable[i].code);
                break;
            }
        }
        if(i==propertytable_count)
        {
            if(*p>='A' && *p<='Z' || *p>='a' && *p<='z') //如果符合就是字符串常量
            {
                findcreate(p);
            }
            else if(*p>=32)
            {
                strcpy(symbol[symbol_count].sign,p);
                symbol[symbol_count++].code=0;
            }
        }
    }
}

void Test(char *p)
{
    int k;
    char word[30];
    while(*p!='\0')
    {
        if(*p>='A' && *p<='Z' || *p>='a' && *p<='z') // 判断单词是否为字符串
        {
            k=0;
            word[k++]=*p;
            p++;
            while(*p>='A' && *p<='Z' || *p>='a' && *p<='z' || *p>='0' && *p<='9' || *p=='_')
            {
                word[k++]=*p;
                p++;
            }
            word[k]='\0';
            if(strcmp(word,"int") == 0 || strcmp(word,"float") == 0 || strcmp(word,"char") == 0)
            {
                type=1;  // 为1代表int float char 类型的字符串变量
            }
            find(word);
        }
        else if(*p>='0' && *p<= '9') //判断单词是否为整数
        {
            k=0;
            word[k++]=*p;
            p++;
            while(*p>='0' && *p<='9')
            {
                word[k++]=*p;
                p++;
            }
            word[k]='\0';
            find(word);
        }
        else if(*p=='<' || *p=='>' || *p=='=' || *p=='!' || *p=='&' || *p=='|')
        {
            k=0;
            word[k++]=*p;
            p++;
            if(*(p-1)=='&')
            {
                if(*p=='&')
                {
                    word[k++]=*p;
                    p++;
                }
            }
            else if(*(p-1)=='|')
            {
                if(*p=='|')
                {
                    word[k++]=*p;
                    p++;
                }
            }
            else
            {
                if(*p=='=')
                {
                    word[k++]=*p;
                    p++;
                }
            }
            word[k]='\0';
            find(word);
        }
        else if(*p==' ')
        {
            p++;
        }
        else
        {
            k=0;
            word[k++]=*p;
            word[k]='\0';
            if(strcmp(word,";") == 0)
            {
                type=0;
            }
            p++;
            find(word);
        }
    }
}

precede1(int a)
{
    int i;
    int PAT[]={'i',3,4,5,6,17,18,'#','E'};
    i=0;
    while(PAT[i]!=a && i<=8)
    {
        i++;
    }
    if(i==9)
    {
        i=7;
    }
    return i;
}

entry(char *p)// 查变量的符号表入口地址
{
    int i;
    for(i=0; i < signtable_count; i++)
    {
        if(strcmp(signtable[i].name,p) == 0)
        {
            return i;
        }
    }
    if(strcmp(p,"T") == 0)
    {
        i=1000 + T_i;
        T_i++;
    }
    else
    {
        i=changestring(p)+10000;
    }
    return i;
}

newtemp(char op,int E1_place,int E2_place)
{
    int temp,temp1,temp2;
    char T[4];
    if (T_i <= 9)
    {
        T[0]='T';
        T[1]=T_i+'0';
        T[2]='\0';
    }
    else
    {
        T[0]='T';
        T[1]=T_i / 10+'0';
        T[2]=T_i % 10+'0';
        T[3]='\0';
    }
    if(E1_place >=10000)
    {
        temp1=E1_place-10000;
    }
    else
    {
        temp1=signtable[E1_place].value;
    }
    if(E2_place>=10000)
    {
        temp2=E2_place-10000;
    }
    else
    {
        temp2=signtable[E2_place].value;
    }
    if(op=='+')
    {
        temp=temp1+temp2;
    }
    if(op =='*')
    {
        temp=temp1 * temp2;
    }
    if(op=='-')
    {
        temp=temp1-temp2;
    }
    if(op=='/')
    {
        if(temp2!=0)
        {
            temp=temp1/temp2;
        }
    }
    strcpy(signtable[1000 + T_i].name,T);
    signtable[1000 + T_i].value=temp;
    return 1000 + T_i;
}

gen(char *op,int arg1,int arg2,char *result) // 产生四元式
{
    strcpy(quad[quad_i].op,op);
    if(arg1 >= 10000)
    {
        strcpy(quad[quad_i].arg1,symbol[findstring(arg1 - 10000)].sign);
    }
    else if(arg1==-1)
    {
        strcpy(quad[quad_i].arg1,"-");
    }
    else
    {
        strcpy(quad[quad_i].arg1,signtable[arg1].name);
    }
    if(arg2>=10000)
    {
        strcpy(quad[quad_i].arg2,symbol[findstring(arg2 - 10000)].sign);
    }
    else if(arg2==-1)
    {
        strcpy(quad[quad_i].arg2,"-");
    }
    else
    {
        strcpy(quad[quad_i].arg2,signtable[arg2].name);
    }
    if(strcmp(result,"T") == 0)
    {
        if (T_i <= 9)
        {
            quad[quad_i].result[0]='T';
            quad[quad_i].result[1]=T_i+'0';
            quad[quad_i].result[2]='\0';
            quad[quad_i].result[3]='\0';
        }
        else
        {
            quad[quad_i].result[0]='T';
            quad[quad_i].result[1]=T_i/10+'0';
            quad[quad_i].result[2]=T_i%10+'0';
            quad[quad_i].result[3]='\0';
        }
    }
    else
    {
        strcpy(quad[quad_i].result,result);
    }
    quad_i++;
    NXQ=quad_i;
}

E()
{
    int sym,acc,false=0,true=1,t,j,E1_place,E2_place,x,l;
    struct SqStack sp1,sp2,sp3;
    InitStack(&sp1);
    Push(&sp1,0);
    InitStack(&sp2);
    Push(&sp2,24);
    InitStack(&sp3);
    Push(&sp3,'@');
    Flag=0;
    sym1=symbol[E_i++].code;
    if(sym1 == 1 || sym1 == 2)
    {
        sym='i';
    }
    else
    {
        sym=sym1;
    }
    acc=false;
    while(!acc)
    {
        l=GetTop(&sp1);
        j=precede1(sym);
        t=action1[l][j];
        if(t==-1)
        {
            printf("error1\n");
            return false;
        }
        if(t==-2)
        {
            acc=true;
        }
        if(t>=0 && t<100)
        {
            Push(&sp1,t);
            Push(&sp2,sym);
            if(sym=='i')
            {
                Push(&sp3,entry(symbol[E_i-1].sign));
            }
            else
            {
                Push(&sp3,'@');
            }
            sym1=symbol[E_i++].code;
            if(sym1==1 || sym1==2)
            {
                sym='i';
            }
            else
            {
                sym=sym1;
            }
        }
        if(t>=100 && t<=200)
            switch(t)
            {
            case 101:
            {
                Pop(&sp1,&x);
                Pop(&sp1,&x);
                Pop(&sp1,&x);
                Pop(&sp2,&x);
                Pop(&sp2,&x);
                Pop(&sp2,&x);
                E1_place=*(sp3.top - 3);
                E2_place=*(sp3.top - 1);
                Temp=newtemp('+',E1_place,E2_place);
                Pop(&sp3,&x);
                Pop(&sp3,&x);
                Pop(&sp3,&x);
                t=GetTop(&sp1);
                Push(&sp2,'E');
                j=precede1('E');
                x=action1[t][j];
                Push(&sp1,x);
                gen("+",E1_place,E2_place,"T");
                T_i++;
                Push(&sp3,Temp);
                break;
            }
            case 102:
            {
                Pop(&sp1,&x);
                Pop(&sp1,&x);
                Pop(&sp1,&x);
                Pop(&sp2,&x);
                Pop(&sp2,&x);
                Pop(&sp2,&x);
                E1_place=*(sp3.top - 3);
                E2_place=*(sp3.top - 1);
                Temp=newtemp('-',E1_place,E2_place);
                Pop(&sp3,&x);
                Pop(&sp3,&x);
                Pop(&sp3,&x);
                t=GetTop(&sp1);
                Push(&sp2,'E');
                j=precede1('E');
                x=action1[t][j];
                Push(&sp1,x);
                gen("-",E1_place,E2_place,"T");
                T_i++;
                Push(&sp3,Temp);
                break;
            }
            case 103:
            {
                Pop(&sp1,&x);
                Pop(&sp1,&x);
                Pop(&sp1,&x);
                Pop(&sp2,&x);
                Pop(&sp2,&x);
                Pop(&sp2,&x);
                E1_place=*(sp3.top - 3);
                E2_place=*(sp3.top - 1);
                Temp=newtemp('*',E1_place,E2_place);
                Pop(&sp3,&x);
                Pop(&sp3,&x);
                Pop(&sp3,&x);
                t=GetTop(&sp1);
                Push(&sp2,'E');
                j=precede1('E');
                x=action1[t][j];
                Push(&sp1,x);
                gen("*",E1_place,E2_place,"T");
                T_i++;
                Push(&sp3,Temp);
                break;
            }
            case 104:
            {
                Pop(&sp1,&x);
                Pop(&sp1,&x);
                Pop(&sp1,&x);
                Pop(&sp2,&x);
                Pop(&sp2,&x);
                Pop(&sp2,&x);
                E1_place=*(sp3.top - 3);
                E2_place=*(sp3.top - 1);
                Temp=newtemp('/',E1_place,E2_place);
                Pop(&sp3,&x);
                Pop(&sp3,&x);
                Pop(&sp3,&x);
                t=GetTop(&sp1);
                Push(&sp2,'E');
                j=precede1('E');
                x=action1[t][j];
                Push(&sp1,x);
                gen("/",E1_place,E2_place,"T");
                T_i++;
                Push(&sp3,Temp);
                break;
            }
            case 105:
            {
                Pop(&sp1,&x);
                Pop(&sp1,&x);
                Pop(&sp1,&x);
                Pop(&sp2,&x);
                Pop(&sp2,&x);
                Pop(&sp2,&x);
                Temp=*(sp3.top - 2);
                Pop(&sp3,&x);
                Pop(&sp3,&x);
                Pop(&sp3,&x);
                t=GetTop(&sp1);
                Push(&sp2,'E');
                j=precede1('E');
                x=action1[t][j];
                Push(&sp1,x);
                Push(&sp3,Temp);
                break;
            }
            case 106:
            {
                Pop(&sp1,&x);
                Pop(&sp2,&x);
                Push(&sp2,'E');
                Temp=*(sp3.top - 1);
                t=GetTop(&sp1);
                j=precede1('E');
                x=action1[t][j];
                Push(&sp1,x);
                Flag++;
            }
            }
    }
    return true;
}

precede2(int a)
{
    int i;
    int PAT[]={'i','r',17,18,34,14,15,'#','E','A','O'};
    i=0;
    if(a>=7 && a<=12)
    {
        return 1;
    }
    while(PAT[i]!=a && i<=10)
    {
        i++;
    }
    if(i==2)
    {
        bracket++;
    }
    if(i==3)
    {
        bracket--;
    }
    if(bracket==-1 || i==11)
    {
        i=7;
        bracket=0;
    }
    return i;
}

Backpatch(int p,int t)
{
    int Q;
    char q[10];
    Q=p;
    while(Q != 0)
    {
        strcpy(q,quad[Q].result);
        if(t <= 9)
        {
            quad[Q].result[0]=t+'0';
            quad[Q].result[1]='\0';
        }
        else
        {
            quad[Q].result[0]=t/10+'0';
            quad[Q].result[1]=t%10+'0';
            quad[Q].result[2]='\0';
        }
        Q=changestring(q);
    }
}

Merg(int p1,int p2)
{
    int p;
    if(p1>p2)
    {
        return p1;
    }
    if(p2 == 0)
    {
        return p1;
    }
    else
    {
        p=p2;
        while(strcmp(quad[p].result,"0"))
        {
            p=changestring(quad[p].result);
        }
        if(p1 > 9)
        {
            quad[p].result[0]=p1/10+'0';
            quad[p].result[1]=p1%10+'0';
        }
        else
        {
            quad[p].result[0]=p1+'0';
            quad[p].result[1]='\0';
        };
        return p2;
    }
}

EB()
{
    int sym,acc,false=0,true=1,t,j,temp,E1_place,E2_place,x,l,op;
    int E_temp,EA_FC,EO_TC,NXQ_temp=0;
    char tempstring[10];
    struct SqStack sp1,sp2,sp3;
    InitStack(&sp1);
    Push(&sp1,0);
    InitStack(&sp2);
    Push(&sp2,24);
    InitStack(&sp3);
    Push(&sp3,'@');
    sym1=symbol[E_i++].code;
    if(sym1 == 1 || sym1 == 2)
    {
        strcpy(tempstring,symbol[E_i - 1].sign);
        sym1=symbol[E_i].code;
        if(sym1>=3 && sym1<=6 || sym1 == 16)
        {
            NXQ_temp=NXQ;
            if(sym1==16)
            {
                E_i++;
                if(E())
                {
                    temp=entry(tempstring);
                    gen("=",1000+T_i-1,-1,signtable[temp].name);
                    E_i--;
                }
                else ;
            }
            else
            {
                strcpy(tempstring,"T");
                E_i--;
                E();
                T_i--;
                E_i--;
            }
        }
        sym='i';
    }
    else
    {
        sym=sym1;
    }
    acc=false;
    while(!acc)
    {
        l=GetTop(&sp1);
        j=precede2(sym);
        t=action2[l][j];
        if(t==-1)
        {
            printf("error2\n");
            return false;
        }
        if(t==-2)
        {
            acc=true;
        }
        if(t>=0 && t<100)
        {
            Push(&sp1,t);
            Push(&sp2,sym);
            if(sym=='i')
            {
                Push(&sp3,entry(tempstring));
            }
            else
            {
                Push(&sp3,'@');
            }
            sym1=symbol[E_i++].code;
            if(sym1==1 || sym1==2)
            {
                strcpy(tempstring,symbol[E_i - 1].sign);
                sym1=symbol[E_i].code;
                if(sym1 >= 3 && sym1 <= 6 || sym1 == 16)
                {
                    NXQ_temp=NXQ;
                    if(sym1 == 16)
                    {
                        E_i++;
                        if(E())
                        {
                            temp=entry(tempstring);
                            gen("=",1000 + T_i - 1,-1,signtable[temp].name);
                            E_i--;
                        }
                        else ;
                    }
                    else
                    {
                        strcpy(tempstring,"T");
                        E_i--;
                        E();
                        T_i--;
                        E_i--;
                    }
                }
                sym='i';
            }
            else
            {
                sym=sym1;
            }
        }
        if(t >= 100 && t <= 200)
            switch(t)
            {
            case 101:
            {
                Pop(&sp1,&x);
                Pop(&sp2,&x);
                E1_place=*(sp3.top - 1);
                t=GetTop(&sp1);
                Push(&sp2,'E');
                j=precede2('E');
                x=action2[t][j];
                Push(&sp1,x);
                E_TC=NXQ;
                E_FC=NXQ + 1;
                gen("jnz",E1_place,-1,"0");
                gen("j",-1,-1,"0");
                break;
            }
            case 102:
            {
                Pop(&sp1,&x);
                Pop(&sp1,&x);
                Pop(&sp1,&x);
                op=*(sp2.top - 2);
                Pop(&sp2,&x);
                Pop(&sp2,&x);
                Pop(&sp2,&x);
                E1_place=*(sp3.top - 3);
                E2_place=*(sp3.top - 1);
                Pop(&sp3,&x);
                Pop(&sp3,&x);
                Pop(&sp3,&x);
                t=GetTop(&sp1);
                Push(&sp2,'E');
                j=precede2('E');
                x=action2[t][j];
                Push(&sp1,x);
                E_TC=NXQ;
                E_FC=NXQ + 1;
                if(op == 7)
                {
                    gen("j<",E1_place,E2_place,"0");
                }
                if(op == 8)
                {
                    gen("j<=",E1_place,E2_place,"0");
                }
                if(op == 9)
                {
                    gen("j==",E1_place,E2_place,"0");
                }
                if(op == 10)
                {
                    gen("j!=",E1_place,E2_place,"0");
                }
                if(op == 11)
                {
                    gen("j>",E1_place,E2_place,"0");
                }
                if(op == 12)
                {
                    gen("j>=",E1_place,E2_place,"0");
                }
                gen("j",-1,-1,"0");
                Push(&sp3,'@');
                break;
            }
            case 103:
            {
                Pop(&sp1,&x);
                Pop(&sp1,&x);
                Pop(&sp1,&x);
                Pop(&sp2,&x);
                Pop(&sp2,&x);
                Pop(&sp2,&x);
                temp=*(sp3.top - 2);
                Pop(&sp3,&x);
                Pop(&sp3,&x);
                Pop(&sp3,&x);
                t=GetTop(&sp1);
                Push(&sp2,'E');
                j=precede2('E');
                x=action2[t][j];
                Push(&sp1,x);
                Push(&sp3,temp);
                break;
            }
            case 104:
            {
                Pop(&sp1,&x);
                Pop(&sp1,&x);
                Pop(&sp2,&x);
                Pop(&sp2,&x);
                Pop(&sp3,&x);
                Pop(&sp3,&x);
                t=GetTop(&sp1);
                Push(&sp2,'E');
                j=precede2('E');
                x=action2[t][j];
                Push(&sp1,x);
                E_temp=E_FC;
                E_FC=E_TC;
                E_TC=E_temp;
                Push(&sp3,'@');
                break;
            }
            case 105:
            {
                Pop(&sp1,&x);
                Pop(&sp1,&x);
                Pop(&sp2,&x);
                Pop(&sp2,&x);
                Pop(&sp3,&x);
                Pop(&sp3,&x);
                t=GetTop(&sp1);
                Push(&sp2,'A');
                j=precede2('A');
                x=action2[t][j];
                Push(&sp1,x);
                if(NXQ_temp > 1)
                {
                    Backpatch(E_TC,NXQ_temp);
                    NXQ_temp=0;
                }
                else
                {
                    Backpatch(E_TC,NXQ);
                }
                EA_FC=E_FC;
                Push(&sp3,'@');
                break;
            }
            case 106:
            {
                Pop(&sp1,&x);
                Pop(&sp1,&x);
                Pop(&sp2,&x);
                Pop(&sp2,&x);
                Pop(&sp3,&x);
                Pop(&sp3,&x);
                t=GetTop(&sp1);
                Push(&sp2,'E');
                j=precede2('E');
                x=action2[t][j];
                Push(&sp1,x);
                E_FC=Merg(EA_FC,E_FC);
                Push(&sp3,'@');
                break;
            }
            case 107:
            {
                Pop(&sp1,&x);
                Pop(&sp1,&x);
                Pop(&sp2,&x);
                Pop(&sp2,&x);
                Pop(&sp3,&x);
                Pop(&sp3,&x);
                t=GetTop(&sp1);
                Push(&sp2,'O');
                j=precede2('O');
                x=action2[t][j];
                Push(&sp1,x);
                if(NXQ_temp > 1)
                {
                    Backpatch(E_FC,NXQ_temp);
                    NXQ_temp=0;
                }
                else
                {
                    Backpatch(E_FC,NXQ);
                }
                EO_TC=E_TC;
                Push(&sp3,'@');
                break;
            }
            case 108:
            {
                Pop(&sp1,&x);
                Pop(&sp1,&x);
                Pop(&sp2,&x);
                Pop(&sp2,&x);
                Pop(&sp3,&x);
                Pop(&sp3,&x);
                t=GetTop(&sp1);
                Push(&sp2,'E');
                j=precede2('E');
                x=action2[t][j];
                Push(&sp1,x);
                E_TC=Merg(EO_TC,E_TC);
                Push(&sp3,'@');
                break;
            }
            }
    }
    return true;
}

Program()
{
    int temp,q,ffc,Tchain;
    char s_q[10];
    char tempstring[10];
    sym1=symbol[E_i++].code;
    if(sym1 >= 27 && sym1 <= 29)
    {
        sym1=symbol[E_i++].code;
        while(sym1 != 24)//;
        {
            if(sym1 == 1)
            {
                sym1=symbol[E_i++].code;
                if(sym1 == 16) //=
                {
                    Program();
                }
                else if(sym1 == 25) //,
                {
                    sym1=symbol[E_i++].code;
                }
                else if(sym1 == 24)//;
                {
                    break;
                }
                else
                {
                    printf("various value defined error!\n");
                }
            }
            else
            {
                printf("various value defined error!\n");
            }
        }
    }
    else if(sym1 == 1)
    {
        strcpy(tempstring,symbol[E_i - 1].sign);
        sym1=symbol[E_i++].code;
        if(sym1 == 16)
        {
            Schain=0;
            if(E())
            {
                temp=entry(tempstring);
                if(Flag == 1)
                {
                    gen("=",Temp,-1,signtable[temp].name);
                }
                else
                {
                    gen("=",1000 + T_i - 1,-1,signtable[temp].name);
                }
            }
            if(sym1 != 24)
            {
                printf("lack of ; in fuzi\n");
            }
        }
        else
        {
            printf("lack of=in fuzhi\n");
        }
    }
    else if(sym1 == 30)//if
    {
        sym1=symbol[E_i++].code;
        if(sym1 == 17)
        {
            if_flag=1;
            EB();
            if(sym1 == 18)
            {
                Backpatch(E_TC ,NXQ);
                ffc=E_FC;
                Program();
                sym1=symbol[E_i++].code;
                if(sym1 == 31)
                {
                    q=NXQ;
                    gen("j",-1,-1,"0");
                    Backpatch(ffc,NXQ);
                    E_FC=q;
                    Tchain=Merg(Schain,q);
                    Program();
                    Schain=Merg(Tchain,Schain);
                }
                else
                {
                    E_i--;
                    Schain=Merg(ffc,Schain);
                }
            }
            else
            {
                printf("lack of ) in if sentences\n");
            }
        }
        else
        {
            printf("lack of ( in if sentences\n");
        }
    }
    else if(sym1 == 32)//while
    {
        sym1=symbol[E_i++].code;
        if(sym1 == 17)
        {
            q=NXQ;
            EB();
            if(sym1 == 18)
            {
                while_flag=1;
                Backpatch(E_TC,NXQ);
                ffc=E_FC;
                Program();
                Backpatch(Schain,NXQ);
                if(q < 10)
                {
                    s_q[0]=q + '0';
                    s_q[1]='\0';
                }
                else
                {
                    s_q[0]=q / 10 + '0';
                    s_q[1]=q % 10 + '0';
                    s_q[2]='\0';
                }
                gen("j",-1,-1,s_q);
                Schain=ffc;
                E_FC=ffc;
            }
            else
            {
                printf("lack of ) in while sentences\n");
            }
        }
        else
        {
            printf("lack of ( in while sentences\n ");
        }
    }
    else if(sym1 == 33)//do
    {
        q=NXQ;
        Program();
        Backpatch(Schain,NXQ);
        sym1=symbol[E_i++].code;
        if(sym1 == 32)
        {
            sym1=symbol[E_i++].code;
            if(sym1 == 17)
            {
                EB();
                if(sym1 == 18)
                {
                    do_flag=1;
                    Backpatch(E_TC,q);
                    Schain=E_FC;
                }
                else
                {
                    printf("lack of ) in do while sentences\n");
                }
            }
            else
            {
                printf("lack of ( in do while sentences\n");
            }
        }
    }
}

Printquad()
{
    int i;
    printf("code is:\n");
    for(i=1; i < quad_i; i++)
    {
        printf("(%d): (%s,%s,%s,%s)\n",i,quad[i].op,quad[i].arg1,quad[i].arg2,quad[i].result);
    }
}

int IsInteger(char *p)
{
    if(*p >= '0' && *p <= '9')
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int comp(const void *a,const void *b)
{
    const int *p=a;
    const int *q=b;
    return *p - *q;
}

void quadtocom() //四元式翻译成汇编
{
    int i,j=0,n,k;
    int arr[number];
    for (i=1; i < quad_i; i++)//把每个四元式要跳转的序号存入数组arr
    {
        if (IsInteger(quad[i].result))//判断四元式的result是否为整数
        {
            int arrnum=changestring(quad[i].result);//把数字字符串转化为整数
            for (n=0; n < j; n++)//判断整数是否已在arr数组中,目的是消除重复项
            {
                if (arr[n] == arrnum)
                {
                    break;
                }
            }
            if (n == j)
            {
                arr[j++]=arrnum;
            }
        }
    }
    
	qsort(arr,j,sizeof(arr[0]),comp); // 排序
    for (i=0; i < j; i++)
    {
        L[L_i].i=arr[i];
        if (i >= 0 && i < 9)
        {
            L[L_i].li[0]='L';
            L[L_i].li[1]=i + '1';
            L[L_i].li[2]='\0';
        }
        else
        {
            L[L_i].li[0]='L';
            L[L_i].li[1]=(i + 1) / 10 + '0';    //把int变成char
            L[L_i].li[2]=(i + 1) % 10 + '0';
            L[L_i].li[3]='\0';
        }
        L_i++;
    }
    for (i=0; i < L_i; i++) // 打印
    {
        printf("%d   %s\n",L[i].i,L[i].li);
    }
    for (i=1; i < quad_i; i++) // 从第一个四元式翻译成汇编
    {
        if (strcmp(quad[i].op,"jnz") == 0) //判断
        {
            for (k=0; k < j; k++)
            {
                if (L[k].i == i)
                {
                    strcpy(com[com_i].lable,L[k].li);
                    break;
                }
            }
            if (k == j)
            {
                com[com_i].lable[0]='\0';
            }
            strcpy(com[com_i].op,"CMP");
            strcpy(com[com_i].arg1,quad[i].arg1);
            strcpy(com[com_i].arg2,"0");
            com_i++;
            strcpy(com[com_i].lable,"");
            strcpy(com[com_i].op,"JNZ");
            for (k=0; k < j; k++)
            {
                if (L[k].i == changestring(quad[i].result))
                {
                    strcpy(com[com_i].arg1,L[k].li);
                }
            }
            strcpy(com[com_i].arg2,"");
            com_i++;
        }
        if (strcmp(quad[i].op,"j") == 0)
        {
            for (k=0; k < j; k++)
            {
                if (L[k].i == i)
                {
                    strcpy(com[com_i].lable,L[k].li);
                    break;
                }
            }
            if (k == j)
            {
                com[com_i].lable[0]='\0';
            }
            strcpy(com[com_i].op,"JMP");
            for (k=0; k < j; k++)
            {
                if (L[k].i == changestring(quad[i].result))
                {
                    strcpy(com[com_i].arg1,L[k].li);
                }
            }
            strcpy(com[com_i].arg2,"");
            com_i++;
        }
        if (strcmp(quad[i].op,"j>") == 0)
        {
            for (k=0; k < j; k++)
            {
                if (L[k].i == i)
                {
                    strcpy(com[com_i].lable,L[k].li);
                    break;
                }
            }
            if (k == j)
            {
                com[com_i].lable[0]='\0';
            }
            strcpy(com[com_i].op,"CMP");
            strcpy(com[com_i].arg1,quad[i].arg1);
            strcpy(com[com_i].arg2,quad[i].arg2);
            com_i++;
            strcpy(com[com_i].lable,"");
            strcpy(com[com_i].op,"JA");
            for (k=0; k < j; k++)
            {
                if (L[k].i == changestring(quad[i].result))
                {
                    strcpy(com[com_i].arg1,L[k].li);
                }
            }
            strcpy(com[com_i].arg2,"");
            com_i++;
        }
        if (strcmp(quad[i].op,"j>=") == 0)
        {
            for (k=0; k < j; k++)
            {
                if (L[k].i == i)
                {
                    strcpy(com[com_i].lable,L[k].li);
                    break;
                }
            }
            if (k == j)
            {
                com[com_i].lable[0]='\0';
            }
            strcpy(com[com_i].op,"CMP");
            strcpy(com[com_i].arg1,quad[i].arg1);
            strcpy(com[com_i].arg2,quad[i].arg2);
            com_i++;
            strcpy(com[com_i].lable,"");
            strcpy(com[com_i].op,"JAE");
            for (k=0; k < j; k++)
            {
                if (L[k].i == changestring(quad[i].result))
                {
                    strcpy(com[com_i].arg1,L[k].li);
                }
            }
            strcpy(com[com_i].arg2,"");
            com_i++;
        }
        if (strcmp(quad[i].op,"j<") == 0)
        {
            for (k=0; k < j; k++)
            {
                if (L[k].i == i)
                {
                    strcpy(com[com_i].lable,L[k].li);
                    break;
                }
            }
            if (k == j)
            {
                com[com_i].lable[0]='\0';
            }
            strcpy(com[com_i].op,"CMP");
            strcpy(com[com_i].arg1,quad[i].arg1);
            strcpy(com[com_i].arg2,quad[i].arg2);
            com_i++;
            strcpy(com[com_i].lable,"");
            strcpy(com[com_i].op,"JB");
            for (k=0; k < j; k++)
            {
                if (L[k].i == changestring(quad[i].result))
                {
                    strcpy(com[com_i].arg1,L[k].li);
                }
            }
            strcpy(com[com_i].arg2,"");
            com_i++;
        }
        if (strcmp(quad[i].op,"j<=") == 0)
        {
            for (k=0; k < j; k++)
            {
                if (L[k].i == i)
                {
                    strcpy(com[com_i].lable,L[k].li);
                    break;
                }
            }
            if (k == j)
            {
                com[com_i].lable[0]='\0';
            }
            strcpy(com[com_i].op,"CMP");
            strcpy(com[com_i].arg1,quad[i].arg1);
            strcpy(com[com_i].arg2,quad[i].arg2);
            com_i++;
            strcpy(com[com_i].lable,"");
            strcpy(com[com_i].op,"JBE");
            for (k=0; k < j; k++)
            {
                if (L[k].i == changestring(quad[i].result))
                {
                    strcpy(com[com_i].arg1,L[k].li);
                }
            }
            strcpy(com[com_i].arg2,"");
            com_i++;
        }
        if (strcmp(quad[i].op,"j==") == 0)
        {
            for (k=0; k < j; k++)
            {
                if (L[k].i == i)
                {
                    strcpy(com[com_i].lable,L[k].li);
                    break;
                }
            }
            if (k == j)
            {
                com[com_i].lable[0]='\0';
            }
            strcpy(com[com_i].op,"CMP");
            strcpy(com[com_i].arg1,quad[i].arg1);
            strcpy(com[com_i].arg2,quad[i].arg2);
            com_i++;
            strcpy(com[com_i].lable,"");
            strcpy(com[com_i].op,"JE");
            for (k=0; k < j; k++)
            {
                if (L[k].i == changestring(quad[i].result))
                {
                    strcpy(com[com_i].arg1,L[k].li);
                }
            }
            strcpy(com[com_i].arg2,"");
            com_i++;
        }
        if (strcmp(quad[i].op,"j!=") == 0)
        {
            for (k=0; k < j; k++)
            {
                if (L[k].i == i)
                {
                    strcpy(com[com_i].lable,L[k].li);
                    break;
                }
            }
            if (k == j)
            {
                com[com_i].lable[0]='\0';
            }
            strcpy(com[com_i].op,"CMP");
            strcpy(com[com_i].arg1,quad[i].arg1);
            strcpy(com[com_i].arg2,quad[i].arg2);
            com_i++;
            strcpy(com[com_i].lable,"");
            strcpy(com[com_i].op,"JNE");
            for (k=0; k < j; k++)
            {
                if (L[k].i == changestring(quad[i].result))
                {
                    strcpy(com[com_i].arg1,L[k].li);
                }
            }
            strcpy(com[com_i].arg2,"");
            com_i++;
        }
        if (strcmp(quad[i].op,"=") == 0)
        {
            for (k=0; k < j; k++)
            {
                if (L[k].i == i)
                {
                    strcpy(com[com_i].lable,L[k].li);
                    break;
                }
            }
            if (k == j)
            {
                com[com_i].lable[0]='\0';
            }
            strcpy(com[com_i].op,"MOV");
            strcpy(com[com_i].arg1,"R0");
            strcpy(com[com_i].arg2,quad[i].arg1);
            com_i++;
            strcpy(com[com_i].lable,"");
            strcpy(com[com_i].op,"MOV");
            strcpy(com[com_i].arg1,quad[i].result);
            strcpy(com[com_i].arg2,"R0");
            com_i++;
        }
        if (strcmp(quad[i].op,"+") == 0)
        {
            for (k=0; k < j; k++)
            {
                if (L[k].i == i)
                {
                    strcpy(com[com_i].lable,L[k].li);
                    break;
                }
            }
            if (k == j)
            {
                com[com_i].lable[0]='\0';
            }
            strcpy(com[com_i].op,"MOV");
            strcpy(com[com_i].arg1,"R0");
            strcpy(com[com_i].arg2,quad[i].arg1);
            com_i++;
            strcpy(com[com_i].lable,"");
            strcpy(com[com_i].op,"MOV");
            strcpy(com[com_i].arg1,"R1");
            strcpy(com[com_i].arg2,quad[i].arg2);
            com_i++;
            strcpy(com[com_i].lable,"");
            strcpy(com[com_i].op,"ADD");
            strcpy(com[com_i].arg1,"R1");
            strcpy(com[com_i].arg2,"R0");
            com_i++;
            strcpy(com[com_i].lable,"");
            strcpy(com[com_i].op,"MOV");
            strcpy(com[com_i].arg1,quad[i].result);
            strcpy(com[com_i].arg2,"R1");
            com_i++;
        }
        if (strcmp(quad[i].op,"-") == 0)
        {
            for (k=0; k < j; k++)
            {
                if (L[k].i == i)
                {
                    strcpy(com[com_i].lable,L[k].li);
                    break;
                }
            }
            if (k == j)
            {
                com[com_i].lable[0]='\0';
            }
            strcpy(com[com_i].op,"MOV");
            strcpy(com[com_i].arg1,"R0");
            strcpy(com[com_i].arg2,quad[i].arg1);
            com_i++;
            strcpy(com[com_i].lable,"");
            strcpy(com[com_i].op,"MOV");
            strcpy(com[com_i].arg1,"R1");
            strcpy(com[com_i].arg2,quad[i].arg2);
            com_i++;
            strcpy(com[com_i].lable,"");
            strcpy(com[com_i].op,"SUB");
            strcpy(com[com_i].arg1,"R1");
            strcpy(com[com_i].arg2,"R0");
            com_i++;
            strcpy(com[com_i].lable,"");
            strcpy(com[com_i].op,"MOV");
            strcpy(com[com_i].arg1,quad[i].result);
            strcpy(com[com_i].arg2,"R1");
            com_i++;
        }
        if (strcmp(quad[i].op,"*") == 0) //乘法
        {
            for (k=0; k < j; k++)
            {
                if (L[k].i == i)
                {
                    strcpy(com[com_i].lable,L[k].li);
                    break;
                }
            }
            if (k == j)
            {
                com[com_i].lable[0]='\0';
            }
            strcpy(com[com_i].op,"MOV");
            strcpy(com[com_i].arg1,"AL");
            strcpy(com[com_i].arg2,quad[i].arg1);
            com_i++;
            strcpy(com[com_i].lable,"");
            strcpy(com[com_i].op,"MUL");
            strcpy(com[com_i].arg1,quad[i].arg2);
            strcpy(com[com_i].arg2,"");
            com_i++;
            strcpy(com[com_i].lable,"");
            strcpy(com[com_i].op,"MOV");
            strcpy(com[com_i].arg1,quad[i].result);
            strcpy(com[com_i].arg2,"AX");
            com_i++;
        }
        if (strcmp(quad[i].op,"/") == 0)  //除法
        {
            for (k=0; k < j; k++)
            {
                if (L[k].i == i)
                {
                    strcpy(com[com_i].lable,L[k].li);
                    break;
                }
            }
            if (k == j)
            {
                com[com_i].lable[0]='\0';
            }
            strcpy(com[com_i].op,"MOV");
            strcpy(com[com_i].arg1,"AX");
            strcpy(com[com_i].arg2,quad[i].arg1);
            com_i++;
            strcpy(com[com_i].lable,"");
            strcpy(com[com_i].op,"DIV");
            strcpy(com[com_i].arg1,quad[i].arg2);
            strcpy(com[com_i].arg2,"");
            com_i++;
            strcpy(com[com_i].lable,"");
            strcpy(com[com_i].op,"MOV");
            strcpy(com[com_i].arg1,quad[i].result);
            strcpy(com[com_i].arg2,"AL");
            com_i++;
        }
    }
}

void printcom() 
{
    int i;
    for (i=0; i < com_i; i++)
    {
		if (strcmp(com[i].lable,"") != 0)
        {
            printf("%s:",com[i].lable);
            printf(" %s %s",com[i].op,com[i].arg1);}
		else
			printf("    %s %s",com[i].op,com[i].arg1);
        if (strcmp(com[i].arg2,"") != 0)
        {
            printf(",%s",com[i].arg2);
        }
        printf("\n");
    }
}

void Finput() //
{
    int i=0;
    char ch;
    char string[string_length]; // C语言程序文本字符串
    char file[length]; // 文件名称字符串
    FILE *fp;
    printf("input filename:");
    scanf("%s",file);
    if((fp=fopen(file,"rb")) == null)
    {
        printf("file not found");
        return;
    }
    ch=fgetc(fp);
    while(ch != EOF) // 判断程序是否读完
    {
        string[i++]=ch;
        ch=fgetc(fp);
    }
    string[i]='\0'; // 作为程序字符串结尾标识
    printf("c program is :\n");
    printf("%s\n",string);
    Test(string);  // 对程序进行词法分析
    while(E_i < symbol_count)
    {
        Program();
        if(if_flag || while_flag || do_flag)
        {
            Backpatch(E_FC,NXQ);
            if_flag=0;
            while_flag=0;
            do_flag=0;
        }
    }
    Printquad();
    quadtocom();
    printcom();
}

int main()
{
    Create();//把关键字表中的symbol 和 code输入到propertytable结构体中
    Finput();
}