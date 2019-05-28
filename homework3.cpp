#include<iostream>
#include<cstring>
using namespace std;

template<class T>
class linkStack {
private:
	struct node {
		node *next;
		T data;
		int flag;
		node(const T &x, node *N = NULL, int f = 0) :data(x), next(N), flag(f) {}
		node() :next(NULL) {}
		~node() {}
	};
	node *top;
public:
	linkStack();
	~linkStack();
	bool isEmpty()const;
	void push(const T &x);
	T pop();
	T Top()const;
	void op();
	int opr();

};
template<class T>
linkStack<T>::linkStack()
{
	top = NULL;
}

template<class T>
linkStack<T>::~linkStack()
{
	node *tmp;
	while (top != NULL)
	{
		tmp = top;
		top = top->next;
		delete tmp;

	}
}
template<class T>
bool linkStack<T>::isEmpty()const
{
	return top == NULL;
}

template<class T>
void linkStack<T>::push(const T &x)
{
	top = new node(x, top);
}

template<class T>
T linkStack<T>::pop()
{
	node *tmp = top;
	T value = tmp->data;
	top = top->next;
	delete tmp;
	return value;
}

template<class T>
T linkStack<T>::Top()const
{
	return top->data;
}
template <class T>
void linkStack<T>::op()
{
	top->flag++;
}

template<class T>
int linkStack<T>::opr()
{
	return top->flag;
}

template<class T>
class Tree {
private:
	struct node {
		node *left, *right, *parent;
		T data;
		int height;

		node() :left(NULL), right(NULL) {}
		node(const T &x, node *L = NULL, node *R = NULL) : data(x), left(L), right(R) {}
		~node() {}
	};
	int Height(node *t)const;
	node *root;
public:
	Tree() : root(NULL) {};
	Tree(T x) { root = new node(x); }
	~Tree() {}
	bool isEmpty()const;
	void mark();
	int Height()const;
	void create();
	void path();
};

template<class T>
bool Tree<T>::isEmpty()const
{
	return root == NULL;
}

template<class T>
void Tree<T>::create()
{
	linkStack<node *> s;
	node *tmp;
	T x, data;
	cin >> x;
	root = new node(x);
	s.push(root);
	bool flag = false;
	while (!s.isEmpty())
	{
		while (s.opr() == 2)
		{
			s.pop();
			if (s.isEmpty())
			{
				flag = true; break;
			}
		}
		if (flag) break;
		cin >> data;
		tmp = s.Top();
		s.op();
		if (s.opr() == 1)
		{
			if (data != '#')s.push(tmp->left = new node(data));
			continue;
		}
		if (s.opr() == 2)
		{
			if (data != '#')s.push(tmp->right = new node(data));
		}
	}
}

template<class T>
int Tree<T>::Height(Tree<T>::node *t)const
{
	if (t == NULL) return 0;
	else
	{
		int lt = Height(t->left), rt = Height(t->right);
		if (lt > rt)
			return lt + 1;
		return rt + 1;
	}
}

template<class T>
int Tree<T>::Height()const
{
	return Height(root);
}

int main()
{
	Tree<char> a;
	a.create();
	cout << a.Height() << '\n';
	a.path();

	return 0;
}
template<class T>
void Tree<T>::path()
{
	if (root == NULL) return;
	int H = Height(root), i = 0;
	//T path[20];
	cout<< root->data;
	node *tmp = root;
	while (i < H)
	{
	    if(tmp->right==NULL && tmp->left)
        {
            tmp=tmp->left;
            cout<<tmp->data;
        }
        if(tmp->left==NULL && tmp->right)
        {
            tmp=tmp->right;
            cout<<tmp->data;
        }
        if(tmp->left==NULL && tmp->right)
            break;
        if(Height(tmp->left) >= Height(tmp->right))
        {
            tmp=tmp->left;
            cout<<tmp->data;
        }
        else
        {
            tmp=tmp->right;
            cout<<tmp->data;
        }
        i++;
    }
}


//		if (tmp->right==NULL&& tmp->left!=NULL)
//		{
//			tmp = tmp->left;
//			path[i + 1] = tmp->data;
//		}
//		if (tmp->left ==NULL&& tmp->right != NULL)
//		{
//			tmp = tmp->right;
//			path[i + 1] << tmp->data;
//		}
//		if (tmp->left==NULL && tmp->right != NULL)
//			break;
//		if (Height(tmp->left) >= Height(tmp->right))
//		{
//			tmp = tmp->left;
//			path[i + 1] << tmp->data;
//		}
//		else
//		{
//			tmp = tmp->right;
//			path[i + 1] << tmp->data;
//		}
//		i++;
//	}
//for (i = 0; i <= 20; i++)
//	cout << path[i];
//}
//
