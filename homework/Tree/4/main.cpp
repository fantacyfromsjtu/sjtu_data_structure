#include <iostream>
#include <bits/stdc++.h>
#include <list>
#include <sstream>
#include <iomanip>
#include <string>
using namespace std;

struct Token {  // 一个简单的结构体，成员只有一个字符串，用来储存数值或符号
    string text;
    Token(string text) : text(text) {}
    double doubleValue() {  // 将string类型转化为double类型
        stringstream ss(text);
        double value;
        ss >> value;
        return value;
    }
};

class Parser {

    struct Tree {      // 二叉树
        Token token;   // 储存数值或符号
        Tree * left;   // 指向左子树的指针
        Tree * right;  // 指向右子树的指针

        Tree(Token token) : token(token) {
            left = 0;
            right = 0;
        }
        ~Tree() {
            if (left != 0) delete left;
            if (right != 0) delete right;
        }
    };

    Tree * expression;  // 指向表达式二叉树的指针
    double result;      // 整个表达式的计算结果


    // ！！！计算表达式的值
    static double execute(Tree * expression) {
        if (expression->left == 0) {   // ！！！左子树为空时，token储存的是当前子树的值
            return expression->token.doubleValue();
        } else {   // ！！！左右子树均存在，分别计算左右子树的值，再根据符号进行四则运算
            double leftnum= execute(expression->left);
            double rightnum= execute(expression->right);
            if(expression->token.text=="+") return leftnum+rightnum;
            if(expression->token.text=="-") return leftnum-rightnum;
            if(expression->token.text=="*") return leftnum*rightnum;
            if(expression->token.text=="/") return leftnum/rightnum;
        }
    }

public:
    Parser() {
        expression = 0;
    }

    ~Parser() {
        if (expression != 0) delete expression;
    }

    // 执行表达式计算
    double execute() {
        if (expression != 0) {
            result = execute(expression);
            delete expression;
            expression = 0;
        }
        return result;
    }

    // 创建一棵新树, 这里用list模拟实现栈的功能
    void create(list<Tree*> &subTreeStack, list<string> &operatorStack) {
        Tree* node = new Tree(Token(operatorStack.back()));  // 新子树值为此时符号栈的顶部
        operatorStack.pop_back();              // pop掉符号栈的栈顶
        node->right = subTreeStack.back();     // 新树的右孩子为子树栈的顶部
        subTreeStack.pop_back();               // pop掉子树栈的栈顶
        if (!subTreeStack.empty()) {
            node->left = subTreeStack.back();  // 新树的左孩子为此时子树栈的顶部
            subTreeStack.pop_back();
        } else {  // 考虑特殊情况: -5、-0、+0
            Tree* temp = new Tree(Token("0"));
            node->left = temp;                 // 新树的左孩子为一个值为0的子树
        }
        subTreeStack.push_back(node);   // 新树加进栈顶
    }

    // ！！！将表达式构建成一棵二叉树
    bool parse(string str) {
        bool minusflag= false;
        if (expression != nullptr) {
            delete expression;
            expression = nullptr;
        }
        int len=str.size();
        int i=0;
        list<Tree*> subTreeStack;
        list<string> operatorStack;
        while(i<len){
            if (!(str[i]>='0'&&str[i]<='9'||str[i]=='+'||str[i]=='-'||str[i]=='*'
                  ||str[i]=='/'||str[i]=='.'||str[i]=='('||str[i]==')')) return false;

            if(str[i]>='0'&&str[i]<='9'){
                string curnum;
                if(minusflag)  {curnum="-"; minusflag= false;}
                bool isxiaoshu= false;
                for(;i<len;i++){
                    if(str[i]>='0'&&str[i]<='9') curnum+=str[i];
                    else if(str[i]=='+'||str[i]=='-'||str[i]=='*'||str[i]=='/'||str[i]=='('||str[i]==')'){
                        i--;
                        break;
                    }
                    else if(!isxiaoshu&&str[i]=='.'){
                        curnum+=str[i];
                        isxiaoshu= true;
                        if(i+1==len||!(str[i+1]>='0'&&str[i+1]<='9')) return false;
                    }
                    else return false;
                }
                Tree* leaf=new Tree(Token(curnum));
                subTreeStack.push_back(leaf);
            }
            else if(str[i]=='('){
                operatorStack.emplace_back("(");
                if(str[i+1]=='-'){
                    i++;
                    minusflag= true;
                }
            }
            else if(str[i]==')'){
                while(!operatorStack.empty()&&operatorStack.back()!="("){
                    create(subTreeStack, operatorStack);
                }
                operatorStack.pop_back();
            }
            else if(str[i]=='*'||str[i]=='/'){
                while (!operatorStack.empty()&&(operatorStack.back()=="*"||operatorStack.back()=="/")){
                    create(subTreeStack,operatorStack);
                }
                string token(1,str[i]);
                operatorStack.push_back(token);
            }
            else if(str[i]=='+'||str[i]=='-'){
                while (!operatorStack.empty()&&(operatorStack.back()!="(")){
                    create(subTreeStack,operatorStack);
                }
                string token(1,str[i]);
                operatorStack.push_back(token);
            }
            i++;
        }
        while (!operatorStack.empty()){
            if(subTreeStack.empty()) return false;
            create(subTreeStack,operatorStack);
        }
        if (subTreeStack.size() != 1 || !operatorStack.empty()) {
            return false;  // 解析失败
        }
        expression = subTreeStack.back();
        return true;
    }
};

int main(int argc, char const *argv[]) {
    Parser p = Parser();
    string expression;
    while (cin >> expression) {
        if (expression.length() > 0) {  // 不处理空字符串
            if(p.parse(expression))
                cout << fixed << setprecision(3) <<  p.execute() << endl;
            else
                cout << "invalid"<<endl;
        }
    }
    return 0;
}