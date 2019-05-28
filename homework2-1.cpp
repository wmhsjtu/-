#include<iostream>
#include<cstring>
using namespace std;

class seqStack
{
private:
    int top_p;
    char *elem;
    int maxsize;
    void doublespace();
public:
    seqStack(int initsize=10);
    ~seqStack();
    bool isEmpty()const;
    void push(const char &x);
    char pop();
    char top()const;
};

void seqStack::doublespace()
{
    char *tmp = elem;
    elem = new char [2*maxsize];
    for(int i=0; i<maxsize; ++i)
        elem[i] = tmp[i];

    maxsize*=2;
    delete []tmp;
}


seqStack::seqStack(int initsize)
{
    maxsize = initsize;
    elem = new char [maxsize];
    top_p = -1;
}


seqStack::~seqStack()
{
    delete []elem;
}


bool seqStack::isEmpty()const
{
    return top_p == -1;
}


void seqStack::push(const char &x)
{
    if(top_p == maxsize-1)
       doublespace();
    elem[++top_p] = x;
}


char seqStack::pop()
{
    return elem[top_p--];
}


char seqStack::top()const
{
    return elem[top_p];
}

int main()
{
    char s[100000];
    seqStack fuhao;

    cin.getline(s,1000000);
    for(int i=0; s[i]!='\0'; ++i)
    {
        if(s[i]>='a' && s[i]<='z') cout<<s[i];
        else if(s[i] == '(') fuhao.push(s[i]);
        else if(s[i] == ')')
        {
            while(fuhao.top() != '(')
            {
                cout<<fuhao.pop();
            }
            if(fuhao.top() == '(')
                fuhao.pop();
        }
        else if(s[i] == '*' || s[i] == '/')
        {
            //括号中多次pop判断会直接出栈吗？
            while(fuhao.top() != '+' && fuhao.top() != '-' && fuhao.top() != '(' && !fuhao.isEmpty())
            {
               cout<<fuhao.pop();
            }

            fuhao.push(s[i]);
        }
        else if(s[i] == '+' || s[i] == '-')
        {
            while(!fuhao.isEmpty() && fuhao.top()!='(')
            {
                cout<<fuhao.pop();
            }
            fuhao.push(s[i]);
        }
    }

    while(!fuhao.isEmpty())
        cout<<fuhao.pop();
    return 0;
}


