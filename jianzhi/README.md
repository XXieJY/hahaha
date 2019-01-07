1.DP的经典题目+LCS/LiS
2.排列组合的题目

#### 575. Distribute Candies
这道题给我们一堆糖，每种糖的个数不定，分给两个人，让我们求其中一个人能拿到的最大的糖的种类数。


1. 我们利用集合set的自动去重复特性来求出糖的种类数。
2. 然后跟n/2比较，取二者之中的较小值返回即可，参加代码如：

```cpp
class Solution {
public:
    int distributeCandies(vector<int>& candies) {
        unordered_set<int> s;
        for (int candy : candies) 
            s.insert(candy);
        return min(s.size(), candies.size() / 2);
    }
};
```

#### 463. Island Perimeter(和dfs无关的，求岛屿周长，且图中只有一个岛屿（因为只有一个岛屿所以和连通子、DFS算法什么的都没关系）)

解题思路：  
* 这道题给了我们一个格子图，若干连在一起的格子形成了一个小岛，规定了图中只有一个相连的岛，且岛中没有湖，让我们求岛的周长。
* 我们知道一个格子有四条边，但是当两个格子相邻，周围为6，若某个格子四周都有格子，那么这个格子一条边都不算在周长里。那么我们怎么统计出岛的周长呢？第一种方法，我们对于每个格子的四条边分别来处理，首先看左边的边，只有当左边的边处于第一个位置或者当前格子的左面没有岛格子的时候，左边的边计入周长。其他三条边的分析情况都跟左边的边相似，这里就不多叙述了，参见代码如下：

```cpp
class Solution {
public:
    int islandPerimeter(vector<vector<int>>& grid) {
        if (grid.empty() || grid[0].empty()) return 0;
        int m = grid.size(), n = grid[0].size(), res = 0;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == 0) continue;
                if (j == 0 || grid[i][j - 1] == 0) ++res;
                if (i == 0 || grid[i - 1][j] == 0) ++res;
                if (j == n - 1 || grid[i][j + 1] == 0) ++res;
                if (i == m - 1 || grid[i + 1][j] == 0) ++res;
            }
        }
        return res;
    }
};
```

#### 130. Surrounded Regions
解题思路：  
* 这道题有点像围棋，将包住的O都变成X，但不同的是边缘的O不算被包围，跟之前那道Number of Islands 岛屿的数量很类似，都可以用DFS来解。
* 在网上看到大家普遍的做法是扫面矩阵的四条边，如果有O，则用DFS遍历，将所有连着的O都变成另一个字符，比如，这样剩下的O都是被包围的，然后将这些O变成X，在把特殊字符变回O就行了。代码如下：

```cpp
class Solution {
public:
    void solve(vector<vector<char> >& board) {
        for (int i = 0; i < board.size(); ++i) {
            for (int j = 0; j < board[i].size(); ++j) {
                if ((i == 0 || i == board.size() - 1 || j == 0 || j == board[i].size() - 1) && board[i][j] == 'O')
                    solveDFS(board, i, j);
            }
        }
        for (int i = 0; i < board.size(); ++i) {
            for (int j = 0; j < board[i].size(); ++j) {
                if (board[i][j] == 'O') board[i][j] = 'X';
                if (board[i][j] == '$') board[i][j] = 'O';
            }
        }
    }
    void solveDFS(vector<vector<char> > &board, int i, int j) {
        if (board[i][j] == 'O') {
            board[i][j] = '$';
            if (i > 0 && board[i - 1][j] == 'O')
                solveDFS(board, i - 1, j);
            if (j < board[i].size() - 1 && board[i][j + 1] == 'O')
                solveDFS(board, i, j + 1);
            if (i < board.size() - 1 && board[i + 1][j] == 'O')
                solveDFS(board, i + 1, j);
            if (j > 1 && board[i][j - 1] == 'O')
                solveDFS(board, i, j - 1);
        }
    }
};
```



#### 200. Number of Islands**
Given a 2d grid map of '1's (land) and '0's (water), count the number of islands. An island is surrounded by water and is formed by connecting adjacent lands horizontally or vertically. You may assume all four edges of the grid are all surrounded by water.

解题思路：  
* 这道求岛屿数量的题的本质是**求矩阵中连续区域的个数。**  
* 求矩阵连续区域个数需要想到用深度优先搜索DFS来解：
  * 先建立一个visited数组用来记录某个位置是否被访问过。
  * 然后开始DFS二维数组：
    * 对于一个为‘1’且未被访问过的位置X，我们递归进入其上下左右位置上为‘1’的数。
    * 然后将X的visited对应值赋为true，继续进入其所有相连的邻位置，这样可以将这个连通区域所有的数找出来
    * 找完本次区域后，我们将结果res自增1，然后我们在继续找下一个为‘1’且未被访问过的位置，以此类推直至遍历完整个原数组即可得到最终结果，代码如下：

```cpp
class Solution {
public:
    int numIslands(vector<vector<char> > &grid) {
        if (grid.empty() || grid[0].empty()){
          return 0;
        }

        int m, n, res;
        m = grid.size();
        n = grid[0].size();
        res = 0;
        vector<vector<bool> > visited(m, vector<bool>(n, false));

        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == '1' && !visited[i][j]) {
                    DFS(grid, visited, i, j);
                    ++res;
                }
            }
        }
        return res;
    }

    void DFS(vector<vector<char> > &grid,
      vector<vector<bool> > &visited, int x, int y) {

        //先检测越界，再检测是否已经访问过
        if (x < 0 || x >= grid.size() || y < 0 ||
          y >= grid[0].size() || grid[x][y] != '1' || visited[x][y]) {
              return;
          }

        //对于未访问过的节点，将其标记为已访问
        //然后BFS地访问其四方向相邻节点
        visited[x][y] = true;
        DFS(grid, visited, x - 1, y);
        DFS(grid, visited, x + 1, y);
        DFS(grid, visited, x, y - 1);
        DFS(grid, visited, x, y + 1);
    }
};
```
#### 695. Max Area of Island

解题思路：  
* 需要统计出每个岛的大小，再来更新结果res。
* 先遍历grid，当遇到为1且未访问过的的点则进入递归函数。
  * 在递归函数中，我们首先判断i和j是否越界，还有grid[i][j]是否为1，我们没有用visited数组，而是直接修改了grid数组，遍历过的标记为-1。
  * 如果合法，那么cnt自增1，并且更新结果res，然后对其周围四个相邻位置分别调用递归函数即可，参见代码如下：

```cpp
class Solution {
public:
    vector<vector<int>> dirs{{-1,0},{1,0},{0,-1},{0,1}};

    int maxAreaOfIsland(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size(), res = 0;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] != 1) continue;
                int cnt = 0;
                helper(grid, i, j, cnt, res);
            }
        }
        return res;
    }

    void helper(vector<vector<int>>& grid, int i, int j, int& cnt, int& res) {
        //越界检查
        int m = grid.size(), n = grid[0].size();
        if (i < 0 || i >= m ||
            j < 0 || j >= n ||
            grid[i][j] <= 0)
        {
            return;
        }
        //表示结点为已访问
        grid[i][j] *= -1;

        //最大连通区域面积累计
        res = max(res, ++cnt);

        for (auto dir : dirs)
        {
            helper(grid, i + dir[0], j + dir[1], cnt, res);
        }
    }
};
```

#### 720. Longest Word in Dictionary
解题思路*：
* 这道题给了我们一个字典，是个字符串数组，然后问我们从单个字符开始拼，最长能组成啥单词，注意中间生成的字符串也要在字典中存在，而且当组成的单词长度相等时，返回字母顺序小的那个。
* 那么为了快速的查找某个单词是否在字典中存在，我们将所有单词放到哈希集合中，在查找的时候，可以采用BFS或者DFS都行。
* 先来看BFS的做法，使用一个queue来辅助，我们先把所有长度为1的单词找出排入queue中，当作种子选手，然后我们进行循环，每次从队首取一个元素出来，如果其长度大于我们维护的最大值mxLen，则更新mxLen和结果res，如果正好相等，也要更新结果res，取字母顺序小的那个。
* 然后我们试着增加长度，做法就是遍历26个字母，将每个字母都加到单词后面，然后看是否在字典中存在，存在的话，就加入queue中等待下一次遍历，完了以后记得要恢复状态，参见代码如下：
```cpp
class Solution {
public:
    string longestWord(vector<string>& words) {
        string res = "";
        int mxLen = 0;
        unordered_set<string> s(words.begin(), words.end());
        queue<string> q;
        for (string word : words) {
            if (word.size() == 1) q.push(word);
        }
        while (!q.empty()) {
            string t = q.front(); q.pop();
            if (t.size() > mxLen) {
                mxLen = t.size();
                res = t;
            } else if (t.size() == mxLen) {
                res = min(res, t);
            }
            for (char c = 'a'; c <= 'z'; ++c) {
                t.push_back(c);
                if (s.count(t)) q.push(t);
                t.pop_back();
            }
        }
        return res;
    }
};
```




bits相关问题：
#### 010 二进制中1的个数
解题思路：  
循环左移测试数，flag一直左移（乘以2），当超出表示标识范围的时候，我们就可以终止了，但是这样子的话，最高位的符号位没有测试，因此要单独测试，同时由于会溢出，我们的flag需要用long来标识。

```cpp
class Solution
{
public:
    int NumberOf1(int n)
    {
        int count = 0;
        int i = 0;
        unsigned long flag = 1;

        while(flag <= INT_MAX)
        {
            debug <<n <<" & " <<flag <<" == "<<(n & flag) <<endl;
            if((n & flag) != 0)
            {
                count++;
            }
            flag <<= 1;
        }

        //  由于循环终结，我们使用的是flag <= INT_MAX
        //  因此前面的循环只会执行31次
        if((n & flag) != 0)    //  最后测试符号位
        {
            count++;
        }

        return count;
    }

};
```

#### *011 数值的整数次方

题目描述:  
给定一个double类型的浮点数base和int类型的整数exponent。求base的exponent次方。

解题思路：  
此题也是很爱在面试阶段考察的题目.
浮点数的次方主要考察计算时处理边界情况  
指数幂的所有边界包括:
  * 指数为0的情况，不管底数是多少都应该是1
  * 指数为负数的情况，求出的应该是其倒数幂的倒数
  * 指数为负数的情况下，底数不能为0

```cpp
class Solution
{
public:
    double Power(double base, int exponent)
    {
        //  指数为0的情况，不管底数是多少都应该是1.0
        if(exponent == 0)
        {
            return 1.0;
        }
        //  指数为负数的情况下，底数不能为0
        if(Equal(base, 0.0) == true && exponent < 0)
        {
            return 0.0;
        }

        double res = 1.0;
        if(exponent > 0.0)
        {
            res = PowerNormal(base, exponent);
        }
        else
        {
            res = PowerNormal(base, -exponent);
            res = 1 / res;
        }
        return res;
    }

private :
    double PowerNormal(double base, int exponent)
    {

        double res = 1;
        for(int i = 0; i < exponent; i++)
        {
            res *= base;
        }

        return res;

    }
    double Equal(double left, double right)
    {
        if(fabs(left - right) <  0.0000001)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
};
```

#### 046 求1+2+3+...+n
解题思路:  
主要考察如何使用递归模拟乘法  使用短路模拟if语句.

```cpp
class Solution
{
public:
    int res;
    int Sum_Solution(int n)
    {
        res = 0;
        return (MultiRecursion(n, n + 1) >> 1);
    }

    int MultiRecursion(int a, int b)
    {
        a && MultiRecursion(a >> 1, b << 1);    //  递归的进行运算

        (a & 1) && (res += b);                  //  短路


        return res;
    }

};
```
#### 064 数据流之中的中位数
题目描述  

如何得到一个数据流中的中位数？如果从数据流中读出奇数个数值，那么中位数就是所有数值排序之后位于中间的数值。如果从数据流中读出偶数个数值，那么中位数就是所有数值排序之后中间两个数的平均值。

解题思路:  
对于数据流，对应的就是在线算法了，一道很经典的题目就是在1亿个数中找到最大的前100个数，这是一道堆应用题，找最大的前100个数，那么我们就创建一个大小为100的最小化堆，每来一个元素就与堆顶元素比较，因为堆顶元素是目前前100大数中的最小数，前来的元素如果比该元素大，那么就把原来的堆顶替换掉。

那么对于这一道题呢？如果单纯的把所有元素放到一个数组里，每次查找中位数最快也要O(n)，综合下来是O(n^2)的复杂度。我们可以利用上面例子中的想法，用一个最大堆来维护当前前n/2小的元素，那么每次找中位数只到取出堆顶就可以了。但是，有一个问题，数据要动态增长，有可能之前被替换掉的元素随着元素的增加又跑回来了，所以我们不能单纯得向上题一样把元素丢掉，我们可以再用一个最小化堆来存前n/2大的元素。

```cpp
class Solution
{
protected:
    vector<int>     m_min; //数组中的后一半元素组成一个最小化堆
    vector<int>     m_max; //数组中的前一半元素组成一个最大化堆

public:
    /*  将元素插入的堆中，　
     *  为了保证数据平均的分配到两个堆中, 两个堆的数据数目之差不能超过１
     *  插入的元素会两个堆元素的平衡, 因此两个堆都必须调整
     *
     *  比如将元素插在后半段(最小堆)中,
     *  则最小堆调整后的堆顶(最小值)需要弹出并压入到前半段中才能保证平衡
     *　也就是说,　在最小堆中插入元素, 最后完成调整后将导致最大堆中元素+1
     *
     *  因此我们可以假定, 0 <= m_min.size( ) - m_max.size( ) <= 1
     *  那么
     *
     *  插入前如果整个数组的元素个数为偶数, 说明两个堆中元素个数相等
     *  则最终元素应该插入m_min中,即先把元素插入到m_max中在调整到m_min中
     *
     *  插入前如果整个数组的元素个数为奇数, 说明m_max元素多了1个
     *  则最终元素应该插入m_max中,
     *  即先把元素插入到m_min中在调整到m_max中
     *  */
    void Insert(int num)
    {
        if(((m_min.size( ) + m_max.size( )) & 1) == 0)
        {
            /*  偶数数据的情况下
             *  直接将新的数据插入到数组的后半段
             *  即在最小堆中插入元素
             *
             *  此时最小堆中多出一个元素,
             *  即最小元素, 将其弹出后, 压入前半段(即最大堆中)
             *  */
            if(m_max.size( ) > 0 && num < m_max[0])
            {
                m_max.push_back(num);
                push_heap(m_max.begin( ), m_max.end( ), less<int>( ));

                num = m_max[0];
                pop_heap(m_max.begin(), m_max.end(), less<int>());
                m_max.pop_back();
            }
            m_min.push_back(num); //把前一半找到的最大值放到后一半中
            push_heap(m_min.begin( ), m_min.end( ), greater<int>( ));
            debug <<"left = " <<m_max.size( ) <<", " <<m_min.size( ) <<endl;
        }
        else
        {
            /*  否则数组中元素是奇数
             *  将
             *
             * */
            if(m_min.size( ) > 0 && num > m_min[0])    //  奇数数据的情况下，则在最大堆中插入元素
            {
                m_min.push_back(num);
                push_heap(m_min.begin(), m_min.end(), greater<int>());
                num=m_min[0];
                pop_heap(m_min.begin(), m_min.end(), greater<int>());
                m_min.pop_back();
            }
            m_max.push_back(num); //把后一半找到的最大值放到前一半中
            push_heap(m_max.begin(), m_max.end(), less<int>());
        }
    }

    /*  由于假定, 0 <= m_min.size( ) - m_max.size( ) <= 1
     *  因此
     *  当总元素个数为偶数时, 中位数即(m_max[0] + m_min[0]) / 2
     *  当总元素个数为奇数时, 中位数即m_min[0];  */
    double GetMedian()
    {
        int size = m_min.size( ) + m_max.size( );
        if(size==0) return -1;
        double median = 0;
        if((size & 1) != 0)
        {
            median = (double) m_min[0];
        }
        else
        {
            median = (double) (m_max[0] + m_min[0]) / 2;
        }
        return median;
    }
};
```




数论相关：


  * 041-和为S的连续正数序列
  * 045-孩子们的游戏(圆圈中最后剩下的数)

#### 009 斐波那契数列
题目描述

大家都知道斐波那契数列， 现在要求输入一个整数n， 请你输出斐波那契数列的第n项。

解题思路：  
对于斐波那契数列相关问题，都应该统一使用for循环计算数列的第n项进行解决。

```cpp
class Solution
{

public:
    int Fibonacci(int n)
    {
        if(n <= 1)
        {
            return n;
        }
        long one = 0;
        long two = 1;;
        long res = 0;

        for(int i = 2; i <= n; i++)
        {
            res = one + two;

            one = two;
            two = res;
        }

        return res;
    }
};
```

#### 279. Perfect Squares
Given a positive integer n, find the least number of perfect square numbers (for example, 1, 4, 9, 16, ...) which sum to n.  

For example, given n = 12, return 3 because 12 = 4 + 4 + 4; given n = 13, return 2 because 13 = 4 + 9.  

**解题思路**：  
##### 使用四平方和定理：  
* 这道题是考察四平方和定理。题中说是给我们一个正整数，求它最少能由几个完全平方数组成。
* 根据四平方和定理，**任意一个正整数均可表示为4个整数的平方和，其实是可以表示为4个以内的平方数之和，那么就是说返回结果只有1,2,3或4其中的一个。** 首先我们将数字化简一下，由于一个数如果含有因子4，那么我们可以把4都去掉，并不影响结果，比如2和8,3和12等等，返回的结果都相同
* 下面我们就来尝试的将其拆为两个平方数之和，如果拆成功了那么就会返回1或2，因为其中一个平方数可能为0. (注：由于输入的n是正整数，所以不存在两个平方数均为0的情况)。
* 注意下面的!!a + !!b这个表达式，**用两个感叹号!!的作用就是看a和b是否为正整数，都为正整数的话返回2，只有一个是正整数的话返回1**。  
参见代码如下：

```cpp
class Solution {
public:
    int numSquares(int n) {
        while (n % 4 == 0) n /= 4;
        if (n % 8 == 7) return 4;
        for (int a = 0; a * a <= n; ++a) {
            int b = sqrt(n - a * a);
            if (a * a + b * b == n) {
                return !!a + !!b;
            }
        }
        return 3;
    }
};
```


#### 034 丑数
题目描述

把只包含因子2、3和5的数称作丑数（Ugly Number）。

例如6、8都是丑数，但14不是，因为它包含因子7。 习惯上我们把1当做是第一个丑数。求按从小到大的顺序的第N个丑数。

解题思路：  
根据丑数的定义，丑数应该是另一个丑数乘以2、3或者5的结果（1除外）。 因此我们可以创建一个数组，里面的数字是排好序的丑数。里面的每一个丑数是前面的丑数乘以2、3或者5得到的。那关键就是确保数组里的丑数是有序的了。 我们假设数组中已经有若干个丑数，排好序后存在数组中。我们把现有的最大丑数记做M。 现在我们来生成下一个丑数，该丑数肯定是前面某一个丑数乘以2、3或者5的结果。 我们首先考虑把已有的每个丑数乘以2。在乘以2的时候，能得到若干个结果小于或等于M的。由于我们是按照顺序生成的，小于或者等于M肯定已经在数组中了，我们不需再次考虑； 我们还会得到若干个大于M的结果，但我们只需要第一个大于M的结果，因为我们希望丑数是按从小到大顺序生成的，其他更大的结果我们以后再说。 我们把得到的第一个乘以2后大于M的结果，记为M2。同样我们把已有的每一个丑数乘以3和5，能得到第一个大于M的结果M3和M5。那么下一个丑数应该是M2、M3和M5三个数的最小者。
```cpp
class Solution
{
protected:
    int ugly[10000];
    int min(int a, int b, int c)
    {
        int temp = (a < b ? a : b);

        return (temp < c ? temp : c);
    }

public:
    int GetUglyNumber_Solution(int N)
    {
        ugly[0] = 1;
        int index2 = 0;
        int index3 = 0;
        int index5 = 0;
        int index = 1;
        while (index < N)
        {
            //竞争产生下一个丑数
            int val = min(ugly[index2]*2,
                          ugly[index3]*3,
                          ugly[index5]*5);

            if (val == ugly[index2] * 2) //将产生这个丑数的index*向后挪一位；
            {
                ++index2;
            }
            if (val == ugly[index3] * 3)   //这里不能用elseif，因为可能有两个最小值，这时都要挪动；
            {
                ++index3;
            }
            if (val == ugly[index5] * 5)
            {
                ++index5;
            }

            ugly[index++] = val;
        }
        int result = ugly[N - 1];
        return result;
    }
};
```

#### 验证数值回文
比如 1221 这个数字，如果 计算 1221 / 1000， 则可得首位1， 如果 1221 % 10， 则可得到末尾1，进行比较，然后把中间的22取出继续比较。代码如下：
```cpp
class Solution {
public:
    bool isPalindrome(int x) {
        if (x < 0) return false;
        int div = 1;
        while (x / div >= 10) div *= 10;
        while (x > 0) {
            int left = x / div;
            int right = x % 10;
            if (left != right) return false;
            x = (x % div) / 10;
            div /= 100;
        }
        return true;
    }
};
```

####  生成杨辉三角的二维数组
http://www.cnblogs.com/grandyang/p/4031536.html
```cpp
class Solution {
public:
    vector<vector<int> > generate(int numRows) {
        vector<vector<int> > res;
        if (numRows <= 0) return res;
        res.assign(numRows, vector<int>(1));
        for (int i = 0; i < numRows; ++i) {
            res[i][0] = 1;
            if (i == 0) continue;
            for (int j = 1; j < i; ++j) {
                res[i].push_back(res[i-1][j] + res[i-1][j-1]);
            }
            res[i].push_back(1);
        }
        return res;
    }
};
```



## 基础算法
* 查找算法：二分查找
* 排序算法：快速排序、归并排序
* 指针操作：前后差一步指针、快慢指针、左右指针
* 链表操作：链表遍历(链表环)、链表变形(链表转数组、链表头插)

---

### 查找算法
#### 二分查找

* 基本二分查找框架
```cpp
class Solution {
  int binarySearch(vector<int> E, int T)
  {
    //判断边界条件
    if((int S = E.size()) == 0)
    {
      return -1;
    }

    //声明二分查找辅助变量：左边界和右边界和中间节点
    int L = 0, R = S - 1, pivot = 0;

    //二分查找主循环体，出口条件必须是left <= right
    //L<=R结合pivot+-1可以推导出的最后结果是L与R一定会在
    //查找失败时交叉
    while(L <= R)
    {
      //每次循环更新pivot
      pivot = L + (R - L) / 2;
      //根据题目查找要求确定不同的E[pivot]与T间的比较关系
      if (E[pivot] ? T)
      {
        //更新Left或Right或返回结果
      }
      else
      {
        //更新Right或Left或返回结果
      }
    }
    //返回查找失败的结果
  }
}
```

* 在无重复有序数组中查找
```cpp
class Solution{
  int binarySearch(vector<int> E, int T)
  {
    if((int S = E.size()) == 0)
    {
      return -1;
    }
    int L = 0, R = S - 1, pivot = 0;
    while (L <= R)
    {
      pivot = L + (R - L) / 2;
      if(E[pivot] == T)
      {
        return pivot;
      }
      else if(E[pivot] < T)
      {
        L = pivot + 1;
      }
      else
      {
        R = pivot - 1;
      }
    }
    return -1;
  }
}
```

* 在有重复有序数组中查找（那就是查找区间了）
```cpp
class Solution{
    vector<int> binarySearch(vector<int> E, int T)
    {
        if ((int S = E.size()) == 0)
        {
            return -1;
        }

        //初始化变量，先查找左边界
        int L = 0, R = S - 1, pivot = 0, A = -1, B = -1;
        while (L <= R)
        {
            pivot = L + (R - L) / 2;
            //左右游标回向目标值的左边界靠拢
            if (E[pivot] >= T)
            {
                R = pivot - 1;
            }
            else
            {
                L = pivot + 1;
            }
        }
        //注意这里的判断条件
        //因为允许可重复查找则有可能会查找出边界或者结果事实上是大于Target的值
        if (L < S && E[L] == T)
        {
            A = L;
        }
        else
        {
            return new vector<int>{-1, -1};
        }
        L = 0, R = S - 1, pivot = 0;
        while (L <= R)
        {
            pivot = L + (R - L) / 2;
            if (E[pivot] <= T)
            {
                L = pivot + 1;
            }
            else
            {
                R = pivot - 1;
            }
        }
        //注意这里的判断条件
        //因为允许可重复查找则有可能会查找出边界或者结果事实上是小于Target的值
        if (R > = 0 && E[R] == T)
        {
            return new vector<int>{L, R};
        }
        else
        {
            return new vector<int>{-1, -1};
        }
    }
}
```

---

### 排序算法（基本上都是分治的思想，要么top-down，要么bottom-up）
#### 快速排序(分治top-down递归) ps: [partition算法](http://blog.jobbole.com/105219/)
* 快速排序的基本过程：
  1. 进行每一趟排序时， 从数据中选出一个pivot，然后将大于等于或小于等于pivot的数值分别调整到pivot的左右两侧
  2. 然后再分别对pivot左右两部分数据再进行快速排序。 重复上述操作，直到待排序数据长度等于1.
* 快速排序的特点：
  1. 时间复杂度O(nlogn) 空间复杂度O(1) 是不稳定排序算法
  2. 递归型的快速排序通常需要实现两个个helper函数
    * 第一个用来调用快速排序算法，分割排序后数据以及重复调用自身；
    * 第二个实现快速排序算法。每次调用它，都先确定一个pivot，然后将大于等于或小于等于pivot的数据分别放在pivot两侧）
  3. 快速排序有Lomuto 和 Hoare两种常见的实现方式。

* Lomuto快速排序:
  1. 选择数据中的首个元素 或者 最后一个元素作为pivot。
  2. 将大于或者小于pivot的数据 放到pivot前面 （这里看是升序还是降序）
  3. 然后将当前pivot放到它的**最终位置**上。
  4. 重复递归，直至出口为 L < R

```cpp
class Solution{
    void lquick(vector<int> &E, int L, int R)
    {
	     if (L < R)
	     {
		       int p = lpartition(E, L, R);
		       lquick(E, L, p - 1);
		       lquick(E, p + 1, R);
	     }
}

    int lpartition(vector<int> &E, int L, int R)
    {
	     //i指定了当前pivot在排序后最终位置的前一个元素
       //快排交换元素的起点是E[-1]，每次找到标定的元素值E[j] < pivot时
       //应该是i先自加，然后和E[j]进行swap
       //最后i位置是pivot的最终位置的前一个元素
	     int pivot = E[R], i = L - 1;
	     for (int j = L; j < R; j++)
	     {
		       if (E[j] < pivot)
		       {
			          swap(E[++i], E[j]);
		       }
		       else
		       {
			          //do nothing
		       }
	      }
	      swap(E[++i], E[R]);
	      return i;
    }
}
```

#### 归并排序(分治bottom-up递归)
递归排序的基本过程：
* 分治一般都需要辅助空间。
* 先divide然后再merge，divide的出口是L < R，即子数列长度等于1时不可再分。
* 然后bottom-up的merge, 先是大小为2的小数组被排好序，然后再对两个大小为2的数组排序成大小为4的数组。

递归排序的应用：
* 递归排序除了被用作排序还会考逆序对的问题。
* 同时，递归排序的核心代码也就是标准的分治bottom-up的代码。


* 分治bottom up代码  

```cpp
class Solution{
    void mergeSort(...)
    {
        if(递归出口)
        {
            分治递归1();
            分治递归2();
            本层分治处理函数();
        }
    }
    void merge(...)
    {
        处理特定的分治逻辑;
    }
}

```

* 标准归并排序代码  

```cpp
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

//将有二个有序数列a[first...mid]和a[mid...last]合并。
void merge(int a[], int first, int mid, int last, int temp[])
{
	int i = first, j = mid + 1, k = 0;
	while (i <= mid && j <= last)
	{
		if (a[i] <= a[j])
        {
            temp[k++] = a[i++];
        }
		else
		{
            temp[k++] = a[j++];
        }
	}
	while (i <= mid)
	{
        temp[k++] = a[i++];
    }
	while (j <= last)
    {
        temp[k++] = a[j++];
    }
	for (i = 0; i < k; i++)
	{
        a[first + i] = temp[i];
    }
}
```

---

### 指针操作：前后差一步指针、快慢指针、左右指针

#### 前后差一步指针
常见题型：字符串滑动窗口问题、
##### 015 链表中倒数第k个结点
题目描述
输入一个链表，输出该链表中倒数第k个结点。  

解题思路：  
对于这种单链表的倒数第N个节点，就是前后差异指针方法。  

然后关于指定第k个节点的问题，都会需要注意类似：  
  * 链表可能为NULL  
  * 链表长度可能没有K个  
的边界问题。  

```cpp
/// 1 -> 2 -> 3 -> 4 -> 5
/// 比如要走倒数第3个节点
/// 那么right先走到第3 - 1个节点&[2]
/// 那么right指针向前走到其下一个节点为NULL时, left节点既是倒数第K个节点
/// 此时两个指针相差为K - 1
/// 因此right需要走到链表尾部前一个结点


/// 1 -> 2 -> 3 -> 4 -> 5
/// 比如要走倒数第3个节点
/// 那么right先走到第3个节点&[2]
/// 那么right指针向前走到链表尾部为NULL时, left节点既是倒数第K个节点
/// 此时两个指针相差为K
/// 因此right需要走到链表尾部前

class Solution
{
public:
    ListNode* FindKthToTail(ListNode* pListHead, unsigned int k)
    {
        if(pListHead == NULL)
        {
            return NULL;
        }
        unsigned int i = 0;
        ListNode *right = pListHead;

        //  left指针先向前走K - 1步
        while(i < k - 1 && right != NULL)
        {
            debug <<"index  = " <<i <<", value = " <<right->val <<endl;
            right = right->next;
            i++;
        }

        if(right == NULL)
        {
            cout <<"the list length = " <<i <<" < " <<k <<endl;
            return NULL;
        }

        ListNode *left = pListHead;
        while(right->next != NULL)
        {
            debug <<"index  = " <<i++ <<", value = " <<right->val <<endl;

            left = left->next;
            right = right->next;
        }

        return left;

    }
};
```

#### 快慢指针
常见题型： 链表环问题、

##### 141. Linked List Cycle 判断链表是否有环

解题思路：
这道题是快慢指针的经典应用。只需要设两个指针，一个每次走一步的慢指针和一个每次走两步的快指针，如果链表里有环的话，两个指针最终肯定会相遇。代码如下：

```cpp
class Solution {
public:
    bool hasCycle(ListNode *head) {
        ListNode *slow = head, *fast = head;
        //注意快慢指针循环的判断条件是：
        //快指针本身非空且快指针的下一个节点也非空
        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
            if (slow == fast) return true;
        }
        return false;
    }
};
```

#### 左右指针*
常见题型：字符串翻转问题、字符串回文问题

##### 167. Two Sum II - Input array is sorted 两数之和之二 - 输入数组有序
Given an array of integers that is already sorted in ascending order, find two numbers such that they add up to a specific target number.
The function twoSum should return indices of the two numbers such that they add up to the target, where index1 must be less than index2. Please note that your returned answers (both index1 and index2) are not zero-based.  
You may assume that each input would have exactly one solution.   
Input: numbers={2, 7, 11, 15}, target=9  
Output: index1=1, index2=2  

解题思路：  
* 需要两个指针，一个指向开头，一个指向末尾，然后向中间遍历。
* 如果指向的两个数相加正好等于target的话，直接返回两个指针的位置即可。
* 若小于target，左指针右移一位。
* 若大于target，右指针左移一位，以此类推直至两个指针相遇停止，参见代码如下：
```cpp
class Solution {
public:
    vector<int> twoSum(vector<int>& numbers, int target) {
        int l = 0, r = numbers.size() - 1;
        while (l < r) {
            int sum = numbers[l] + numbers[r];
            if (sum == target) return {l + 1, r + 1};
            else if (sum < target) ++l;
            else --r;
        }
        return {};
    }
};
```

##### 633. Sum of Square Numbers 平方数之和
Given a non-negative integer c, your task is to decide whether there're two integers a and b such that a2 + b2 = c.  

Example 1:  

Input: 5  
Output: True  
Explanation: 1 * 1 + 2 * 2 = 5  

解题思路：  
这里用a和b代表了左右两个范围，分别为0和c的平方根，然后while循环遍历，如果a*a + b*b刚好等于c，那么返回true；如果小于c，则a增大1；反之如果大于c，则b自减1，参见代码如下：
```cpp
class Solution {
public:
    bool judgeSquareSum(int c) {
        int a = 0, b = sqrt(c);
        while (a <= b) {
            if (a * a + b * b == c) return true;
            else if (a * a + b * b < c) ++a;
            else --b;
        }
        return false;
    }
};
```

##### 345. Reverse Vowels of a String（双指针+额外判定 变形字符串）
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

##### 680. Valid Palindrome II(可以修改一次字符串，再判断回文串的问题)
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

---
