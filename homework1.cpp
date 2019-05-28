// homework1.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#include <iostream>
using namespace std;
struct node
{
	int zhishu;
	float xishu;
	node *next;
	node(const float &x1, const int &x2, node *n = NULL)
	{
		xishu = x1;
		zhishu = x2;
		next = n;
	}
	node() :next(NULL) {}
};
class linklist {
private:
	node *head;
	int currentlength;
	node *move(int i)const
	{
		node *p = head;
		while (i-- >= 0)
			p = p->next;
		return p;
	};
public:
	linklist();//
	void create(node &x);//
	void change();//
	void paixu();
	linklist cheng(linklist a, linklist b);
	void adjust();//
	void insert(int i, const float &x1, const int &x2);
	void print()const ;//
};
linklist::linklist() {
	head = new node;
	currentlength = 0;
	head->next = NULL;
}
void linklist::create(node &x) {
	x.next = head->next;
	head->next = &x;
}

void linklist :: insert(int i, const float &x1, const int &x2)
{
	node *p = move(i - 1);
	p->next = new node(x1, x2, p->next);
	currentlength++;
}
void linklist::change() {
	node *q = head->next, *r, *w;
	while (q) {
		r = q->next; w = q;
		while (r) {
			if (q->zhishu == r->zhishu)
			{
				q->xishu += r->xishu;
				w->next = r->next;
				delete r;
				r = w->next;
			}
			else {
				w = r; r = r->next;
			}

		}
		q = q->next;
	}
}
void linklist::paixu() {
	node *p = head->next, *q;
	float  tmp1;
	int tmp;
	for (; p != NULL; p = p->next)
	{
		q = p->next;
		for (; q != NULL; q = q->next)
		{
			if (p->zhishu > q->zhishu)
			{
				tmp = p->zhishu;
				p->zhishu = q->zhishu;
				q->zhishu = tmp;
				tmp1 = q->xishu;
				q->xishu = p->xishu;
				p->xishu = tmp1;
			}
		}
	}
}
linklist linklist::cheng(linklist a, linklist b) {
	linklist c; node *r = c.head, *w;
	node *p = a.head->next, *q;
	while (p) {
		q = b.head->next;
		while (q) {
			w = new node;
			w->zhishu = p->zhishu + q->zhishu;
			w->xishu = p->xishu*q->xishu;
			w->next = NULL;
			r->next = w;
			r = w;
			q = q->next;
		}
		p = p->next;
	}

	return c;

}
void  linklist::adjust()
{
	node *p = head->next, *q = head;
	while (p) {
		if (p->xishu != 0) {
			q = p;
			p = p->next;
		}
		else { q -> next = p ->next;
		delete p;
		p = q->next;
		}
	}
}
void linklist::print()const {

		node *p = head->next;
		while (p != NULL)
		{
			cout << p->xishu << ',' << p->zhishu  << ' ';
			p = p->next;
		}
		cout << "\n";

};

int main()
{
	linklist x1, x2, x3;
	char ch = ' ';
	float a;
	int b;

	while (ch == ' ')
	{
		cin >> a >> ch >> b;
		x1.insert(0, a, b);
		cin.get(ch);
		if (ch == '\n')
			break;
	}
	ch = ' ';
	while (ch == ' ')
	{
		cin >> a >> ch >> b;
		x2.insert(0, a, b);
		cin.get(ch);
		if (ch == '\n')
			break;
	}
	x3 = x3.cheng(x1, x2);
	x3.adjust();
	x3.change();
	x3.paixu();
	x3.print();

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

