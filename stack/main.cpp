#include <iostream>
#include "stack.h"
using namespace std;

//判断回文字符串
bool isReserve(const char *s){
    linkStack<char> st;
    while(*s!='\0'){
        st.push(*s);
        s++;
    }
    for(int i=0;!st.isEmpty();i++){
        if(s[i]!=st.pop()) return false;
    }
    return true;
}

//括号匹配
bool parenMatch( const char *str ){
    linkStack<char> mystack;
    while(*str!='\0'){
        if(*str=='('||*str=='['||*str=='{'){
            mystack.push(*str);
        }
        else if(mystack.isEmpty()){
            return false;
        }
        else if(*str==')'){
                if(mystack.top()!='(') return false;
                mystack.pop();
        }
        else if(*str==']'){
            if(mystack.top()!='[') return false;
            mystack.pop();
        }
        else if(*str=='}'){
            if(mystack.top()!='{') return false;
            mystack.pop();
        }
        str++;
    }
    if(!mystack.isEmpty()) return false;
    return true;
}

// 后缀表达式
int calcPost(const char *sufStr){
    linkStack<char> mystack;
    while(*sufStr!='\0'){
        char cur=*sufStr;
        if(cur>='0'&&cur<='9'){
            mystack.push(cur);
        }
        else{
            int second=mystack.pop()-'0';
            int first=mystack.pop()-'0';
            switch (cur) {
                case '+': mystack.push(first+second+'0');
                    break;
                case '-': mystack.push(first-second+'0');
                    break;
                case '*': mystack.push(first*second+'0');
                    break;
                case '/': mystack.push(first/second+'0');
                    break;
            }
        }
        sufStr++;
    }
    return mystack.pop()-'0';
}
//中缀转后缀
void inToSufForm(const string& in){
    linkStack<char> mystack;
    for(auto &op :in){
        if(op>='0'&&op<='9'){
            cout<<op;
            continue;
        }
        switch (op) {
            case '(':
                mystack.push(op);
                break;
            case ')':
                while(mystack.top()!='('){
                    cout<<mystack.pop();
                }
                mystack.pop();
                break;
            case '*':
            case '/':
                while(!mystack.isEmpty()&&(mystack.top()=='*'||mystack.top()=='/')){
                    cout<<mystack.pop();
                }
                mystack.push(op);
                break;
            case '+':
            case '-':
                while (!mystack.isEmpty()&&mystack.top()!='('){
                    cout<<mystack.pop();
                }
                mystack.push(op);
                break;
        }
    }
    while(!mystack.isEmpty()){
        cout<<mystack.pop();
    }
}
int main() {
    //检测回文
    cout<<isReserve("werew")<<endl;
    cout<<isReserve("werreeew")<<endl;
    cout<<endl;
    //括号匹配
    cout<<parenMatch("([[{}]])")<<endl;
    cout<<parenMatch("((([[[]])))")<<endl;
    cout<<parenMatch("(()")<<endl;
    cout<<endl;

    //计算后缀表达式
    cout<<calcPost("5723*-*82/+")<<endl;
    cout<<calcPost("123*+45*6/-")<<endl;

    //中缀转后缀
    inToSufForm("2+3");
    cout<<endl;
    inToSufForm("(5+6*(7+3)/3)/4+5");
    cout<<endl;
    return 0;
}
