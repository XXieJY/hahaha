###1.排序算法
* O(nlogn)：快排不稳定、堆排不稳定、归并稳定；  
* O(n^2)：冒泡稳定，插入稳定、选择不稳定；  
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
void merge(int a[], int first, int mid, int last, int temp[]){
    int leftIndex = first, rightIndex = mid+1, k = 0;
    while(leftIndex<=mid&&rightIndex<=last){
        if(a[leftIndex]<=a[rightIndex])
            temp[k] = a[leftIndex];
        else
            temp[k] = a[rightIndex];
        ++k;
    }
    while(leftIndex<=mid)
        temp[k++]=a[leftIndex++];
    while(rightIndex<=last)
        temp[k++]=a[rightIndex++];

    for(int i=0;i<k;++i)
        a[first++] = temp[i];
}

void mergesort(int a[], int first, int last, int temp[]){
    if(first<last){
        int mid = (first + last) / 2;
        mergesort(a[], first, mid, temp[]);
        mergesort(a[], mid+1, last, temp[]);
        merge(a, first, last, temp);
    }
}
```


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

void swap(int &a, int &b){
    int temp = a;
    a = b;
    b = temp;
}

int partition(vector<int> &v, int first, int last){
    
    int pivotValue = v[last], guard = first - 1;
    for(int cur=first; cur<last; ++cur){
        if(v[cur]<pivotValue){
            ++guard;
            swap(v[cur], v[guard]);
        }
        else{/*do nothing*/}
    }
    ++guard;
    swap(v[cur], v[guard]);
    return guard;
}

void quickSort(vector<int> &v, int first, int last){
    if(first<last){
        int pivotIndex = partition(v, first, last);
        quick(v, first, pivotIndex-1);
        quick(v, pivotIndex+1, last);
    }
    else
        return;
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
