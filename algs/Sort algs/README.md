* 稳定排序算法：插入排序、冒泡排序、归并排序；  
* 不稳定排序算法：快速排序、堆排序、选择排序；  

* 平均O(nlogn)排序算法：快速排序、堆排序、归并排序；  
* 平均O(n^2)排序算法：插入排序、选择排序、冒泡排序；  

* 快排：pivot选择最小元素或者最大元素是表现最差O(n^2)
* 冒泡：如果数据元素本来就是逆序的那么此时冒泡表现最差O(n^2)
* 堆排序、归并排序：任何情况下都是O(nlogn)


```cpp
void insertion_sort(int arr[])
{   int len = sizeof(arr)/sizeof(arr[0]);
    for(int cur=1; cur<len; ++cur){
        int value = arr[cur];
        int index = cur-1;
        while((index>=0)&&(value<arr[index])){
            arr[index+1]=arr[index];
            --index;
        }
        arr[index+1]=value;
    }
}
```
归并排序
```cpp

//
//  midNumberHeap.cpp
//  Main
//
//  Created by pg on 2017/9/9.
//  Copyright © 2017年 jingyu. All rights reserved.
//
#include <vector>
#include <cmath>
#include <iostream>
#include <algorithm>
using namespace std;

//将有二个有序数列a[first...mid]和a[mid...last]合并。
void merge(int a[], int first, int mid, int last, int temp[])
{
	int i = first, j = mid + 1, k = 0;
	while (i <= mid && j <= last)
	{
		if (a[i] <= a[j])
			temp[k++] = a[i++];
		else
			temp[k++] = a[j++];
	}
	while (i <= mid)
		temp[k++] = a[i++];
	while (j <= last)
		temp[k++] = a[j++];
	for (i = 0; i < k; i++)
		a[first + i] = temp[i];
}
//递归地完成归并排序
void mergeSort(int a[], int first, int last, int temp[])
{
	if (first < last)
	{
		int mid = (first + last) / 2;
		mergeSort(a, first, mid, temp);    //左边有序
		mergeSort(a, mid + 1, last, temp); //右边有序
		merge(a, first, mid, last, temp); //再将二个有序数列合并
	}  
}

/*测试，对给定数组做堆排序*/
int main(int argc, char* argv[])
{
	int A[] = {19, 1, 10, 14, 16, 4, 7, 9, 3, 2, 8, 5, 11};
	return 0;
}
```

---------

```cpp
//
//  quickSort.cpp -快速排序代码
//  快速排序的定义：
//  1. 进行每一趟排序时， 从数据中选出一个pivot，然后将大于等于或小于等于pivot的数值分别调整到pivot的左右两侧
//  2. 然后再分别对pivot左右两部分数据再进行快速排序。 重复上述操作，直到待排序数据长度等于1.
//  快速排序的特点：
//  1. 时间复杂度O(nlogn) 空间复杂度O(1) 是不稳定排序算法
//  2. 快速排序通常需要实现一个 quick函数（用来调用快速排序算法，分割排序后数据以及重复调用自身）
//  和一个 partition函数（实现快速排序算法。每次调用它，都先确定一个pivot，然后将大于等于或小于等于pivot的数据分别放在pivot两侧）
//  3. 快速排序有Lomuto 和 Hoare两种常见的实现方式。
//  Lomuto快速排序:
//  选择数据中的首个元素 或者 最后一个元素作为pivot。
//  将大于或者小于pivot的数据 放到pivot前面 （这里看是升序还是降序）
//  然后将当前pivot放到它的最终位置上。
//  输出pivot的位置给quick函数，quick函数根据pivot的位置，调用两次quick函数，将pivot前后的待排序数据进行排序
//  重复上述排序操作 直到待排序序列大小等于1
//  Hoare快速排序：
//  选择数据中的中间元素 作为pivot
//  对整个数据设定头指针和尾指针，使用头尾指针相向遍历整组数据。
//  在遍历过程中，将(head=大于等于pivot, tail=小于等于pivot) 或者 (head=小于等于pivot, tail=大于等于pivot)的逆序对交换位置，
//  此番操作在head和tail相遇或者错开时结束。 不需要再调整pivot的位置。
//  quick3way quicksort: The fastest quick sort code.

#include <vector>
#include <cmath>
#include <iostream>
#include <algorithm>
using namespace std;

int lpartition(vector<int> &v, int l, int h);
int hpartition(vector<int> &v, int l, int h);
void swap(int &f, int &b);

//Lomuto quick sort
void lquick(vector<int> &v, int l, int h)
{
	// h is the sequence number of v, not the size of v
	// execute quick sort entil the size of v is 1
	if (l < h)
	{
		int p = lpartition(v, l, h);
		//The Lomuto quick sort can specify the final position of one pivot in one partition
		lquick(v, l, p - 1);
		lquick(v, p + 1, h);
	}
}

int lpartition(vector<int> &v, int l, int h)
{
	// i指定了当前pivot在排序后最终位置的前一个元素
	int pivot = v[h], i = l - 1;
	for (int j = l; j < h; j++)
	{
		if (v[j] < pivot)
		{
			swap(v[++i], v[j]);
		}
		else
		{
			//do nothing
		}
	}
	swap(v[++i], v[h]);
	return i;
}

//Hoare quick sort
void hquick(vector<int> &v, int l, int h)
{
	if (l < h)
	{
		int p = hpartition(v, l, h);
		// hoare partition在每轮quick sort中并不能确定一个pivot的最终位置
		hquick(v, l, p);
		hquick(v, p + 1, h);
	}
}

int hpartition(vector<int> &v, int l, int h)
{
	int i = l, j = h, pivot = v[l + (h - l) / 2]; // 取中间一个数还可以是v[(h+l)/2]
	while (i < j)   //Hoare快排 在头尾指针相遇或者错过时结束
	{
		while (v[i] < pivot)
		{
			++i;
		}
		while (v[j] > pivot)
		{
			--j;
		}
		if (i < j) {
			swap(v[i++], v[j--]);
		}
	}
	return i;
}



void quick3way(vector<int> &v, int l, int h)
{
	if (l >= h) return;
	int la = lo, i = lo + 1, hb = h;
	int pivot = v[lo];
	while (i <= hb)
	{
		int cmp = v[i] <= pivot ? -1 : 1;
		if (v[i] == pivot) cmp = 0;
		if (cmp < 0) swap(v[la++], v[i++]);
		else if (cmp > 0) swap(v[i], v[hb--]);
		else i++;
	}
	quick3way(v, l, la - 1);
	quick3way(v, hb + 1， h);
}

void swap(int &f, int &b)
{
	int tmp = f;
	f = b;
	b = tmp;
}


/*测试，对给定数组做堆排序*/
int main(int argc, char* argv[])
{
	int A[] = {19, 1, 10, 14, 16, 4, 7, 9, 3, 2, 8, 5, 11};
	vector<int> a(A, A+(sizeof(A)/sizeof(A[0])));
	hquick(a, 0, 12);
	for (vector<int>::iterator b = a.begin(), e = a.end(); b != e; ++b)
	{
		cout << *b << " ";
	}
	return 0;
}
```
---------

```cpp
//对函数进行重载，传入数组指针和数组大小，同时进行第二次改进
/*第二次改进：传统冒泡排序中每一趟排序操作只能找到一个最大值或最小值*/
/*我们考虑利用在每趟排序中进行正向和反向两遍冒泡的方法一次可以得到两个最终值(最大者和最小者)*/
/*从而使排序趟数几乎减少了一半*/
void Bubble_sort(int a[],int size)
{
	int low = 0;
	int high = size-1;
	while(high > low)
	{
		for (int i = low; i != high; ++i)//正向冒泡，确定最大值
		{
			if (a[i] > a[i+1])
			{
				int temp = a[i];
				a[i] = a[i+1];
				a[i+1] = temp;
			}
		}
		--high;

		for (int j = high; j != low; --j)//反向冒泡，确定最小值
		{
			if (a[j] < a[j-1])
			{
				int temp = a[j];
				a[j] = a[j-1];
				a[j-1] = temp;
			}
		}
		++low;
	}
}
```

-------------------

//
//  heap.cpp -最大最小堆的生成、堆排序。
//  二叉堆的定义:
//    1. 二叉堆是完全二叉树或者是近似完全二叉树。
//    2. 父结点的键值总是大于或等于（小于或等于）任何一个子节点的键值。
//    3. 每个结点的左子树和右子树都是一个二叉堆（都是最大堆或最小堆）。
//  二叉堆满足二个特性(假设以0为堆起点)
//    1. i结点的父结点下标为 (int)floor((i – 1) / 2)
//    2. i结点的左右子节点下标为 i * 2 + 1， i * 2 + 2
//  堆的复杂度：
//    1. 空间复杂度 O(n)
//    2. 时间复杂度 O(nlogn) 是基于比较的排序算法复杂度下界
//

```cpp
#include <cstdio>
#include <cstdlib>
#include <cmath>
using namespace std;

int parent(int);
int left(int);
int right(int);
void HeapAdjust(int [], int, int);
void BuildHeap(int [], int);
void print(int [], int);
void HeapSort(int [], int);

/*返回父节点*/
int parent(int i)
{
	return (int)floor((i - 1) / 2);
}

/*返回左孩子节点*/
int left(int i)
{
	return (2 * i + 1);
}

/*返回右孩子节点*/
int right(int i)
{
	return (2 * i + 2);
}

/*对以某一节点为根的子树做堆调整(保证最大堆性质)*/
void HeapAdjust(int A[], int i, int heap_size)
{
	int l = left(i);
	int r = right(i);
	int largest;
	int temp;
	if(l < heap_size && A[l] > A[i])
	{
		largest = l;
	}
	else
	{
		largest = i;
	}
	if(r < heap_size && A[r] > A[largest])
	{
		largest = r;
	}
	if(largest != i)
	{
		temp = A[i];
		A[i] = A[largest];
		A[largest] = temp;
		HeapAdjust(A, largest, heap_size);
	}
}

/*建立最大堆*/
void BuildHeap(int A[], int heap_size)
{
	for(int i = heap_size / 2 - 1; i >= 0; i--)
	{
		HeapAdjust(A, i, heap_size);
	}
}

/*输出结果*/
void print(int A[], int heap_size)
{
	for(int i = 0; i < heap_size;i++)
	{
		printf("%d ", A[i]);
	}
	printf("\n");
}

/*堆排序*/
void HeapSort(int A[], int heap_size)
{
	BuildHeap(A, heap_size);
	int temp;
	for(int i = heap_size - 1; i >= 0; i--)
	{
		temp = A[0];
		A[0] = A[i];
		A[i] = temp;
		HeapAdjust(A, 0, i);
	}
	print(A, heap_size);
}


//  新加入i结点  其父结点为(i - 1) / 2
void HeapInsertionFixed(int a[], int i)
{
	int j, temp;

	temp = a[i];
	j = (i - 1) / 2;      //父结点
	while (j >= 0 && i != 0)
	{
		if (a[j] <= temp)
			break;

		a[i] = a[j];     //把较大的子结点往下移动,替换它的子结点
		i = j;
		j = (i - 1) / 2;
	}
	a[i] = temp;
}

/*测试，对给定数组做堆排序*/
int main(int argc, char* argv[])
{
	const int heap_size = 13;
	int A[] = {19, 1, 10, 14, 16, 4, 7, 9, 3, 2, 8, 5, 11};
	HeapSort(A, heap_size);
	system("pause");
	return 0;
}
```

---------------
