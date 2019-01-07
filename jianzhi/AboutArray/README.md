数组：

数组搜索问题：数组中所有非递减子序列、
topK问题：找出（有序or无序）数组中第K大的数topk、从长序列中找出前K大的数字、
数组变形问题：旋转数组的搜索操作、两个排序数组求交集、


#### 求出数组所有元素的右边第一个比其大的数
* 这个问题，从直觉上来讲，应当是一遍遍历，便可以解决问题。
* 这类问题的特点是: 既要详尽保留信息，又要呈现未解决问题的积累特性。
* 具体到这个问题，选栈来保留未解决的子问题。

具体做法：
1. 栈里面保留元素的索引：因为索引的信息要比内容多，索引既可以确定元素的内容还可以确定元素的位置。
2. 初始栈，里面为第一个元素的索引。
3. 如果栈不为空，而且当前处理元素的值比栈顶索引代表的元素的值大，则栈顶元素的右边第一个比其大的值就是当前访问的元素。
4. 弹出栈顶元素，继续处理栈里的元素，直至为空或当前处理元素不大于栈顶元素。
5. 将当前元素压入栈。
6. 循环3~5。

```cpp 
vector<int> foo(vector<int> a)
{   
    int length = a.size();
	vector<int> res(length, -1);
	stack<int> indexes;
	indexes.push(0);
	for (int i = 1; i < length; i++){
		while (!indexes.empty() && a[i]>a[(indexes.top())]){
			res[(indexes.top())] = a[i];
			indexes.pop();
		}
		indexes.push(i);
	}
	return res;
}
```

#### 使用位运算找无序数组中第一个顺位缺失数字
Xor异或：由于b^b=0(这里是进行位异或)，所以a^b^b=a^0=a.

这里取a=0,依次与‘i’，‘nums[i]’进行异或运算.
如：a = a^0^0^1^1…^k^…n^n = a^k = 0^k = k.
```cpp
class Solution {
public:
    int missingNumber(vector<int>& nums) {
        int result = nums.size();
        int i=0;
        
        for(int num:nums){
            result ^= num;
            result ^= i;
            i++;
        }
        return result;
    }
};
```

#### 求一个无序数组求中位数
中位数在奇数个元素的数组中就是中间那个数，在偶数个元素的数组中就是中间两个数的平均值。


#### 有序数组去多个重复
1. 使用cur作为哨兵维护无重复段的尾部的后一个位置。
2. 从第nums[1]个数开始，只有当前数大于nums[cur-1]才nums[cur++]=val
4. 否则for(int val:nums)进入nums数组下一个元素，而cur不自增仍然维持无重复段尾部。  

输入： [1,1,2],  
输出: [1,2]


```cpp
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
    int cur = 0;
    for (int val : nums)
        if (!cur || val > nums[cur-1])
            nums[cur++] = val;
    return cur;
}
};
```

#### 查找数组中唯一的一个重复元素
给N个数的数组，数组元素取值范围只有[1,n-1],并保证数组有且仅有一个重复数字，找出他。  
Input: [1,3,4,2,2]  
Output: 2  

```cpp
class Solution {
public:
int findDuplicate(vector<int>& nums) {
    int n=nums.size()-1;
    int low=1;
    int high=n;
    int mid;
    while(low<high){
        mid=(low+high)/2;
        int count=0;
        for(int num:nums){
            if(num<=mid) count++;
        }
        if(count>mid) high=mid;
        else low=mid+1; 
    }
    return low;
}
};
```

#### 二分搜索

```cpp
int search(vector<int>& nums, int target) {
    
    int left = 0;
    int right = nums.size()-1;
    
    while(left <= right) {
        int mid = (left + right)/2;
        if(nums[mid] < target) 
            left = mid+1;
        else if(nums[mid] > target) 
            right = mid-1;
        else 
            return mid;
    }
    return -1;
}
```

#### 实现包含min功能的栈
题目描述

1. 需要用到一个存储实时min值的辅助栈，辅助栈的栈顶永远都是当前栈的最小值。min栈的栈顶只能越来越小
2. 当入栈元素大于min栈栈顶元素时，该元素只入普通存储栈不入min栈。反之则既入普通栈又入min栈
3. 在出栈时如果元素是min栈栈顶元素，则min栈也出栈。

```cpp
#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    stack<int> E, EMin;
    
    void push(int value) {
        E.push(value);
        if(EMin.empty())
            EMin.push(value);
        if(value<=EMin.top())
            EMin.push(value);
    }
     
    void pop() {
        if(E.top()==EMin.top())
            EMin.pop();
        E.pop();
    }
   
    int top() {
        return E.top();       
    }
     
    int min() {
        return EMin.top();
    }
     
};
```

#### 判断栈的压入、弹出序列是否正确

* 利用到的性质：
  * 当某个元素出栈时，早于其入栈的元素不会晚于其出栈
* 解题过程：
  1. 创建一个模拟栈，每次往其中push一个元素
  2. 每次push元素之后，和出栈序列的第一个元素对比：
        * 如果相等则说明当前元素已经出栈，此时也把这个元素从模拟栈中pop_back掉
        * 然后继续这个比较过程，直到不相等
  3. 最后返回模拟栈是否为空的结果

```cpp
class Solution {
public:
     bool IsPopOrder(vector<int> pushV, vector<int> popV) {
        if (pushV.size() == 0) 
            return false;

        vector<int> stack;
        for (int i = 0, j = 0; i < pushV.size();) {
            stack.push_back(pushV[i++]);
            while (j < popV.size() && 
                stack.back() == popV[j]) {

                tack.pop_back();
                j++;
            }
        }
        return stack.empty();
    }
};
```

#### 用两个栈实现队列
用两个栈来实现一个队列，完成队列的Push和Pop操作。 队列中的元素为int类型。

本题没有什么特殊的东西，算是对队列FIFO和栈FILO的理解吧。

```cpp
class Solution{
public:
    void push(int V){
        E1.push(V);
    }

    int pop(){
      int RS, TMP;
      RS = 0;
      TMP = 0;
      if (!E2.empty()){
          RS = E2.top();
          E2.pop();
          return RS;
      }
      while(!E1.empty()){
        TMP = E1.top();
        E2.push(TMP);
        E1.pop();
      }
    }
private:
    stack<int> E1, E2;
}
```



### 数组变形相关


#### 将数组元素组成一个数值最大的数字  
给一组数字，要求将这些数字组成一个数值最大的数字。
For example, given [3, 30, 34, 5, 9], the largest formed number is 9534330.  


解题思路:  

1. 大数值题目记得使用字符串进行保存。 
2. 对于任意给定正整数的数组，Largest Number是唯一的，只有当每个元素都处在数组所有元素中的一个特定相对位置时才能得到那个Largest Number。
2. 所以，本题‘找到数组的Largest formed number’问题转化成‘按特定排序规则对数组正整数进行排序，得到Largest formed number’ 是合理的思路


解题步骤:
1. 将题目求Largest formed number 看成对数组元素按特定排序规则排序的题目，特定规则为: 如果 字符串组合 str1+str2 < str2+str1，此时应该将str2排在str1前面（可以看作是：str2 < str1）.  
2. 把nums数组中所有正整数转化成字符串然后存到临时vector<string> tmp中。 将上述规则写成自定义函数，然后对tmp按规则排序.  
3. 排序后会得到这么一个vector<string> tmp，即: 对于tmp中的任两个元素 str1 和 str2 (str1位于str2之前), 都有 str1+str2 > str2+str1; 此时tmp组成的字符串满足nums的Largest formed number要求.  
比如： [3, 30, 34, 5, 9] --排序后--> [9,5,34,3,30]; 此时 "95 > 59", "934 > 349", "93 > 39", "930 > 309"，说明9排在第一个位置时，数组组成的字符串才有可能是Largest formed number.  

```cpp
class Solution {
public:
    string largestNumber(vector<int>& nums) {
        //先将数字转为字符串然后放入vector<string>中
        vector<string> tmp;
        for(auto i:nums) {
            tmp.push_back(to_string(i));
        }
        //然后使用字符串大小比较的方式对vector<string>进行排序
        // [捕获数据方式](参数列表){函数体}
        sort(begin(tmp), end(tmp),
            [](string& s1, string& s2){ return s1+s2 > s2+s1;});
        //最后将tmp的字符串连起来形成一个largetst number
        string result;
        for(auto s:tmp)
            result+=s;
        //并去掉前到导0
        while(result[0]=='0' && result.length()>1)
            result.erase(0,1);
        return result;
    }
};
```

#### Wiggle Sort II
给一个无序数组，将其排列成nums[0] < nums[1] > nums[2] < nums[3]....  的规律。

Example:    
(1) Given nums = [1, 5, 1, 1, 6, 4], one possible answer is [1, 4, 1, 5, 1, 6].     
(2) Given nums = [1, 3, 2, 2, 3, 1], one possible answer is [2, 3, 1, 3, 1, 2].    


解题思路:  

给定一个整数序列，需要得到一个wiggle sort序列，其中：任意奇数位置的元素都大于其左右相邻偶数位置的元素。  

可以先:  
1. 对整组序列按递减排序。
2. 然后找到序列的中间数m，那么位于中间数之前的元素就都大于位于中间数之后的元素。
3. 使用插空法的方式，将中间数之后的元素插到到中间数之前的序列的奇数位置上。

如:
origin: [1,5,1,1,6,4]  
reverse sort: [6,5,4,1,1,1], median is [4], the larger part is [6,5], the smaller part is [1,1,1]  
insertion operation: [1,6,1,5,1,4]

``` cpp
class Solution {
private:
	int partition(vector<int>& nums, int l, int h) {
		int pivot = nums[h], m = l - 1;
		for (int i = l; i < h; i++) {
			if (nums[i] > pivot) {
				int tmp = nums[i];
				nums[i] = nums[++m];
				nums[m] = tmp;
			}
			else {
				//do nothing
			}
		}
		int tmp = nums[h];
		nums[h] = nums[++m];
		nums[m] = tmp;
		return m;
	}
	void quickSort(vector<int>& nums, int l, int h) {
		int p;
		if (l < h) {
			p = partition(nums, l, h);
			quickSort(nums, l, p - 1);
			quickSort(nums, p + 1, h);
		}
	}
public:

	void wiggleSort(vector<int>& nums) {
		int s = nums.size();
		if (s == 0) return;
		if (s == 1) return;
		quickSort(nums, 0, s - 1);
		vector<int> tmp = nums;
		//这里应该取中间数的前一位，而不是就取中间数的位置。
		//如果直接取中间数的位置，在当中间数大于2个的时候，得到的结果会有两个中间数连在一起
		int median = nums.size() / 2 - 1, i = 0, j = median + 1;
		vector<int>::iterator iter = nums.begin();
		while (i <= median && j < s) {
			*iter = tmp[j];
			*(++iter) = tmp[i];
			++j;
			++i;
			++iter;
		}
        if (j < s) {
			*iter = tmp[j];
		}
		if (i <= median) {
			*iter = tmp[i];
		}
	}

};
```





#### 求两个有重复数组的交集
Given nums1 = [1, 2, 2, 1], nums2 = [2, 2], return [2].


```cpp
class Solution {
public:
    vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
        //使用一个unordered_set存储其中一个数组nums1
        unordered_set<int> dict(nums1.begin(), nums1.end());
        vector<int> res;
        //如果第一次在dict中查到nums2的元素a，则将a存入res
        //并将数值a从dict中删去这样既保证查找到了两数组交集又保证交集不重复
        for (auto a : nums2)
            if (dict.count(a)) {
                res.push_back(a);
                dict.erase(a);
            }
        return res;
    }
};
```

#### 计算数组中的每个元素右侧所有小于它的值的元素的个数
1. 创建一个新数组空间tmp用于将原数组的元素从尾到头的排序
2. 从原数组nums的最后一个元素nums[nums.size()-1]开始，用binary search
插入tmp。
3. 当一个元素插入tmp的right+1处后, 它左侧的元素个数即right的值就是它在原数组时右侧小它的元素的个数。

```cpp
class Solution {
public:
    vector<int> countSmaller(vector<int>& nums)
    {
        vector<int> tmp, res(nums.size());
        for (int i = nums.size() - 1; i >= 0; --i)
        {
            //这个地方和一般二分搜索有一个区别就是右界为tmp.size()
            //而不是一般的tmp.size()-1，这是因为最开始的时候tmp是
            //一个空数组需要特殊处理。因此即使右界取tmp.size()对
            //mid和二分的影响不大
            int left = 0, right = tmp.size();
            while (left < right)
            {
                int mid = left + (right - left) / 2;
                if (tmp[mid] >= nums[i])
                    right = mid;
                else
                    left = mid + 1;
            }
            //将当前元素nums[i]插入tmp的tmp[right]处
            //此时tmp[right]右边有(right-0)即right个元素
            tmp.insert(tmp.begin() + right, nums[i]);
            res[i] = right;
        }
        return res;
    }
};
```

#### 二维数组中的查找
在一个二维数组中，每一行都按照从左到右递增的顺序排序，每一列都按照从上到下递增的顺序排序。请完成一个函数，输入这样的一个二维数组和一个整数，判断数组中是否含有该整数。

1. 从二维数组的右上角开始查找

```cpp
class Solution {
public:
    bool Find(int T, vector<vector<int> > E) {
        if(E.size() == 0 || E[0].size() == 0)
            return false;
        
        int x = 0, y = E[0].size()-1, rows = E.size();
        while(x < rows && y >= 0)
        {
            if(T == E[x][y])
                return true;
            else if(T < E[x][y])
                --y;
            else
                ++x;
        }
        return false;
    }
};
```

#### 004将空格替换成为字符
请实现一个函数，将一个字符串中的空格替换成“%20”。 例如，当字符串为We Are Happy.则经过替换之后的字符串为We%20Are%20Happy。

1. 先确定空格在字符串中出现的数目
2. 在从后往前完成替换，每个非空格字符往后挪空格数目的位置
```cpp
#include <iostream>
using namespace std;
class Solution{
public:
  void replaceSpace(char *str,int length)
  {
      int i, j;
      int count = 0;
      int len = length;
      for(int i = 0; i < length; i++)
          if(str[i] == ' ')
              count++;
      len = length + count * 2;
      for(i = length - 1, j = len - 1;
          i >= 0 && j >= 0;)
      {
          if(str[i] == ' ')
          {
              str[j--] = '0';
              str[j--] = '2';
              str[j--] = '%';
              i--;
          }
          else
              str[j--]  = str[i--];
      }
      str[len] = '\0';
  }
};
```



#### 顺时针打印矩阵
题目描述
输入一个矩阵，按照从外向里以顺时针的顺序依次打印出每一个数字，
例如， 如果输入如下矩阵：

##### 思路：
这题也是比较特殊的题，主要就是打印二维举证的过程中注意边界的控制，不能超出矩阵本来的
边界，也不能重复打印已经打印过的位置，因此可以将边界视作不断缩小的情。
因此，按顺时针逆时针或者某种方向打印数组时，需要注意的有两点：
  1. 维护边界，不要超过数组范围，不要输出已经输出过的点。
  2. 模拟输出时，数组下标的变化。

```cpp
class Solution {
public:
    vector<int> printMatrix(vector<vector<int> > E) {
        int m, n;
        vector<int> res;
        if ((m = E.size()) == 0 || (n = E[0].size()) == 0)
        {
            return res;
        }
        vector<vector<bool> > visited = vector<vector<bool> >(m, vector<bool>(n, false));
        const int D[4][2] = {{0,1},{1,0},{0,-1},{-1,0}};
        for(int c = m * n, i = 0, j = 0, d = 0; c >= 0; --c)
        {
            res.push_back(E[i][j]);
            visited[i][j] = true;
            int ti = i+D[d][0], tj = j + D[d][1];
            if(ti < 0 || ti >= m ||
                tj < 0 || tj >= n ||
                visited[ti][tj])
            {
                d = (d + 1) % 4;
            }
            i += D[d][0];
            j += D[d][1];
        }
        return res;
    }
};
```

#### 输出旋转数组中最小的数字

> 数组{3,4,5,1,2}为{1,2,3,4,5}的一个旋转，该数组的最小值为1。


对于旋转数组的二分搜索：
1. 将旋转数组分为前后两个第增序列[[low....mid][mid+1....high]]，其中因为旋转过所有a[low] > a[high], a[mid-1] < a[mid] > a[mid+1]
2. 如果A[pivot] > A[low],则说明A[pivot]属于[low...mid]的子序列
3. 如果A[pivot]小于A[high]则说明A[pivot]属于后面的子序列则最大值在A[pivot]之前。

```cpp
class Solution {
public:
    int findMin(vector<int> &num) {
        int start=0, end=num.size()-1;
        //二分出口情况2：数组大小为奇数个
        //此时最终一定会有start==end，答案即为start
        while (start<end) {
            //二分搜索出口情况1：数组大小为偶数个
            //start<end且num[start]<num[end]
            if (num[start]<num[end])
                return num[start];
            //二分搜索，如果num[mid] > num[start]
            //说明mid还在前一个子序列中，此时要向后查找最小元素
            //因此让start = mid+1;
            int mid = (start+end)/2;
            if (num[mid]>=num[start]) 
                start = mid+1;
            else 
                end = mid;
        }
        return num[start];
    }
};
```

#### 665. Non-decreasing Array (改变一个数成为非递减数组)
解题思路：  
这道题给了我们一个数组，说我们最多有1次修改某个数字的机会，问能不能将数组变为非递减数组。题目中给的例子太少，不能覆盖所有情况，我们再来看下面三个例子：  

4，2，3  
-1，4，2，3  
2，3，3，2，4  

我们通过分析上面三个例子可以发现，当我们发现后面的数字小于前面的数字产生冲突后，有时候需要修改前面较大的数字(比如前两个例子需要修改4)，有时候却要修改后面较小的那个数字(比如前第三个例子需要修改2)，那么有什么内在规律吗？
* 是有的，判断修改那个数字其实跟再前面一个数的大小有关系，首先如果再前面的数不存在，比如例子1，4前面没有数字了，我们直接修改前面的数字为当前的数字2即可。
* 而当再前面的数字存在，并且小于当前数时，比如例子2，-1小于2，我们还是需要修改前面的数字4为当前数字2；
* 如果再前面的数大于当前数，比如例子3，3大于2，我们需要修改当前数2为前面的数3。
* 这是修改的情况，由于我们只有一次修改的机会，所以用一个变量cnt，初始化为1，修改数字后cnt自减1，当下次再需要修改时，如果cnt已经为0了，直接返回false。遍历结束后返回true，参见代码如下：

```cpp
class Solution {
public:
    bool checkPossibility(vector<int>& nums) {
        int cnt = 1, n = nums.size();
        for (int i = 1; i < n; ++i) {
            if (nums[i] < nums[i - 1]) {
                if (cnt == 0) return false;
                if (i == 1 || nums[i] >= nums[i - 2]) nums[i - 1] = nums[i];
                else nums[i] = nums[i - 1];
                --cnt;
            }
        }
        return true;
    }
};
```


#### 014 调整数组顺序使得奇数位于偶数前面并保持奇数之间和偶数之间的相对位置
题目描述

输入一个整数数组，实现一个函数来调整该数组中数字的顺序，使得所有的奇数位于数组的前半部分，所有的偶数位于位于数组的后半部分，并保证奇数和奇数，偶数和偶数之间的相对位置不变。

> 样例输入
5 1 2 3 4 5

> 样例输出
1 3 5 2 4

##### 解题思路：
这题算是调整数组顺序的问题，虽然没有按大小排序的要求，但是按其他任意排序的问题都应该归结为排序问题。
然后本题还要求是稳定的排序，因此只能考虑插入排序、冒泡排序。综上所述，调整数组奇数偶数的相对位置，就是
在考察简单的冒泡排序。
```cpp
#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    void reOrderArray(vector<int> &E) {
        int S, tmp;

        S = E.size();
        if(S <= 1) return;

        tmp = 0;
        while (S >= 2) {
            int i, j;
            i = 0;
            j = 1;
            for (; j < S; ++i, ++j){
                if (E[i] % 2 == 0 && E[j] % 2 != 0){
                    tmp = E[i];
                    E[i] = E[j];
                    E[j] = tmp;
                }
            }
            --S;
        }
    }
};
```

#### 范围搜索一个有序且有重复元素的数组
For example,  
Given [5, 7, 7, 8, 8, 10] and target value 8,  
return [3, 4].  


我们的思路是首先对原数组使用二分查找法。
1. 先找出其中一个目标值的位置。
2. 然后向两边搜索找出起始和结束的位置，代码如下：

```cpp
class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        int idx = search(nums, 0, nums.size() - 1, target);
        if (idx == -1) 
            return {-1, -1};
        int left = idx, right = idx;
        while (left > 0 && nums[left - 1] == nums[idx]) 
            --left;
        while (right < nums.size() - 1 && 
            nums[right + 1] == nums[idx]) 
            ++right;
        return {left, right};
    }
    int search(vector<int>& nums, int left, int right, int target) {
        if (left > right) 
            return -1;
        int mid = left + (right - left) / 2;
        if (nums[mid] == target) 
            return mid;
        else if (nums[mid] < target) 
            return search(nums, mid + 1, right, target);
        else 
            return search(nums, left, mid - 1, target);
    }
};
```

#### Third Maximum Number 第三大的数 (变量记录元素值法)

1. 用三个变量first, second, third保存前三大的数字。
2. 然后遍历数组，当前元素num[i]>first，third = second, second = first, first=num[i]。
3. 如果first>num[i]>second，那么third = second, second = num[i]
4. 如果first>second>num[i]>third, 那么third=num[i]

注意这里有个坑，就是初始化要用长整型long的最小值，否则当数组中有INT_MIN存在时，程序就不知道该返回INT_MIN还是最大值first了，参见代码如下：

```cpp
class Solution {
public:
    int thirdMax(vector<int>& nums) {
        long first = LONG_MIN, second = LONG_MIN, third = LONG_MIN;
        for (int num : nums) {
            if (num > first) {
                third = second;
                second = first;
                first = num;
            } 
            else if (num > second && num < first) {
                third = second;
                second = num;
            } 
            else if (num > third && num < second)
                third = num;
        }
        return (third == LONG_MIN || third == second) ? first : third;
    }
};
```


#### 029 数组中出现次数超过一半的数字(排序和查找法)
题目描述
数组中有一个数字出现的次数超过数组长度的一半，请找出这个数字。例如输入一个长度为9的数组{1,2,3,2,2,2,5,4,2}。由于数字2在数组中出现了5次，超过数组长度的一半，因此输出2。如果不存在则输出0。
##### 解题思路：
这题算是数组元素统计题，是比较好想到题解的。最简单的就是，对数组排序，然后中间的那个数一定是
超过数组一半元素的嫌疑数，然后再遍历一遍数组，计算嫌疑数出现的次数即可。

我这里用的是数组元素的对消法，如果存在超出数组一半的元素，那么我们对数组中相同元素两两
相合，不同元素两两相消，那么剩下的元素就是嫌疑元素，然后再遍历一遍数组元素确认这个嫌疑元素
出现的次数即可。


```cpp
class Solution {
public:
    int MoreThanHalfNum_Solution(vector<int> E) {
        int S = E.size()
        if (S == 0)
            return 0;
        else if (S == 1)
            return E[0];
        else
        {
            int count = 1, res = E[0];
            for(int i = 1; i < S; ++i)
            {
                count += E[i] == res ? 1 : -1;
                if (count == 0)
                {
                    res = E[i];
                    count = 1;
                }
            }
            int recount = 0;
            for (int i = 0; i < S; ++i)
            {
                if (E[i] == res)
                    ++recount;
            }
            return 2*recount > S ? res : 0;
        }
    }
};
```

#### 030 最小的K个数
题目描述
输入n个整数，找出其中最小的K个数。例如输入4,5,1,6,2,7,3,8这8个数字，则最小的4个数字是1,2,3,4。

##### 解题思路：
这题算是常见搜索相关问题里面被讨论比较多，比较有深度的问题。因为可以应用上的方法很多，从快速排序的各种加强版本，到最小堆。July还为此专门有一个专题。[专题](https://github.com/gatieme/CodingInterviews/tree/master/030-%E6%9C%80%E5%B0%8F%E7%9A%84K%E4%B8%AA%E6%95%B0)

* 最大堆求数组最小k个数：
```cpp
class Solution {
public:
    vector<int> Solution(vector<int> E, int k)
    {        
        vector<int> res;

        if(E.size( ) == 0 || E.size( ) < k)
        {
            return res;
        }
        make_heap(E.begin( ), E.R( ), greater_class());

        for(int i = 0; i < k; i++)
        {
            //最小的元素在栈顶
            res.push_back(E[0]);

            ///  一下两种操作均可以
            // [1]  --  清除它, 然后重新排序堆
            //E.erase(E.begin( ));
            //sort_heap(E.begin( ), E.R( ));
            // [2]  --  当然从堆出弹出这个栈顶元素
            pop_heap(E.begin( ), E.R( ), greater_class( ));   // 弹出一个元素后，剩下的又重建了 heap，仍保持heap的性质
            E.pop_back();         // vector 删除末尾元素
        }

        return res;
    }

    class greater_class
    {
    public:

        bool operator()(int a, int b)
        {
            return a > b;
        }
    }
};
```

#### 036 数组中的逆序对
题目描述

在数组中的两个数字，如果前面一个数字大于后面的数字，则这两个数字组成一个逆序对。 输入一个数组，求出这个数组中的逆序对的总数

> 样例输入
7 5 6 4

>样例输出
5

##### 解题思路：
逆序对相关问题直接和归并排序相关的。
* 采用归并排序，计算每次左右两边的逆序对。
* 然后再计算merge后的逆序对。

```cpp
class Solution {
public:
    int InversePairs(vector<int> E) {
       int S = E.size();
       if(S <= 0)
       {
           return 0;
       }
       vector<int> copy(E.begin(),E.end());
       return InversePairsCore(E, copy, 0, S-1) % 1000000007;
    }
    long long InversePairsCore(vector<int> &E, vector<int> &copy, int L, int R)
    {
       if(L == R)
          {
            copy[L] = E[L];
            return 0;
          }
       int M = L + (R - L) / 2;
       long long res1 = InversePairsCore(E, copy, L, M);
       long long res2 = InversePairsCore(E, copy, M + 1, R); 
       
       int i = M;
       int j = R;
       int indexcopy = R;
       long long count = 0;
       while(i >= L && j > M)
          {
             if(E[i] > E[j])
                {
                  copy[indexcopy--] = E[i--];
                  count += j - M;
                }
             else
                {
                  copy[indexcopy--] = E[j--];
                }          
          }
       for(; i >= L; --i)
           copy[indexcopy--] = E[i];
       for(; j > M; --j)
           copy[indexcopy--] = E[j];
       for (int i = L; i <= R; ++i)
           E[i] = copy[i];
       return res1 + res2 + count;
    }
};
```

#### 038 数字在排序数组中出现的次数
题目描述  
统计一个数字在排序数组中出现的次数。

解题思路：  
* 暴力搜索解空间求解：  
本题可以简单地使用顺序暴力统计的方式解题。相当于遍历解空间以求解。

* 提升解空间维度+二分搜索求解：  
但是这题也可以高效地在解空间中搜索，就是将解空间增大一个维度，以“数值+元素位置”作为解空间的两个维度，此时每个元素都是唯一的了，然后通过二分搜索找出第一个出现的数字K和最后一个出现的数字k，然后将他们的序号相减就得到数字K在数组中出现的次数。


```cpp
class Solution
{
    /*二分查找 找到第一个K 和 最后一个K 二者位置相减*/
public:
    int GetNumberOfK(vector<int> E ,int k)
    {
        if(E.empty())
        {
            return 0;
        }

        int RESULT, A, B, S;
        S = E.size();
        RESULT = 0;
        A = GetFirstIndex(E, k, 0, S - 1);
        B  = GetLastIndex(E, k, 0, S - 1);

        if(A > -1 && B > -1)
        {
            RESULT = B - A + 1;
            return RESULT;
        }
    }

    // 查找第一个的位置
    int GetFirstIndex(vector<int> &E, int L, int R, int k)
    {
        if(L > R)
        {
            return -1;
        }

        int mid;

        mid = L + (R - L) / 2;

        if(E[mid] > k)
        {
            R = mid - 1;
        }
        else if(E[mid] < k)
        {
            L = mid + 1;
        }
        else
        {
            if((mid > 0 && E[mid-1] != k) || mid == 0)
            {
                return mid;
            }
            else
            {
                R = mid - 1;
            }
        }

        return GetFirstIndex(E, k, L, R);
    }

    int GetLastIndex(vector<int> &E, int L, int R, int k)
    {
        if(L > R)
        {
            return -1;
        }

        int mid;
        mid = (L + R) / 2;

        if(E[mid] > k)
        {
            R = mid - 1;
        }
        else if(E[mid] < k)
        {
            L = mid + 1;
        }
        else
        {
            if((mid>0 && E[mid+1] !=k) || mid == R)
            {
                return mid;
            }
            else
            {
                L = mid +1;
            }
        }

        return GetLastIndex(E,k,low,R);
    }
};
```

#### 040 数组中只出现一次的数字
题目描述

一个整型数组里除了两个数字之外，其他的数字都出现了两次。请写程序找出这两个只出现一次的数字。  

> 样例输入  
2 4 3 6 3 2 5 5

> 样例输出  
4 6

解题思路：  
此题是一道搜索问题，但是此题根数字排序无关只和数字出现次数有关。并且只有两个元素只出现一次，其他元素都出现了两次。这样的出现次数应该及时联系到与“两个相同元素相抵”有关的算术运算。  
 * 全局计数相抵：即全局遍历整个数组，相同元素则计数加1，不同则计数减1，计数为0时换成下一个元素进行计数。这种方法在问题“求出现次数超过数组一半大小的元素”中使用到。  

但是本题如果使用全局计数相抵相关的方法，其时间复杂度依然是O(n^2)，因为需要对每个元素进行全局遍历，才能确定它是不是只出现一次。  

* 异或相同元素结果为0：因为相同元素的异或结果为0，所以把数组中的元素一起异或得到的结果一定不为0，因为存在两个只出现一次的元素。然后根据bit位找到bit值为1的最高位元素，根据这个位置是否为1可以把数组分成两部分。然后再对这两部分分别计算异或，可想而知这两个结果就是只出现一次的两个数字。  
ps: 找xor中最后一个1的位置的时候，可以用(XOR & (-XOR))

```cpp
class Solution
{
public:
    #define INT_SIZE (sizeof(int) * 8)

    #define IS_BIT(number, index) (((number) & (1 << (index))) >>index)

    void FindNumsAppearOnce(vector<int> array, int *num1, int *num2)
    {
        *num1 = *num2 = 0;
        if(array.size( ) < 2)
        {
            return ;
        }
        int XOR = array[0];
        for(int i = 1; i < array.size( ); i++)
        {
            XOR ^= array[i];
        }

        ///  查找到1的位置
        int flag = XOR & (-XOR);
        *num1 = *num2 = XOR;// 也可以等于XOR
        for(int i = 0; i < array.size( ); i++)
        {
            if((array[i] & flag) == flag)
            {
                *num1 ^= array[i];
            }
            else
            {
                *num2 ^= array[i];
            }
        }
    }
};
```

#### *051 数组中重复的数字

**题目描述**  
在一个长度为n的数组里的所有数字都在0到n-1的范围内。数组中某些数字是重复的，但不知道有几个数字是重复的。也不知道每个数字重复几次。请找出数组中任意一个重复的数字。例如，如果输入长度为7的数组{2,3,1,0,2,5,3}，那么对应的输出是重复的数字2或者3。  

> 样例输入  
2, 3, 1, 0, 2, 5, 3  
2, 1, 3, 1, 4  

> 样例输出  
2  
1


解题思路：  
本题最简单的解法就是为每个元素遍历整个数组也就是遍历整个解空间。  

缩小解空间：如果再将元素排序后在进行搜索，，那么可以将每个元素搜索时涉及到的解空间大小缩小到其元素相邻的右边一个元素。

再降低时间复杂度：因为排序最好的时间复杂度只能到O(nlogn),所以本题如果还想提高时间复杂度，那么可以往hashset辅助查找。也就是说我们可以从前到后构造一个unique set，每当有元素被添加到set时，需要查找是否已经存在此元素，若存在则说明重复。

```cpp
class Solution
{
public:
    bool CheckValidity(int *numbers, int length)
    {
      //  输入数据不合法
      if(numbers == NULL || length <= 0)
      {
        return false;
      }

      //  元素必须在[0, n-1]的范围
      for(int i = 0; i < length; i++)
      {
        if(numbers[i] < 0 || numbers[i] > length - 1)
        {
          return false;
        }
      }

      return true;
    }
    // Parameters:
    //        numbers:     an array of integers
    //        length:      the length of array numbers
    //        duplication: (Output) the duplicated number in the array number
    // Return value:       true if the input is valid, and there are some duplications in the array number
    //                     otherwise false
    bool duplicate(int numbers[], int length, int* duplication)
    {
        *duplication = -1;

        if(CheckValidity(numbers, length) == false)
        {
            return false;
        }

        set<int> s;
        bool isDup;
        isDup = false;
        for(int i = 0; i < length; i++)
        {
            if(s.count(numbers[i]) == 1)  // 如果当前元素已经存在set中
            {
                isDup = true;
                *duplication = numbers[i];
                break;
            }
            s.insert(numbers[i]);

        }

        return isDup;
    }
};
```


#### 052 构建乘积数组
**题目描述**

给定一个数组A[0,1,...,n-1],请构建一个数组B[0,1,...,n-1],其中B中的元素B[i]=A[0]A[1]...A[i-1]A[i+1]...A[n-1]。不能使用除法。
> 样例输入  
[1, 2, 3, 4, 5]

>样例输出  
[120, 60, 40, 30, 24]

* 解法1：  
这个解法就是利用解的叠加性，简化计算过程。

<分析>：  
解释下代码，设有数组大小为5。  
对于第一个for循环  
第一步：b[0] = 1;  
第二步：b[1] = b[0] * a[0] = a[0]  
第三步：b[2] = b[1] * a[1] = a[0] * a[1];  
第四步：b[3] = b[2] * a[2] = a[0] * a[1] * a[2];  
第五步：b[4] = b[3] * a[3] = a[0] * a[1] * a[2] * a[3];  
然后对于第二个for循环  
第一步  
temp *= a[4] = a[4];  
b[3] = b[3] * temp = a[0] * a[1] * a[2] * a[4];  
第二步  
temp *= a[3] = a[4] * a[3];  
b[2] = b[2] * temp = a[0] * a[1] * a[4] * a[3];  
第三步  
temp *= a[2] = a[4] * a[3] * a[2];  
b[1] = b[1] * temp = a[0] * a[4] * a[3] * a[2];  
第四步  
temp *= a[1] = a[4] * a[3] * a[2] * a[1];  
b[0] = b[0] * temp = a[4] * a[3] * a[2] * a[1];  
由此可以看出从b[4]到b[0]均已经得到正确计算。  

```cpp
class Solution {
public:
  vector<int> multiply(const vector<int>& E) {
      vector<int> vec;
      int sz=E.size();
      if(sz==0)
        return vec;
      vec.push_back(1);
      for(int i=0;i<sz-1;i++)
        vec.push_back(vec.back()*E[i]);
      int tmp=1;
      for(int i=sz-1;i>=0;i--)
      {
        vec[i]=vec[i]*tmp;
        tmp=tmp*E[i];
      }
      return vec;
  }
};
```

* **解法2**：
B[i]的值可以看作下图的矩阵中每行的乘积。  
下三角用连乘可以很容求得，上三角，从下向上也是连乘。  
因此我们的思路就很清晰了，先算下三角中的连乘，即我们先算出B[i]中的一部分，然后倒过来按上三角中的分布规律，把另一部分也乘进去。


```cpp
public class Solution {
    public int[] multiply(int[] A) {
        int length = A.length;
        int[] B = new int[length];
        if(length != 0 ){
            B[0] = 1;
            //计算下三角连乘
            for(int i = 1; i < length; i++){
                B[i] = B[i-1] * A[i-1];
            }
            int temp = 1;
            //计算上三角
            for(int j = length-2; j >= 0; j--){
                temp *= A[j+1];
                B[j] *= temp;
            }
        }
        return B;
    }
}
```


### 子数组的和的相关问题
计算子数组之和的常用方法应该是建立累加数组，然后我们可以快速计算出任意一个长度为k的子数组，用来更新结果res。

#### Maximum Average Subarray I 子数组的最大平均值

```cpp
class Solution {
public:
    double findMaxAverage(vector<int>& nums, int k) {
        int n = nums.size();
        vector<int> sums = nums;
        for (int i = 1; i < n; ++i) {
            sums[i] = sums[i - 1] + nums[i];
        }
        double mx = sums[k - 1];
        for (int i = k; i < n; ++i) {
            mx = max(mx, (double)sums[i] - sums[i - k]);
        }
        return mx / k;
    }
};
```




### 数组排列组合+DFS

#### 79. Word Search

解题思路*：  
这道题是典型的深度优先遍历DFS的应用，原二维数组就像是一个迷宫，可以上下左右四个方向行走，我们以二维数组中每一个数都作为起点和给定字符串做匹配，我们还需要一个和原数组等大小的visited数组，是bool型的，用来记录当前位置是否已经被访问过，因为题目要求一个cell只能被访问一次。如果二维数组board的当前字符和目标字符串word对应的字符相等，则对其上下左右四个邻字符分别调用DFS的递归函数，只要有一个返回true，那么就表示可以找到对应的字符串，否则就不能找到，具体看代码实现如下：

```cpp
class Solution {
public:
    bool exist(vector<vector<char> > &board, string word) {
        if (word.empty()) return true;
        if (board.empty() || board[0].empty()) return false;
        vector<vector<bool> > visited(board.size(), vector<bool>(board[0].size(), false));
        for (int i = 0; i < board.size(); ++i) {
            for (int j = 0; j < board[i].size(); ++j) {
                if (search(board, word, 0, i, j, visited)) return true;
            }
        }
        return false;
    }
    bool search(vector<vector<char> > &board, string word, int idx, int i, int j, vector<vector<bool> > &visited) {
        if (idx == word.size()) return true;
        if (i < 0 || j < 0 || i >= board.size() || j >= board[0].size() || visited[i][j] || board[i][j] != word[idx]) return false;
        visited[i][j] = true;
        bool res = search(board, word, idx + 1, i - 1, j, visited)
                 || search(board, word, idx + 1, i + 1, j, visited)
                 || search(board, word, idx + 1, i, j - 1, visited)
                 || search(board, word, idx + 1, i, j + 1, visited);
        visited[i][j] = false;
        return res;
    }
};
```

### 滑动窗口计算数组的子数组
解题思路：  
这道题给了我们一个数组，让我们求最短的无序连续子数组，根据题目中的例子也不难分析出来是让我们找出数组中的无序的部分。
* 那么我最开始的想法就是要确定无序子数组的起始和结束位置，这样就能知道子数组的长度了。
    * 所以我们用一个变量start来记录起始位置，然后我们开始遍历数组，当我们发现某个数字比其前面的数字要小的时候，说明此时数组不再有序，所以我们要将此数字向前移动，移到其应该在的地方；
    * 我们用另一个变量j来记录移动到的位置，然后我们考虑要不要用这个位置来更新start的值，当start还是初始值-1时，肯定要更新，因为这是出现的第一个无序的地方，还有就是如果当前位置小于start也要更新，这说明此时的无序数组比之前的更长了。
* 我们举个例子来说明，比如数组[1,3,5,4,2]，第一个无序的地方是数字4，它移动到的正确位置是坐标2，此时start更新为2，然后下一个无序的地方是数字2，它的正确位置是坐标1，所以此时start应更新为1，这样每次用i - start + 1来更新结果res时才能得到正确的结果，参见代码如下：
```cpp
class Solution {
public:
    int findUnsortedSubarray(vector<int>& nums) {
        int res = 0, start = -1, n = nums.size();
        for (int i = 1; i < n; ++i) {
            if (nums[i] < nums[i - 1]) {
                int j = i;
                while (j > 0 && nums[j] < nums[j - 1]) {
                    swap(nums[j], nums[j - 1]);
                    --j;
                }
                if (start == -1 || start > j) start = j;
                res = max(res, i - start + 1);
            }
        }
        return res;
    }
};
```
