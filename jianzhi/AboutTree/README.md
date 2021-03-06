### 相关考点：  
* 二叉树遍历问题：二叉树的前中后层序遍历的递归与非递归解法。
* 二叉树重建：使用递归、前中后序的知识（二叉树和数组重建、二叉树和链表重建）
* 树的匹配问题：使用递归，和特定匹配要求（相关题目：树的子结构、对称/镜像树、路径和值的匹配、树深度匹配）
* 二叉搜索树的问题： BST的前中后序、BST与双向链表转化
* 平衡二叉树问题：AVl的树判定、AVl树的性质；






---

#### 树的匹配问题*


1. Same Tree  
解题思路：  
判断两棵树是否相同和之前的判断两棵树是否对称都是一样的原理，利用深度优先搜索DFS来递归。代码如下：

```cpp
class Solution {
public:
    bool isSameTree(TreeNode *p, TreeNode *q) {
        //当且仅当树p和树q的所有节点都匹配完了，说明p,q是同一个树
        if (p == nullptr && q == nullptr)
            return true;
        //p,q不能完全匹配完整，或者当前p,q节点不匹配时返回false
        if ((p !== nullptr && q == nullptr)
            || (p == nullptr && q != nullptr)|| (p->val != q->val))
            return false;
        //继续层序地递归匹配
        return isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
    }
};
```

2.  树的子结构

输入两颗二叉树A，B，判断B是不是A的子结构。

解题思路：  
要查找树A中是否存在和树B结构一样的子树，可以分成两步递归：  

1. 第一步：  
**递归地在树A中找到和B的根节点的值一样的结点R； 这实际上就是树的遍历。**  
递归调用HasSubTree遍历二叉树A。如果发现某一结点的值和树B的头结点的值相同，则转向第2步判断两个结点为根的数是否存在父子关系

2. 第二步：  
**再递归地判断树A中以R为根结点的子树是不是包含和树B一样的结构：**  
这个过程其实就是要要判断两棵树对应的节点数据是否相同。这个是一个递归的过程:
    * 判断B树是否为空：
      * 如果当前传入的B树节点是空，则说明B树的某条到叶子节点的路径是在A树中的，
  此时应该在递归中返回true。
      * 如果当前传入的B树节点非空，但A树是空，则说明B树这一条路径不能在A树中cover住，
    所以此时应该在递归中返回false。

    * 如果A,B树当前传入结点都非空，那么就去判断这两个节点是否相等：
      * 如果不相等，则返回false。
      * 如果相等，则继续递归判断左右子节点。


```cpp
class Solution {
public:
    bool HasSubtree(TreeNode* A, TreeNode* B)
    {
        //包含特殊情况B树为空树，返回false
        //若A节点都不能作为B的根节点，也返回false
        if(A == NULL || B == NULL)
            return false;

        //先递归地从A中匹配到B树的根节点
        bool result;
        result = false;
        if(A->val == B->val)
        {
            if(!DoesAHaveB(A,B))
                return HasSubtree(A->left,B) || HasSubtree(A->right,B);
            else
                return true;
        }
        else
            return HasSubtree(A->left,B) || HasSubtree(A->right,B);

    }

    bool DoesAHaveB(TreeNode *A, TreeNode *B)
    {
        //如果B的节点全部匹配完了，说明B是A的子树
        if(B == NULL)      
            return true;
        //如果B的节点没有匹配完毕但是A的可用匹配节点已经用完了，说明B不是A子树
        if(A == NULL)  
            return false;
        // 当前AB节点的值不相等，那么两个树必然不是父子关系
        if(A->val != B->val)
            return false;
        //如果AB节点都没有匹配完毕且当前AB节点值是匹配的则继续层序递归地匹配下去
        else      
            return DoesAHaveB(A->left, B->left)
                && DoesAHaveB(A->right, B->right);
    }
};
```

3. 对称的二叉树 101. Symmetric Tree  
**题目描述**：  
请实现一个函数，用来判断一颗二叉树是不是对称的。
注意，如果一个二叉树同此二叉树的镜像是同样的，定义其为对称的


题目分析：  
判断二叉树是否对称和二叉树镜像是一类题目。
  * 制造二叉树镜像时就是层序遍历然后交换左右子树；
  * 所以判断二叉树镜像时可以层序遍历然后判断当前结点的左右子结点是否相等。

```cpp
class Solution
{
public:
    bool isSymmetrical(TreeNode* pRoot)
    {
        if(pRoot == NULL)
            return true;  
        return isSymmetricalRecursion(pRoot->left, pRoot->right);
    }

    bool isSymmetricalRecursion(TreeNode *pLeft, TreeNode *pRight)
    {
        //层序遍历：先判断左右子节点是否相等。
        if(pLeft->val != pRight->val)
            return false;
        //左右子树节点均匹配完毕，返回true
        if(pLeft == NULL && pRight == NULL)
            return true;
        //此时说明pLeft和pRight不同时为空但是有一个节点是空
        //说明左右子树节点数目不对称，一边匹配完了另一边仍剩余节点
        if(pLeft == NULL || pRight == NULL)
            return false;
        //左子树的左与右子树的右对称,左子树的右与右子树的左对称
        return isSymmetricalRecursion(pLeft->left, pRight->right)
            && isSymmetricalRecursion(pLeft->right, pRight->left);
    }
};
```


4.  二叉树的镜像  
题目描述

操作给定的二叉树，将其变换为源二叉树的镜像。

解题思路：  
1. 递归解法制造镜像二叉树最简单： 按照先序遍历访问每个节点，然后交换当前节点的左右指针
即可。

```cpp
class Solution
{
public:
    void Mirror(TreeNode *pRoot)
    {

        if(pRoot == NULL)
        {
            return;
        }

        swap(pRoot->left, pRoot->right);
        Mirror(pRoot->left);
        Mirror(pRoot->right);
    }

};
```



5.  二叉树中和为某一值的路径  

解题思路：
用先序遍历，递归来实现。

* 每次访问一个节点，那么就将当前权值求和
* 如果当前权值和与期待的和一致，那么说明我们找到了一个路径，保存或者输出
* 否则的话就递归其左右孩子节点 这里需要注意一个问题，就是递归退出的时候。  
**权值和的信息是保存在递归栈中的会恢复，但是我们保存的路径是无法恢复的，那么我们就需要在递归返回时将数据弹出**

**针对递归问题，传参数优于使用static共享变量，因为共享变量会导致多线程问题以及资源竞争**
```cpp
class Solution
{
public:
    vector< vector<int> > m_res;
    vector< vector<int> > FindPath(TreeNode* root, int expectNumber)
    {
        if(root == NULL)
            return m_res;

        vector<int> path;
        FindPath(root, expectNumber, path, 0);

        return m_res;
    }

    //注意这里的递归是传值而非传引用。
    //而且因为传值的特性也起到了回溯路径records的功能
    void FindPath(TreeNode* root, int expectNumber,
        vector<int> path, int currentSum)
    {
        currentSum += root->val;
        path.push_back(root->val);

        //如果当前节点是叶子节点且currentSum等于expectedNumber
        //则说明找到一条合法路径
        if(root->left == NULL && root->right == NULL
            && currentSum == expectNumber)
            m_res.push_back(path);
        //如果左子节点非空，则继续往下找
        if(root->left != NULL)
            FindPath(root->left, expectNumber, path, currentSum);
        //如果右子节点非空则继续往下找
        if(root->right != NULL)
            FindPath(root->right, expectNumber, path, currentSum);

    }

};
```

#### 039 二叉树的深度（Bottom-Up和Top-Down必备题目）

**题目描述**  
输入一棵二叉树，求该树的深度。从根结点到叶结点依次经过的结点（含根、叶结点）形成树的一条路径，最长路径的长度为树的深度。

解题思路：  
本题是一道比较简单地题目，主要考察树的深度遍历方法。然后值得注意的就是，递归两种主要的解题&参数传递的思路，一种是自顶向下的，另一种是自底向上的。  
相关链接： [树的遍历](http://blog.csdn.net/gatieme/article/details/51163010)

* 自顶向下传递参数的递归思路：  
**因此top-down是将算法信息放置在递归接口参数中传递下去**
```cpp
public:
int depth = 0;
int TreeDepthRecursion(TreeNode *root, int depth)
    {
        if(root == NULL)
        {
            return depth;
        }
        else
        {
            //将当前节点的深度depth+1以top-down地方向传递到下一层
            //因此top-down是将算法信息放置在递归接口参数中传递下去
            int leftDepth = TreeDepthRecursion(root->left, depth + 1);
            int rightDepth = TreeDepthRecursion(root->right, depth + 1);
            return max(leftDepth, rightDepth);
        }
    }
```

* 自底向上返回参数的递归思路：  
**Bottom up是将算法信息return的方式返回到上一层调用该接口的代码段对象中去。**
```cpp
int TreeDepthRecursion(TreeNode *root)
    {
        if(root == NULL)
        {
            return 0;
        }
        else
        {
            int leftDepth = TreeDepthRecursion(root->left);
            int rightDepth = TreeDepthRecursion(root->right);
            //bottom up代码写在递归调用的最后面
            return max(leftDepth, rightDepth) + 1;
        }
    }
```

#### 058 二叉树的下一个结点
**题目描述**  
给定一个二叉树和其中的一个结点，请找出中序遍历顺序的下一个结点

**解题思路**：  
中序遍历时，当前结点与下一个被遍历到的结点间的关系是：
* 1.有无右子树：
    * 如果当前结点有右子树:  那么其中序遍历的下一个结点就是其右子树的最左结点；
    * 如果当前结点没有右子树&它是其父结点的左子结点:那么其中序遍历的下一个结点就是他的父亲结点；
    * 如果当前结点没有右子树&它是其父结点的右子结点:这种情况下其下一个结点应该是当前结点所在的左子树的根节点, 因此我们可以顺着其父节点一直向上遍历, 直到找到一个是它父结点的左子结点的结点。


  ```cpp
  class Solution {
  public:
      TreeLinkNode* GetNext(TreeLinkNode* pNode)
      {
          if(pNode == NULL)
              return NULL;

          TreeLinkNode *pNext = NULL;
          //  如果当前结点有右子树, 那么其中序遍历的下一个结点就是其右子树的最左结点
          if(pNode->right != NULL)
          {
              //  找到右子树的最左孩子
              pNext = pNode->right;
              while(pNext->left != NULL)
                  pNext = pNext->left;
              return pNext;
          }
          else if(pNode->right == NULL && pNode->next != NULL)
          {
              TreeLinkNode *pCurrent = pNode;
              TreeLinkNode *pParent = pNode->next;

              //如果pCurrent就直接是pParent的左子节点，则跳过while直接将pParent返回
              //如果pCurrent是pParent的右子节点，则向上查找pParent节点直至pCurrent==pParent->left返回pParent或者pParent为NULL则返回NULL
              while(pParent != NULL && pCurrent == pParent->right)
              {
                  pCurrent = pParent;
                  pParent = pParent->next;
              }
              reutnr pParent;
          }

          return pNext;
      }
  };
  ```

---
**
### 二叉搜索树问题

#### 99. Recover Binary Search Tree
解题思路：  
* 遍历二叉搜索树到一维数组中。然后对数组排序以后再放回BST中。
* 这种最一般的解法可针对任意个数目的节点错乱的情况，这里先贴上此种解法：  

```cpp
class Solution {
public:
    void recoverTree(TreeNode *root) {
        vector<TreeNode*> list;
        vector<int> vals;
        inorder(root, list, vals);
        sort(vals.begin(), vals.end());
        for (int i = 0; i < list.size(); ++i) {
            list[i]->val = vals[i];
        }
    }
    void inorder(TreeNode *root, vector<TreeNode*> &list, vector<int> &vals) {
        if (!root) return;
        inorder(root->left, list, vals);
        //将BST节点值按中序遍历顺序存在list
        //将BST节点按中序遍历顺序存在另一个list
        list.push_back(root);
        vals.push_back(root->val);
        inorder(root->right, list, vals);
    }
};
```




#### 024 二叉搜索树的后序遍历序列
题目描述

输入一个整数数组，判断该数组是不是某二叉搜索树的后序遍历的结果。如果是则输出Yes,否则输出No。假设输入的数组的任意两个数字都互不相同。

#####解题思路：
要判定一个序列是否是BST的后序遍历，则必须先熟悉BST的性质：  
  * 二叉排序树或者是一棵空树，或者是具有下列性质的二叉树：

    * 若左子树不空，则左子树上所有结点的值均小于它的根结点的值；

    * 若右子树不空，则右子树上所有结点的值均大于或等于它的根结点的值；

    * 左、右子树也分别为二叉排序树；

    * 没有键值相等的节点。

    * 对一棵二叉搜索树进行中序遍历（左根右）可得到一个关键字递增有序序列。

* 然而，BST的后序序列的合法序列是：  
    * 对于一个序列S，最后一个元素是x （也就是根）  


* 如果去掉最后一个元素的序列为T，那么T满足：

    * T可以分成两段，前一段（左子树）小于x，后一段（右子树）大于x，

    * 且这两段（子树）都是合法的后序序列。

    * 完美的递归定义  

比如二叉排序树的后序遍历是：
> 后序序列 2, 9, 5, 16, 17, 15, 19, 18, 12  

1. 当前树的根是12，12可以把后序序列分成两段：[2,9,5] 和 [16,17,15,19,18]
2. 然后左子树[2,9,5]被子树树根5分割成[2],[9]，右子树是[16,17]，[19,18]
3. 然后继续递归地套用这个关系就可以循环检验出是否是二叉搜索树的后序遍历了

```cpp
class Solution {
public:
	/*
	step1：最后一个为根节点；
	step2：从根节点的左边开始往前遍历，找到第一个比它大的节点作为右子树，记为right
	step3：从右子树的左边开始往前遍历，找到第一个比它小的节点作为左子树，记为left
	step4：判断( left, right )中的值是否都比根节点大，如果有比根节点小的则返回false
	step5: 判断( 0, left )中的值是否都比根节点小，如果有比根节点大的则返回false
	step6: 返回true

	时间复杂度：O(n), 空间复杂度: O(1)
	没有证明过，但是代码通过了，求反例，心里没底
	*/
	bool VerifySquenceOfBST(vector<int> sequence) {
		if (sequence.empty()) return true;
		int len = sequence.size();

		int left = -1, right = -1;
		for (int i = len - 2; i >= 0; --i)
		{
			if (right == -1 && sequence[i] > sequence[len - 1])
                right = i;
			if (left == -1 && sequence[i] < sequence[len - 1])
                left = i;
		}
        cout <<"left = " <<left <<", right = " <<right <<endl;
		for (int i = right - 1; i > left; --i)
        {
            if (sequence[i] < sequence[len - 1])
            {
                return false;
            }
        }
		for (int i = left - 1; i > 0; --i)
		{
			if (sequence[i] > sequence[len - 1])
            {

                return false;
            }

        }
		return true;
	}
};
```

#### 完全二叉树判定

1. 如果将叶子节点没有子节点的现象叫做空洞。
2. 会发现在广度优先遍历完全二叉树时，这些空洞是在广度优先的遍历的末尾，所以，但我们遍历到空洞的时候，整个二叉树就已经遍历完成了。
3. 而如果，是非完全二叉树，我们遍历到空洞的时候，就会发现，空洞后面还有没有遍历到的值。这样，只要根据是否遍历到空洞，整个树的遍历是否结束来判断是否是完全的二叉树。

```cpp
bool isCompleteTree2(Node* root)
	{
		if (root == NULL)
			return true;
		Node* tmp = NULL;
		queue&lt;Node*&gt; q;
		q.push(root);
		while (tmp = q.front())
		{
			q.push(tmp-&gt;_left);
			q.push(tmp-&gt;_right);
			q.pop();
		}
 
		while (!q.empty())
		{
			tmp = q.front();
			if (tmp != NULL)
				return false;
			q.pop();
		}
		return true;
	}
```

---

### 平衡二叉树问题

#### 039 平衡二叉树
题目描述

输入一棵二叉树，判断该二叉树是否是平衡二叉树。

解题思路：  
要判定是否是平衡二叉树需要知道平衡二叉树的定义：  
  * 平衡二叉树要求对于每一个节点来说，它的左右子树的高度之差不能超过1

递归解法：
  * 递归的判断二叉树的每一个节点，判断其左右子树的高度差：
    * 如果高度差小于1 则继续将其左右子树进行平衡二叉树的判断直到叶子节点返回true。
    * 如果高度差大于1则返回false，判断结束。

```cpp
class Solution
{
public:
    bool IsBalanced_Solution(TreeNode* root)
    {
        if(root == NULL)
        {
            return true;
        }

        int leftDepth = TreeDepth(root->left);
        int rightDepth = TreeDepth(root->right);

        if(fabs(leftDepth - rightDepth) <= 1)
        {
            return IsBalanced_Solution(root->left) && IsBalanced_Solution(root->right);
        }
        else
        {
            return false;
        }
    }

    int TreeDepth(TreeNode *root)
    {
        if(root == NULL)
        {
            return 0;
        }

        int leftDepth = TreeDepth(root->left);
        int rightDepth = TreeDepth(root->right);

        //  返回左右子树中深度最深的
        return max(leftDepth, rightDepth) + 1;
    }
};
```

---

#### 95. Unique Binary Search Trees （BST和卡特兰数）

卡特兰数递归过程：  
0 1 2 3 4  5    

5 = 0*4 + 1*3 + 2*2 + 3*1 + 4*0    

4 = 0*3 + 1*2 + 3*0    

```cpp
class Solution {
public:
    int numTrees(int n) {
        vector<int> dp(n + 1, 0);
        dp[0] = 1;
        dp[1] = 1;
        for (int i = 2; i <= n; ++i) {
            for (int j = 0; j < i; ++j) {
                dp[i] += dp[j] * dp[i - 1 - j];
            }
        }
        return dp[n];
    }
};
```





#### 513. Find Bottom Left Tree Value
Given a binary tree, find the leftmost value in the last row of the tree.

**解题思路**：  
1. 这题可以直接通过先序遍历+维护当前深度和最大深度来做。
* 因为本题要求二叉树的最左下树结点的值，那么首先应该想到使用先序遍历很快能访问到左下角节点。
* 然后维护一个最大深度和当前节点的深度，由于先序遍历遍历的顺序是根-左-右，所以每一行最左边的结点肯定最先遍历到，那么由于是新一行，那么当前深度肯定比之前的最大深度大，所以我们可以更新最大深度为当前深度，结点值res为当前结点值，这样在遍历到该行其他结点时就不会更新结果res了，参见代码如下：
* **此题只有使用共享参数的递归才比较好做,因此所有递归都会根据深度的判断去修改统一个res变量。**

```cpp
class Solution {
public:
    int findBottomLeftValue(TreeNode* root) {
        if (!root) return 0;
        //初始化树的深度为1，最左节点值为root->val
        int max_depth = 1, res = root->val;
        helper(root, 1, max_depth, res);
        return res;
    }
    //注意递归接口传树深度的引用和最左节点值的引用
    void helper(TreeNode* node, int depth, int& max_depth, int& res) {
        if (!node) return;
        //根据先序遍历的特性，每次深度增加是第一个被访问的节点
        //一定是当前层的最左子节点
        if (depth > max_depth) {
            max_depth = depth;
            res = node->val;
        }
        helper(node->left, depth + 1, max_depth, res);
        helper(node->right, depth + 1, max_depth, res);
    }
};
```
2. 使用层序遍历二叉树，也就是BFS的思路，每次遍历到新的一层时，将第一个树节点，也就是当前层的最左节点的值记录下来
直到层序遍历完毕，最后返回保存的值。
```cpp
class Solution {
public:
    int findBottomLeftValue(TreeNode* root) {
        if (!root) return 0;
        int res = 0;
        queue<TreeNode*> q;
        q.push(root);
        while (!q.empty()) {
            int n = q.size();
            for (int i = 0; i < n; ++i) {
                TreeNode *t = q.front(); q.pop();
                if (i == 0) res = t->val;
                if (t->left) q.push(t->left);
                if (t->right) q.push(t->right);
            }
        }
        return res;
    }
};
```

#### 515. Find Largest Value in Each Tree Row
You need to find the largest value in each row of a binary tree.

**解题思路**：  
这题按BFS思路遍历每层元素然后，每层中最大的保存到结果中。

```cpp
class Solution {
public:
    vector<int> largestValues(TreeNode* root) {
        //基本上，树的root节点在代码中都需要特殊对待，单独被判断。
        if (!root) return {};
        vector<int> res;
        queue<TreeNode*> q;
        q.push(root);
        while (!q.empty()) {
            int n = q.size(), mx = INT_MIN;
            for (int i = 0; i < n; ++i) {
                TreeNode *t = q.front(); q.pop();
                mx = max(mx, t->val);
                if (t->left) q.push(t->left);
                if (t->right) q.push(t->right);
            }
            res.push_back(mx);
        }
        return res;
    }
};
```

#### 199. Binary Tree Right Side View
Given a binary tree, imagine yourself standing on the right side of it, return the values of the nodes you can see ordered from top to bottom.

**解题思路**：  
* 这道题要求我们打印出二叉树每一行最右边的一个数字，实际上是求二叉树层序遍历的一种变形，我们只需要保存每一层最右边的数字即可。
* 这道题需要用到数据结构队列queue，遍历每层的节点时,先取出当前层的最后一个节点(也就是queue的最后一个节点)，然后把下一层的节点都存入到queue中。
* 每当开始新一层节点的遍历之前，先把新一层最后一个节点值存到结果中，代码如下：
```cpp
class Solution {
public:
    vector<int> rightSideView(TreeNode *root) {
        vector<int> res;
        if (!root) return res;
        queue<TreeNode*> q;
        q.push(root);
        while (!q.empty()) {
            res.push_back(q.back()->val);
            int size = q.size();
            for (int i = 0; i < size; ++i) {
                TreeNode *node = q.front();
                q.pop();
                if (node->left) q.push(node->left);
                if (node->right) q.push(node->right);
            }
        }
        return res;
    }
};
```

#### 111. Minimum Depth of Binary Tree

解题思路：  
二叉树的经典问题之最小深度问题就是就最短路径的节点个数，还是用深度优先搜索DFS来完成。

```cpp
class Solution {
public:
    int minDepth(TreeNode *root) {
        //判断根节点是否为空，如果为空直接返回0
        if (root == NULL) return 0;
        //判断当前节点是否是叶子节点，如果是则当前路径到尽头了，返回1让路径长度增加1；
        if (root->left == NULL && root->right == NULL) return 1;

        //当前节点有至少一个子节点时，当前节点就不是叶子节点
        //此时递归判断左右子节点之后的路径
        if (root->left == NULL) return minDepth(root->right) + 1;
        else if (root->right == NULL) return minDepth(root->left) + 1;
        else return 1 + min(minDepth(root->left), minDepth(root->right));
    }

};
```
如果要将先判定叶子结点改为后判定叶子结点来做minimun depth问题，应该这么写：
```cpp
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    int minDepth(TreeNode* root) {
        if (!root)
        {
            return 0;
        }
        int L, R;
        L = minDepth(root->left);
        R = minDepth(root->right);
        if((L==0&&R==0) || (L!=0&&R!=0))
        {
            return 1+min(L,R);
        }
        else if (L!=0)
        {

            return 1+L;
        }
        else
        {
            return 1+R;
        }
    }
};
```

#### 104. Maximum Depth of Binary Tree
最深路径可以不考虑判定参与比较的路径是否有效（即路径是否深入到叶子结点），但是最浅路径就必须
先判断是路径是否合法。否则直接用min判断会得到不合法的路径值。

```cpp
class Solution {
public:
    int maxDepth(TreeNode* root) {
        //定义辅助变量
        int L, R;

        //定义向下访问到叶子结点是为递归的出口
        if (!root)
        {
            return 0;
        }

        //递归调用
        L = maxDepth(root->left);
        R = maxDepth(root->right);
        return 1 + max(L, R);
    }
};
```
