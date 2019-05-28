#include <iostream>
using  namespace std;

template <class Type>
class BinarySearchTree
{
private:
	struct BinaryNode
	{
		Type data;
		BinaryNode *left;
		BinaryNode *right;
		BinaryNode(const Type & thedata, BinaryNode *lt, BinaryNode *rt) : data(thedata), left(lt), right(rt) { }
	};
	BinaryNode *root;
public:
	BinarySearchTree(BinaryNode *t = NULL) { root = t; }
	bool find(const Type & x) const;
	void insert(const Type & x);
	void remove(const Type & x);
	bool findout(const Type &x)const;
private:
	void insert(const Type & x, BinaryNode * & t);
	void remove(const Type & x, BinaryNode * & t);
	bool findout(const Type & x, BinaryNode *t) const;
	bool find(const Type & x, BinaryNode *t) const;
	//void makeEmpty(BinaryNode * & t);
};
template <class Type>
bool BinarySearchTree<Type>::find(const Type &x) const
{
	return find(x, root);
}

template <class Type>
bool BinarySearchTree<Type>::findout(const Type &x) const
{
	return findout(x, root);
}

template <class Type>
bool BinarySearchTree<Type>::find(const Type & x, BinaryNode *t) const
{
	if (t == NULL)
		return false;
	else if (x < t->data)
		return find(x, t->left);
	else if (t->data < x)
		return find(x, t->right);
	else return true;
}
template <class Type>
bool BinarySearchTree<Type>::findout(const Type & x, BinaryNode *t) const
{
	if (t == NULL)
		return false;
	else if (x < t->data)
	{
		cout << t->data << " ";
		return findout(x, t->left);
	}
	else if (t->data < x)
	{
		cout << t->data << " ";
		return findout(x, t->right);
	}
	else
		cout << t->data;
	return true;
}
template <class Type>
void BinarySearchTree<Type>::insert(const Type & x)
{
	insert(x, root);
}

template <class Type>
void BinarySearchTree<Type>::insert(const Type & x, BinaryNode *&t)
{
	if (t == NULL)
		t = new BinaryNode(x, NULL, NULL);
	else if (x < t->data)  insert(x, t->left);
	else if (t->data < x)  insert(x, t->right);
}
template <class Type>
void BinarySearchTree<Type>::remove(
	const Type & x)
{
	remove(x, root);
}
template <class Type>
void BinarySearchTree<Type>::remove(const Type & x, BinaryNode * & t)
{
	if (t == NULL)  return;
	if (x < t->data)   remove(x, t->left);
	else if (t->data < x)  remove(x, t->right);
	else if (t->left != NULL && t->right != NULL) {
		BinaryNode *tmp = t->right;
		while (tmp->left != NULL)
			tmp = tmp->left;
		t->data = tmp->data;
		remove(t->data, t->right);
	}
	else {
		BinaryNode *oldNode = t;
		t = (t->left != NULL) ? t->left : t->right;
		delete oldNode;
	}
}

int main()
{
	int n;
	cin >> n;
	int a[100];
	for (int i = 0; i < n; ++i)
		cin >> a[i];
	int x;
	cin >> x;
	BinarySearchTree<int>  tree;
	for (int i = 0; i < n; ++i)
		tree.insert(a[i]);
	cout << (tree.find(x) ? 1 : -1) << endl;
	tree.findout(x);
	return 0;
}


