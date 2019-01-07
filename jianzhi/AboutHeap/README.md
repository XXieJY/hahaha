## 堆相关题目

常见题型有：
* K-th问题: 小顶堆可以保存最大Topk、大顶堆可以保存最小TopK.
* c++使用priority_queue实现最大最小堆；

* hash-set 应该使用 unordered_map；



### k-th问题：

#### 215. Kth Largest Element in an Array
Input: [3,2,1,5,6,4] and k = 2
Output: 5
解题思路：  

* 使用STL库的priority_queue可以方便地制造大顶堆（priority-queue默认）和小顶堆：
    * priority_queue<int, vector<int>, less<int>> maxHeap;
    * priority_queue<int, vector<int>, greater<int>> minHeap;
* 大顶堆更方便保存Kth smallest元素，小顶堆更方便保存Kth largest元素

```cpp

//大顶堆解Kth-largest问题
class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        priority_queue<int> pq(nums.begin(), nums.end());
        for (int i = 0; i < k - 1; i++) {
            pq.pop();
        }
        return pq.top();
    }
};

//小顶堆解Kth largest问题
class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        priority_queue<int, vector<int>, greater<int>> pq;
        for (int num : nums) {
            pq.push(num);
            if (pq.size() > k) {
                pq.pop();
            }
        }
        return pq.top();
    }
};
```

#### 378. Kth Smallest Element in a Sorted Matrix
解题思路：  
* kth最小问题，可以使用容积为k的小顶堆实现，也可以使用容积为k的大顶堆，每次进来第k+1个数时，去掉堆顶元素，这样遍历完留下来的堆顶元素必然是第k小的元素；
* 我们使用一个最大堆，然后遍历数组每一个元素，将其加入堆，根据最大堆的性质，大的元素会排到最前面，然后我们看当前堆中的元素个数是否大于k，大于的话就将首元素去掉，循环结束后我们返回堆中的首元素即为所求:
```cpp
class Solution {
public:
    int kthSmallest(vector<vector<int>>& matrix, int k)
    {
        priority_queue<int> q;
        for (int i = 0; i < matrix.size(); ++i)
        {
            for (int j = 0; j < matrix[i].size(); ++j)
            {
                q.emplace(matrix[i][j]);
                if (q.size() > k)
                {
                   q.pop();
                }
            }
        }
        return q.top();
    }
};
```

### Top k频率问题：（hash表 + pair + heap）

#### 347. Top K Frequent Elements
解题思路：  
这道题给了我们一个数组，让我们统计前k个高频的数字，那么对于这类的统计数字的问题，首先应该考虑用哈希表来做，建立数字和其出现次数的映射，然后再按照出现次数进行排序。我们可以用堆排序来做，使用一个最大堆来按照映射次数从大到小排列，在C++中使用priority_queue来实现，默认是最大堆，参见代码如下：
```cpp
class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        //构建hashmap和最大堆priority_queue
        unordered_map<int, int> m;
        priority_queue<pair<int, int>> q;
        vector<int> res;
        for (auto a : nums)
        {
            ++m[a];
        }
        for (auto it : m)
        {
            q.push({it.second, it.first});
        }
        for (int i = 0; i < k; ++i)
        {
            res.push_back(q.top().second); q.pop();
        }
        return res;
    }
};
```

#### 692. Top K Frequent Words
解题思路：  
这道题让我们求前K个高频词，跟之前那道题Top K Frequent Elements极其类似，换了个数据类型就又是一道新题。唯一的不同就是之前那道题对于出现频率相同的数字，没有顺序要求。而这道题对于出现频率相同的单词，需要按照字母顺序来排。但是解法都一样，还是用最大堆和桶排序的方法。首先来看最大堆的方法，思路是先建立每个单词和其出现次数之间的映射，然后把单词和频率的pair放进最大堆，如果没有相同频率的单词排序要求，我们完全可以让频率当作pair的第一项，这样priority_queue默认是以pair的第一项为key进行从大到小的排序，而当第一项相等时，又会以第二项由大到小进行排序，这样就与题目要求的相同频率的单词要按字母顺序排列不相符，当然我们可以在存入结果res时对相同频率的词进行重新排序处理，也可以对priority_queue的排序机制进行自定义，这里我们采用第二种方法，我们自定义排序机制，我们让a.second > b.second，让小频率的词在第一位，然后当a.second == b.second时，我们让a.first < b.first，这是让字母顺序大的排在前面（这里博主需要强调一点的是，priority_queue的排序机制的写法和vector的sort的排序机制的写法正好顺序相反，同样的写法，用在sort里面就是频率小的在前面，不信的话可以自己试一下）。定义好最小堆后，我们首先统计单词的出现频率，然后组成pair排序最小堆之中，我们只保存k个pair，超过了就把队首的pair移除队列，最后我们把单词放入结果res中即可，参见代码如下：

```cpp
class Solution {
public:
    vector<string> topKFrequent(vector<string>& words, int k) {
        vector<string> res(k);
        unordered_map<string, int> freq;
        auto cmp = [](pair<string, int>& a, pair<string, int>& b) {
            return a.second > b.second || (a.second == b.second && a.first < b.first);
        };
        priority_queue<pair<string, int>, vector<pair<string, int>>, decltype(cmp) > q(cmp);
        for (auto word : words) ++freq[word];
        for (auto f : freq) {
            q.push(f);
            if (q.size() > k) q.pop();
        }
        for (int i = res.size() - 1; i >= 0; --i) {
            res[i] = q.top().first; q.pop();
        }
        return res;
    }
};
```

#### 451. Sort Characters By Frequency
* 给一个字符串按照字符出现的频率来排序，那么毫无疑问肯定要先统计出每个字符出现的个数。
* 我们可以利用优先队列的自动排序的特点，先使用hashmap循环记录每个单词的出现次数。
* 然后把个数和字符组成pair放到优先队列里排好序后，再取出来组成结果res即可，参见代码如下：

```cpp
class Solution {
public:
    string frequencySort(string s) {
        string res = "";
        priority_queue<pair<int, char>> q;
        unordered_map<char, int> m;
        for (char c : s)
        {
          ++m[c];
        }
        for (auto a : m)
        {
          q.push({a.second, a.first});
        }
        while (!q.empty())
        {
            auto t = q.top();
            q.pop();
            res.append(t.first, t.second);
        }
        return res;
    }
};
```
