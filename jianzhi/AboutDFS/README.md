#### DFS题型识别：
1. 排列组合常用DFS解题。
2. 树和图找路径相关问题也有用DFS解题

## 排列组合的DFS
### 概念
* 排列和组合的区分：
  * 看问题是否和顺序有关。有关就是排列，无关就是组合。
  * 90%DFS的题, 要么是排列, 要么是组合。



### 回溯法+DFS/BFS题型：
LeetCode的：Permutaions, PermutationsII, Combination Sum, Conbination SumII;  
**这几题解法中的for循环，不仅是为了递归拆解出可能的解，同时也使用pop_back()在每层递归上
进行一定程度的回溯，这样结合才能解题**



## 常见DFS题型：  
* 基于树的深度优先搜索 Tree-based DFS
* 基于组合的深度优先搜索 Combination-based DFS
* 基于排列、图的深度优先搜索 Permutation / Graph based DFS

### 递归的模板：

```cpp
主函数(...)
{
声明一些递归需要的辅助变量，如：res保存当前递归得到的结果，out保存目前递归得到的不完整结果。
  还比如：level和visited等记录递归进度的变量；

进入递归

返回结果

}

递归函数(...)
{
先判断递归是否到达出口，不是则继续，是则保存当前out的结果到res中，因为out已经是一个完整的递归结果。

因为还没到递归出口，使用for循环拆解当前递归的cases
{
  向out中添加当前递归层的case；
  进入下一层递归；
  从out中取回当前递归层的case；
}
}
```

---
