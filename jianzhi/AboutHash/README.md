* Hash和String相关题目；

### K-sum相关问题
* 给你一组N个数字，然后给你一个常数target，我们的goal是在这一堆数里面找到K个数字，使得这K个数字的和等于target。
* 注意这一组数字可能有重复项：比如 1 1 2 3 , 求3sum, 然后 target  = 6, 你搜的时候可能会得到 两组1 2 3, 1 2 3，1 来自第一个1或者第二个1, 但是结果其实只有一组，所以最后结果要去重。

#### 1. Two Sum
解题思路：  
O(n)的算法来实现，整个实现步骤为：
* 先遍历一遍数组，建立map数据。
* 然后再遍历一遍，开始查找，找到则记录index。代码如下：
```cpp
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        //声明辅助hash表和记录结果的数组
        unordered_map<int, int> m;
        vector<int> res;

        //将元素存入哈希k=元素值,v=元素在数组中的索引
        for (int i = 0; i < nums.size(); ++i)
        {
            m[nums[i]] = i;
        }

        //根据剩余值t在hash表中查找
        for (int i = 0; i < nums.size(); ++i)
        {
            int t = target - nums[i];
            //如果unordered_map中存在数值t使得t+nums[i] = target
            //且这个t不与nums[i]为同一个元素，说明找到一个2sum解
            if (m.count(t) && m[t] != i)
            {
                res.push_back(i);
                res.push_back(m[t]);
                break;
            }
        }
        return res;
    }
};
```

#### 3-sum
找到数组中三个元素的和等于0的所有cases。
Given array nums = [-1, 0, 1, 2, -1, -4]。  
A solution set is:  
[  
  [-1, 0, 1],  
  [-1, -1, 2]  
]  

1. 化解3-sum问题为2-sum问题：先排序然后一个指针先固定1st元素，从头开始循环。
2. 然后在数组的其他数中找出2个数的和加上这个指针指向的数的和等于target就行了。
3. 这两个数的和2nd+3rd=target-1st。

```cpp
vector<vector<int> > threeSum(vector<int> &num) {
    
    vector<vector<int> > res;

    std::sort(num.begin(), num.end());

    for (int i = 0; i < num.size(); i++) {   
        int target = -num[i];
        int front = i + 1;
        int back = num.size() - 1;
        while (front < back) {
            int sum = num[front] + num[back];
            // Finding answer which start from number num[i]
            if (sum < target)
                front++;
            else if (sum > target)
                back--;
            else {
                vector<int> triplet(3, 0);
                triplet[0] = num[i];
                triplet[1] = num[front];
                triplet[2] = num[back];
                res.push_back(triplet);
                // Processing duplicates of Number 2
                // Rolling the front pointer to 
                //the next different number forwards
                while (front < back && num[front] == triplet[1]) 
                    front++;
                // Processing duplicates of Number 3
                // Rolling the back pointer to 
                //the next different number backwards
                while (front < back && num[back] == triplet[2]) 
                    rear--;
            }
        }
        // Processing duplicates of Number 1
        while (i + 1 < num.size() && num[i + 1] == num[i]) 
            i++;
    }
    return res;
    
}
```


#### 290. Word Pattern

解题思路：  
这道题给我们一个模式字符串，又给我们一个单词字符串，让我们求单词字符串中单词出现的规律是否符合模式字符串中的规律。

1. 用哈希表来做，建立模式字符串中每个字符和单词字符串每个单词之间的映射，而且这种映射必须是一对一关系的，不能'a‘和’b'同时对应‘dog'。
2. 碰到一个新字符时，首先检查其是否在哈希表中出现。
    * 若出现且其映射的单词若不是此时对应的单词，则返回false。
    * 若没有在哈希表中出现，我们还要遍历一遍哈希表，看新遇到的单词是否已经是哈希表中的映射。如果没有，再跟新遇到的字符建立映射，参见代码如下：
```cpp
class Solution {
public:
    bool wordPattern(string pattern, string str) {
        //使用<char, string>映射字符串中单词
        //使用istringstream读取单词
        unordered_map<char, string> m;
        istringstream in(str);
        int i = 0;
        for (string word; in >> word; ++i) {
            if (m.find(pattern[i]) != m.end()) {
                if (m[pattern[i]] != word) return false;
            } else {
                for (unordered_map<char, string>::iterator it = m.begin(); it != m.end(); ++it) {
                    if (it->second == word) return false;
                }
                m[pattern[i]] = word;
            }
        }
        return i == pattern.size();
    }
};
```

#### 500. Keyboard Row
这道题给了我们一些单词，问哪些单词可以由键盘上的一行中的键符打出来，难度其实并不大。
* 首先我们把键盘的三行字符分别保存到三个set中.
* 然后遍历每个单词中的每个字符，分别看当前字符是否在三个集合中，如果在，对应的标识变量变为1，我们统计三个标识变量之和就知道有几个集合参与其中了，参见代码如下：

```cpp
class Solution {
public:
    vector<string> findWords(vector<string>& words) {
        vector<string> res;
        unordered_set<char> row1{'q','w','e','r','t','y','u','i','o','p'};
        unordered_set<char> row2{'a','s','d','f','g','h','j','k','l'};
        unordered_set<char> row3{'z','x','c','v','b','n','m'};
        for (string word : words) {
            //访问字符串中每个单词的每个英文字母在三个set的哪个；
            int one = 0, two = 0, three = 0;
            for (char c : word) {
                if (c < 'a') c += 32;
                if (row1.count(c)) one = 1;
                if (row2.count(c)) two = 1;
                if (row3.count(c)) three = 1;
                if (one + two + three > 1) break;
            }
            if (one + two + three == 1)
            {
              res.push_back(word);
            }
        }
        return res;
    }
};
```



#### 给一个长度为n的数组，数字从1到n。有一个数字重复出现了一次，从而造成了另一个数字的缺失，让我们找出重复的数字和缺失的数字。
1. 使用另外一个数组统计每个数字出现的次数。
2. 然后再遍历次数数组，如果某个数字出现了两次就是重复数，如果出现了0次，就是缺失数，参见代码如下：

```cpp
class Solution {
public:
    vector<int> findErrorNums(vector<int>& nums)
    {
        //声明两个辅助数组：
        //1.cnt记录每个数字的出现次数cnt[i]=times
        //2.res记录重复数字和缺失数字
        vector<int> res(2, 0), cnt(nums.size(), 0);
        for (int num : nums)
            ++cnt[num - 1];
        for (int i = 0; i < cnt.size(); ++i)
        {
            if (res[0] != 0 && res[1] != 0)
                return res;
            if (cnt[i] == 2)
                res[0] = i + 1;
            else if (cnt[i] == 0)
                res[1] = i + 1;

        }
        return res;
    }
};
```


---
