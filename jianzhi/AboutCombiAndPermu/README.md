index90%的排列，组合题目都用DFS解。


#### Combination题目

1. Combination Sum（理解递归和DFS的优秀题目）  
给定一个组无重复数值和一个目标值，找到所有组合Combinations，加起来等于目标值。
数组中的元素可以重复使用.

解题思路：  
**像这种结果要求返回所有符合要求解的题十有八九都是要利用到递归，而且解题的思路都大同小异。**
1. 都需要多写一个递归函数，这里我们新加入三个变量，start记录当前的递归到的下标，out为当前解，res保存所有已经得到的解。每次调用新的递归函数时，此时的target要减去当前数组的的数。
2. **递归函数注意：递归接口的定义、出口的定义、递归拆解方式的思考。**   

假设candidates=[1,7,4,15,9,6,3]此时dfs的搜索combinations的顺序会是:
1. 开始是[3], [3,3], [3,3,3]...直至sum > target时返回上一层递归。
2. 继续是[6],[6,3],[6,3,3]....直至sum > target时返回上一层递归。
3. 然后继续[6,6],[6,6,3],[6,6,3,3]...直至sum > target时返回上一层递归。  

具体看代码如下：

```cpp
class Solution {
public:
    //像DFS,BFS这类需要在递归栈中共享遍量的，可以把变量声明为全局Public的
    vector<vector<int>> ret;
    vector<int> tmp;

    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        dfs(0, 0, target, candidates);
        return ret;
    }
    //DFS接口定义参数index:=当前递归到的元素下标，sum:=当前元素combination的和，
    //target:=目标和，candidates:=给定的一组无重复元素
    void dfs(int index, int sum, int target, vector<int>& candidates) {
        //注意这里下标是[0,candidates.size()-1]，而candidate.size == 7
        //从出口条件可以分析递归是从底Index=candidates.size()-1;处bottom-up进行combination的;
        if(index == candidates.size()) {
            if(sum == target)
                ret.push_back(tmp);
            return;
        }
        else{
            //这里的dfs调用的作用是把当前的sum结果直接推到递归出口去检验
            //sum是否等于target
            dfs(index+1, sum, target, candidates);
            //这里的for循环和dfs调用直接负责combination sum的逻辑
            int c = candidates[index];
            for(; ;) {
                sum += c;
                tmp.push_back(c);
                if(sum > target) break;
                dfs(index+1, sum, target, candidates);
            }
            //负责回溯已经用过现在已经没用的元素
            while(tmp.size() && tmp[tmp.size() - 1] == c)
                tmp.pop_back();
        }
    }
};
```



#### 40. Combination Sum II
给定一个组无重复数值和一个目标值，找到所有组合Combinations，加起来等于目标值。  
数组中的元素不可以重复使用.  

递归解法：

```cpp
class Solution {
public:
    vector<vector<int>> ret;
    vector<int> tmp;


    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        //combinationsum2必须先排序如[1,1,2,5,6,7,10]
        sort(candidates.begin(), candidates.end());  
        dfs(0, 0, target, candidates);
        //combinationsum2的递归解还包含去重复步骤
        //但是这一步超级耗费时间
        set<vector<int>> ret_set(ret.begin(), ret.end());
        ret.assign(ret_set.begin(), ret_set.end());
        return ret;
    }

    void dfs(int index, int sum, int target, vector<int>& candidates){
        if(index == candidates.size()) {
            if(sum == target)
                ret.push_back(tmp);
            return;
        }
        else{
            dfs(index+1, sum, target, candidates);

            int c = candidates[index];
            sum += c;
            tmp.push_back(c);
            if(sum <= target)
                dfs(index+1, sum, target, candidates);
            tmp.pop_back();
            return;
        }
    }
};
```

topdown递归解法：

```cpp
vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
    vector<vector<int>> res;
    vector<int> current;
    sort(candidates.begin(),candidates.end());
    backTracking(candidates.begin(),current,res,candidates,target);
    return res;
}

void backTracking(vector<int>::iterator n, vector<int>& current,
    vector<vector<int>>& res, const vector<int>& candidates, int target){
    if(!target)
        res.push_back(current);
    else if(target>0){
        for(; n!=candidates.end() && (*n)<=target; ++n){
            current.push_back(*n);
            backTracking(n+1, current, res, candidates, target-*n);
            current.pop_back();
            while(n+1!=candidates.end() && *(n+1)==*n)
                ++n;
        }
    }
}
```


#### combinations
Given two integers n and k, return all possible combinations of k numbers out of 1 ... n.    
Example:  
Input: n = 4, k = 2  
Output:
[[2,4],[3,4],[2,3],[1,2],[1,3],[1,4],]


```cpp
class Solution {
public:
    vector<vector<int> >res;
    vector<int> temp;
    vector<vector<int> > combine(int n, int k) {
        if(n < k)
            return res;
        combine(0,0,n,k);
        return res;
    }

    void combine(int index, int tmpLen, int n, int k){
        if(tmpLen == k){
            res.push_back(temp);
            return;
        }
        for(int i = index; i < n; i++){
            temp.push_back(i + 1);
            combine(i + 1, tmpLen + 1, n, k);
            temp.pop_back();
            }
        }
};
```


#### 46. Permutations
Given a collection of distinct numbers, return all possible permutations.  
> For example,[1,2,3] have the following permutations:  
[  [1,2,3],  [1,3,2],  [2,1,3],  [2,3,1],  [3,1,2], [3,2,1] ]  

解题思路：
* 而此题使用DFS求全排列问题
* **排列问题需要用到一个visited数组来标记某个数字是否访问过。**
* **然后在DFS递归函数从的循环应从头开始**
其余思路大体相同，代码如下：

```cpp
class Solution {
public:
    vector<vector<int> > permute(vector<int> &candidates)
    {
        //声明DFS求排列需要用到的变量
        vector<vector<int> > res;
        vector<int> tmp;
        vector<int> visited(candidates.size(), 0);

        //进入DFS
        dfs(candidates, 0, visited, tmp, res);
        return res;
    }
    void dfs(vector<int> &candidates, int index, vector<int> &visited,
             vector<int> &tmp, vector<vector<int> > &res) {
        //index指示当前tmp数组的长度，当index == candidates.size()时说明
        //候选元素已经用完，tmp是一个完整的permutation答案，此时为递归出口
        if (index == candidates.size())
            res.push_back(tmp);
        else
        {
            //i代表选取candidates的元素的下标
            //i在tmp的每次递归中都是从0开始，这样permutation的规则
            for (int i = 0; i < candidates.size(); ++i)
            {
                //有序
                if (visited[i] != 0)
                    continue;
                //每次选取candidates的一个元素candidates[i]作为当前tmp的第index个
                //元素，并标记visited[i]=1，然后进入第index+1个元素的递归
                visited[i] = 1;
                tmp.push_back(candidates[i]);
                dfs(candidates, index + 1, visited, tmp, res);
                //为tmp的第index个元素去掉元素candidate[i] 并在后序的for循环中
                //选择一个新的candidate[i]
                tmp.pop_back();
                visited[i] = 0;
            }
        }
    }
};
```

#### 47. Permutations II
候选元素包含重复数字的permutation问题。

> For example,[1,1,2] have the following unique permutations:  
[  
  [1,1,2],  
  [1,2,1],  
  [2,1,1]  
]

解题思路：
* 本题是关于排列的DFS问题，需要使用visited标记，并且每个递归的拆解循环都要从待选数据集的开头开始选取
* 含重复元素的permutation题的解法：
  * 1.先对待选数据集排序
  * 2.在递归中先判断当前的数和前一个相邻的数是否相等
    * 如果相等，前面的数必须已经使用了，即对应的visited中的值为1，当前的数字才能使用
    * 否则需要跳过，这样就不会产生重复排列了，代码如下：

```cpp
class Solution {
public:
    vector<vector<int> > permuteUnique(vector<int> &candidates)
    {
        vector<vector<int> > res;
        vector<int> tmp;
        vector<int> visited(candidates.size(), 0);

        sort(candidates.begin(), candidates.end());
        dfs(candidates, 0, visited, tmp, res);
        return res;
    }
    void dfs(vector<int> &candidates, int level, vector<int> &visited,
             vector<int> &tmp, vector<vector<int> > &res)
    {
        //出口
        if (level==candidates.size())
          res.push_back(tmp);
        else
        {
            for (int i=0; i<candidates.size(); ++i)
            {
                if (visited[i] != 0)
                    continue;
                //如果当前元素candidates[i]等于其前一个元素candidates[i-1]
                //则此时只有当前一个元素在当前permutation中用过了当前元素才能使用
                if (i>0 && candidates[i]==candidates[i-1] &&
                    visited[i-1]==0)
                    continue;

                //将元素推入tmp并标记visited[i] = 1;
                tmp.push_back(candidates[i]);
                visited[i] = 1;
                dfs(candidates, level + 1, visited, tmp, res);
                tmp.pop_back();
                visited[i] = 0;
            }
        }
    }
};
```


#### 输出N个括号的全排列结果


>For example, given n = 3, a solution set is:  
[  "((()))",  "(()())",  "(())()",  "()(())",  "()()()"  ]

解题思路：  
* 输出括号的有效全排列，需要用到DFS递归。
* 定义递归出口：
  1. 非法出口：如果在某次递归时左括号剩余的个数大于右括号剩余的个数，即最终会出现')('这样的非法串，所以这种情况直接返回，不继续处理。
  * 有效出口：如果left和right都为0，则说明此时生成的字符串已有3个左括号和3个右括号，且字符串合法，则存入结果中后返回。
* 如果以上两种情况都不满足，若此时left大于0，则调用递归函数，注意参数的更新，若right大于0，则调用递归函数，同样要更新参数。代码如下：

```cpp
class Solution {
public:
    vector<string> res;
    vector<string> generateParenthesis(int n) {

        dfs(n, n, "");
        return res;
    }
    void dfs(int left, int right, string out) {
        //当左括号剩余个数left>右括号剩余个数right，此时说明当前递归的括号全排列
        //是非法序列，因此走非法递归出口直接返回上层
        if (left > right)
            return;
        if (left == 0 && right == 0)
            res.push_back(out);
        else {
            if (left > 0)  
                dfs(left - 1, right, out + '(');
            if (right > 0)
                dfs(left, right - 1, out + ')');
        }
    }
};
```

#### 494 加减的target的组合个数
给一组数字和一个target值，对每个数字任意添加+或者-符号，求有多少种组合使得这组数字
的和等于target。

解题思路：  
* 对于这种求多种情况的问题，首先要想到使用递归来做。
* 我们从第一个数字，调用递归函数，在递归函数中，分别对目标值进行加上当前数字调用递归，和减去当前数字调用递归，这样会涵盖所有情况，并且当所有数字遍历完成后，我们看若目标值为0了，则结果res自增1，参见代码如下：

```cpp
class Solution {
public:
    int res = 0;
    int findTargetSumWays(vector<int>& nums, int target) {
        helper(nums, target, 0);
        return res;
    }
    void helper(vector<int>& nums, int target, int index) {
        //递归出口
        if (index == nums.size()) {
            if (target == 0)
                ++res;
            else
                return;
        }
        //对于当前数组元素nums[index]只有+和-两种选择
        //所以讲他们分别递归下去，符合当前问题的combination规则
        helper(nums, target-nums[index], index+1);
        helper(nums, target+nums[index], index+1);
    }
};
```


---


## DFS和剪枝
#### word breakII !!!3/8
Given a string s and a dictionary of words dict, add spaces in s to construct a sentence where each word is a valid dictionary word.

Return all such possible sentences.

For example, given
s = "catsanddog",
dict = ["cat", "cats", "and", "sand", "dog"].

A solution is ["cats and dog", "cat sand dog"].

[ref](https://www.cnblogs.com/yuzhangcmu/p/4037299.html)
[ref2](https://www.cnblogs.com/yuzhangcmu/p/4037299.html)

题目分析：  
* 本题考察DFS + 剪枝优化  

* DP与DFS的区别：DP是Bottom-up 而DFS是TOP-DOWN.

* 剪枝方法：定义一个一位数组possible，其中possible[i] = true表示在[i, n]区间上有解，n为s的长度，如果某个区间之前被判定了无解，下次循环时就会跳过这个区间，从而大大减少了运行时间。

DFS+剪枝：
```cpp
class Solution {
public:
    vector<string> wordBreak(string s, unordered_set<string>& wordDict) {
        vector<string> res;
        string out;
        vector<bool> possible(s.size() + 1, true); //剪枝部分
        wordBreakDFS(s, wordDict, 0, possible, out, res);
        return res;
    }
    void wordBreakDFS(string &s, unordered_set<string> &wordDict, int start, vector<bool> &possible, string &out, vector<string> &res) {
        if (start == s.size()) {
            res.push_back(out.substr(0, out.size() - 1));
            return;
        }
        for (int i = start; i < s.size(); ++i) {
            string word = s.substr(start, i - start + 1);
            if (wordDict.find(word) != wordDict.end() && possible[i + 1]) {  //剪枝部分
                out.append(word).append(" ");
                int oldSize = res.size();   //剪枝部分
                wordBreakDFS(s, wordDict, i + 1, possible, out, res);
                if (res.size() == oldSize) possible[i + 1] = false;  //剪枝部分
                out.resize(out.size() - word.size() - 1);
            }
        }
    }
};
```

#### Palindrome Partitioning !!!3/8
Given a string s, partition s such that every substring of the partition is a palindrome.

Return all possible palindrome partitioning of s.

For example, given s = "aab",
Return

  [
    ["aa","b"],
    ["a","a","b"]
  ]

解题思路：

* 这又是一道需要用DFS来解的题目，既然题目要求找到所有可能拆分成回文数的情况，那么肯定是所有的情况都要遍历到。对于每一个子字符串都要分别判断一次是不是回文数，那么肯定有一个判断回文数的子函数，还需要一个DFS函数用来递归，再加上原本的这个函数，总共需要三个函数来求解。

* 那么，对原字符串的所有子字符串的访问顺序是什么呢，如果原字符串是 abcd, 那么访问顺序为: a -> b -> c -> d -> cd -> bc -> bcd-> ab -> abc -> abcd, 这是对于没有两个或两个以上子回文串的情况。那么假如原字符串是 aabc，那么访问顺序为：a -> a -> b -> c -> bc -> ab -> abc -> aa -> b -> c -> bc -> aab -> aabc，中间当检测到aa时候，发现是回文串，那么对于剩下的bc当做一个新串来检测，于是有 b -> c -> bc，这样扫描了所有情况，即可得出最终答案。  

代码如下：
```cpp
class Solution {
public:
    vector<vector<string>> partition(string s) {
        vector<vector<string>> res;
        vector<string> out;
        partitionDFS(s, 0, out, res);
        return res;
    }
    void partitionDFS(string s, int start, vector<string> &out, vector<vector<string>> &res) {
        if (start == s.size()) {
            res.push_back(out);
            return;
        }
        for (int i = start; i < s.size(); ++i) {
            if (isPalindrome(s, start, i)) {
                out.push_back(s.substr(start, i - start + 1));
                partitionDFS(s, i + 1, out, res);
                out.pop_back();
            }
        }
    }
    bool isPalindrome(string s, int start, int end) {
        while (start < end) {
            if (s[start] != s[end]) return false;
            ++start;
            --end;
        }
        return true;
    }
};
```



####  Subsets 子集合
Given a set of distinct integers, S, return all possible subsets.  

Note:  

Elements in a subset must be in non-descending order.  
The solution set must not contain duplicate subsets.  


For example,  
If S = [1,2,3], a solution is:  

[    
  [3],  
  [1],  
  [2],  
  [1,2,3],  
  [1,3],  
  [2,3],  
  [1,2],  
  []  
]  

解题思路：  
这道求子集合的问题，由于其要列出所有结果。
* 下面来看递归的解法，相当于一种深度优先搜索，参见网友JustDoIt的博客，由于原集合每一个数字只有两种状态，要么存在，要么不存在，那么在构造子集时就有选择和不选择两种情况，所以可以构造一棵二叉树，左子树表示选择该层处理的节点，右子树表示不选择，最终的叶节点就是所有子集合，树的结构如下：

```cpp
// Recursion
class Solution {
public:
    vector<vector<int> > subsets(vector<int> &S) {
        vector<vector<int> > res;
        vector<int> out;
        sort(S.begin(), S.end());
        getSubsets(S, 0, out, res);
        return res;
    }
    void getSubsets(vector<int> &S, int pos, vector<int> &out, vector<vector<int> > &res) {
        res.push_back(out);
        for (int i = pos; i < S.size(); ++i) {
            out.push_back(S[i]);
            getSubsets(S, i + 1, out, res);
            out.pop_back();
        }
    }
};
```


####  Subsets II 子集合之二
Given a collection of integers that might contain duplicates, S, return all possible subsets.  

Note:  

Elements in a subset must be in non-descending order.  
The solution set must not contain duplicate subsets.  


For example,  
If S = [1,2,2], a solution is:  

[  
  [2],  
  [1],  
  [1,2,2],  
  [2,2],  
  [1,2],  
  []  
]  

解题思路：  
对于递归的解法，根据之前 Subsets 子集合 里的构建树的方法，在处理到第二个2时，由于前面已经处理了一次2，这次我们只在添加过2的[2] 和 [1 2]后面添加2，其他的都不添加。  
代码只需在原有的基础上增加一句话，while (S[i] == S[i + 1]) ++i; 这句话的作用是跳过树中为X的叶节点，因为它们是重复的子集，应被抛弃。代码如下：

```cpp
class Solution {
public:
    vector<vector<int>> subsetsWithDup(vector<int> &S) {
        if (S.empty()) return {};
        vector<vector<int>> res;
        vector<int> out;
        sort(S.begin(), S.end());
        getSubsets(S, 0, out, res);
        return res;
    }
    void getSubsets(vector<int> &S, int pos, vector<int> &out, vector<vector<int>> &res) {
        res.push_back(out);
        for (int i = pos; i < S.size(); ++i) {
            out.push_back(S[i]);
            getSubsets(S, i + 1, out, res);
            out.pop_back();
            while (i + 1 < S.size() && S[i] == S[i + 1]) ++i;
        }
    }
};
```








---
