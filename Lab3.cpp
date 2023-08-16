#include<iostream>
using namespace std;

#define starksize 100
typedef struct{
    char *base;
    char *top;
    int length ;
}StarkTR; //寄存运算符

typedef struct{
    int *base;
    int *top;
    int length ;
}StarkND; //寄存操作数

int InitTR(StarkTR &L){   //初始化寄存operater栈
    L.base = new char[starksize];
    L.top = L.base;
    L.length = starksize;
    return 1;
}
int InitND(StarkND &L){   //初始化寄存operand栈
    L.base = new int[starksize];
    L.top = L.base;
    L.length = starksize;
    return 1;
}

int PushTR(StarkTR &L,char e){   //入栈
    if(L.top - L.base == L.length){
        cout<<"栈满！";
        return 0;
    }
    *L.top++ = e;
    return 1;
}
int PushND(StarkND &L,int e){   //入栈
    if(L.top - L.base == L.length){
        cout<<"栈满！";
        return 0;
    }
    *L.top++ = e;
    return 1;
}

char PopTR(StarkTR &L,char &e){   //出栈
    if(L.top - L.base == 0){
        cout<<"栈空！";
        return 0;
    }
    e = *--L.top;
    return 1;
}
int PopND(StarkND &L,int &e){   //出栈
    if(L.top - L.base == 0){
        cout<<"栈空！";
        return 0;
    }
    e = *--L.top;
    return 1;
}

char GetTopTR(StarkTR L){  //取栈顶元素
    if(L.top != L.base)
        return *(L.top -1);
}
int GetTopND(StarkND L){  //取栈顶元素
    if(L.top != L.base)
        return *(L.top -1);
}

char Precede(char a,char b){     //< > = 都代表优先级
    //只考虑 + - * / （ ） 的运算
    if(a == '+'||a == '-'){
        if(b == '+'||b == '-'||b == ')'||b == '#')return '>';
        else return '<';
    }
    else if(a == '*'||a == '/'){
        if(b == '+'||b == '-'||b == ')'||b == '#'||b == '*'||b == '/')return '>';
        else return '<';
    }
    else if(a == '^') {
        if(b == '+'||b == '-'||b == ')'||b == '#'||b == '*'||b == '/')return '>';
        else return '<';
    }
    else if(a == '('){
        if(b == ')')return '=';
        else return '<';
    }
    else if(a == ')'){
        return '>';
    }
    else{
        if(b == '#')return '=';
        else return '<';
    }
}

int Operate(int a,char s,int b){
    if(s == '+'){
        return a+b;
    }
    else if(s == '-'){
        return a-b;
    }
    else if(s == '*'){
        return a*b;
    }
    else if(s == '/'){
        return a/b;
    }
    else if(s == '^') {
        int result = 1;
        while (b != 0)
        {
            if ((b & 1) == 1)
            {
                result *= a;
            }
            a *= a;
            b >>= 1;
        }
        return result;
    }
}


int EvaluateExpression(){
    StarkTR operater;
    StarkND operand;
    char ch,op;
    int t,k,a,b;
    InitTR(operater);
    InitND(operand);
    PushTR(operater, '#'); //将表达式起始符“#”压入operater栈中
    cout<<"please input a evaluate expression(以 # 结束):"<<endl;
    cin>>ch;
    while(ch != '#'||GetTopTR(operater) != '#'){
        t = 0;
        k = 0;
        while(ch <= '9'&&ch >= '0'){
            t = t*10 + (ch - 48);   //0的ASCLL码是48
            cin>>ch;
            k++;
        }
        if(k) PushND(operand,t);
        switch(Precede(GetTopTR(operater),ch)){
            case '<':
                PushTR(operater,ch);
                cin>>ch;
                break;
            case '>':
                PopTR(operater,op);
                PopND(operand,b);
                PopND(operand,a);
                PushND(operand,Operate(a,op,b));
                break;
            case '=':
                PopTR(operater,op);
                cin>>ch;
                break;
        }
    }
    return GetTopND(operand);
}

int main(){
    cout<<EvaluateExpression();
    return 0;
}
