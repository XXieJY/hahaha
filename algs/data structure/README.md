[ref july](https://blog.csdn.net/v_JULY_v/article/details/6305212)

### map、unordered_map、unordered_set的stl原理以及简单实现
* map的内部结构是R-B-tree来实现的
* unordered_map内部结构是hashtable中存放键值对
* unordered_set就是在hashtable中存放value

区别在于使用非内置类型时：
1. stl::map 的key需要定义operator< 。 
2. 而stl::unordered_map需要定义hash_value函数并且重载operator==。
3. 对于内置类型，如string，这些都不用操心。对于自定义的类型做key，就需要自己重载operator< 或者hash_value()了。 

```cpp

#include<string>
#include<iostream>
#include<map>
 
using namespace std;
 
struct person
{
	string name;
	int age;
 
	person(string name, int age)
	{
		this->name =  name;
		this->age = age;
	}
 
	bool operator < (const person& p) const
	{
		return this->age < p.age;
	}
};
 
map<person,int> m;
int main()
{
	person p1("Tom1",20);
	person p2("Tom2",22);
	person p3("Tom3",22);
	person p4("Tom4",23);
	person p5("Tom5",24);
	m.insert(make_pair(p3, 100));
	m.insert(make_pair(p4, 100));
	m.insert(make_pair(p5, 100));
	m.insert(make_pair(p1, 100));
	m.insert(make_pair(p2, 100));
	
	for(map<person, int>::iterator iter = m.begin(); iter != m.end(); iter++)
	{
		cout<<iter->first.name<<"\t"<<iter->first.age<<endl;
	}
	
	return 0;
}


//例子二
#include<string>
#include<iostream>
 
#include<boost/unordered_map.hpp>
 
using namespace std;
 
struct person
{
	string name;
	int age;
 
	person(string name, int age)
	{
		this->name =  name;
		this->age = age;
	}
 
	bool operator== (const person& p) const
	{
		return name==p.name && age==p.age;
	}
};
 
size_t hash_value(const person& p)
{
	size_t seed = 0;
	boost::hash_combine(seed, boost::hash_value(p.name));
	boost::hash_combine(seed, boost::hash_value(p.age));
	return seed;
}
 
int main()
{
	typedef boost::unordered_map<person,int> umap;
	umap m;
	person p1("Tom1",20);
	person p2("Tom2",22);
	person p3("Tom3",22);
	person p4("Tom4",23);
	person p5("Tom5",24);
	m.insert(umap::value_type(p3, 100));
	m.insert(umap::value_type(p4, 100));
	m.insert(umap::value_type(p5, 100));
	m.insert(umap::value_type(p1, 100));
	m.insert(umap::value_type(p2, 100));
	
	for(umap::iterator iter = m.begin(); iter != m.end(); iter++)
	{
		cout<<iter->first.name<<"\t"<<iter->first.age<<endl;
	}
	
	return 0;
}

```

#### 1.map
1. stl::map是按照operator<比较判断元素是否相同，以及比较元素的大小，然后选择合适的位置插入到红黑树中。
2. 如果对map进行遍历（中序遍历）的话，输出的结果是有序的。顺序就是按照operator< 定义的大小排序。



#### 2.unordered_map
首先分配一大片内存，形成许多桶。是利用hash函数，对key进行映射到不同区域（桶）进行保存。

其插入过程是：
1. 得到key
2. 通过hash函数得到hash值
3. 得到桶号(一般都为hash值对桶数求模)
4. 存放key和value在桶内。

其取值过程是:
1. 得到key
2. 通过hash函数得到hash值
3. 得到桶号(一般都为hash值对桶数求模)
4. 比较桶的内部元素是否与key相等，若都不相等，则没有找到。
5. 取出相等的记录的value。

------------

### heap在STL中的原理以及heap的简单实现

#### 1.利用STL使用Heap
1. 在stl中通常使用algorithm库内的make_heap, pop_heap, push_heap, sort_heap实现堆的构建。
2. 或者使用priority_queue代替堆的实现，此时Priority_queue会自动调用上述make_heap, pop_heap, push_heap，sort_heap等方法来维护堆。

priority_queue的使用范例：
```cpp
#include <iostream> 
#include <queue> 
  
using namespace std; 
  
void showpq(priority_queue <int> gq) 
{ 
    //大顶堆默认
    priority_queue <int> g = gq;
    //小顶堆需要传入greater<>
    //std::priority_queue<int, std::vector<int>, std::greater<int> > third (gq.begin(),gq.end()); 
    while (!g.empty()) 
    { 
        cout << '\t' << g.top(); 
        g.pop(); 
    } 
    cout << '\n'; 
} 
  
int main () 
{ 
    priority_queue <int> gquiz; 
    gquiz.push(10); 
    gquiz.push(30); 
    gquiz.push(20); 
    gquiz.push(5); 
    gquiz.push(1); 
  
    cout << "The priority queue gquiz is : "; 
    showpq(gquiz); 
  
    cout << "\ngquiz.size() : " << gquiz.size(); 
    cout << "\ngquiz.top() : " << gquiz.top(); 
  
  
    cout << "\ngquiz.pop() : "; 
    gquiz.pop(); 
    showpq(gquiz); 
  
    return 0; 
} 
```


make_heap系列的使用范例。
注意：
1. make_heap默认是大顶堆，如果需要小顶堆则要写一个comp函数传入。
```cpp
struct greaters{ 
  bool operator()(const long& a,const long& b) const{ 
    return a>b; 
  } 
}; 
  
int main() 
{ 
    // initializing vector; 
    vector<int> vi = { 15, 6, 7, 9, 11, 45 }; 
      
    // using make_heap() to transform vector into 
    // a min heap 
    make_heap(vi.begin(),vi.end(), greaters()); 
      
    // checking if heap using  
    // front() function 
    cout << "The minimum element of heap is : "; 
    cout << vi.front() << endl; 
      
} 
```
2. 注意要先在vector中用push_back之后再调用push_heap
3. 调用完pop_heap之后要接着调用vector.pop_back()。
```cpp
#include<iostream>
#include<vector>
#include<algorithm>
 
using namespace std;
 
int main()
{
    int a[] = {15, 1, 12, 30, 20};
    vector<int> ivec(a, a+5);
    for(vector<int>::iterator iter=ivec.begin();iter!=ivec.end();++iter)
        cout<<*iter<<" ";
    cout<<endl;
 
    make_heap(ivec.begin(), ivec.end());//建堆
    for(vector<int>::iterator iter=ivec.begin();iter!=ivec.end();++iter)
        cout<<*iter<<" ";
    cout<<endl;
 
    pop_heap(ivec.begin(), ivec.end());//先pop,然后在容器中删除
    ivec.pop_back();
    for(vector<int>::iterator iter=ivec.begin();iter!=ivec.end();++iter)
        cout<<*iter<<" ";
    cout<<endl;
 
    ivec.push_back(99);//先在容器中加入，再push
    push_heap(ivec.begin(), ivec.end());
    for(vector<int>::iterator iter=ivec.begin();iter!=ivec.end();++iter)
        cout<<*iter<<" ";
    cout<<endl;
 
    sort_heap(ivec.begin(), ivec.end());
    for(vector<int>::iterator iter=ivec.begin();iter!=ivec.end();++iter)
        cout<<*iter<<" ";
    cout<<endl;
 
    return 0;
}
```



#### 2.简单堆实现：

完全二叉树性质：
1. 所有的叶结点都出现在倒数第一层和倒数第二层。
2. 叶子节点数n0为节点总数n的一半，即n0=n/2。
3. 节点i的做孩子为2i,右孩子为2i+1。
4. 若i>1，则i的父亲节点为i/2{以1为根节点时}，或者(i-1)/2{以0为根节点时}。
5. 若i>1且i是奇数，则i的左兄弟一定是i-1。
6. 若i<n且i是偶数，则i的做兄弟一定是i+1。
7. 若i>n/2，则i一定是叶子节点。
8. 第k层最多有2^(k-1)个节点，共k层的完全二叉树最多有(2^k)-1个节点。


堆的性质：
1. 堆总是一棵完全二叉树。
2. 堆中某个节点的值总是不大于或不小于其父节点的值。
3. 将根节点最大的堆叫做最大堆或大根堆，根节点最小的堆叫做最小堆或小根堆。
4. n个结点的堆，高度为O(logn),时间复杂度为O(logn)。


根据完全二叉树有堆的定义：
1. n个元素的序列{k1,k2,ki,…,kn}当且仅当满足下关系时，称之为堆。
    * (ki <= k2i,ki <= k2i+1), (i = 1,2,3,4...n/2)
    * 或者(ki >= k2i,ki >= k2i+1), (i = 1,2,3,4...n/2)
2. 若将和此次序列对应的一维数组（即以一维数组作此序列的存储结构）看成是一个完全二叉树，则堆的含义表明，完全二叉树中所有非终端结点的值均不大于（或不小于）其左、右孩子结点的值。

堆的操作及实现：
1. 堆可以使用数组实现，依照上述堆的定义和完全二叉树的性质来操纵数组形成大顶堆或者小顶堆。
2. 在初始化堆和pop堆元素的时候应该调用AdjustDown向下调整来调整堆结构，在push堆元素的时候应该调用AdjustUp向上调整来调整堆结构。

```cpp
#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<malloc.h>
typedef int HPDataType;
typedef struct Heap
{
	HPDataType* data;//存放数据的数组
	int sz;//堆的数组元素个数
	int capacity;//堆的容量
}Heap;
 
 
void HeapInit(Heap* hp);//堆的初始化
void HeapDestory(Heap* hp);//堆的销毁
void HeapPush(Heap* hp, HPDataType x);//堆的插入
void HeapPop(Heap* hp);//堆的删除
HPDataType* HeapTop(Heap*hp);//获取堆顶的数据
int HeapSize(Heap* hp);//求堆的大小
int HeapEmpty(Heap* hp);//判断堆是否为空
void HeapSort(Heap*hp);//堆的冒泡排序


#include"Heap.h"
void Swap(HPDataType* x1, HPDataType* x2)
{
	HPDataType x = *x1;
	*x1 = *x2;
	*x2 = x;
}

void AdjustDown(HPDataType*data, int n, int root)//向下调整方法
{
	int parent = root;
	int child = parent * 2 + 1;
 
 
	while (child < n)
	{
		//选取左右孩子中较大的那个，默认为左孩子
		if ((data[child]<data[child + 1])
			&&(child+1<n))    //child+1<n防止出界
		{
			child++;
		}
		if (data[child] > data[parent])//比较孩子和父亲的大小，
		{
			Swap(&data[child], &data[parent]);
			parent = child;
			child = parent * 2 + 1;
		}
		else
		{
			break;
		}
	}
}

void HeapInit(Heap* hp, HPDataType*data, int n)//堆的初始化
{
	assert(hp);
	int i = 0;
	hp->data = (HPDataType*)malloc(sizeof(HPDataType)*n);//开辟数组大小的字节
	hp->sz = n;
	hp->capacity = n;
	for ( i = 0; i < n; i++)//给堆的数组赋值
	{
		hp->data[i] = data[i];
	}
	for (i = (n - 2) / 2; i >= 0; i--)//找到非叶子的最后一个节点，把大的向上调，小的向下
	{
		AdjustDown(hp->data, hp->sz, i);//
	}
 
}

void HeapDestory(Heap* hp)//堆的销毁
{
	assert(hp);
	free(hp->data);
	hp->data = NULL; 
	hp->sz = hp->capacity = 0;
}

//向上调整法，在HeapPop()中让孩子和父亲比较大小,把小的向上调整
void AdjustUp(HPDataType*data, int n, int child)
{
	assert(data);
	int parent = (child-1)/2;
	while (child > 0)
	{
		if (data[parent]<data[child])//当父亲小于孩子时，进行交换
		{
			Swap(&data[parent], &data[child]);
			child = parent;//改变孩子的大小
			parent = (child - 2) / 2;//改变父亲的大小
 
		}
		else
		{
			break;
		}
	}
}

void HeapPush(Heap* hp, HPDataType x)//堆的插入
{
	assert(hp);
	if (hp->sz == hp->capacity)//当堆的大小等于容量的大小，就要扩容
	{
		hp->capacity *= 2;
		hp->data = (HPDataType*)realloc(hp->data,sizeof(HPDataType)*hp->capacity);//开辟空间
	}
	hp->data[hp->sz] = x;
    //个数加1
	hp->sz++;
    //向上调整法，把大的调上去，小的放下边
	AdjustUp(hp->data, hp->sz,hp->sz-1);
}

//堆的删除,把堆顶数据和最后一个数据交换，再把对顶数据向下调整
void HeapPop(Heap* hp)
{
	assert(hp);
	Swap(&hp->data[0], &hp->data[hp->sz - 1]);
	HPDataType* cur = &hp->data[hp->sz - 1];
	hp->sz--;
	AdjustDown(hp->data, hp->sz, 0);
	return *cur;
}

HPDataType* HeapTop(Heap*hp)//获取堆顶的数据,
{
	assert(hp);
	return hp->data[0];
}

int HeapSize(Heap* hp)
{
	assert(hp);
	return hp->sz;
}

int HeapEmpty(Heap* hp)//空为0，非空1
{
	return hp->sz == 0 ? 0 : 1;//三字符运算
}

void PrintHeap(Heap* hp)//打印函数
{
	assert(hp);
	for (int i = 0; i < hp->sz; i++)
	{
		printf("%d ", hp->data[i]);
	}
	printf("\n");
}

void HeapSort(Heap*hp)//冒泡泡排序
{
	int i = 0;
	int j = 0;
	for (i = 0; i < hp->sz - 1; i++)
	{
		int flag = 0;//优化标记
		for (j = 0; j < hp->sz - i - 1; j++)//循环趟数
		{
			if (hp->data[j] < hp->data[j + 1])//比较次数
			{
				HPDataType tmp = hp->data[j];
				hp->data[j] = hp->data[j + 1];
				hp->data[j + 1] = tmp;
				flag = 1;
			}
		}
		if (flag == 0)//当里面没有交换时，说明交换完成
			return;
	}
}
```

---------------


### stack在STL的实现以及简单实现一个stack
1. stack在STL中是一个适配器，它的底层默认是deque。deque可以双端访问，stack只可以一端访问。
2. stack数据结构的定义就是不允许随机访问遍历，因此也没有实现迭代器，而是只能在栈顶访问。
3. stack的主要方法有 
    * empty() 堆栈为空则返回真
    * pop() 移除栈顶元素（不会返回栈顶元素的值） 
    * push() 在栈顶增加元素
    * size() 返回栈中元素数目
    * top() 返回栈顶元素                                                
```cpp

class MyStack
{
private:
	char *m_pBuffer;     // 栈空间的指针
	int m_iSize;         // 栈容量
	int m_iTop;          // 栈顶
 
public:
	MyStack(int size);
	~MyStack();
	bool stackEmpty();    //判断栈是否为空
	bool stackFull();     //判断栈是否满
	void clearStack();    // 清空栈
	int stackLength();    // 已有元素的个数
	bool push(char elem); // 将元素入栈 
	bool pop(char &elem); // 出栈
	void stackTraverse(); // 栈遍历
};


#include "MyStack.h"
#include<iostream>
using namespace std;
 
MyStack::MyStack(int size)
{
	m_iSize = size;
	m_pBuffer = new char[size];
	m_iTop = 0;
}
 
 
MyStack::~MyStack()
{
	delete[] m_pBuffer;
}
 
bool MyStack::stackEmpty()
{
	if (m_iTop == 0)
		return true;
	else
		return false;
}
 
bool MyStack::stackFull()
{
	if (m_iTop >= m_iSize)
		return true;
	else
		return false;
}
 
void MyStack::clearStack()
{
	m_iTop = 0;
}
 
int MyStack::stackLength()
{
	return m_iTop;
}
 
bool MyStack::push(char elem)
{
	if (stackFull())
	{
		return false;
	}
	m_pBuffer[m_iTop] = elem;
	m_iTop++;
	return true;
}
 
bool MyStack::pop(char &elem)
{
	if (stackEmpty())
		return false;
	m_iTop--;
	elem = m_pBuffer[m_iTop];
	return true;
}
 
void MyStack::stackTraverse()
{
	for (int i = m_iTop - 1; i >= 0; i--)
	{
		cout << m_pBuffer[i] << ",";
	}
	cout << endl;
 
}
```

#### queue原理及其简单实现

1. queue同stack一样也是适配器，queue的底层实现依然是dequeue。

```cpp
class Queue
{
public:
    //构造函数：初始化队列，假设队列元素都为简单的整型数据
    //C++实现                   //C语言实现

    Queue(int QueueCapacity);   //InitQueue(&Q)       创建队列
    virtual ~Queue();           //DestroyQueue(&Q)    销毁队列
    void ClearQueue();          //ClearQueue(&Q)      清空队列
    bool QueueEmpty() const;    //QueueEmpty(Q)       判断队列是否为空
    bool QueueFull() const;     //QueueFull(Q)        判断队列是否为满
    int QueueLength() const;    //QueueLength(Q)      队列长度
    bool EnQueue(int element);  //EnQueue(&Q,element) 新元素入队
    bool DeQueue(int &element); //DeQueue(&Q,&element)首元素出队
    void QueueTraverse();       //QueueTranverse(Q)   遍历队列
private:
    int *m_pQueue;              //队列数组指针
    int m_iQueueLen;            //队列元素的个数
    int m_iQueueCapacity;       //队列的数组容量
    int m_iHead;
    int m_iTail;
};

//类中成员函数的实现

#include"Queue.h"
#include<iostream>
using namespace std;

Queue::Queue(int QueueCapacity)
{
    m_iQueueCapacity = QueueCapacity;      //队列容量，初始化时给定
    m_pQueue = new int[m_iQueueCapacity];  //申请空间
    m_iHead = 0;                           //队列头的位置
    m_iTail = 0;                           //队列尾的位置
    m_iQueueLen = 0;                       //队列初始长度
}

Queue::~Queue()
{
    delete []m_pQueue;                     //
    m_pQueue = NULL;                       //释放空间
}

void Queue::ClearQueue()        //清空队列只需将头尾、长度置为0
{
    m_iHead = 0;                           
    m_iTail = 0;
    m_iQueueLen = 0;
}

bool Queue::QueueEmpty() const   //判断队列是否为空：队列长度等于0即为空
{
    if(m_iQueueLen == 0)
        return true;
    else
        return false;
}

/判断队列是否为满：队列长度等于队列申请的空间 即为满
bool Queue::QueueFull() const  /
{
    if(m_iQueueLen == m_iQueueCapacity)
        return true;
    else
        return false;
}

int Queue::QueueLength() const            //求队列的长度 
{
    return m_iQueueLen;
}

bool Queue::EnQueue(int element)      //元素入队：先判断队列是否未满
{
    if(QueueFull())
        return false;
    else
    {
        m_pQueue[m_iTail] = element;            //将入队元素的值赋给队尾
        m_iTail++;                              //队尾后移 1
        m_iTail = m_iTail % m_iQueueCapacity;   //队尾的下标变成 m_iTail % m_iQueueCapacity
        m_iQueueLen++;                          //队列长度加 1
        return true;
    }
}

bool Queue::DeQueue(int &element)     //元素出队：先判断队列是否为空
{
    if(QueueEmpty())
        return false;
    else
    {
        element = m_pQueue[m_iHead];  //将要出队的队列头的值赋给给定的变量
        m_iHead++;                     //队列头后移 1
        m_iHead = m_iHead % m_iQueueCapacity;   //头的下标更新为 m_iHead % m_iQueueCapacity
        m_iQueueLen--;                  //队列长度减 1
        return true;
    }
}

void Queue::QueueTraverse()   //遍历对列打印出各元素的值
{
    //i 从头开始访问，直到访问完所有元素，长度为m_iQueueLen + m_iHead
    for(int i = m_iHead; i < m_iQueueLen + m_iHead; i++)   
        cout<< m_pQueue[i % m_iQueueCapacity] << endl;
}
```



#### deque原理 [参考](https://stackoverflow.com/questions/6292332/what-really-is-a-deque-in-stl)
* deque的数据存放在多块固定大小的chunks或者vector中，然后这些连续存储空间被存放在map中的指针所指向。
* 这里的map不是stl的map容器，而只是一块存放指针的连续存储空间。
* deque内部使用迭代器维护deque。每个iterator有四个成员指针(cur,first,last,node)，其中start iterator的node指针指向deque的map的第一个非空指针，finish iterator的node指针指向deque的map的最后一个非空指针。
* deque的最大任务，便是在这些分段的定量连续空间上，维护其整体连续的假象，并提供随机存取的接口。避开了“重新配置、复制、释放”的轮回，代价则是复杂的迭代器架构。

#### 平衡二叉树[ref1](https://www.tutorialspoint.com/data_structures_algorithms/avl_tree_algorithm.htm)[ref2](https://www.geeksforgeeks.org/avl-tree-set-1-insertion/)
平衡二叉搜索树即AVL树，具有以下性质：
1. 它是一棵空树或它的左右两个子树的高度差的绝对值不超过1，并且左右两个子树都是一棵平衡二叉树。
2. 节点个数为n的AVL树，高度始终保持在O(logn)，查询效率也为O(logn)。
3. 高度为h的AVL树，节点数N最多为2h-1。

平衡二叉树的选择调整分为四种：
1. Left rotation
2. Right rotation
3. Left-Right rotation
4. Right-Left rotation



```cpp
// C program to insert a node in AVL tree 
#include<stdio.h> 
#include<stdlib.h> 
  
// An AVL tree node 
struct Node 
{ 
    int key; 
    struct Node *left; 
    struct Node *right; 
    int height; 
}; 
  
// A utility function to get maximum of two integers 
int max(int a, int b); 
  
// A utility function to get the height of the tree 
int height(struct Node *N) 
{ 
    if (N == NULL) 
        return 0; 
    return N->height; 
} 
  
// A utility function to get maximum of two integers 
int max(int a, int b) 
{ 
    return (a > b)? a : b; 
} 
  
/* Helper function that allocates a new node with the given key and 
    NULL left and right pointers. */
struct Node* newNode(int key) 
{ 
    struct Node* node = (struct Node*) 
                        malloc(sizeof(struct Node)); 
    node->key   = key; 
    node->left   = NULL; 
    node->right  = NULL; 
    node->height = 1;  // new node is initially added at leaf 
    return(node); 
} 
  
// A utility function to right rotate subtree rooted with y 
// See the diagram given above. 
struct Node *rightRotate(struct Node *y) 
{ 
    struct Node *x = y->left; 
    struct Node *T2 = x->right; 
  
    // Perform rotation 
    x->right = y; 
    y->left = T2; 
  
    // Update heights 
    y->height = max(height(y->left), height(y->right))+1; 
    x->height = max(height(x->left), height(x->right))+1; 
  
    // Return new root 
    return x; 
} 
  
// A utility function to left rotate subtree rooted with x 
// See the diagram given above. 
struct Node *leftRotate(struct Node *x) 
{ 
    struct Node *y = x->right; 
    struct Node *T2 = y->left; 
  
    // Perform rotation 
    y->left = x; 
    x->right = T2; 
  
    //  Update heights 
    x->height = max(height(x->left), height(x->right))+1; 
    y->height = max(height(y->left), height(y->right))+1; 
  
    // Return new root 
    return y; 
} 
  
// Get Balance factor of node N 
int getBalance(struct Node *N) 
{ 
    if (N == NULL) 
        return 0; 
    return height(N->left) - height(N->right); 
} 
  
// Recursive function to insert a key in the subtree rooted 
// with node and returns the new root of the subtree. 
struct Node* insert(struct Node* node, int key) 
{ 
    /* 1.  Perform the normal BST insertion */
    if (node == NULL) 
        return(newNode(key)); 
  
    if (key < node->key) 
        node->left  = insert(node->left, key); 
    else if (key > node->key) 
        node->right = insert(node->right, key); 
    else // Equal keys are not allowed in BST 
        return node; 
  
    /* 2. Update height of this ancestor node */
    node->height = 1 + max(height(node->left), 
                           height(node->right)); 
  
    /* 3. Get the balance factor of this ancestor 
          node to check whether this node became 
          unbalanced */
    int balance = getBalance(node); 
  
    // If this node becomes unbalanced, then 
    // there are 4 cases 
  
    // Left Left Case 
    if (balance > 1 && key < node->left->key) 
        return rightRotate(node); 
  
    // Right Right Case 
    if (balance < -1 && key > node->right->key) 
        return leftRotate(node); 
  
    // Left Right Case 
    if (balance > 1 && key > node->left->key) 
    { 
        node->left =  leftRotate(node->left); 
        return rightRotate(node); 
    } 
  
    // Right Left Case 
    if (balance < -1 && key < node->right->key) 
    { 
        node->right = rightRotate(node->right); 
        return leftRotate(node); 
    } 
  
    /* return the (unchanged) node pointer */
    return node; 
} 
  
// A utility function to print preorder traversal 
// of the tree. 
// The function also prints height of every node 
void preOrder(struct Node *root) 
{ 
    if(root != NULL) 
    { 
        printf("%d ", root->key); 
        preOrder(root->left); 
        preOrder(root->right); 
    } 
} 
  
/* Drier program to test above function*/
int main() 
{ 
  struct Node *root = NULL; 
  
  /* Constructing tree given in the above figure */
  root = insert(root, 10); 
  root = insert(root, 20); 
  root = insert(root, 30); 
  root = insert(root, 40); 
  root = insert(root, 50); 
  root = insert(root, 25); 
  
  /* The constructed AVL Tree would be 
            30 
           /  \ 
         20   40 
        /  \     \ 
       10  25    50 
  */
  
  printf("Preorder traversal of the constructed AVL"
         " tree is \n"); 
  preOrder(root); 
  
  return 0; 
} 
```

#### 红黑树 [ref](https://www.geeksforgeeks.org/red-black-tree-set-1-introduction-2/)

红黑树是一棵满足下述性质的二叉查找树：
1. 每一个结点要么是红色，要么是黑色。
2. 根结点是黑色的。
3. 所有叶子结点都是黑色的（实际上都是Null指针，下图用NIL表示）。叶子结点不包含任何关键字信息，所有查询关键字都在非终结点上。
4. 每个红色结点的两个子节点必须是黑色的。换句话说：从每个叶子到根的所有路径上不能有两个连续的红色结点
5. 从任一结点到其每个叶子的所有路径都包含相同数目的黑色结点



