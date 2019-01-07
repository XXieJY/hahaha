学习一个算法，可分为3个步骤：首先了解算法本身解决什么问题，然后学习它的解决策略，
最后了解某些相似算法之间的联系。

例如图算法中:
* 广度优先搜索： 是一层一层往外遍历，寻找最短路径，其策略是采取队列的方法。
* 最小生成树：是最小代价连接所有点，其策略是贪心，比如Prim的策略是贪心+权重队列。
* Dijkstra： 是寻找单源最短路径，其策略是贪心+非负权重队列。
* Floyd： 是多结点对的最短路径，其策略是动态规划。
* 深度优先搜索DFS:DP是Bottom-up 而DFS是TOP-DOWN.


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
