#include<iostream>
#include<cstring>
using namespace std;

template<class elemtype>
class linkqueue{
private:
    struct node{
        elemtype data;
        node *next;
        node(const elemtype &x, node *N=NULL)
        {
            next = N;  data = x;
        }
        node():next(NULL){}
        ~node(){}
    };
    int length;
    node *front;
    node *rear;
public:
    linkqueue();
    ~linkqueue();
    elemtype dequeue();
    elemtype gethead()const;
    bool isEmpty()const;
    void enqueue(const elemtype &x);
    int Length()const;
};

template<class elemtype>
elemtype linkqueue<elemtype>::dequeue()
{
    node *tmp = front;
    elemtype value = front->data;
    front = front->next;
    if(front == NULL) rear = NULL;
    delete tmp;
    length--;
    return value;
}

template<class elemtype>
elemtype linkqueue<elemtype>::gethead()const
{
    return front->data;
}

template<class elemtype>
bool linkqueue<elemtype>::isEmpty()const
{
    return front == NULL;
}

template<class elemtype>
void linkqueue<elemtype>::enqueue(const elemtype &x)
{
    if(rear == NULL)
        front = rear = new node(x);
    else
        rear = rear->next = new node(x);
    length++;
}

template<class elemtype>
int linkqueue<elemtype>::Length()const
{
    return length;
}

template<class elemtype>
linkqueue<elemtype>::linkqueue()
{
    length = 0;
    front = rear = NULL;
}

template<class elemtype>
linkqueue<elemtype>::~linkqueue()
{
    node *tmp;
    while(front!=NULL)
    {
        tmp = front;
        front = front->next;
        delete tmp;
    }
}


template <class T>
T queuepop(linkqueue<T> &que1, linkqueue<T> &que2)
{
    T value, i=0;
    while(i < que1.Length()-1)
    {
        que2.enqueue(que1.gethead());
        que1.dequeue();
        i++;
    }
    value = que1.gethead();
    que1.dequeue();
    i=0;
    while(i<que2.Length())
    {
        que1.enqueue(que2.gethead());
        que2.dequeue();
        i++;
    }
    return value;
}
template <class T>
T queuepush(linkqueue<T> &que1)
{
    T x;
    cin>>x;
    que1.enqueue(x);
}
int main()
{
    char s[10];
    cin.getline(s,10);
    if(!strcmp(s,"int"))
    {
        linkqueue<int> que1, que2;
        queuepush(que1);
        queuepush(que1);
        cout<<queuepop(que1, que2)<<' ';
        queuepush(que1);
        cout<<queuepop(que1, que2)<<' ';
        cout<<queuepop(que1, que2)<<' ';
        queuepush(que1);
        queuepush(que1);
        cout<<queuepop(que1, que2)<<' ';
        cout<<queuepop(que1, que2);
    }
    else
    {
        linkqueue<char> que1, que2;
        queuepush(que1);
        queuepush(que1);
        cout<<queuepop(que1, que2)<<' ';
        queuepush(que1);
        cout<<queuepop(que1, que2)<<' ';
        cout<<queuepop(que1, que2)<<' ';
        queuepush(que1);
        queuepush(que1);
        cout<<queuepop(que1, que2)<<' ';
        cout<<queuepop(que1, que2);
    }
    return 0;
}
