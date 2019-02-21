1. STL中可以使用priority_queue代替堆实现
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

2. 使用数组实现简单的堆数据结构

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



