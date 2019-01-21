### 1.排序算法
* O(nlogn)：快排不稳定、堆排不稳定、归并稳定；  
* O(n^2)：冒泡稳定，插入稳定、选择不稳定；  
* 快排：pivot选择最小元素或者最大元素是表现最差O(n^2)
* 冒泡：如果数据元素本来就是逆序的那么此时冒泡表现最差O(n^2)
* 堆排序、归并排序：任何情况下都是O(nlogn)


#### 插入排序稳定n^2
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
#### 归并排序不稳定nlogn
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

#### 快速排序不稳定nlogn
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

#### 冒泡排序稳定n^2
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

#### 堆排序不稳定nlogn
```cpp
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

### 2.树的遍历(前/中/后/层序)、树的恢复(前+中/中+后恢复树)、树的分解(树转数组、树转链表)

* 树的前中后序非递归遍历使用栈辅助实现，树的层序非递归遍历使用队列辅助实现

#### 树的前序遍历

1. 递归法二叉树前序遍历

```cpp
vector<int> Preorder(TreeNode* root){
    
    vector<int> res;
    Recursion(root, res);
    
    return res;
}

void Recursion(TreeNode* root, vector<int> &res){
    
    if(root==NULL)
        return;
    
    //do current node operations here
    cout << root->value;
    res.push_back(root->value);
    
    Recursion(root->leftChild);
    Recursion(root->rightChild);
    
    //do bottom up operations here
}
```

2. 非递归法二叉树前序遍历  

使用栈辅助实现**非递归前序遍历**
1. 把根节点push到栈中
2. 循环下列步骤直至栈空
  * 取出栈顶元素并访问，然后将栈顶元素的左右子节点按照先右后左的顺序推入栈中

代码如下：

```cpp
vector<int> PreorderIteration(TreeNode* root){

    vector<int> ret;
    if(root==NULL)
        return ret;

    stack<TreeNode* > helper{{root}};
    while(!helper.empty()){
        TreeNode* cur = helper.top();
        helper.pop();
        ret.push_back(cur->value);

        if(cur->rightChild)
            helper.push(cur->rightChild);
        if(cur->leftChild)
            helper.push(cur->leftChild);
    }
    return ret;
}

```
#### 树的中序遍历

1. 中序遍历的递归解法：

```cpp
vector Inorder(TreeNode* root){
    
    vector<int> ret;
    Recursion(root, ret);
    return ret;
}

void Recursion(TreeNode* root, vector<int> &ret){
    
    if(root==NULL)
        return;
    
    if(root->leftChild)
        Inorder(root->leftChild, ret);
    
    //do current node operations here
    cout << root->value;
    ret.push_back(root->value);
    
    if(root->rightChild)
        Inorder(root->rightChild, ret);
    //do bottom up operations here
}
```

2. 中序遍历非递归解法：  
思路是从根节点开始循环执行以下操作直至节点访问完毕且辅助栈空
* 将当前节点及其所有左子结点压入栈，直至叶子节点的左子节点为空。
* 然后取出栈顶节点访问并保存节点值。
* 然后将当前节点切换为当前节点的右子节点，继续上述循环。

```cpp
vector<int> InorderIteration(TreeNode* root){
    
    vector<int> ret;
    if(root==NULL)
        return ret;
    
    stack<TreeNode*> helper;
    TreeNode* cur = root;
    while(cur!=NULL || !helper.empty()){
        while(cur!=NULL){
            helper.push(cur);
            cur = cur->leftChild;
        }
        
        //do current node operation here
        cur = helper.top();
        helper.pop();
        cout << cur->value;
        ret.push_back(cur->value);
        
        cur = cur->rightChild;
        //do bottom up operations here
    }
    return ret;
}
```


#### 树的后序遍历

1.后序遍历的递归解法：

```cpp
vector<int> PostOrder(TreeNode* root){
    
    vector<int> ret;
    Recursion(root, ret);
    return ret;
}

void Recursion(TreeNode* root, vector<int> ret){
    
    if(root==NULL)
        return;
    
    if(root->leftChild)
        Recursion(root->leftChild, ret);
    if(root->rightChild)
        Recursion(root->rightChild, ret);
    
    //do current operations here
    ret.push_back(root->value);
}
```

2 后序遍历非递归解法：  

由于后序遍历的顺序是左-右-根，而先序遍历的顺序是根-左-右，二者其实还是很相近的，我们可以先在先序遍历的方法上做些小改动，使其遍历顺序变为根-右-左，然后翻转一下，就是左-右-根啦，翻转的方法我们使用反向Q，哦不，是反向加入结果res，每次都在结果res的开头加入结点值，而改变先序遍历的顺序就只要该遍历一下入栈顺序，先左后右，这样出栈处理的时候就是先右后左啦，参见代码如下：


```cpp
vector<int> PostOrder(TreeNode* root){
    
    if(root==NULL)
        return {};
        
    vector<int> ret;
    stack<TreeNode* > helper{{root}};
    while(!helper.empty()){
        TreeNode* cur = helper.top();
        helper.pop();
	//将非递归先序遍历的结果反向插入ret中
        ret.insert(ret.begin(), cur->value);
        
        if(cur->leftChild)
            helper.push(cur->leftChild);
        if(cur->rightChild)
            helper.push(cur->rightChild);
    }
    return ret;
}
```

#### 二叉树层序遍历（队列辅助层序遍历）*
解题思路：  
* 层序遍历二叉树是典型的广度优先搜索BFS的应用，但是这里稍微复杂一点的是，我们要把各个层的数分开，存到一个二维向量里面。
* 大体思路还是基本相同的，建立一个queue，然后先把根节点放进去，这时候找根节点的左右两个子节点，这时候去掉根节点，此时queue里的元素就是下一层的所有节点。
* 用一个for循环遍历它们，然后存到一个一维向量里，遍历完之后再把这个一维向量存到二维向量里，以此类推，可以完成层序遍历。代码如下：

```cpp
vector<vector<int> > levelOder(TreeNode* root){
    
    if(root==NULL)
        return {{}};
    
    vector<vector<int> > ret;
    queue<TreeNode* > helper;
    helper.push(root);
    while(!helper.empty()){
        vecot<int> curLevel;
        int levelNodeCounts = helper.size();
        for(int index=0; index<levelNodeCounts; ++index){
            TreeNode* cur = helper.front();
            helper.pop();
            curLevel.puash_back(cur->value);
            if(cur->leftChild)
                helper.push(cur->leftChild);
            if(cur->rightChild)
                helper.push(cur->rightChild);
        }
        ret.push_back(curLevel);
    }
    return ret;
}
```



### 求二叉树维度属性问题（二叉树高度，二叉树宽度，二叉树子节点最近公共祖先节点，二叉树到叶子节点的路径）：

#### dfs求二叉树高度：   

求二叉树高度采用分治算法bottom-up的方法
* 叶子节点的左右空节点开始，将底层的数的高度bottom-up的带上来
* 然后再merger一下，比如在第i层的cur节点，将其得到的leftHeight和rightHeight取最大值
* 然后+1返回上一层

```cpp
int GetBinaryMaximumHeight(TreeNode* root){
    if(root==NULL)
        return 0;
    else
        return 1 + Math.max(GetBinaryMaximumHeight(root->leftChild),
            GetBinaryMaximumHeight(root->rightChild));
}
```

#### 求二叉树宽度
分治法bottom up地传递当前层的宽度
* 当前节点左右子节点有一个为空，则向上返回1
* 否则向上返回左右宽度和

```cpp
public  static int countOfLeaf(TreeNode root)
{
    if(root==null)
        return 0;
	
    if(root.left==null  || root.right==null)
        return 1;
    else
        return countOfLeaf(root.left)+countOfLeaf(root.right);
}
```

### 二叉树的LCA（最近公共祖先）问题：

#### 235 Lowest Common Ancestor of a Binary Search Tree

解题思路：  
* 二叉搜索树节点值的关系：左<根<右。因此有规律：
    * 如果根节点的值大于p和q之间的较大值，说明p和q都在左子树中，那么此时我们就进入根节点的左子节点继续递归
    * 如果根节点小于p和q之间的较小值，说明p和q都在右子树中，那么此时我们就进入根节点的右子节点继续递归
    * 如果根节点介于左右子节点之间，则说明找到最近公共祖先

```cpp
TreeNode* Bfs(TreeNode* root, TreeNode* p, TreeNode* q){
    
    if(root==NULL)
        return NULL;
    
    if((root->value)>max(p->val,q->val))
        return Bfs(root->leftChild, p, q);
    else if((root->value)<min(p->val,q->val))
        return Bfs(root->rightChild, p, q);
    else 
        return root;
}
```

#### 求二叉树从根节点到给定节点的路径

```cpp
bool DoesExistRoot2LeafPath(TreeNode* root, TreeNode* leaf, vector<int> &ret){
        
    if(root==NULL)
        return false;
    else{
        ret.push_back(root->value);
        if(root==leaf){
            for(int x:ret) cout<<x<<',';
            return true;
        }
        
        bool foo = false;
        if(!foo&&root->leftChild!=NULL)
            foo = DoesExistRoot2LeafPath(root->leftChild, leaf, ret);
        if(!foo&&root->rightChild!=NULL)
            foo = DoesExistRoot2LeafPath(root->rightChild, leaf, ret);
        
        //回溯当前节点
        if(!foo)
            ret.pop_back();
        
        return foo;
    }
}
```

#### 二叉树重建相关问题*：  

1. 用前序遍历和中序遍历还原二叉树

解题思路：  

* 由于先序的顺序的第一个肯定是根，所以原二叉树的根节点可以知道，题目中给了一个很关键的条件就是树中没有相同元素，有了这个条件我们就可以在中序遍历中也定位出根节点的位置，并以根节点的位置将中序遍历拆分为左右两个部分，分别对其递归调用原函数。代码如下：

```cpp
class Solution {
public:
    TreeNode *buildTree(vector<int> &preorder, vector<int> &inorder)
    {
        return buildTree(preorder, 0, preorder.size() - 1,
            inorder, 0, inorder.size() - 1);
    }

    TreeNode *buildTree(vector<int> &preorder, int pLeft, int pRight,
        vector<int> &inorder, int iLeft, int iRight)
    {
        if (pLeft > pRight || iLeft > iRight)
        {
            return NULL;
        }
        int i = 0;
        for (i = iLeft; i <= iRight; ++i)
        {
            if (preorder[pLeft] == inorder[i]) break;
        }
        TreeNode *cur = new TreeNode(preorder[pLeft]);
        //preoder的剩余元素被递归地划分为[pLeft+1,pLeft+(i-ileft)]
        //&[pleft+(i-iLeft)+1, pRight]。其中i-iLeft的值
        //即为当前根节点的左子树的节点个数
        //inoder的剩余元素被递归地划分为[iLeft, i-1]&[i+1,iRight]
        cur->left = buildTree(preorder, pLeft + 1,
            pLeft + (i - iLeft), inorder, iLeft, i - 1);
        cur->right = buildTree(preorder, pLeft + (i - iLeft + 1),
            pRight, inorder, i + 1, iRight);
        return cur;
    }
};
```

2. 用中序遍历和后序遍历还原二叉树*  

解题思路：  

* 我们知道中序的遍历顺序是左-根-右，后序的顺序是左-右-根，对于这种树的重建一般都是采用递归来做。
* 由于后序的顺序的最后一个肯定是根，所以原二叉树的根节点可以知道，题目中给了一个很关键的条件就是树中没有相同元素，有了这个条件我们就可以在中序遍历中也定位出根节点的位置，并以根节点的位置将中序遍历拆分为左右两个部分，分别对其递归调用原函数。代码如下：

```cpp
class Solution {
public:
    TreeNode *buildTree(vector<int> &inorder, vector<int> &postorder) {
        return buildTree(inorder, 0, inorder.size() - 1,
            postorder, 0, postorder.size() - 1);
    }

    TreeNode *buildTree(vector<int> &inorder, int iLeft, int iRight,
        vector<int> &postorder, int postLeft, int postRight)
    {
        if (iLeft > iRight || postLeft > postRight)
            return NULL;    
        int i = 0;
        for (i = iLeft; i < inorder.size(); ++i)
        {
            if (inorder[i] == cur->val) break;
        }
        //同理inorder剩余节点被递归划分为[iLeft, i-1]&[i+1, iRight]
        //postorder剩余节点被递归划分为[postLeft, postLeft+(i-iLeft)-1]
        //&[postLeft+(i-iLeft),postRight-1]
        TreeNode *cur = new TreeNode(postorder[postRight]);
        cur->left = buildTree(inorder, iLeft, i - 1,
            postorder, postLeft, postLeft + (i-iLeft) - 1);
        cur->right = buildTree(inorder, i + 1, iRight,
            postorder, postLeft + (i-iLeft), postRight - 1);
        return cur;
    }
};
```
