#### c++的io操作：  
* 基于控制台的io: 需要inlcude iostream
    * 命令包括istream读,ostream写,iostream
* 基于文件的io: 需要include fstream
    *命令包括ifstream读,ofstream写, fstream
* 基于字符串的io: 需要Inlcude sstream**主要用于类型转换**
    * 命令包括istringstream, ostringstream, stringstream


#### 常见字符串题型以及对应的解题思路

1. 字符串的查找： 多用hash记录历史的方式，加上带左右边界和历史窗口大小记录等的变量，进行字符串的查找(通常都是为了从原字符串中查找出子串)。  

2. 字符串的枚举、生成： 多使用dfs枚举字符串。  

3. 像括号字符串问题的：多是使用栈完成。

4. 字符串匹配： 像回文串系列的题目，是字符串的匹配题目。字符串匹配应当划分子问题 然后使用dp.


-------------


### 常见例题


#### 删除字符串的ac和b：
```cpp
#include <iostream>
using namespace std;

void delete_chars(char * str)
{
	int location = 0;
	int i = 0;

    while( str[i] != '\0'){
        if(str[i] != 'b'){
            str[location] = str[i];
            if(location == 0){
                location++;
                i++;
                continue;
            }
            if (str[location] == 'c' 
                && str[location -1] == 'a' )
                location--;
            else
                location++;
		}		
	    i++;
    }
    str[location] = '\0';
}

int main()
{
	char s[20] = "caaccbacd";
	delete_chars(s);
	cout<<s<<endl;
	system("pause()");
	return 0;
}
```

#### 字符串中最长不重复子串substring（必须连续）的长度
给定一字符串只包含数字，请写一个算法，找出该字符串中的最长不重复子串（不重复是指子串中每一元素不同于子串中其他元素）
如：“120135435”最长不重复子串为 “201354”
```cpp
int lengthOfLongestSubstring(string s) {
        vector<int> dict(256, -1);
        int maxLen = 0, start = -1;
        for (int i = 0; i != s.length(); i++) {
            if (dict[s[i]] > start)
                start = dict[s[i]];
            dict[s[i]] = i;
            maxLen = max(maxLen, i - start);
        }
        return maxLen;
    }
```

#### 字符串中出现次数最多的字符
```cpp
#include<stdio.h>
#include<stdlib.h>
//统计字符串中出现次数最多的字母，如果字母出现次数相同，则按a-z字典序输出第一个。
int countCharacter(const char * str)
{
	int i=0,max=str[0]-'a';
	int num[26]={0};
	while(str[i] != '\0')
	{
		int x = str[i]-'a';
		num[x]++;
		if(num[x] > num[max])
		{
			max=x;
			i++;
		}
        else if(num[x] == num[max] && x < max){
			max=x;
			i++;
		}
        else
			i++;
	}
	return max;
}
 
int main()
{
	int re;
	const char *str = (char *)malloc(sizeof(char)*100);
	printf("input:");
	scanf("%s",str);
	re = countCharacter(str);
	printf("output:%c\n",'a'+re);
	return 0;
}

```



#### 最长回文子串：

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
                //即：(当前子串的两端字符是否相等 
                // && (子串长度为1或者2 
                // || 子串包含的子串[i+1 : j-1]是否是回文串)
                dp[i][j] = (s[i] == s[j] 
                    && (j - i < 2  || dp[i + 1][j - 1]));
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

#### 2.最长回文子序列（可不连续）
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
                    dp[i][j] = dp[i + 1][j - 1] + 2;
                else
                    dp[i][j] = max(dp[i + 1][j], dp[i][j - 1]);
            }
        }
        return dp[0][n - 1];
    }
};
```

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


#### 字符串中第一个无重复字符的位置

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

#### 字符串中单词的个数

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
              continue;
            ++res;
            while (i < n && s[i] != ' ')
               ++i;
        }
        return res;
    }
};
```

#### 字符串的括号是否匹配

1. 用一个栈，从开始遍历输入字符串。
2. 如果当前字符为左半边括号时，则将其压入栈中。
3. 如果遇到右半边括号时，若此时栈为空，则直接返回false。
4. 如不为空，则取出栈顶元素，若为对应的左半边括号，则继续循环，反之返回false，代码如下：
```cpp
class Solution {
public:
    bool isValid(string s) {
        //声明辅助栈，用来括号匹配
        stack<char> parentheses;
        for (int i = 0; i < s.size(); ++i) {
            if (s[i] == '(' || s[i] == '[' || s[i] == '{')
                parentheses.push(s[i]);
            else
            {
                if (parentheses.empty())
                     return false;
                else if (s[i] == ')' && parentheses.top() != '(')
                    return false;
                else if (s[i] == ']' && parentheses.top() != '[')
                    return false;
                else if (s[i] == '}' && parentheses.top() != '{')
                    return false;
                else
                    parentheses.pop();
            }
        }
        return parentheses.empty();
    }
};
```

#### 最长有效括号字符串序列
  
1. 还是借助栈来求解。
2. 然后还需要定义个start变量来记录当前合法括号串的起始位置。
3. 遍历字符串。
4. 如果遇到左括号，则将当前下标压入栈。
5. 如果遇到右括号
    * 如果当前栈为空，则将下一个坐标位置记录到start。
    * 如果栈不为空，则将栈顶元素取出，此时若栈为空，则更新结果和i - start + 1中的较大值，否则更新结果和i - 栈顶元素中的较大值，代码如下：
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
                m.push(i);
            else if (s[i] == ')')
            {
                if (m.empty())
                    start = i + 1;
                else
                {
                    m.pop();
                    res = m.empty() ? max(res, i - start + 1) : 
                        max(res, i - m.top());
                }
            }
        }
        return res;
    }
};
```


#### 14. 最长公共前缀
Input: ["flower","flow","flight"]  
Output: "fl"

解题思路：  
1. 没有什么特别的技巧，顺序查找即可。
2. 定义两个变量i和j，其中i是遍历搜索字符串中的字符，j是遍历字符串集中的每个字符串。
3. 首先将单词上下排好，则相当于一个各行长度有可能不相等的二维数组。
4. 采用纵向逐列遍历。我们每次取出第一个字符串的某一个位置的单词，然后遍历其他所有字符串的对应位置看是否相等。
5. 在遍历的过程中，如果某一行没有了，说明其为最短的单词，因为共同前缀的长度不能长于最短单词，所以此时返回已经找出的共同前缀。
```cpp
class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        //判断边界条件
        if (strs.empty())
            return "";

        string res = "";
        for (int j = 0; j < strs[0].size(); ++j) {
            char c = strs[0][j];
            for (int i = 1; i < strs.size(); ++i) 
                if (j >= strs[i].size() || strs[i][j] != c)
                    return res;
            res.push_back(c);
        }
        return res;
    }
};
```


#### 翻转整个字符串
  
Given s = "hello world", return "dlrow olleh".  
1. 直接从两头往中间走，同时交换两边的字符即可，参见代码如下
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

#### 翻转字符串中的元音对

Example 1:  
Given s = "hello", return "holle".  

Example 2:  
Given s = "leetcode", return "leotcede".  
  
1. 元音字母有五个a,e,i,o,u，需要注意的是大写的也算，所以总共有十个字母。
2. 同样使用双指针从头尾遍历
3. 用isVowel的函数来判断当前字符是否为元音字母。
4. 如果两边都是元音字母，那么我们交换。
5. 如果左边的不是，向右移动一位，如果右边的不是，则向左移动一位，参见代码如下：
```cpp
class Solution {
public:
    string reverseVowels(string s) {
        int left = 0, right= s.size() - 1;
        while (left < right) {
            if (isVowel(s[left]) && isVowel(s[right])) 
                swap(s[left++], s[right--]);
            else if (isVowel(s[left])) 
                --right;
            else 
                ++left;
        }
        return s;
    }
    bool isVowel(char c) {
        return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' || c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U';
    }
};
```

#### 翻转字符串中的单词

**解题思路**：  
1.使用双栈，先逆序单词然后进第二个栈逆序整个句子。

```cpp
class Solution
{
public:
    string ReverseSentence(string str)
    {
        if (str.size() == 0)
            return str;

        string result;
        stack<char>stk1;
        stack<char>stk2;

        //把str中的全部压入第一个栈
        for (auto i : str)
            stk1.push(i);

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


#### 打印1到最大的N位数
 

```cpp
class Solution {
public:
        void PrintToMaxOfDigits(int N) {
                if (N <= 0) 
                    return;

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

                for (; i < S; ++i) 
                    if (E[i] != '0') 
                        break;     

                if (i != S) 
                    cout << &E[i] << endl;
        }
};
```

#### 求电话号码的字母组合
即数字2到9中每个数字可以代表若干个字母，然后给一串数字，求出所有可能的组合。
1. 建立一个字典(hash)，用来保存每个数字所代表的字符串。
2. 使用level记录当前生成的字符串的字符个数。

```cpp
class Solution {
public:
    vector<string> letterCombinations(string digits)
    {
        //判断边界条件
        vector<string> res;
        if (digits.empty())
            return res;

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
             res.push_back(out);
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



#### 把字符串转换成整数

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
            P++;

        F= false;
        //  判断符号位
        if (*P == '+')
            P++;
        else if (*P == '-')
            P++;
            F = true;

        RES = 0;
        for (; P != V.end( ); P++)
        {
            if ('0' <= *P && *P <= '9')
            {
                RES *= 10;
                RES += *P - '0';
            }
            else
                break;

            //  解决OVER_FLOW的问题
            //  INT_MAX     2147483647
            //  INT_MIN     -2147483648  F = true
            //  负数绝对值最大为INT_MAX + 1
            //  正数最大值为INT_MAX
            if((F == true  && RES > (unsigned long)(INT_MAX) + 1)
              || (F == false && RES > INT_MAX))
                break;

        }

        //如果P没遍历到字符串尾部说明字符串转整数失败
        //要么是字符串中有非0-9的数值
        //要么字符串代表的数值溢出了
        if(P != V.end( ))
            return 0;
        else
        {

            if (F == true)
                RES = -RES;

            if (RES >= INT_MAX)
                RES = INT_MAX;
            else if (RES <= INT_MIN)
                RES = INT_MIN;

            return (int)RES;

        }
    }
};
```

#### 表示数值的字符串
请实现一个函数用来判断字符串是否表示数值（包括整数和小数）

1. 首先看第一个字符是不是正负号。
2. 如果是，在字符串上移动一个字符，继续扫描剩余的字符串中0到9的数位。
3. 如果是一个小数，则将遇到小数点。
4. 另外，如果是用科学计数法表示的数值，在整数或者小数的后面还有可能遇到’e’或者’E’。

```cpp
class Solution
{
public:
    bool isNumeric(char* str)
    {
        if(str == NULL)
            return false;

        if(*str == '+' || *str == '-')
            ++str;

        if(*str == '\0')
            return false;

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
                    numberic = IsExponential(&str);
            }
            else if(*str == 'e' || *str == 'E')
                numberic = IsExponential(&str);
            else
                numberic = false;
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
            return false;

        ++(*str);

        if(**str == '+' || **str == '-')
            ++(*str);
        if(**str == '\0')
            return false;

        ScanDigits(str);

        return (**str == '\0') ? true : false;
    }



};
```



#### 最长回文子串
* 此题可以用动态规划Dynamic Programming来解。
* 维护一个二维数组dp，其中dp[i][j]表示字符串区间[i, j]是否为回文串。
  * 当i = j时，只有一个字符，肯定是回文串。
  * 如果i = j + 1，说明是相邻字符，此时需要判断s[i]是否等于s[j]。
  * 如果i和j不相邻，即i - j >= 2时，除了判断s[i]和s[j]相等之外，dp[j + 1][i - 1]若为真，就是回文串，通过以上分析，可以写出递推式如下：

  >  dp[i, j] = 1,    if i == j  
     dp[i, j]= s[i] == s[j],     if j = i + 1  
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

For example,  
"A man, a plan, a canal: Panama" is a palindrome.  
"race a car" is not a palindrome.  


* 建立两个指针，left和right, 分别从字符的开头和结尾处开始遍历整个字符串。
* 如果遇到非字母数字的字符就跳过，继续往下找，直到找到下一个字母数字或者结束遍历。如果遇到大写字母，还要将其转为小写。
* 等左右指针都找到字母数字时，比较这两个字符
  * 若相等，则继续比较下面两个分别找到的字母数字；
  * 若不相等，直接返回false.  

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
