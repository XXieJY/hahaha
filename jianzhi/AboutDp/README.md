
#### DP的六种主流问题：
1. 坐标&序列DP    
2. 划分DP
3. 背包DP  
4. 区间DP  

#### 常见的动态规划题型
1. 求最大最小的问题
2. 判断可不可行,存不存在
3. 统计方案个数

#### 解决一个动态规划问题的步骤是什么？
0. 先运用穷举思路试试水
1. 状态是什么
2. 状态转移方程是什么
3. 状态的初始值是什么
4. 问题要求的最后答案是什么

---

#### Maximum Product Subarray 求最大子数组乘积

解题思路：  
* 这道题最直接的方法就是用DP来做，而且要用两个dp数组，其中f[i]表示子数组[0, i]范围内的最大子数组乘积，g[i]表示子数组[0, i]范围内的最小子数组乘积，初始化时f[0]和g[0]都初始化为nums[0]，其余都初始化为0。
* 那么从数组的第二个数字开始遍历，那么此时的最大值和最小值只会在这三个数字之间产生，即f[i-1]*nums[i]，g[i-1]*nums[i]，和nums[i]。所以我们用三者中的最大值来更新f[i]，用最小值来更新g[i]，然后用f[i]来更新结果res即可，参见代码如下：

```cpp
class Solution {
public:
    int maxProduct(vector<int>& nums) {
        int res = nums[0], n = nums.size();
        vector<int> f(n, 0), g(n, 0);
        f[0] = nums[0];
        g[0] = nums[0];
        for (int i = 1; i < n; ++i) {
            f[i] = max(max(f[i - 1] * nums[i], g[i - 1] * nums[i]), nums[i]);
            g[i] = min(min(f[i - 1] * nums[i], g[i - 1] * nums[i]), nums[i]);
            res = max(res, f[i]);
        }
        return res;
    }
};
```

### 最长XXX问题
* 最长公共子序列（longest common sequence）：不要求连续
* 最长公共子串（longest common substring）：要求连续

#### 1.最长公共子序列（不连续）
```cpp
#include <iostream>
#include <vector>

#define GO_UP 1;
#define GO_LEFT 2;
#define GO_DIAGONAL 3;

using namespace std;


class Solution {

public:
    int findLCSequence(const string& str1, const string& str2){
            if(str1.empty() || str2.empty())
                return 0;
            vector<vector<int> > dp(str1.size()+1, 
                vector<int>(str2.size()+1));
            vector<vector<int> > dpPath(str1.size()+1, 
                vector<int>(str2.size()+1));
            for(int i=0; i<=str1.length(); ++i)
                dp[i][0] = 0;
            for(int j=0; j<=str2.length(); ++j)
                dp[0][j] = 0;
            
            
            for(int i=1; i<=str1.length(); ++i){
                for(int j=1; j<=str2.length(); ++j){
                    if(str1[i-1]==str2[j-1]){
                        dp[i][j]=dp[i-1][j-1]+1;
                        dpPath[i][j] = GO_DIAGONAL;
                    }
                    //子串和子序列的差别在这里
                    else{
                        if(dp[i-1][j]>dp[i][j-1]){
                            dp[i][j]=dp[i-1][j];
                            dpPath[i][j]=GO_UP;
                        }
                        else{
                            dp[i][j]=dp[i][j-1];
                            dpPath[i][j]=GO_LEFT;
                        }
                    }
                }
            }
            int i = str1.size(), j = str2.size();
            while(i!=0&&j!=0){
                if(dpPath[i][j]==1)
                    cout << str1[i-1] << " ";
                else if(dpPath[i][j]==GO_UP)
                    --i;
                else if(dpPath[i][j]=GO_LEFT)
                    --j;
            }
            return dp[str1.size()][str2.size()];
        }
};
```

#### 2.最长公共子串（连续）
```cpp
#include <iostream>
#include <vector>
using namespace std;

class Solution {

public:
    int findLCString(const string& str1, const string& str2){
            if(str1.empty() || str2.empty())
                return 0;
            vector<vector<int> > dp(str1.size()+1, 
                vector<int>(str2.size()+1));
            for(int i=0; i<=str1.length(); ++i)
                dp[i][0] = 0;
            for(int j=0; j<=str2.length(); ++j)
                dp[0][j] = 0;
            
            int res = 0;
            for(int i=1; i<=str1.length(); ++i){
                for(int j=1; j<=str2.length(); ++j){
                    if(str1[i-1]==str2[j-1]){
                        dp[i][j]=dp[i-1][j-1]+1;
                        if(dp[i][j]>res)
                            res = dp[i][j];
                    }
                    //子串和子序列的差别在这里
                    else
                        dp[i][j] = 0;
                }
            }
        }
};
```

####  Longest Increasing Subsequence 最长递增子序列 LIS(不连续)

解题思路*：  
* 其中dp[i]表示以nums[i]为结尾的最长递增子串的长度。
* 对于每一个nums[i]，我们从第一个数再搜索到i，如果发现某个数小于nums[i]，我们更新dp[i]，更新方法为dp[i] = max(dp[i], dp[j] + 1)，即比较当前dp[i]的值和那个小于num[i]的数的dp值加1的大小.
* 我们就这样不断的更新dp数组，到最后dp数组中最大的值就是我们要返回的LIS的长度，参见代码如下：

```cpp
class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        vector<int> dp(nums.size(), 1);
        int res = 0;
        for (int i = 0; i < nums.size(); ++i) {
            for (int j = 0; j < i; ++j) {
                if (nums[i] > nums[j]) {
                    dp[i] = max(dp[i], dp[j] + 1);
                }
            }
            res = max(res, dp[i]);
        }
        return res;
    }
};
```


####  Longest Continuous Increasing Subsequence(最长连续递增子序列LCIS)

解题思路*：  
* 由于有了连续这个条件，跟之前那道Number of Longest Increasing Subsequence比起来，其实难度就降低了很多。
* 我们可以使用一个计数器，如果遇到大的数字，计数器自增1；如果是一个小的数字，则计数器重置为1。
* 我们用一个变量cur来表示前一个数字，初始化为整型最大值，当前遍历到的数字num就和cur比较就行了，每次用cnt来更新结果res，参见代码如下：

```cpp
class Solution {
public:
    int findLengthOfLCIS(vector<int>& nums) {
        int res = 0, cnt = 0, cur = INT_MAX;
        for (int num : nums) {
            if (num > cur) ++cnt;
            else cnt = 1;
            res = max(res, cnt);
            cur = num;
        }
        return res;
    }
};
```

#### 55. 数组跳棋问题

For example:  
A = [2,3,1,1,4], return true.  
A = [3,2,1,0,4], return false.  

解题思路：  
这里有几个思维转弯的地方：怎么将“能否走到终点的定义具体化” --> 取最大的步数是否大于等于0作为判断条件，因为如果取最小剩余步数或者一般剩余步数时并不能完全断定是否能走到该点，抽象地说，这里的最大剩余步数可以cover住其他情况，也就是说当最大剩余步数>=0时我们可以说至少有一种方式可以走到终点，至于一般步数或者最小步数也能不能到达终点那就是possible fine,（动态规划中取最大最小的思想）-->根据取最大步数定义动态转移方程，到达当前节点的最大剩余步数等于dp[i-1]和A[i-1]之中的最大值减一；
* 具体化问题：如何才算能走到终点？**即走到最终点时剩余步数>=0，因此只要找到走到dp[n]时的最大步数(极端情况)，如果最大步数>=0则该
问题至少有一个解了。**
* 压缩问题规模，尝试剥离子问题：将抽象的判断问题具体化以后，尝试缩小问题规模，dp[1]的步数剩余应该是dp[1]=2，递推公式为：dp[i] = max(dp[i - 1], A[i - 1]) - 1，如果当某一个时刻dp数组的值为负了，说明无法抵达当前位置，则直接返回false。
* 维护一个一位数组dp，其中dp[i]表示走道i位置时剩余的最大步数。
* 最后我们判断dp数组最后一位是否为非负数即可知道是否能抵达该位置，代码如下：

```cpp
class Solution {
public:
    bool canJump(int A[], int n) {
        vector<int> dp(n, 0);
        for (int i = 1; i < n; ++i) {
            dp[i] = max(dp[i - 1], A[i - 1]) - 1;
            if (dp[i] < 0) return false;
        }
        return dp[n - 1] >= 0;
    }
};
```

#### 70. Climbing Stairs
You are climbing a stair case. It takes n steps to reach to the top.
Each time you can either climb 1 or 2 steps. In how many distinct ways can you climb to the top?
Note: Given n will be a positive integer.

解题思路：  
* 本题要求找出有多少种爬到梯子最高点的方法，这里是求所有可能性的个数，所以是使用DP而不是DFS。
* 首先分析边界点，那么就是梯子为0阶时，返回0；梯子为1阶时返回1；梯子为2阶时返回2；因此dp[1]=1, dp[2]=2;
* 再来是状态转移公式：dp[i] = dp[i - 1] + dp[i - 2];  (3<= i <= n)

```cpp
class Solution {
public:
    int climbStairs(int n) {
        if (n == 0) return 0;
        if (n == 1) return 1;
        int dp[n+1];
        dp[1] = 1;
        dp[2] = 2;

        for (int i = 3; i <= n; ++i) {
            dp[i] = dp[i - 1] + dp[i - 2];
        }
        return dp[n];
    }
};
```



#### 120. Triangle
Given a triangle, find the minimum path sum from top to bottom. Each step you may move to adjacent numbers on the row below.

For example, given the following triangle  
[  
     [2],  
    [3,4],  
   [6,5,7],  
  [4,1,8,3]  
]  
The minimum path sum from top to bottom is 11 (i.e., 2 + 3 + 5 + 1 = 11).

解题思路：  
* 此题使用bottom-up的dp方式
* 因为bottom-up减少了需要记忆memoization，当前节点经过计算的值就是从三角形最后一行bottom up上来的最小值。因此，只需要复制了三角形最后一行，作为用来更新的一位数组(bottom up的过程中，数组中有些节点会慢慢被弃用，但这是可允许的行为)。
* 根据这个思想，设定bottom up的状态转移方程，之后逐个遍历这个DP数组，对于每个数字，和它之后的元素比较选择较小的再加上上面一行相邻位置的元素做为新的元素，然后一层一层的向上扫描，整个过程和冒泡排序的原理差不多，最后最小的元素都冒到前面，第一个元素即为所求。代码如下：

```cpp
class Solution {
public:
    int minimumTotal(vector<vector<int> > &triangle) {
        int n = triangle.size();
        vector<int> dp(triangle.back()); //辅助数组
        for (int i = n - 2; i >= 0; --i) { //bottom up的循环
            for (int j = 0; j <= i; ++j) {
                dp[j] = min(dp[j], dp[j + 1]) + triangle[i][j]; //本题的状态转移方程
            }
        }
        return dp[0];
    }
};
```

#### 3.最长不公共子序列sequence
```cpp
class Solution {
public:
    int findLUSlength(string a, string b) {
        int l1=a.size(),l2=b.size(),i;
        for(i=0;i<l1&&i<l2;i++){
            if(a[i]!=b[i]){
                return max(l1,l2);
            }
        }
        if(i==l1&&i==l2){
            return -1;
        }
        if(i==l1){
            return l2;
        }
        if(i==l2){
            return l1;
        }
    }
};
```


#### Longest Palindromic Subsequence 最长回文子序列（不连续）
Example 1:
Input:
"bbbab"
Output:
4
```cpp
  int longestPalindromeSubseq(string s) {
        int n = s.size();
        //dp数组大小为(n+1)*n
        vector<vector<int>> dp(n+1,vector<int>(n));
        //初始化边界条件dp[1][i] = 1
        for(int i=0;i<n;i++) 
            dp[1][i]=1;
        for(int i=2;i<=n;i++) //length
            for(int j=0;j<n-i+1;j++) {//start index 
                dp[i][j] = s[j]==s[i+j-1]?2+dp[i-2][j+1]:max(dp[i-1][j],dp[i-1][j+1]);
        return dp[n][0]; 
    }
```

#### Longest Palindromic Substring最长回文子串
Example 1:

Input: "babad"
Output: "bab"
Note: "aba" is also a valid answer.

```cpp
string longestPalindrome(string s) {
    if (s.empty()) return "";
    if (s.size() == 1) return s;
    int min_start = 0, max_len = 1;
    for (int i = 0; i < s.size();) {
      if (s.size() - i <= max_len / 2) break;
      int j = i, k = i;
      while (k < s.size()-1 && s[k+1] == s[k]) ++k; // Skip duplicate characters.
      i = k+1;
      while (k < s.size()-1 && j > 0 && s[k + 1] == s[j - 1]) { ++k; --j; } // Expand.
      int new_len = k - j + 1;
      if (new_len > max_len) { min_start = j; max_len = new_len; }
    }
    return s.substr(min_start, max_len);
}
```


#### 62. Unique Paths
A robot is located at the top-left corner of a m x n grid (marked 'Start' in the diagram below).
The robot can only move either down or right at any point in time. The robot is trying to reach the bottom-right corner of the grid (marked 'Finish' in the diagram below).
How many possible unique paths are there?

解题思路：  
* 本题为求次数的问题，因此可以使用DP而不是使用DFS。
* 这跟爬梯子问题很类似，那道题是说可以每次能爬一格或两格，问到达顶部的所有不同爬法的总数。而这道题是每次可以向下走或者向右走，求到达最右下角的所有不同走法的个数。
* 具体化问题：**维护一个二维数组dp，其中dp[i][j]表示到当前位置不同的走法的个数**
* 求得子问题得出递推式：然后可以得到递推式为: **dp[i][j] = dp[i - 1][j] + dp[i][j - 1]**
* 减少空间消耗：这里为了节省空间，我们使用一维数组dp，一行一行的刷新也可以，代码如下：

```cpp
//这种限定往右或者下走格子的问题，其左侧边和上册边的dp值必须先进行初始化。
//这里左侧边和上侧边的dp值皆为1。
class Solution {
public:
    int uniquePaths(int m, int n)
    {
        vector<int> dp(n, 1);
        for (int i = 1; i < m; ++i) //一行一行地算，从第一行开始。为第0行是边界
        {
            for (int j = 1; j < n; ++j) //每行从第一列开始。第零列是边界。
            {
                dp[j] += dp[j - 1];
            }
        }
        return dp[n - 1];
    }
};
```


#### 63. Unique Paths II

Follow up for "Unique Paths":

Now consider if some obstacles are added to the grids. How many unique paths would there be?

An obstacle and empty space is marked as 1 and 0 respectively in the grid.

> For example,  
There is one obstacle in the middle of a 3x3 grid as illustrated below.  
[  
  [0,0,0],  
  [0,1,0],  
  [0,0,0]  
]  
The total number of unique paths is 2.

解题思路：  
这道题是之前那道 Unique Paths 不同的路径 的延伸，在路径中加了一些障碍物，还是用动态规划Dynamic Programming来解。
* 不同的是当遇到为1的点，将该位置的dp数组中的值清零，其余和之前那道题并没有什么区别，代码如下：

```cpp
//在参考Unique Paths的题目的同时，因为可能有障碍物所以不能一次性将左边界和上边界初始化为1
//本题使用二维数组来保存dp的结果，可以对比着和上一题一起看。
//一个是使用一维数组来做二维路径dp，另一个是使用二维数组来做二维路径dp
class Solution {
public:
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        //边界情况检测：1.如果地图是空的则返回0；2.如果[0][0]处直接就是一个障碍物则也返回0
        if (obstacleGrid.empty() || obstacleGrid[0].empty() || obstacleGrid[0][0] == 1)
        {
            return 0;
        }
        //初始化辅助变量，二维数组dp[i][j]
        vector<vector<int> > dp(obstacleGrid.size(), vector<int>(obstacleGrid[0].size(), 0));
        for (int i = 0; i < obstacleGrid.size(); ++i)
        {
            for (int j = 0; j < obstacleGrid[i].size(); ++j)
            {
                if (obstacleGrid[i][j] == 1)
                {
                    dp[i][j] = 0;
                }
                else if(i==0 && j ==0)
                {
                    dp[i][j] = 1;
                }
                //上边界
                else if (i == 0 && j > 0)
                {
                    dp[i][j] = dp[i][j - 1];
                }
                //左边界
                else if (i > 0 && j == 0)
                {
                    dp[i][j] = dp[i - 1][j];
                }
                else
                {
                    dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
                }
            }
        }
        return dp.back().back();
    }
};
```


#### 64. Minimum Path Sum
Given a m x n grid filled with non-negative numbers, find a path from top left to bottom right which minimizes the sum of all numbers along its path.

Note: You can only move either down or right at any point in time.

>Example 1:  
[[1,3,1],  
 [1,5,1],  
 [4,2,1]]  
Given the above grid map, return 7. Because the path 1→3→1→1→1 minimizes the sum.

解题思路：  
* 比较直接的路径DP，使用Top Down+Momoization即可。
* 关于记忆过往答案：维护一个二维的dp数组，其中dp[i][j]表示当前位置的最小路径和。
* 关于状态转移方程：根据题意可以得到****dp[i][j] = grid[i][j] + min(dp[i - 1][j], dp[i][j - 1])****，代码如下：

```cpp
class Solution {
public:
    int minPathSum(vector<vector<int> > &grid) {
        //声明Dp使用的辅助数组
        int m, n;
        m = grid.size();
        n = grid[0].size();
        int dp[m][n];

        //初始化DP的边界
        dp[0][0] = grid[0][0];
        //因为要找路径最小和，所以每一步加法操作肯定只要考虑向下加或者向右加
        //此时可以直接将左右边界直接计算出来，因为左边界dp[i][0]只有向下走才能走全
        //上边界只有向右走才能走全
        for (int i = 1; i < m; ++i)
        {
            dp[i][0] = grid[i][0] + dp[i - 1][0];
        }
        for (int i = 1; i < n; ++i)
        {
            dp[0][i] = grid[0][i] + dp[0][i - 1];
        }

        //向右下角出口进行DP
        for (int i = 1; i < m; ++i)
        {
            for (int j = 1; j < n; ++j)
            {
                dp[i][j] = grid[i][j] + min(dp[i - 1][j], dp[i][j - 1]);
            }
        }
        return dp[m - 1][n - 1];
    }
};
```






---
## 字符串的查找和匹配DP

#### 5. Longest Palindromic Substring（最长回文子串查找）
Given a string s, find the longest palindromic substring in s. You may assume that the maximum length of s is 1000.  

Example:  

Input: "babad"  

Output: "bab"  

Note: "aba" is also a valid answer.  

解题思路：  
* 此题可以用动态规划Dynamic Programming来解。
* 维护一个二维数组dp，其中dp[i][j]表示字符串区间[i, j]是否为回文串。
  * 当i = j时，只有一个字符，肯定是回文串。
  * 如果i = j + 1，说明是相邻字符，此时需要判断s[i]是否等于s[j]。
  * 如果i和j不相邻，即i - j >= 2时，除了判断s[i]和s[j]相等之外，dp[j + 1][i - 1]若为真，就是回文串，通过以上分析，可以写出递推式如下：

  >  dp[i, j] = 1,    if i == j  
     dp[i, j]= s[i] == s[j],                                if j = i + 1  
    dp[i, j]= s[i] == s[j] && dp[i + 1][j - 1],    if j > i + 1      

```cpp
class Solution {
public:
    string longestPalindrome(string s)
    {
        //初始化二维dp数组和一些辅助变量
        //left right len 作为全局变量存储当前最长回文子串的左右边界以及长度
        int dp[s.size()][s.size()] = {0}, left = 0, right = 0, len = 0;

        //二维dp的for循环
        for (int j = 0; j < s.size(); ++j)
        {
            //长度为1的子串一定是回文串
            dp[j][j] = 1;
            for (int i = 0; i < j; ++i)
            {
                //判断子串[i,j]是否是回文串的dp递推式
                //即：(当前子串的两端字符是否相等 && (子串长度为1或者2 || 子串包含的子串[i+1 : j-1]是否是回文串)
                dp[i][j] = (s[i] == s[j] && (j - i < 2 || dp[i + 1][j - 1]));
                //如果当前回文串的长度大于记录中的回文串则替换它
                if (dp[i][j] && len < j - i + 1)
                {
                    len = j - i + 1;
                    left = i;
                    right = j;
                }
            }
        }
        return s.substr(left, right - left + 1);
    }
};
```


#### 72. Edit Distance
解题思路：  
* 首先维护一个二维的数组dp，其中dp[i][j]表示从word1的前i个字符转换到word2的前j个字符所需要的步骤。那我们可以先给这个二维数组dp的第一行第一列赋值，这个很简单，因为第一行和第一列对应的总有一个字符串是空串，于是转换步骤完全是另一个字符串的长度。
* 最短编辑距离可以看作路径DP的变化形式。主要是理解将编辑距离问题转化成二维DP问题后与原问题的对应关系。
  * 当word1[i] == word2[j]时，dp[i][j] = dp[i - 1][j - 1]。
  * 其他情况时，dp[i][j]是其左，左上，上的三个值中的最小值加1。

```cpp
class Solution {
public:
    int minDistance(string word1, string word2) {
        int n1 = word1.size(), n2 = word2.size();
        int dp[n1 + 1][n2 + 1];
        //初始化边界条件
        for (int i = 0; i <= n1; ++i)
        {
            dp[i][0] = i;
        }
        for (int i = 0; i <= n2; ++i)
        {
            dp[0][i] = i;
        }
        //根据状态转移方程进行dp
        for (int i = 1; i <= n1; ++i)
        {
            for (int j = 1; j <= n2; ++j)
            {
                if (word1[i - 1] == word2[j - 1])
                {
                    dp[i][j] = dp[i - 1][j - 1];
                }
                else
                {
                    dp[i][j] = min(dp[i - 1][j - 1], min(dp[i - 1][j], dp[i][j - 1])) + 1;
                }
            }
        }
        return dp[n1][n2];
    }
};
```

#### 91. Decode Ways
A message containing letters from A-Z is being encoded to numbers using the following mapping:  

> 'A' -> 1  
'B' -> 2  
...  
'Z' -> 26  
Given an encoded message containing digits, determine the total number of ways to decode it.  

For example,  
Given encoded message "12", it could be decoded as "AB" (1 2) or "L" (12).  

The number of ways decoding "12" is 2.  
解题思路：  
* 建立一位dp数组，长度比输入数组长多多2，全部初始化为1，因为斐波那契数列的前两项也为1，然后从第三个数开始更新，对应数组的第一个数。
* 对每个数组首先判断其是否为0，若是将改为dp赋0，若不是，赋上一个dp值，此时相当如加上了dp[i - 1], 然后看数组前一位是否存在，如果存在且满足前一位不是0，且和当前为一起组成的两位数不大于26，则当前dp值加上dp[i - 2], 至此可以看出来跟斐波那契数组的递推式一样，代码如下：
```cpp
class Solution {
public:
    int numDecodings(string s)
    {
        if (s.empty() || (s.size() > 1 && s[0] == '0'))
        {
            return 0;
        }
        vector<int> dp(s.size() + 1, 0);
        dp[0] = 1;
        for (int i = 1; i < dp.size(); ++i)
        {
            dp[i] = (s[i - 1] == '0') ? 0 : dp[i - 1];
            if (i > 1 && (s[i - 2] == '1' || (s[i - 2] == '2' && s[i - 1] <= '6')))
            {
                dp[i] += dp[i - 2];
            }
        }
        return dp.back();
    }
};
```



#### 97. Interleaving String

&nbsp; 0 d b b c a  
0 T F F F F F  
a T F F F F F  
a T T T T T F  
b F T T F T F  
c F F T T T T  
c F F F T F T  

解题思路：  
* 首先，这道题的大前提是字符串s1和s2的长度和必须等于s3的长度，如果不等于，肯定返回false。那么当s1和s2是空串的时候，s3必然是空串，则返回true。所以直接给dp[0][0]赋值true，然后若s1和s2其中的一个为空串的话，那么另一个肯定和s3的长度相等，则按位比较，若相同且上一个位置为True，赋True，其余情况都赋False，这样的二维数组dp的边缘就初始化好了。
* 下面只需要找出递推公式来更新整个数组即可，我们发现，在任意非边缘位置dp[i][j]时，它的左边或上边有可能为True或是False，两边都可以更新过来，只要有一条路通着，那么这个点就可以为True。
  * 那么我们得分别来看，如果左边的为True，那么我们去除当前对应的s2中的字符串s2[j - 1] 和 s3中对应的位置的字符相比（计算对应位置时还要考虑已匹配的s1中的字符），为s3[j - 1 + i], 如果相等，则赋True，反之赋False。 而上边为True的情况也类似。
* 所以可以求出递推公式为：**dp[i][j] = (dp[i - 1][j] && s1[i - 1] == s3[i - 1 + j]) || (dp[i][j - 1] && s2[j - 1] == s3[j - 1 + i]);**
* 其中dp[i][j] 表示的是 s2 的前 i 个字符和 s1 的前 j 个字符是否匹配 s3 的前 i+j 个字符，根据以上分析，可写出代码如下：

```cpp
class Solution {
public:
    bool isInterleave(string s1, string s2, string s3) {
        if (s1.size() + s2.size() != s3.size())
        {
            return false;
        }

        int n1 = s1.size();
        int n2 = s2.size();
        vector<vector<bool> > dp(n1 + 1, vector<bool> (n2 + 1, false));

        dp[0][0] = true;
        //初始化左边界
        for (int i = 1; i <= n1; ++i)
        {
            dp[i][0] = dp[i - 1][0] && (s1[i - 1] == s3[i - 1]);
        }
        //初始化上边界
        for (int i = 1; i <= n2; ++i)
        {
            dp[0][i] = dp[0][i - 1] && (s2[i - 1] == s3[i - 1]);
        }
        //开始dp推导
        for (int i = 1; i <= n1; ++i)
        {
            for (int j = 1; j <= n2; ++j)
            {
                dp[i][j] = (dp[i - 1][j] && s1[i - 1] == s3[i - 1 + j]) ||
                    (dp[i][j - 1] && s2[j - 1] == s3[j - 1 + i]);
            }
        }
        return dp[n1][n2];
    }
};
```

#### 115. Distinct Subsequences(二维DP的字符串匹配问题)
解题思路：  
* 看到有关字符串的子序列或者配准类的问题，首先应该考虑的就是用动态规划Dynamic Programming来求解，这个应成为条件反射。而所有DP问题的核心就是找出递推公式，想这道题就是递推一个二维的dp数组，下面我们从题目中给的例子来分析，这个二维dp数组应为：
> &nbsp; 0 r a b b b i t  
0 1 1 1 1 1 1 1 1  
r 0 1 1 1 1 1 1 1  
a 0 0 1 1 1 1 1 1  
b 0 0 0 1 2 3 3 3  
b 0 0 0 0 1 3 3 3  
i 0 0 0 0 0 0 3 3  
t 0 0 0 0 0 0 0 3   

* 首先，若原字符串和子序列都为空时，返回1，因为空串也是空串的一个子序列。
* 若原字符串不为空，而子序列为空，也返回1，因为空串也是任意字符串的一个子序列。
* 而当原字符串为空，子序列不为空时，返回0，因为非空字符串不能当空字符串的子序列。理清这些，二维数组dp的边缘便可以初始化了,下面只要找出递推式，就可以更新整个dp数组了。
* 我们通过观察上面的二维数组可以发现:
  * 当更新到dp[i][j]时，dp[i][j] >= dp[i][j - 1] 总是成立。
  * 再进一步观察发现，当 T[i - 1] == S[j - 1] 时，dp[i][j] = dp[i][j - 1] + dp[i - 1][j - 1]，若不等， dp[i][j] = dp[i][j - 1]，所以，综合以上，递推式为：
  * dp[i][j] = dp[i][j - 1] + (T[i - 1] == S[j - 1] ? dp[i - 1][j - 1] : 0)

根据以上分析，可以写出代码如下：
```cpp
class Solution {
public:
    int numDistinct(string S, string T) {
        int dp[T.size() + 1][S.size() + 1];
        for (int i = 0; i <= S.size(); ++i) dp[0][i] = 1;    
        for (int i = 1; i <= T.size(); ++i) dp[i][0] = 0;    
        for (int i = 1; i <= T.size(); ++i) {
            for (int j = 1; j <= S.size(); ++j) {
                dp[i][j] = dp[i][j - 1] + (T[i - 1] == S[j - 1] ? dp[i - 1][j - 1] : 0);
            }
        }
        return dp[T.size()][S.size()];
    }
};
```

---

## 划分型DP

#### Perfect Squares 分割整数为完全平方数(没理解，建议记住递推式)
Given a positive integer n, find the least number of perfect square numbers (for example, 1, 4, 9, 16, ...) which sum to n.  

For example, given n = 12, return 3 because 12 = 4 + 4 + 4; given n = 13, return 2 because 13 = 4 + 9.  
解题思路：
* 建立一个长度为n+1的一维dp数组，其中dp[i]表示正整数i能少能由多个完全平方数组成，将第一个值初始化为0，其余值都初始化为INT_MAX。
* 使用双循环dp，外层i从0循环到n，内层j从1循环到i+j*j <= n的位置，然后每次更新dp[i+j*j]的值。
* 最后返回dp[n]即可，也就是dp数组的最后一个数字，参见代码如下：

```cpp
class Solution {
public:
    int numSquares(int n) {
        vector<int> dp(n + 1, INT_MAX);
        dp[0] = 0;
        //重要的是 i + j * j
        for (int i = 0; i <= n; ++i)
        {
            for (int j = 1; i + j * j <= n; ++j)
            {
                dp[i + j * j] = min(dp[i + j * j], dp[i] + 1);
            }
        }
        return dp.back();
    }
};
```

#### Integer Break 整数拆成乘积最大元素

解法一：拆3
* 从5开始，数字都需要先拆出所有的3，一直拆到剩下一个数为2或者4，剩4就不用再拆了（因为拆成两个2和不拆没有意义，而且4不能拆出一个3剩一个1，这样会比拆成2+2的乘积小。）
* 那么这样我们就可以写代码了，先预处理n为2和3的情况。
    * 然后先将结果res初始化为1，然后当n大于4开始循环，我们结果自乘3，n自减3。
    * 根据之前的分析，当跳出循环时，n只能是2或者4，再乘以res返回即可：
```cpp
class Solution {
public:
    int integerBreak(int n)
    {
        if (n == 2 || n == 3)
        {
            return n - 1;
        }
        int res = 1;
        while (n > 4)
        {
            res *= 3;
            n -= 3;
        }
        return res * n;
    }
};
```

* dp解法
```cpp
public int integerBreak(int n) {
    int[] dp = new int[n + 1];
    dp[1] = 1;
    for(int i = 2; i <= n; i++) {
        for(int j = 1; j <= i - 1; j++) {
            dp[i] = Math.max(dp[i], Math.max(j * dp[i - j], j * (i - j)));
        }
    }
    return dp[n];
}
```

#### 139. Word Break

Given a non-empty string s and a dictionary wordDict containing a list of non-empty words, determine if s can be segmented into a space-separated sequence of one or more dictionary words. You may assume the dictionary does not contain duplicate words.

For example, given
s = "leetcode",
dict = ["leet", "code"].

Return true because "leetcode" can be segmented as "leet code".

[ref](http://www.cnblogs.com/grandyang/p/4257740.html)

题目分析：
* 这道题仍然是动态规划的题目，我们总结一下动态规划题目的基本思路。
  * 将抽象问题具体化：首先我们要决定要存储什么历史信息以及用什么数据结构来存储信息。
  * 剥离子问题取得状态转移方程：然后是最重要的递推式，就是如从存储的历史信息中得到当前步的结果。
  * 设置合理的起始边界值：最后我们需要考虑的就是起始条件的值。
* 接下来我们套用上面的思路来解这道题。
  * 首先我们要存储的历史信息res[i]是表示到字符串s的第i个元素为止能不能用字典中的词来表示，我们需要一个长度为n的布尔数组来存储信息。
  * 根据无后效性原理：res[i]只和**res[j]**以及**前一位元素E[j]**和**自身res[j+1:i]**三个变量有关系**。
  * 然后假设我们现在拥有res[0,...,i-1]的结果，我们来获得res[i]的表达式。思路是对于每个以i为结尾的子串，看看他是不是在字典里面以及他之前的元素对应的res[j]是不是true，如果都成立，那么res[i]为true，写成式子是

```cpp
class Solution {
public:
    bool wordBreak(string s, unordered_set<string> &dict) {
        int len = s.size();
        vector<bool> res(len + 1, false);
        res[0] = true;
        for (int i = 0; i < len + 1; ++i) {
            for (int j = 0; j < i; ++j) {
                //substr(j,i-j);是从j+1开始往后取i-j个数，也就是取[j+1:i]
                if (res[j] && dict.find(s.substr(j, i-j)) != dict.end()) {
                    res[i] = true;
                    break;
                }
            }
        }
        return res[len];
    }
};
```


---

#### **053 正则表达式匹配**
题目描述

请实现一个函数用来匹配包括'.'和'*'的正则表达式。模式中的字符'.'表示任意一个字符，而'*'表示它前面的字符可以出现任意次（包含0次）。 在本题中，匹配是指字符串的所有字符匹配整个模式。例如，字符串"aaa"与模式"a.a"和"ab*ac*a"匹配，但是与"aa.a"和"ab*a"均不匹配

样例输入  
"a","ab*a"

样例输出  
false

解题思路：  
动态规划

```cpp
class Solution
{
public:
    bool match(string s, string p) {
        /**
         * f[i][j]: if s[0..i-1] matches p[0..j-1]
         * if p[j - 1] != '*'
         *      f[i][j] = f[i - 1][j - 1] && s[i - 1] == p[j - 1]
         * if p[j - 1] == '*', denote p[j - 2] with x
         *      f[i][j] is true iff any of the following is true
         *      1) "x*" repeats 0 time and matches empty: f[i][j - 2]
         *      2) "x*" repeats >= 1 times and matches "x*x": s[i - 1] == x && f[i - 1][j]
         * '.' matches any single character
         */
        int m = s.size(), n = p.size();
        vector<vector<bool>> f(m + 1, vector<bool>(n + 1, false));

        f[0][0] = true;
        for (int i = 1; i <= m; i++)
            f[i][0] = false;
        // p[0.., j - 3, j - 2, j - 1] matches empty iff p[j - 1] is '*' and p[0..j - 3] matches empty
        for (int j = 1; j <= n; j++)
            f[0][j] = j > 1 && '*' == p[j - 1] && f[0][j - 2];

        for (int i = 1; i <= m; i++)
            for (int j = 1; j <= n; j++)
                if (p[j - 1] != '*')
                    f[i][j] = f[i - 1][j - 1] && (s[i - 1] == p[j - 1] || '.' == p[j - 1]);
                else
                    // p[0] cannot be '*' so no need to check "j > 1" here
                    f[i][j] = f[i][j - 2] || (s[i - 1] == p[j - 2] || '.' == p[j - 2]) && f[i - 1][j];

        return f[m][n];
    }
};
```

---

## 区间型DP（涉及区间比较、覆盖之类的问题）

#### 303. Range Sum Query - Immutable

解题思路*：
* 这道题的难点就在于是否能想到来用建立累计直方图的思想来建立一个区间DP；
* 其中dp[i]表示[0, i]区间的数字之和，那么[i,j]就可以表示为dp[j]-dp[i-1]，这里要注意一下当i=0时，直接返回dp[j]即可，参见代码如下：

```cpp
class NumArray {
public:
    NumArray(vector<int> &nums) {
        dp = nums;
        for (int i = 1; i < nums.size(); ++i) {
            dp[i] += dp[i - 1];
        }
    }
    int sumRange(int i, int j) {
        return i == 0? dp[j] : dp[j] - dp[i - 1];
    }
private:
    vector<int> dp;
};
```





#### July最大连续乘积子串

题目描述
给一个浮点数序列，取最大乘积连续子串的值，例如 -2.5，4，0，3，0.5，8，-1，则取出的最大乘积连续子串为3，0.5，8。也就是说，上述数组中，3 0.5 8这3个数的乘积30.58=12是最大的，而且是连续的。

分析与解法
此最大乘积连续子串与最大乘积子序列不同，请勿混淆，前者子串要求连续，后者子序列不要求连续。也就是说，最长公共子串（Longest CommonSubstring）和最长公共子序列（LongestCommon Subsequence，LCS）是：

子串（Substring）是串的一个连续的部分，
子序列（Subsequence）则是从不改变序列的顺序，而从序列中去掉任意的元素而获得的新序列；
更简略地说，前者（子串）的字符的位置必须连续，后者（子序列LCS）则不必。比如字符串“ acdfg ”同“ akdfc ”的最长公共子串为“ df ”，而它们的最长公共子序列LCS是“ adf ”，LCS可以使用动态规划法解决。

解法二  
考虑到乘积子序列中有正有负也还可能有0，我们可以把问题简化成这样：数组中找一个子序列，使得它的乘积最大；同时找一个子序列，使得它的乘积最小（负数的情况）。因为虽然我们只要一个最大积，但由于负数的存在，我们同时找这两个乘积做起来反而方便。也就是说，不但记录最大乘积，也要记录最小乘积。

假设数组为a[]，直接利用动态规划来求解，考虑到可能存在负数的情况，我们用maxend来表示以a[i]结尾的最大连续子串的乘积值，用minend表示以a[i]结尾的最小的子串的乘积值，那么状态转移方程为：



```cpp
double MaxProductSubstring(double *a, int length)
{
	double maxEnd = a[0];
	double minEnd = a[0];
	double maxResult = a[0];
	for (int i = 1; i < length; ++i)
	{
		double end1 = maxEnd * a[i], end2 = minEnd * a[i];
		maxEnd = max(max(end1, end2), a[i]);
		minEnd = min(min(end1, end2), a[i]);
		maxResult = max(maxResult, maxEnd);
	}
	return maxResult;
}
```


#### July字符串编辑距离
题目描述  
给定一个源串和目标串，能够对源串进行如下操作：

* 在给定位置上插入一个字符
* 替换任意字符
* 删除任意字符
* 写一个程序，返回最小操作数，使得对源串进行这些操作后等于目标串，源串和目标串的长度都小于2000。

解题思路：  
* 使用二维dp。
* dp[i][j]来自于三种状态

    1、删除，dp[i-1][j]+1;

    2、插入，dp[i][j-1]+1;

    3、替换，if(a[i]==b[j]) dp[i][j]=dp[i-1][j-1],else dp[i][j]=dp[i-1][j-1]+1;

假如我们要将字符串str1变成str2，那么：
* 设sstr1(i)是str1的子串，范围[0到i），其中sstr1(0)是空串
* 再设sstr2(j)是str2的子串，范围[0到j），其中sstr2(0)是空串  
* dp[i][j]表示将sstr1(i)变成sstr2(j)的编辑距离  

推理过程：  
* 首先d(0,t),0<=t<=str1.size()和d(k,0)是很显然的。 如d(0,t) == t;
* 当我们要计算d(i,j)时，即计算sstr1(i)到sstr2(j)之间的编辑距离。
  * 此时，设当前sstr1(i)形式是somestr1c；sstr2(i)形如somestr2d。
  * 而将somestr1变成somestr2的编辑距离已知是d(i-1,j-1)。那么：
    * 将somestr1c变成somestr2的编辑距离已知是d(i,j-1)
    * 将somestr1变成somestr2d的编辑距离已知是d(i-1,j)   
    **那么利用这三个变量，就可以递推出d(i,j)了： 如果c==d，显然编辑距离和d(i-1,j-1)是一样的 如果c!=d，情况稍微复杂一点：**
      * 如果将c替换成d，编辑距离是somestr1变成somestr2的编辑距离 + 1，也就是d(i-1,j-1) + 1
      * 如果在c后面添加一个字d，编辑距离就应该是somestr1c变成somestr2的编辑距离 + 1，也就是d(i,j-1) + 1
      * 如果将c删除了，那就是要将somestr1编辑成somestr2d，距离就是d(i-1,j) + 1  

那最后只需要看着三种谁最小，就采用对应的编辑方案了。递推公式出来了，程序也就出来了。

[参考链接1](http://blog.unieagle.net/2012/09/19/leetcode%E9%A2%98%E7%9B%AE%EF%BC%9Aedit-distance%EF%BC%8C%E5%AD%97%E7%AC%A6%E4%B8%B2%E4%B9%8B%E9%97%B4%E7%9A%84%E7%BC%96%E8%BE%91%E8%B7%9D%E7%A6%BB%EF%BC%8C%E5%8A%A8%E6%80%81%E8%A7%84%E5%88%92/)

[参考链接2](http://www.dreamxu.com/books/dsa/dp/edit-distance.html)

```cpp
int edit_distance(char *a, char *b)
{
    int lena = strlen(a);
    int lenb = strlen(b);
    int d[lena+1][lenb+1];
    int i, j;

    for (i = 0; i <= lena; i++) {
        d[i][0] = i;
    }
    for (j = 0; j <= lenb; j++) {
        d[0][j] = j;
    }

    for (i = 1; i <= lena; i++) {
        for (j = 1; j <= lenb; j++) {
            // 算法中 a, b 字符串下标从 1 开始，c 语言从 0 开始，所以 -1
            if (a[i-1] == b[j-1]) {
                d[i][j] = d[i-1][j-1];
            } else {
                d[i][j] = min_of_three(d[i-1][j]+1, d[i][j-1]+1, d[i-1][j-1]+1);
            }
        }
    }

    return d[lena][lenb];
}
```
