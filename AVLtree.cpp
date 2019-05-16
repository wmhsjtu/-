// AVLtree.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
using namespace std;
template <class Type>
class AvlTree {
	struct AvlNode
	{
		Type data;
		AvlNode *left;
		AvlNode *right;
		int height;
		AvlNode(const Type &element, AvlNode *lt, AvlNode *rt, int h = 0) : data(element), left(lt), right(rt), height(h) { }
	};

	AvlNode *root;
public:
	AvlTree(AvlNode *t = NULL) { root = t; }
	~AvlTree() { makeEmpty(root); }
	bool find(const Type & x) const;
	void insert(const Type & x) { insert(x, root); }
	void remove(const Type & x) { remove(x, root); }
private:
	void insert(const Type & x, AvlNode * & t);
	bool remove(const Type & x, AvlNode * & t);
	void makeEmpty(AvlNode * & t);
	int height(AvlNode *t) const
	{
		return t == NULL ? -1 : t->height;
	}
	void LL(AvlNode * & t);
	void LR(AvlNode * & t);
	void RL(AvlNode * & t);
	void RR(AvlNode * & t);
	int max(int a, int b) { return (a > b) ? a : b; }
};


template <class Type>
bool AvlTree<Type>::find(const Type & x) const
{
	AvlNode *t = root;
	while (t != NULL && t->data != x)
	{
		if (t->data > x) t = t->left;
		else t = t->right;
	}
	if (t == NULL) 
		return false;
	else 
		return true;
}

template <class Type>
void AvlTree<Type>::insert(const Type & x, AvlNode * & t)
{
	if (t == NULL)
		t = new AvlNode(x, NULL, NULL);
	else if (x < t->data) {
		insert(x, t->left);
		if (height(t->left) - height(t->right) == 2)
			if (x < t->left->data) LL(t); else LR(t);
	}
	else if (t->data < x) {
		insert(x, t->right);
		if (height(t->right) - height(t->left) == 2)
			if (t->right->data < x) RR(t); else RL(t);
	}
	t->height = max(height(t->left), height(t->right)) + 1;
}

template <class Type>
void AvlTree<Type>::LL(AvlNode * & t)
{
	AvlNode *t1 = t->left;
	t->left = t1->right;
	t1->right = t;
	t->height = max(height(t->left), height(t->right)) + 1;
	t1->height = max(height(t1->left), height(t)) + 1;
	t = t1;
}

template <class Type>
void AvlTree<Type>::RR(AvlNode * & t)
{
	AvlNode *t1 = t->right;
	t->right = t1->left;
	t1->left = t;
	t->height = max(height(t->left), height(t->right)) + 1;
	t1->height = max(height(t1->right), height(t)) + 1;
	t = t1;
}

template <class Type>
void AvlTree<Type>::LR(AvlNode * & t)
{
	RR(t->left);
	LL(t);
}

template <class Type>
void AvlTree<Type>::RL(AvlNode * & t)
{
	LL(t->right);
	RR(t);
}

template <class Type>
bool AvlTree<Type>::remove(const Type & x, AvlNode * & t)
{
	bool stop = false;
	int subTree;  // 1表示删除发生在左子树上， 
						 // 2表示删除发生在右子树上
	if (t == NULL)     return true;
	if (x < t->data) { stop = remove(x, t->left); subTree = 1; }
	else if (t->data < x)
	{
		stop = remove(x, t->right); subTree = 2;
	}
	else if (t->left != NULL && t->right != NULL) {
		AvlNode *tmp = t->right;
		while (tmp->left != NULL) tmp = tmp->left;
		t->data = tmp->data;
		stop = remove(t->data, t->right);
		subTree = 2;
	}
	else {
		AvlNode *oldNode = t;
		t = (t->left != NULL) ? t->left : t->right;
		delete oldNode;
		return false;
	}
	if (stop) return true;
	int bf;
	switch (subTree) {
	case 1: bf = height(t->left) - height(t->right) + 1;
		if (bf == 0) return true; //情况一
		if (bf == 1)  return false; //情况二
		if (bf == -1) { //情况三
			int bfr = height(t->right->left) - height(t->right->right);
			switch (bfr) {
			case 0: RR(t); return true;
			case -1: RR(t); return false;
			default: RL(t); return false;
			}
		}
		break;
	case 2: bf = height(t->left) - height(t->right) - 1;
		if (bf == 0) return true; //情况一
		if (bf == -1) return false; //情况二
		if (bf == 1) { //情况三
			int bfl = height(t->right->left)
				- height(t->right->right);
			switch (bfl) {
			case 0: LL(t); return true;
			case 1: LL(t); return false;
			default: LR(t); return false;
			}
		}
	}
}

int main()
{
	cout << "Hello world!" << endl;
	return 0;
}


// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门提示: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
