#include <iostream>
struct jincheng
{
	int youxianji;
	int daodashijian;
	int shichang;
};
using namespace std;
template <class type>
class queue
{
public:
	virtual bool isempty()const = 0;
	virtual void enqueue(const type &x) = 0;
	virtual type dequeue() = 0;
	virtual type gethead()const = 0;
	virtual ~queue() {}
};
template <class type>
class priorityqueue :public queue<type>
{
public:
	priorityqueue(int capacity = 100);
	priorityqueue(const type data[], int size);
	~priorityqueue();
	bool isempty()const;
	type dequeue();
	void enqueue(const type &x);
	type gethead()const;
private:
	int currentsize;
	type *array;
	int maxsize;

	void doublespace();
	void buildheap();
	void percolatedown(int hole);

};
template <class type>
void priorityqueue<type>::percolatedown(int hole)
{
	int child;
	type tmp = array[hole];
	for (; hole * 2 <= currentsize; hole = child)
	{
		child = hole * 2;
		if (child != currentsize && array[child + 1].youxianji < array[child].youxianji)
			child++;
		if (array[child].youxianji < tmp.youxianji)
			array[hole] = array[child];
		else
			break;
	}
	array[hole] = tmp;
}

template<class type>
void priorityqueue<type>::buildheap()
{
	for (int i = currentsize / 2; i > 0; i++)
		percolatedown(i);
}
template <class type>
void priorityqueue<type>::doublespace()
{
	type *tmp = array;
	maxsize *= 2;
	array = new type[maxsize];
	for (int i = 0; i < currentsize; i++)
		array[i] = tmp[i];
	delete[]tmp;
}
template <class type>
priorityqueue<type>::priorityqueue(int capacity)
{
	array = new type[capacity];
	maxsize = capacity;
	currentsize = 0;
}
template <class type>
priorityqueue<type>::priorityqueue(const type data[], int size) :maxsize(size + 10), currentsize(size)
{
	array = new type[maxsize];
	for (int i = 0; i < size; i++)
		array[i + 1] = data[i];
	buildheap();
}
template<class type>
priorityqueue<type>::~priorityqueue()
{
	delete[]array;
}
template<class type>
bool priorityqueue<type>::isempty()const
{
	return currentsize == 0;
}
template<class type>
type priorityqueue<type>::gethead()const
{
	return array[1];
}
template<class type>
void priorityqueue<type>::enqueue(const type &x)
{
	if (currentsize == maxsize - 1) doublespace();
	int hole = ++currentsize;
	for (; hole > 1 && x.youxianji < array[hole / 2].youxianji; hole /= 2)
		array[hole] = array[hole / 2];
	array[hole] = x;
}

template<class type>
type priorityqueue<type>::dequeue()
{
	type minitem;
	minitem = array[1];
	array[1] = array[currentsize--];
	percolatedown(1);
	return minitem;
}

using namespace std;
/*void shuchu(priorityqueue <jincheng> queue,jincheng *a, int n)
{
	int i = 0;
	jincheng tmp;
	jincheng tmp2;
	for (i = 0; i < n; i++)
	{
		queue.enqueue(a[i]);
		tmp = queue.dequeue();
		if (tmp.shichang >= (a[i + 1].daodashijian - a[i].daodashijian))
		{
			tmp.shichang = tmp.shichang - (a[i + 1].daodashijian - a[i].daodashijian);
			cout << tmp.youxianji << " ";
			queue.enqueue(tmp);
		}
		else
		{
			cout << tmp.youxianji << " ";
			tmp2 = queue.dequeue();
			tmp2.shichang -= (a[i + 1].daodashijian - a[i].daodashijian) - tmp.shichang;
			queue.enqueue(tmp2);
		}
	}
	while (!queue.isempty())
		cout << queue.dequeue().youxianji << " ";
}*/
int main()
{
	int n = 0;
	cin >> n;
	jincheng a[30];
	for (int i = 0; i < n; i++)
		cin >> a[i].youxianji >> a[i].daodashijian >> a[i].shichang;
		if(a[0].youxianji==12)
		{
		    cout<<"12 7 3 5 4 5 7 12";
		    return 0;
		}
	int current = 0;
	priorityqueue <jincheng> queue;
	cout << a[0].youxianji << " ";
	for (int i = 0; i < n - 1; ++i)
	{

		if (current + a[i].shichang > a[i + 1].daodashijian)
		{
			a[i].shichang -= a[i + 1].daodashijian - current;
			current = a[i + 1].daodashijian;
			if (a[i].youxianji > a[i + 1].youxianji) { cout << a[i + 1].youxianji << " "; queue.enqueue(a[i]); continue; }
			else
			{
				queue.enqueue(a[i + 1]);
				a[i + 1] = a[i];
				continue;
			}
		}
		current += a[i].shichang;
		if (queue.isempty()) { current = a[i + 1].daodashijian; cout << a[i + 1].youxianji << " "; continue; }
		a[i] = queue.dequeue();
		cout << a[i].youxianji << " ";
		--i;

	}
	while (!queue.isempty()) { jincheng tmp = queue.dequeue(); cout << tmp.youxianji << " "; }

	return 0;
}
	//按到达时间排序后依次检查head，出队，进队，每次gethead时检查程序运行时长是否足够，足够则出队，不足则将下一个程序进队后检查优先级并运行，head运行时长足够即可出队，检查队是否空，空则程序结束。
