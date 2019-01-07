### 字符串的查找
多用hash记录历史的方式，加上带左右边界和历史窗口大小记录等的变量，进行字符串的查找(通常都是为了从原字符串中查找出子串)。  

* 查找子串的度 degree of  an array（使用hash表分别记录每个字符的度和收尾出现的位置）
解题思路：  
统计所有数字的首尾出现位置，那么我们再用一个哈希表，建立每个数字和其首尾出现的位置。我们用变量degree来表示数组的度。好，现在我们遍历原数组，累加当前数字出现的次数，当某个数字是第一次出现，那么我们用当前位置的来更新该数字出现的首尾位置，否则只更新尾位置。每遍历一个数，我们都更新一下degree。当遍历完成后，我们已经有了数组的度，还有每个数字首尾出现的位置，下面就来找出现次数为degree的数组，然后计算其首尾位置差加1就是candidate数组的长度，由于出现次数为degree的数字不一定只有一个，我们遍历所有的，找出其中最小的即可，参见代码如下：
```cpp
class Solution {
public:
    int findShortestSubArray(vector<int>& nums)
    {
        int n = nums.size(), res = INT_MAX, degree = 0;
        unordered_map<int, int> m;
        unordered_map<int, pair<int, int>> pos;
        for (int i = 0; i < nums.size(); ++i)
        {
            if (++m[nums[i]] == 1)
            {
                pos[nums[i]] = {i, i};
            }
            else
            {
                pos[nums[i]].second = i;
            }
            degree = max(degree, m[nums[i]]);
        }
        for (auto a : m)
        {
            if (degree == a.second)
            {
                res = min(res, pos[a.first].second - pos[a.first].first + 1);
            }
        }
        return res;
    }
};
```


### 字符串的枚举、生成
* 使用dfs枚举字符串的时候，应该合理地传递bottom-up的参数，按值传递、按引用传递。  
* 像括号字符串问题的，多是使用栈完成。

### 字符串的匹配
像回文串系列的题目，是字符串的匹配题目。字符串匹配应当划分子问题 然后使用dp.

* Longest Palindromic Substring(子串)：  

```cpp
class Solution {
public:
    string longestPalindrome(string s)
    {
        //初始化二维dp数组和一些辅助变量
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

* Longest Palindromic Subsequence(子序列)

```cpp
class Solution {
public:
    int longestPalindromeSubseq(string s) {
        int n = s.size();
        vector<vector<int>> dp(n, vector<int>(n));
        for (int i = n - 1; i >= 0; --i) {
            dp[i][i] = 1;
            for (int j = i + 1; j < n; ++j)
            {
                if (s[i] == s[j])
                {
                    dp[i][j] = dp[i + 1][j - 1] + 2;
                }
                else
                {
                    dp[i][j] = max(dp[i + 1][j], dp[i][j - 1]);
                }
            }
        }
        return dp[0][n - 1];
    }
};
```
