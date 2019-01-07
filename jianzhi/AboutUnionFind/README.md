#### 684. Redundant Connection
解题思路：  
* 这道题最好的解法使用Union Find来做，其实Union Find的核心思想并不是很难理解，首先我们建立一个长度为(n+1)的数组root，由于这道题并没有明确的说明n是多少，只是说了输入的二位数组的长度不超过1000，那么n绝对不会超过2000。
* 我们加1的原因是由于结点值是从1开始的，而数组是从0开始的，我们懒得转换了，就多加一位得了。我们将这个数组都初始化为-1，有些人喜欢初始化为i，都可以。
* 开始表示每个结点都是一个单独的组，所谓的Union Find就是要让结点之间建立关联，比如若root[1] = 2，就表示结点1和结点2是相连的，root[2] = 3表示结点2和结点3是相连的，如果我们此时新加一条边[1, 3]的话，我们通过root[1]得到2，再通过root[2]得到3，说明结点1有另一条路径能到结点3，这样就说明环是存在的；
* 如果没有这条路径，那么我们要将结点1和结点3关联起来，让root[1] = 3即可，参见代码如下：
```cpp
class Solution {
public:
    vector<int> findRedundantConnection(vector<vector<int>>& edges)
    {
        vector<int> root(2001, -1);
        for (auto edge : edges)
        {
            int x = find(root, edge[0]), y = find(root, edge[1]);
            if (x == y)
            {
              return edge;
            }
            root[x] = y;
        }
        return {};
    }
    int find(vector<int>& root, int i)
    {
        while (root[i] != -1)
        {
            i = root[i];
        }
        return i;
    }
};
```
#### 547. Friend Circles
解题思路：  
* 下面这种解法叫联合查找Union Find，也是一种很经典的解题思路，在之前的两道道题Graph Valid Tree和Number of Connected Components in an Undirected Graph中也有过应用。
* 核心思想是初始时给每一个对象都赋上不同的标签，然后对于属于同一类的对象，在root中查找其标签。
* 如果不同，那么将其中一个对象的标签赋值给另一个对象，注意root数组中的数字跟数字的坐标是有很大关系的，root存的是属于同一组的另一个对象的坐标，这样通过getRoot函数可以使同一个组的对象返回相同的值，参见代码如下：
```cpp
class Solution {
public:
    int findCircleNum(vector<vector<int>>& M) {
        int n = M.size(), res = n;
        vector<int> root(n);
        for (int i = 0; i < n; ++i) root[i] = i;
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                if (M[i][j] == 1) {
                    int p1 = getRoot(root, i);
                    int p2 = getRoot(root, j);
                    if (p1 != p2) {
                        --res;
                        root[p2] = p1;
                    }
                }
            }   
        }
        return res;
    }
    int getRoot(vector<int>& root, int i) {
        while (i != root[i]) {
            root[i] = root[root[i]];
            i = root[i];
        }
        return i;
    }
};
```

#### 261. Graph valid Tree
* Union Find的方法，这种方法对于解决连通图的问题很有效.
* 思想是我们遍历节点，如果两个节点相连，我们将其roots值连上，这样可以帮助我们找到环.
* 我们初始化roots数组为-1，然后对于一个pair的两个节点分别调用find函数，得到的值如果相同的话，则说明环存在，返回false，不同的话，我们将其roots值union上，参见代码如下：
```cpp
class Solution {
public:
    bool validTree(int n, vector<pair<int, int>>& edges) {
        vector<int> roots(n, -1);
        for (auto a : edges) {
            int x = find(roots, a.first), y = find(roots, a.second);
            if (x == y) return false;
            roots[x] = y;
        }
        return edges.size() == n - 1;
    }
    int find(vector<int> &roots, int i) {
        while (roots[i] != -1) i = roots[i];
        return i;
    }
};
```

#### 721. Accounts Merge
解题思路：  
* 这是个归组类的问题。归组类问题很适合使用Union Find来做，LeetCode中有很多道可以使用这个方法来做的题，**比如Friend Circles，Graph Valid Tree，Number of Connected Components in an Undirected Graph，和Redundant Connection等等。**
* 都是要用一个root数组，每个点开始初始化为不同的值，如果两个点属于相同的组，就将其中一个点的root值赋值为另一个点的位置，这样只要是相同组里的两点，通过find函数得到相同的值。
* 在这里，由于邮件是字符串不是数字，所以root可以用哈希map来代替，我们还需要一个哈希映射owner，建立每个邮箱和其所有者姓名之前的映射，另外用一个哈希映射来建立用户和其所有的邮箱之间的映射，也就是合并后的结果。
* 首先我们遍历每个账户和其中的所有邮箱，先将每个邮箱的root映射为其自身，然后将owner赋值为用户名。然后开始另一个循环，遍历每一个账号，首先对帐号的第一个邮箱调用find函数，得到其父串p，然后遍历之后的邮箱，对每个遍历到的邮箱先调用find函数，将其父串的root值赋值为p，这样做相当于将相同账号内的所有邮箱都链接起来了。
* 我们下来要做的就是再次遍历每个账户内的所有邮箱，先对该邮箱调用find函数，找到父串，然后将该邮箱加入该父串映射的集合汇总，这样就我们就完成了合并。最后只需要将集合转为字符串数组，加入结果res中，通过owner映射找到父串的用户名，加入字符串数组的首位置，参见代码如下：
```cpp
class Solution {
public:
    vector<vector<string>> accountsMerge(vector<vector<string>>& accounts) {
        vector<vector<string>> res;
        unordered_map<string, string> root;
        unordered_map<string, string> owner;
        unordered_map<string, set<string>> m;
        for (auto account : accounts) {
            for (int i = 1; i < account.size(); ++i) {
                root[account[i]] = account[i];
                owner[account[i]] = account[0];
            }
        }
        for (auto account : accounts) {
            string p = find(account[1], root);
            for (int i = 2; i < account.size(); ++i) {
                root[find(account[i], root)] = p;
            }
        }
        for (auto account : accounts) {
            for (int i = 1; i < account.size(); ++i) {
                m[find(account[i], root)].insert(account[i]);
            }
        }
        for (auto a : m) {
            vector<string> v(a.second.begin(), a.second.end());
            v.insert(v.begin(), owner[a.first]);
            res.push_back(v);
        }
        return res;
    }
    string find(string s, unordered_map<string, string>& root) {
        return root[s] == s ? s : find(root[s], root);
    }
};
```
