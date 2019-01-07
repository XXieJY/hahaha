### 树的遍历时的top-down和bottom-up

* top down 宜在helper接口处传入值
* top down 宜用预先检测叶子节点方法if (!root->left && !root->right) ，但也注意别漏掉空节点判定if(!root)
* bottom up 宜在返回处返回更新值
* bottom up 宜直接判断到空节点if(!root)，而不要预先判断；
```cpp
//top-down
class Solution {
public:
        int maxDepth(TreeNode* root) {
                if (!root)
                {
                        return 0;
                }
                int result = INT_MIN;
                helper(root, 0, result);
                return result;
        }
        void helper(TreeNode* root, int H, int &result)
        {
                if (!root)
                {
                        return;
                }
                if (!root->left && !root->right)
                {
                        result = max(result, H + 1);
                        return;
                }
                helper(root->left, H + 1, result);
                helper(root->right, H + 1, result);
        }

};

//bottom-up
class Solution {
public:
    int maxDepth(TreeNode* root) {
        if (!root) return 0;
        return 1 + max(maxDepth(root->left), maxDepth(root->right));
    }
};
```

#### path sum 既需要top-down 又需要bottom-up的题目
```cpp
class Solution {
 public:
         bool hasPathSum(TreeNode* root, int sum)
         {
                 if (!root)
                 {
                         return false;
                 }
                 return helper(root, sum, 0);
         }
         bool helper(TreeNode* root, int T, int V)
         {
                 if (!root->left && !root->right)
                 {
                         if (V + root->val == T)
                         {
                                 return true;
                         }
                         return false;
                 }
                 bool b1 = false, b2 = false;
                 if (root->left)
                 {
                         b1 = helper(root->left, T, V + root->val);
                 }
                 if (root->right)
                 {
                         b2 = helper(root->right, T, V + root->val);
                 }
                 return b1 || b2;
         }
 };
```

####计算完全二叉树节点的个数
递归判断子树是否为满二叉树，如果是满二叉树则使用公式2^h - 1计算当前子树的节点个数。
```cpp
class Solution {
public:
    int countNodes(TreeNode* root) {
        int hLeft = 0, hRight = 0;
        TreeNode *pLeft = root, *pRight = root;
        while (pLeft) {
            ++hLeft;
            pLeft = pLeft->left;
        }
        while (pRight) {
            ++hRight;
            pRight = pRight->right;
        }
        if (hLeft == hRight) return pow(2, hLeft) - 1;
        return countNodes(root->left) + countNodes(root->right) + 1;
    }
};
```

#### 二叉搜索树的重建
有序数组的中间元素必定是二叉搜索树的中间节点。
```cpp
class Solution {
public:
    TreeNode *sortedArrayToBST(vector<int> &num) {
        return sortedArrayToBST(num, 0 , num.size() - 1);
    }
    TreeNode *sortedArrayToBST(vector<int> &num, int left, int right) {
        if (left > right) return NULL;
        int mid = (left + right) / 2;
        TreeNode *cur = new TreeNode(num[mid]);
        cur->left = sortedArrayToBST(num, left, mid - 1);
        cur->right = sortedArrayToBST(num, mid + 1, right);
        return cur;
    }
};
```
