### c++可以使用<sstream>库解决字符串流的问题：  
C++引入了ostringstream、istringstream、stringstream这三个类，要使用他们创建对象就必须包含<sstream>这个头文件。
[link](https://www.cnblogs.com/gamesky/archive/2013/01/09/2852356.html)

---

## 字符串相关问题：
* 用STL字符串库有geek解的题目
* 字符串变形：
  * 翻转之类的字符串变形：（使用一个或者多个栈翻转字符串）
  * 字符串和排列组合：常见为字符串打印相关(递归全排列法、交换排列法)
* 字符串查找：
  * 无重复、子串相关问题（使用hash记录位置）
  * 如查找第一次出现的 （常见使用 hash存储、额外数组存储）
  * 匹配括号问题；（使用栈）
* 字符串匹配：
  * 字符串的匹配（通常用DP解字符串匹配问题）
* 字符串和整数间的转换：
  * 字符串转整数
  * 整数转字符串
* 回文问题；（常见是使用DP来解决回文问题，判断回文有专门的dp递推式）

---

### Hash和String相关题目


#### 387. First Unique Character in a String
解题思路：  
* 只要用哈希表建立每个字符和其出现次数的映射<字符char, 出现次数int>。
* 然后按顺序遍历字符串，找到第一个出现次数为1的字符，返回其位置即可，参见代码如下：


#### 30. Substring with Concatenation of All Words

解题思路：  
这道题让我们求串联所有单词的子串，就是说给定一个长字符串，再给定几个长度相同的单词，让我们找出串联给定所有单词的子串的起始位置，还是蛮有难度的一道题。这道题我们需要用到两个哈希表，第一个哈希表先把所有的单词存进去，然后从开头开始一个个遍历，停止条件为当剩余字符个数小于单词集里所有字符的长度。这时候我们需要定义第二个哈希表，然后每次找出给定单词长度的子串，看其是否在第一个哈希表里，如果没有，则break，如果有，则加入第二个哈希表，但相同的词只能出现一次，如果多了，也break。如果正好匹配完给定单词集里所有的单词，则把i存入结果中，具体参见代码如下：
```cpp
class Solution {
public:
    vector<int> findSubstring(string s, vector<string>& words) {
        vector<int> res;
        if (s.empty() || words.empty()) return res;
        int n = words.size(), m = words[0].size();
        unordered_map<string, int> m1;
        for (auto &a : words) ++m1[a];
        for (int i = 0; i <= (int)s.size() - n * m; ++i) {
            unordered_map<string, int> m2;
            int j = 0;
            for (j = 0; j < n; ++j) {
                string t = s.substr(i + j * m, m);
                if (m1.find(t) == m1.end()) break;
                ++m2[t];
                if (m2[t] > m1[t]) break;
            }
            if (j == n) res.push_back(i);
        }
        return res;
    }
};
```

### 用STL字符串库有geek解的题目

#### 165. Compare Version Numbers（sstream拆分带'.'的字符串）
Compare two version numbers version1 and version2.  
If version1 > version2 return 1, if version1 < version2 return -1, otherwise return 0.  

You may assume that the version strings are non-empty and contain only digits and the .   character.  
The . character does not represent a decimal point and is used to separate number sequences.  
For instance, 2.5 is not "two and a half" or "half way to version three", it is the fifth   second-level revision of the second first-level revision.  

Here is an example of version numbers ordering:  

0.1 < 1.1 < 1.2 < 13.37  

解题思路：  
由于这道题我们需要将版本号以’.'分开，那么我们可以借用强大的字符串流stringstream的功能来实现分段和转为整数，使用这种方法写的代码很简洁，如下所示：

```cpp
class Solution {
public:
    int compareVersion(string version1, string version2)
    {
        istringstream v1(version1 + "."), v2(version2 + ".");
        int d1 = 0, d2 = 0;
        char dot = '.';
        //.good()判断流是否还有效，即是否还有数据可以读取
        while (v1.good() || v2.good())
        {
            //使用istringstream拆分数字和dot
            if (v1.good())
            {
                v1 >> d1 >> dot;
            }
            if (v2.good())
            {
                v2 >> d2 >> dot;
            }
            if (d1 > d2)
            {
                return 1;
            }
            else if (d1 < d2)
            {
                return -1;
            }
            d1 = d2 = 0;
        }
        return 0;
    }
};
```

---

### 字符串查找匹配：

#### 3. Longest Substring Without Repeating Characters（最长无重复子串：数组模拟hash table）
* 建立一个256位大小的整型数组来代替哈希表，这样做可以记录256个字符。
* 然后我们需要定义两个变量res和left，其中res用来记录最长无重复子串的长度，left指向该无重复子串左边的起始位置。
* 然后我们遍历整个字符串，对于每一个遍历到的字符：
  * 如果哈希表中该字符串对应的值为0，说明没有遇到过该字符，则此时更新最长无重复子串，i - left + 1，其中i是最长无重复子串最右边的位置，left是最左边的位置.
  * 还有一种情况也需要计算最长无重复子串，就是当哈希表中的值小于left，这是由于此时出现过重复的字符，left的位置更新了，如果又遇到了新的字符，就要重新计算最长无重复子串。
* 最后每次都要在哈希表中将当前字符对应的值赋值为i+1，这样就可以在hash中存储对应字符的下一个字符位置，如果当前字符重复，则直接可以将left移动到当前重复字符的下一个字符位置。代码如下：
```cpp
class Solution {
public:
    int lengthOfLongestSubstring(string s)
    {
        int m[256] = {0}, res = 0, left = 0;
        for (int i = 0; i < s.size(); ++i)
        {
            if (m[s[i]] == 0 || m[s[i]] < left)
            {
                res = max(res, i - left + 1);
            }
            else
            {
                left = m[s[i]];
            }
            m[s[i]] = i+1;
        }
        return res;
    }
};
```

#### 49. Group Anagrams(hash table标识错位词)
解题思路''':
这道题让我们群组给定字符串集中所有的错位词，所谓的错位词就是两个字符串中字母出现的次数都一样，只是位置不同，比如abc，bac, cba等它们就互为错位词.
* 如果把错位词的字符顺序重新排列，那么会得到相同的结果，所以重新排序是判断是否互为错位词的方法。
* 由于错位词重新排序后都会得到相同的字符串，因此使用hash table的方法<string, vector<string>>，将所有错位词都保存到字符串数组中，建立key和字符串数组之间的映射，最后再存入结果res中即可。参考代码如下：

```cpp
class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        //使用unordered_map保存错位词排序结果和所有相同错位词的映射
        vector<vector<string>> res;
        unordered_map<string, vector<string>> m;
        for (string str : strs)
        {
            //将排序后的字符串作为key，则可以将相同的错位词保存在同一个<string, vector<string>>中
            string t = str;
            sort(t.begin(), t.end());
            m[t].push_back(str);
        }
        for (auto a : m)
        {
            res.push_back(a.second);
        }
        return res;
    }
};
```

#### 76. Minimum Window Substring(hash table+滑动窗口匹配)
解题思路：  
这道题的要求是要在O(n)的时间度里实现找到这个最小窗口字串，那么暴力搜索Brute Force肯定是不能用的，我们可以考虑哈希表，其中key是T中的字符，value是该字符出现的次数。
* 我们最开始先扫描一遍T，把对应的字符及其出现的次数存到哈希表中。

* 然后开始遍历S，遇到T中的字符，就把对应的哈希表中的value减一，直到包含了T中的所有的字符，纪录一个字串并更新最小字串值。

* 将子窗口的左边界向右移，略掉不在T中的字符，如果某个在T中的字符出现的次数大于哈希表中的value，则也可以跳过该字符。

```cpp
class Solution {
public:
    string minWindow(string S, string T) {
        //处理边界条件
        if (T.size() > S.size())
        {
             return "";
        }
        //声明字符串子串问题的辅助变量：1.左边界守卫、计数器
        //使用hash table
        string res = "";
        int left = 0, count = 0, minLen = S.size() + 1;
        unordered_map<char, int> m;
        for (int i = 0; i < T.size(); ++i)
        {
            if (m.find(T[i]) != m.end())
            {
                 ++m[T[i]];
            }
            else
            {
                m[T[i]] = 1;
            }
        }
        //遍历字符串S
        for (int right = 0; right < S.size(); ++right)
        {
            if (m.find(S[right]) != m.end())
            {
                --m[S[right]];
                if (m[S[right]] >= 0)
                {
                    ++count;
                }
                //如果窗口已经覆盖字符串T，此时count == T.size()
                while (count == T.size())
                {
                    //如果当前窗口值小于记录中最小窗口值，则更新答案
                    if (right - left + 1 < minLen)
                    {
                        minLen = right - left + 1;
                        res = S.substr(left, minLen);
                    }
                    //更新窗口左边界
                    if (m.find(S[left]) != m.end())
                    {
                        ++m[S[left]];
                        if (m[S[left]] > 0)
                        {
                            --count;
                        }
                    }
                    ++left;
                }
            }
        }
        return res;
    }
};
```

#### 035 第一个只出现一次的字符位置(数组模拟hash table)
解题思路：  
  bitmap方法-同计数法，略微有变动。我们计数数组不简单的存储计数。
  * 声明两个size=26的数组分别存放a-z和A-Z在字符串中出现的情况
  * 只出现一次的字符，则存储这个字符在字符串中出现的位置。
  * 出现多次的字符，就存储标识-1，因此查找数组中非-1的最小值即可。

```cpp
class Solution {
public:
        int FirstNotRepeatingChar(string V) {
                int E[26] = { 0 }, E2[26] = { 0 };
                int S;

                S = V.size();
                for (int i = 0; i < S; ++i) {
                        if ('a' <= V[i] && V[i] <= 'z') {
                                int j = V[i] - 'a';
                                if (E[j] == 0) {
                                        E[j] = i + 1;
                                }
                                else {
                                        E[j] = -1;
                                }
                        }
                        else if ('A' <= V[i] && V[i] <= 'Z') {
                                int j = V[i] - 'A';
                                if (E2[j] == 0) {
                                        E2[j] = i + 1;
                                }
                                else {
                                        E2[j] = -1;
                                }
                        }
                }

                int res = INT_MAX;
                for (int i = 0; i < 26; ++i)
                {
                        if (E[i] != 0 && E[i] != -1)
                        {
                                res = min(res, E[i]);
                        }
                        if (E2[i] != 0 && E2[i] != -1)
                        {
                                res = min(res, E2[i]);
                        }
                }
                return res > V.size() ? -1 : res - 1;
        }


};
```

#### 383. Ransom Note（字符存放在hash table中的查找问题）
Given an arbitrary ransom note string and another string containing letters from all the magazines, write a function that will return true if the ransom note can be constructed from the magazines ; otherwise, it will return false.  

Each letter in the magazine string can only be used once in your ransom note.  

Note:  
You may assume that both strings contain only lowercase letters.  

canConstruct("a", "b") -> false  
canConstruct("aa", "ab") -> false  
canConstruct("aa", "aab") -> true  

解题思路：  
用哈希Map存储待查字符串，然后遍历目标字符串，对hash map进行查找和更新value。
最后如果遍历完时，没有出现value值小于零，则说明可以。

```cpp
class Solution {
public:
    bool canConstruct(string ransomNote, string magazine) {
        unordered_map<char, int> m;
        //将待查字符串中的字符存放到hash table中
        for (char c : magazine)
        {
            ++m[c];
        }
        for (char c : ransomNote)
        {
            if (--m[c] < 0)
            {
                return false;
            }
        }
        return true;
    }
};
```

#### 387. First Unique Character in a String
Given a string, find the first non-repeating character in it and return it's index. If it doesn't exist, return -1.  

Examples:  

s = "leetcode"  
return 0.  

s = "loveleetcode",  
return 2.  

解题思路：  
* 用哈希表建立每个字符和其出现次数的映射。
* 然后按顺序遍历字符串，找到第一个出现次数为1的字符，返回其位置即可，参见代码如下：
```cpp
class Solution {
public:
    int firstUniqChar(string s) {
        unordered_map<char, int> m;
        //先用hash map统计字符串中每个字符出现的次数
        for (char c : s) ++m[c];
        //然后按序遍历字符串找到以第一个map中value为1的字符
        for (int i = 0; i < s.size(); ++i) {
            if (m[s[i]] == 1) return i;
        }
        return -1;
    }
};
```

#### 434. Number of Segments in a String
Count the number of segments in a string, where a segment is defined to be a contiguous sequence of non-space characters.  

Please note that the string does not contain any non-printable characters.  

Example:  

Input: "Hello, my name is John"  
Output: 5  

解题思路：   
* 按序遍历字符串。
* 每次遇到新单词时,res加一，然后往后遍历到单词结尾处。
* 然后再寻找下一个单词第一个字符，寻找过程中如果遇到空格直接跳过，如果不是空格，则计数器加1，然后用个while循环找到下一个空格的位置，这样就遍历完了一个单词，再重复上面的操作直至结束，就能得到正确结果：
```cpp
class Solution {
public:
    int countSegments(string s) {
        int res = 0, n = s.size();
        for (int i = 0; i < n; ++i)
        {
            if (s[i] == ' ')
            {
              continue;
            }
            ++res;
            while (i < n && s[i] != ' ')
            {
               ++i;
            }
        }
        return res;
    }
};
```

#### 20. Valid Parentheses(括号字符串匹配:栈匹配)
这道题让我们验证输入的字符串是否为括号字符串，包括大括号，中括号和小括号。
* 用一个栈，从开始遍历输入字符串。
  * 如果当前字符为左半边括号时，则将其压入栈中。
  * 如果遇到右半边括号时，若此时栈为空，则直接返回false，如不为空，则取出栈顶元素，若为对应的左半边括号，则继续循环，反之返回false，代码如下：
```cpp
class Solution {
public:
    bool isValid(string s) {
        //声明辅助栈，用来括号匹配
        stack<char> parentheses;
        for (int i = 0; i < s.size(); ++i) {
            if (s[i] == '(' || s[i] == '[' || s[i] == '{')
            {
                parentheses.push(s[i]);
            }
            else
            {
                if (parentheses.empty())
                {
                     return false;
                }
                else if (s[i] == ')' && parentheses.top() != '(')
                {
                    return false;
                }
                else if (s[i] == ']' && parentheses.top() != '[')
                {
                    return false;
                }
                else if (s[i] == '}' && parentheses.top() != '{')
                {
                    return false;
                }
                else
                {
                    parentheses.pop();
                }

            }
        }
        return parentheses.empty();
    }
};
```

#### 32. Longest Valid Parentheses(最长有效括号字符串序列)栈+最大值结果记录
解题思路：  
* 最长有效括号比之前那道 Valid Parentheses 验证括号难度要大一些，这里我们还是借助栈来求解，然后还需要定义个start变量来记录合法括号串的起始位置。
* 我们遍历字符串，如果遇到左括号，则将当前下标压入栈，如果遇到右括号，如果当前栈为空，则将下一个坐标位置记录到start，如果栈不为空，则将栈顶元素取出，此时若栈为空，则更新结果和i - start + 1中的较大值，否则更新结果和i - 栈顶元素中的较大值，代码如下：
```cpp
class Solution {
public:
    int longestValidParentheses(string s)
    {
        //还是用栈匹配有效括号
        //然后使用res记录最长有效括号，每次有右括号时，更新res的值
        int res = 0, start = 0;
        stack<int> m;
        for (int i = 0; i < s.size(); ++i)
        {
            if (s[i] == '(')
            {
                m.push(i);
            }
            else if (s[i] == ')')
            {
                if (m.empty())
                {
                    start = i + 1;
                }
                else
                {
                    m.pop();
                    res = m.empty() ? max(res, i - start + 1) : max(res, i - m.top());
                }
            }
        }
        return res;
    }
};
```

#### 91. Decode Ways'(Dp字符串匹配)
A message containing letters from A-Z is being encoded to numbers using the following mapping:  
'A' -> 1  
'B' -> 2  
...  
'Z' -> 26  
Given an encoded message containing digits, determine the total number of ways to decode it.  

For example,  
Given encoded message "12", it could be decoded as "AB" (1 2) or "L" (12).  

The number of ways decoding "12" is 2.  

解题思路：  
* 这道题要求解码方法，跟之前那道 Climbing Stairs 爬梯子问题 非常的相似，但是还有一些其他的限制条件，比如说一位数时不能为0，两位数不能大于26，其十位上的数也不能为0，出去这些限制条件，根爬梯子基本没啥区别，需要用动态规划Dynamci Programming来解。
* 建立一位dp数组，长度比输入数组长多多2，全部初始化为1，因为斐波那契数列的前两项也为1，然后从第三个数开始更新，对应数组的第一个数。
* 对每个数组首先判断其是否为0，若是将改为dp赋0，若不是，赋上一个dp值，此时相当如加上了dp[i - 1], 然后看数组前一位是否存在，如果存在且满足前一位不是0，且和当前为一起组成的两位数不大于26，则当前dp值加上dp[i - 2], 至此可以看出来跟斐波那契数组的递推式一样，代码如下：
```cpp
class Solution {
public:
    int numDecodings(string s)
    {
        //处理边界条件
        if (s.empty() || (s.size() > 1 && s[0] == '0'))
        {
            return 0;
        }
        //声明dp数组
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
        //声明二维dp数组
        int dp[T.size() + 1][S.size() + 1];
        //初始化dp数组的边界值
        for (int i = 0; i <= S.size(); ++i)
        {
             dp[0][i] = 1;  
        }
        for (int i = 1; i <= T.size(); ++i)
        {
             dp[i][0] = 0;
        }
        for (int i = 1; i <= T.size(); ++i)
        {
            for (int j = 1; j <= S.size(); ++j)
            {
                dp[i][j] = dp[i][j - 1] + (T[i - 1] == S[j - 1] ? dp[i - 1][j - 1] : 0);
            }
        }
        return dp[T.size()][S.size()];
    }
};
```




#### 14. Longest Common Prefix

解题思路：  
这道题让我们求一系列字符串的共同前缀，没有什么特别的技巧，无脑查找即可。
* 我们定义两个变量i和j，其中i是遍历搜索字符串中的字符，j是遍历字符串集中的每个字符串。
* 这里将单词上下排好，则相当于一个各行长度有可能不相等的二维数组，我们遍历顺序和一般的横向逐行遍历不同，而是采用纵向逐列遍历。我们每次取出第一个字符串的某一个位置的单词，然后遍历其他所有字符串的对应位置看是否相等。
  * 在遍历的过程中，如果某一行没有了，说明其为最短的单词，因为共同前缀的长度不能长于最短单词，所以此时返回已经找出的共同前缀。
  * 如果有不满足的直接返回res。
  * 如果都相同，则将当前字符存入结果，继续检查下一个位置的字符，参见代码如下：
```cpp
class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        //判断边界条件
        if (strs.empty())
        {
            return "";
        }
        string res = "";
        for (int j = 0; j < strs[0].size(); ++j) {
            char c = strs[0][j];
            //按纵列同时遍历每一行的每个单词
            for (int i = 1; i < strs.size(); ++i) {
                //如果当前行的长度小于j，或者当前行的第j个字符值strs[i][j] != c
                if (j >= strs[i].size() || strs[i][j] != c)
                {
                    return res;
                }
            }
            res.push_back(c);
        }
        return res;
    }
};
```

#### 696. Count Binary Substrings(按顺序遍历字符串再筛选子串的问题)

* 分别统计0和1的个数，而且如果当前遇到的是1，那么只要之前统计的0的个数大于当前1的个数，就一定有一个对应的子字符串。
* 而一旦前一个数字和当前的数字不一样的时候，那么当前数字的计数要重置为1。
* 所以我们遍历元数组，如果是第一个数字，那么对应的ones或zeros自增1。
* 然后进行分情况讨论，如果当前数字是1，然后判断如果前面的数字也是1，则ones自增1，否则ones重置为1。如果此时zeros大于ones，res自增1。反之同理，如果当前数字是0，然后判断如果前面的数字也是0，则zeros自增1，否则zeros重置为1。如果此时ones大于zeros，res自增1。参见代码如下：

```cpp
class Solution {
public:
    int countBinarySubstrings(string s)
    {
        int zeros = 0, ones = 0, res = 0;
        for (int i = 0; i < s.size(); ++i)
        {
            if (i == 0)
            {
                (s[i] == '1') ? ++ones : ++zeros;
            }
            else
            {
                if (s[i] == '1')
                {
                    ones = (s[i - 1] == '1') ? ones + 1 : 1;
                    if (zeros >= ones)
                    {
                        ++res;
                    }
                }
                else if (s[i] == '0')
                {
                    zeros = (s[i - 1] == '0') ? zeros + 1 : 1;
                    if (ones >= zeros)
                    {
                        ++res;
                    }
                }
            }
        }
        return res;
    }
};
```




---

### 字符串变形：

#### 344. Reverse String（双指针变形字符串）
Write a function that takes a string as input and returns the string reversed.  
Example:  
Given s = "hello", return "olleh".  
这道题没什么难度，直接从两头往中间走，同时交换两边的字符即可，参见代码如下：
```cpp
class Solution {
public:
    string reverseString(string s) {
        int left = 0, right = s.size() - 1;
        while (left < right) {
            char t = s[left];
            s[left++] = s[right];
            s[right--] = t;
        }
        return s;
    }
};
```

#### 345. Reverse Vowels of a String（双指针+额外判定 变形字符串）
Write a function that takes a string as input and reverse only the vowels of a string.  

Example 1:  
Given s = "hello", return "holle".  

Example 2:  
Given s = "leetcode", return "leotcede".  

解题思路：  
这道题让我们翻转字符串中的元音字母，元音字母有五个a,e,i,o,u，需要注意的是大写的也算，所以总共有十个字母。
* 我们写一个isVowel的函数来判断当前字符是否为元音字母。
* 如果两边都是元音字母，那么我们交换。
* 如果左边的不是，向右移动一位，如果右边的不是，则向左移动一位，参见代码如下：
```cpp
class Solution {
public:
    string reverseVowels(string s) {
        int left = 0, right= s.size() - 1;
        while (left < right) {
            if (isVowel(s[left]) && isVowel(s[right])) {
                swap(s[left++], s[right--]);
            } else if (isVowel(s[left])) {
                --right;
            } else {
                ++left;
            }
        }
        return s;
    }
    bool isVowel(char c) {
        return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' || c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U';
    }
};
```

#### 042 翻转单词顺序列

**解题思路**：  
字符串逆序就是使用栈的FILO性质，如果是按单词的字符串逆序则使用双栈进行，先逆序单词然后进第二个栈逆序整个句子。

```cpp
class Solution
{
public:
    string ReverseSentence(string str)
    {
        if (str.size() == 0)
        {
            return str;
        }

        string result;
        stack<char>stk1;
        stack<char>stk2;

        for (auto i : str)
        { //把str中的全部压入
            stk1.push(i);
        }
        //  通过将字符串压入栈中, 现在出栈顺序正好是入展顺序的逆序
        //  即我们实现了一次整个字符串的翻转

        //  接下来我们翻转每个单词
        //  只要不是空格就一直入栈(实现翻转)
        //  遇见空格的时候，就读取栈中元素(出栈的顺序正好是每个单词的顺序)
        result = "";
        while (!stk1.empty())
        {
            if (stk1.top() != ' ')
            {   //没有遇到空格 就再弹出 压到第二个栈
                stk2.push(stk1.top());
                stk1.pop();
            }
            else
            {   //如果遇到了空格 一个单词结束了  将第二个栈里的弹出
                stk1.pop();
                while (!stk2.empty())
                {
                    result += stk2.top();
                    stk2.pop();
                }
                result += " ";
            }
        }
        //将第二个栈剩余的单词输出
        while (!stk2.empty()) {
            result += stk2.top();
            stk2.pop();
        }
        return result;
    }
};
```


#### *012 打印1到最大的N位数
**(关于字符串排列组合输出的样板题)**

题目描述  
给定一个数字N，打印从1到最大的N位数。输入每个输入文件仅包含一组测试样例。
对于每个测试案例，输入一个数字N(1<=N<=5)。 输出 对应每个测试案例，依次打印从1到最大的N位数。  

样例输入：  
1  
样例输出：  
1 2 3 4 5 6 7 8 9

##### 解题思路：
对于打印字符串排列组合的相关问题，应该考虑使用递归全排列或者交换排列的方法。  
本题要打印1到N位的所有数，可以递归全排列数的每一位。数字大小低于N位的数字会被高位排0的排序情况表示。  

```cpp
class Solution {
public:
        void PrintToMaxOfDigits(int N) {
                if (N <= 0) {
                        return;
                }

                char* E = new char[N + 1];
                E[N] = '\0';

                for (int i = 0; i < 10; ++i) {
                        E[0] = i + '0';
                        Recursion(E, N, 2);
                }

                delete[] E; //手动申请空间需要手动释放
       }

        void Recursion(char* E, int S, int P) {
                if (P == S) {
                        PrintNumber(E);
                        return;
                }

                for (int i = 0; i < 10; ++i) {
                        E[P - 1] = i + '0';
                        Recursion(E, S, P + 1);
                }
        }

        void PrintNumber(char* E) {
                int S, i;
                S = strlen(E);
                i = 0;

                for (; i < S; ++i) {
                        if (E[i] != '0') {
                                break;
                        }
                }

                if (i != S) {
                        cout << &E[i] << endl;
                }
        }
};
```

#### 17. Letter Combinations of a Phone Number（求字符串排列组合的所有情况应该递归DFS+字典）
解题思路：  
这道题让我们求电话号码的字母组合，即数字2到9中每个数字可以代表若干个字母，然后给一串数字，求出所有可能的组合。
* 我们用递归Recursion来解。
* 此外因为是从字符串待选项中pick排列组合的元素，所有需要建立一个字典(hash)，用来保存每个数字所代表的字符串。
* 然后我们还需要一个变量level，记录当前生成的字符串的字符个数，实现套路和上述那些题十分类似，代码如下：
```cpp
class Solution {
public:
    vector<string> letterCombinations(string digits)
    {
        //判断边界条件
        vector<string> res;
        if (digits.empty())
        {
            return res;
        }
        //创建字典数组
        string dict[] = {"abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
        //进入递归主体
        letterCombinationsDFS(digits, dict, 0, "", res);
        return res;
    }
    void letterCombinationsDFS(string digits, string dict[], int level, string out, vector<string> &res)
    {
        //dfs递归出口
        if (level == digits.size())
        {
             res.push_back(out);
        }
        else
        {
            string str = dict[digits[level] - '2'];
            //每层的每个字符可以分叉出k个递归
            for (int i = 0; i < str.size(); ++i)
            {
                out.push_back(str[i]);
                letterCombinationsDFS(digits, dict, level + 1, out, res);
                out.pop_back();
            }
        }
    }
};
```
---

### 字符串和整数间的转换：

#### 049 把字符串转换成整数

题目描述

写一个函数，求两个整数之和，要求在函数体内不得使用四则运算符号。

> 样例输入  
1a33  
-2147483648

> 样例输出  
0  
-2147483648

##### 解题思路：  
这题主要要注意string To vector时的边界条件，是一道不错的面试题。  

字符串转化为数字时需要注意：
* 排除字符串前面的空白字符
* 判断字符串的符号位
* 判断是否溢出，使用INT_MAX和INT_MIN关键字

```cpp
#include <iostream>
using namespace std;

class Solution
{
public:
    int StrToInt(string V)
    {
        //string使用迭代器遍历
        string::iterator P;
        bool F;
        long long int RES; //保存int大小的数值，需要用到至少long int的变量

        P = V.begin( );
        while (*P == ' ')
        {
            P++;
        }

        F= false;
        //  判断符号位
        if (*P == '+')
        {
            P++;
        }
        else if (*P == '-')
        {
            P++;
            F = true;
        }

        RES = 0;
        for (; P != V.end( ); P++)
        {
            if ('0' <= *P && *P <= '9')
            {
                RES *= 10;
                RES += *P - '0';
            }
            else
            {
                break;
            }

            //  解决OVER_FLOW的问题
            //  INT_MAX     2147483647
            //  INT_MIN     -2147483648  F = true
            //  负数绝对值最大为INT_MAX + 1
            //  正数最大值为INT_MAX
            if((F == true  && RES > (unsigned long)(INT_MAX) + 1)     
              || (F == false && RES > INT_MAX))                         
            {
                break;
            }

        }

        //如果P没遍历到字符串尾部说明字符串转整数失败
        //要么是字符串中有非0-9的数值
        //要么字符串代表的数值溢出了
        if(P != V.end( ))
        {
            return 0;
        }
        else
        {

            if (F == true)
            {
                RES = -RES;
            }

            if (RES >= INT_MAX)
            {
                RES = INT_MAX;
            }
            else if (RES <= INT_MIN)
            {
                RES = INT_MIN;
            }

            return (int)RES;

        }
    }
};
```

####* 054-表示数值的字符串
题目描述  
请实现一个函数用来判断字符串是否表示数值（包括整数和小数）。例如，字符串"+100","5e2","-123","3.1416"和"-1E-16"都表示数值。 但是"12e","1a3.14","1.2.3","+-5"和"12e+4.3"都不是。


解题思路：  
* 直白解题方法：**（字符串遍历匹配）**  
此题径直的解法就是直接按照题目中个自己对数值字符串格式的理解，从头到尾地匹配给定字符串。

我们首先分析一下子可能是数值的字符串的格式 在数值之前可能有一个表示正负的’-‘或者’+’。 接下来是若干个0到9的数位表示数值的整数部分（在某些小数里可能没有数值的整数部分）。 如果数值是一个小数，那么在小数点后面可能会有若干个0到9的数位表示数值的小数部分。如果数值用科学计数法表示，接下来是一个’e’或者‘E’，以及紧跟着的一个整数（可以有正负号）表示指数。 　　 判断一个字符串是否符合上述模式时，

* 首先看第一个字符是不是正负号。
* 如果是，在字符串上移动一个字符，继续扫描剩余的字符串中0到9的数位。
* 如果是一个小数，则将遇到小数点。
* 另外，如果是用科学计数法表示的数值，在整数或者小数的后面还有可能遇到’e’或者’E’。

```cpp
class Solution
{
public:
    bool isNumeric(char* str)
    {
        if(str == NULL)
        {
            return false;
        }

        //  可能遇见符号+/-
        if(*str == '+' || *str == '-')
        {
            ++str;
        }

        if(*str == '\0')
        {
            return false;
        }

        bool numberic = true;

        //  把字符串按照e,E和.分成一段或几段数字
        //  那么e,E和.就是分隔符，在段中的每个字符就必须满足'0'~'9'
        //  str指针作为要被ScanDigits修改的参数传入时需要传入str指针自己的地址值
        //  然后ScanDigits(char** str)指向指针的指针接收
        ScanDigits(&str);

        if(*str != '\0')
        {
            if(*str == '.')
            {
                ++str;
                ScanDigits(&str);

                if(*str == 'e' || *str == 'E')
                {
                    numberic = IsExponential(&str);
                }
            }
            else if(*str == 'e' || *str == 'E')
            {
                numberic = IsExponential(&str);
            }
            else
            {

                numberic = false;
            }
        }

        return numberic && *str == '\0';

    }


    void ScanDigits(char **str)
    {
        while(**str != '\0'
          && (**str >= '0' && **str <= '9'))
        {
            ++(*str);
        }
    }

    bool IsExponential(char **str)
    {
        if(**str != 'e' && **str != 'E')
        {
            return false;
        }

        ++(*str);

        if(**str == '+' || **str == '-')
        {
            ++(*str);
        }
        if(**str == '\0')
        {
            return false;
        }
        ScanDigits(str);

        return (**str == '\0') ? true : false;
    }



};
```

---

### 回文问题****：

#### 5. Longest Palindromic Substring（dp解回文串问题）
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

#### 125. Valid Palindrome(带有空格干扰的回文字符串问题)(双指针处理回文串问题)
Given a string, determine if it is a palindrome, considering only alphanumeric characters and ignoring cases.  

For example,  
"A man, a plan, a canal: Panama" is a palindrome.  
"race a car" is not a palindrome.  
解题思路：  
验证回文字符串是比较常见的问题，所谓回文，就是一个正读和反读都一样的字符串，比如“level”或者“noon”等等就是回文串。
* 但是这里，加入了空格和非字母数字的字符，增加了些难度，但其实原理还是很简单：只需要建立两个指针，left和right, 分别从字符的开头和结尾处开始遍历整个字符串。
* 如果遇到非字母数字的字符就跳过，继续往下找，直到找到下一个字母数字或者结束遍历。
* 如果遇到大写字母，就将其转为小写。
* 等左右指针都找到字母数字时，比较这两个字符
  * 若相等，则继续比较下面两个分别找到的字母数字；
  * 若不相等，直接返回false.  
时间复杂度为O(n), 代码如下：
```cpp
class Solution {
public:
    bool isPalindrome(string s)
    {
        int left = 0, right = s.size() - 1 ;
        while (left < right)
        {
            if (!isAlphaNum(s[left])) ++left;
            else if (!isAlphaNum(s[right])) --right;
            else if ((s[left] + 32 - 'a') %32 != (s[right] + 32 - 'a') % 32) return false;
            else
            {
                ++left; --right;
            }
        }
        return true;
    }
    bool isAlphaNum(char &ch)
    {
        if (ch >= 'a' && ch <= 'z') return true;
        if (ch >= 'A' && ch <= 'Z') return true;
        if (ch >= '0' && ch <= '9') return true;
        return false;
    }
};
```

#### 680. Valid Palindrome II(可以修改一次字符串，再判断回文串的问题)
Given a non-empty string s, you may delete at most one character. Judge whether you can make it a palindrome.  

Example 1:  
Input: "aba"  
Output: True  
Example 2:  
Input: "abca"  
Output: True  
Explanation: You could delete the character 'c'.  

解题思路：  
* 这道题是之前那道Valid Palindrome的拓展，还是让我们验证回复字符串，但是区别是这道题的字符串中只含有小写字母，而且这道题允许删除一个字符。
* 那么当遇到不匹配的时候，我们到底是删除左边的字符，还是右边的字符呢，我们的做法是两种情况都要算一遍，只要有一种能返回true，那么结果就返回true。
* 我们可以写一个子函数来判断字符串中的某一个范围内的子字符串是否为回文串，参见代码如下：.

```cpp
class Solution {
public:
    bool validPalindrome(string s) {
        int left = 0, right = s.size() - 1;
        while (left < right)
        {
            if (s[left] != s[right])
            {
                return isValid(s, left, right - 1) || isValid(s, left + 1, right);
            }
            ++left;
            --right;
        }
        return true;
    }
    bool isValid(string s, int left, int right)
    {
        while (left < right)
        {
            if (s[left] != s[right])
            {
                return false;
            }
            ++left;
            --right;
        }
        return true;
    }
};
```

#### 336. Palindrome Pairs（hash table解回文串问题）
Given a list of unique words. Find all pairs of distinct indices (i, j) in the given list, so that the concatenation of the two words, i.e. words[i] + words[j] is a palindrome.  

Example 1:  
Given words = ["bat", "tab", "cat"]  
Return [[0, 1], [1, 0]]  
The palindromes are ["battab", "tabbat"]  

解题思路：  
这道题给我们了许多单词，让我们找出回文对，就是两个单词拼起来是个回文字符串，我最开始尝试的是brute force的方法，每两个单词都拼接起来然后判断是否是回文字符串，但是通过不了OJ，会超时，可能这也是这道题标为Hard的原因之一吧，那么我们只能找别的方法来做，通过学习大神们的解法，发现如下两种方法比较好，其实两种方法的核心思想都一样，写法略有不同而已，那么我们先来看第一种方法吧，要用到哈希表来建立每个单词和其位置的映射，然后需要一个set来保存出现过的单词的长度，算法的思想是，遍历单词集，对于遍历到的单词，我们对其翻转一下，然后在哈希表查找翻转后的字符串是否存在，注意不能和原字符串的坐标位置相同，因为有可能一个单词翻转后和原单词相等，现在我们只是处理了bat和tab的情况，还存在abcd和cba，dcb和abcd这些情况需要考虑，这就是我们为啥需要用set，由于set是自动排序的，我们可以找到当前单词长度在set中的iterator，然后从开头开始遍历set，遍历比当前单词小的长度，比如abcdd翻转后为ddcba，我们发现set中有长度为3的单词，然后我们dd是否为回文串，若是，再看cba是否存在于哈希表，若存在，则说明abcdd和cba是回文对，存入结果中，对于dcb和aabcd这类的情况也是同样处理，我们要在set里找的字符串要在遍历到的字符串的左边和右边分别尝试，看是否是回文对，这样遍历完单词集，就能得到所有的回文对，参见代码如下：

```cpp
class Solution {
public:
    vector<vector<int>> palindromePairs(vector<string>& words) {
        vector<vector<int>> res;
        unordered_map<string, int> m;
        set<int> s;
        for (int i = 0; i < words.size(); ++i) {
            m[words[i]] = i;
            s.insert(words[i].size());
        }
        for (int i = 0; i < words.size(); ++i) {
            string t = words[i];
            int len = t.size();
            reverse(t.begin(), t.end());
            if (m.count(t) && m[t] != i) {
                res.push_back({i, m[t]});
            }
            auto a = s.find(len);
            for (auto it = s.begin(); it != a; ++it) {
                int d = *it;
                if (isValid(t, 0, len - d - 1) && m.count(t.substr(len - d))) {
                    res.push_back({i, m[t.substr(len - d)]});
                }
                if (isValid(t, d, len - 1) && m.count(t.substr(0, d))) {
                    res.push_back({m[t.substr(0, d)], i});
                }
            }
        }
        return res;
    }
    bool isValid(string t, int left, int right) {
        while (left < right) {
            if (t[left++] != t[right--]) return false;
        }
        return true;
    }
};
```
