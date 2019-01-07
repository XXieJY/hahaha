## 链表

### 常见考点
1. 双指针: 双指针分为先后指针和快慢指针两种。
    * 先后指针主要解决：倒数第k个节点、逆向查找单向链表的相关问题。
    * 快慢指针主要解决：单个链表存在环的问题、找链表的中间节点；
2. 栈和递归：解决逆向查找单向链表的相关问题。
3. 头插法：可以反转链表。



#### 判断链表是否有环

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




#### 链表中环的入口结点

题目描述

一个链表中包含环，请找出该链表的环的入口结点。


解题思路：  
设快慢指针，不过这次要记录两个指针相遇的位置，当两个指针相遇了后，让其一指针从链表头开始，此时再相遇的位置就是链表中环的起始位置。代码如下

```cpp
class Solution {
public:
    ListNode *detectCycle(ListNode *head) {
        ListNode *slow = head, *fast = head;
        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
            if (slow == fast) break;
        }
        if (!fast || !fast->next) return NULL;
        slow = head;
        while (slow != fast) {
            slow = slow->next;
            fast = fast->next;
        }
        return fast;
    }
};
```


#### 链表排序相关  


##### 使用插入排序为单链表排序

解题思路：
1. 链表插入排序思路和一般插入排序思路大致相同，首先维护一个游标cur指向左侧有序子链表的最后一个节点。
2. 不同的是，我们还需要维护一个pre指针，初始化时指向链表表头节点new_head，其作用是：每次需要将右侧无序元素插入到左侧在子链表时，都使用pre指针从new_head位置开始遍历有序子链表，直至找到正确插入位置即cur的后一个节点，此时有pre -> next -> val >= cur -> next -> val;
3. 在pre指针找到当前无序元素正确插入位置时，就可以执行链表节点的插入操作，如图所示：
![](https://coding.net/u/jxie0001/p/config/git/raw/master/InsertionSort.png)


```cpp
class Solution {
public:
    ListNode* insertionSortList(ListNode* head) {
        //链表操作提前制造一个blank head可以统一并简化遍历操作
        ListNode* new_head = new ListNode(0);
        new_head -> next = head;
        //pre始终指向blank head，哨兵cur指向链表当前有序部分的最后一个节点
        ListNode* pre = new_head;
        ListNode* cur = head;
        while (cur) {
            //如果哨兵cur的下一个节点非空，且下一个节点值小于当前节点值。
            //则进入插入阶段
            if (cur->next && cur->next->val < cur->val) {
                //使用pre指针从头结点开始为cur的下一个节点在链表的
                //有序部分找到合适的插入位置，因为cur->next->val < cur->val
                //所以一定能够找到cur->next的合适插入位置
                while (pre->next && pre->next->val < cur->next->val)
                    pre = pre -> next;
                //pre指向cur->next合适位置的前一节点
                //tmp指向cur->next合适位置的后一个节点
                ListNode* temp = pre->next;
                pre->next = cur->next;
                cur->next = cur->next->next;
                pre->next->next = temp;
                //将pre重置到Blank head
                pre = new_head;
            }
            //如果cur->next为空则cur=cur->next后会在下一个循环退出while
            //或者cur->next->val > cur->val，则当前节点直接加入尾部即有序
            else
                cur = cur->next;
        }
        //去掉blank head并返回即可
        ListNode* res = new_head -> next;
        delete new_head;
        return res;
    }
};
```


##### 归并排序单项链表

常见排序方法有很多，插入排序，选择排序，堆排序，快速排序，冒泡排序，归并排序，桶排序等等。。它们的时间复杂度不尽相同，而这里题目限定了时间必须为O(nlgn)，符合要求只有快速排序，归并排序，堆排序，而根据单链表的特点，最适于用归并排序。代码如下：

```cpp
class Solution {
public:
    ListNode* sortList(ListNode* head) {
        if (!head || !head->next) return head;
        ListNode *slow = head, *fast = head, *pre = head;
        while (fast && fast->next) {
            pre = slow;
            slow = slow->next;
            fast = fast->next->next;
        }
        pre->next = NULL;
        return merge(sortList(head), sortList(slow));
    }
    ListNode* merge(ListNode* l1, ListNode* l2) {
        ListNode *dummy = new ListNode(-1);
        ListNode *cur = dummy;
        while (l1 && l2) {
            if (l1->val < l2->val) {
                cur->next = l1;
                l1 = l1->next;
            } else {
                cur->next = l2;
                l2 = l2->next;
            }
            cur = cur->next;
        }
        if (l1) cur->next = l1;
        if (l2) cur->next = l2;
        return dummy->next;
    }
};
```


---

#### 逆向查找/打印
##### 从尾到头打印链表  

本题有三种解法：
  1. 单向链表的头插法可以使得单向链表轻松倒序。
  2. 递归在本质上就是一个栈结构，使用递归可以模拟栈的先进后出特性。
  3. 顺序遍历单链表并入栈，然后出栈即逆序。


使用递归访问单项链表，直到node->next==null; 然后开始从后往前遍历单向链表。

```cpp
class Solution {
  public:
    vector<int> dev;
    vector<int>& printListFromTailToHead(struct ListNode* head) {

    if(head!=NULL) {
      if(head->next!=NULL) {
        dev=printListFromTailToHead(head->next);
      }
      dev.push_back(head->val);
    }
    return dev;
  }
};
```



##### 链表中倒数第k个结点
题目描述
输入一个链表，输出该链表中倒数第k个结点。


使用前后指针，前指针先走k-1步然后前后指针一起走，当前指针走到最后一个节点时，后指针刚好走到倒数第k个节点。

然后关于指定第k个节点的问题，都会需要注意类似：
  * 链表可能为NULL  
  * 链表长度可能没有K个  
的边界问题。  

```cpp
// 1 -> 2 -> 3 -> 4 -> 5
// 比如要走倒数第3个节点，那么right先走到第3 - 1个节点&[2]
// 那么right指针走到链表的最后一个节点5时,此时两个指针距离（tail, head]为k-1,
//而总长度[tail, head]刚好为k此时left节点是倒数第K个节点.

class Solution
{
public:
    ListNode* FindKthToTail(ListNode* pListHead, unsigned int k)
    {
        if(pListHead == NULL)
            return NULL;
        //先计算链表长度处理倒数第K个节点计算时的边界情况
        int length = 0;
        ListNode *cur = pListHead;
        while(cur->next != NULL){
            cur = cur->next;
            ++length;
        }
        if(length < K)
            return NULL;
        //注意right left指针都是从头结点开始计算走路步数
        //i从0开始循环1、2共两步，此时right也只走了两步
        int i = 0;
        ListNode *right = pListHead;
        while(i<k-1)
        {
            right = right->next;
            i++;
        }
        ListNode *left = pListHead;
        while(right->next != NULL)
        {            
            left = left->next;
            right = right->next;
        }
        return left;
    }
};
```

#### 19. Remove Nth Node From End of List
解题思路：  
使用前后指针解决倒数第k相关问题：
* right先走k-1步，left可以走到倒数第k个节点
* right先走k步，left可以走到倒数第k+1个节点
因此只需要先走k步  

代码如下：
```cpp
class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        //如果是空链表则直接返回NULL
        if (!head->next) 
            return NULL;
        //cur先移动k步，然后cur pre一起移动到最后pre就能在
        //倒数第k个节点的前一个节点停下
        ListNode *pre = head, *cur = head;
        for (int i=0; i<n; ++i) 
            cur = cur->next;
        //如果cur是空节点则返回第一个节点
        if (!cur) 
            return head->next;
        while (cur->next) {
            cur = cur->next;
            pre = pre->next;
        }
        pre->next = pre->next->next;
        return head;
    }
};
```


#### 反转链表
 

反转链表的非递归解法即用头插法：
1. 先制造一个Blan head用于统一链表的操作。
2. 然后也是要注意每次保存next的位置防止丢失。  

```cpp
class Solution
{
public:
    ListNode* reverseList(ListNode* head)
    {
        if(head == NULL)
        {
            return NULL;
        }
        //如果没有blank head头节点则制造一个
        ListNode *blankHead = new ListNode(-1);
        blankHead->next = head;
        ListNode *cur = head;
        while (cur->next) {
            ListNode *tmp = cur->next;
            cur->next = tmp->next;
            tmp->next = blankHead->next;
            blankHead->next = tmp;
        }
        return blankHead->next;
    }
    }
};
```

#### 按顺序交换链表相邻节点

```cpp
class Solution {
public:
    ListNode* swapPairs(ListNode* head){
        //建立blankHead节点
        ListNode *blankHead = new ListNode(-1);
        blankHead->next = head;

        for(ListNode* pre = blankHead; pre->next && 
            pre->next->next; ){
            
            ListNode *left = pre->next;
            ListNode *right = pre->next->next;
            left->next = right->next;
            right->next = left;
            pre->next = right;
            pre=right->next;
        }
        return blankHead->next;
    }
};
```

#### 按区间k翻转链表节点

```cpp
class Solution {
public:
    ListNode *reverseKGroup(ListNode *head, int k) {
        if(head==NULL||k==1) 
            return head;
        
        ListNode *preheader = new ListNode(-1);
        preheader->next = head;
        //声明三个辅助变量cur, nex, pre
        ListNode *cur = preheader, *nex, *pre = preheader;
        int num=0;
        //统计一下链表长度
        while(cur = cur->next) 
            num++;
        while(num>=k) {
            //每次翻转链表区间时进行cur,nex指针初始化操作
            //pre指向想象上的blankHead节点
            //cur作为当前链表区间已翻转区段的最后的哨兵
            //nex作为当前需要被头插法翻转的节点
            cur = pre->next;
            nex = cur->next;
            //完全翻转k个链表节点只需要进行k-1次翻转
            for(int i=1;i<k;++i) {
                cur->next=nex->next;
                nex->next=pre->next;
                pre->next=nex;
                nex=cur->next;
            }
            //重置pre到上一个已翻转链表区间的
            //最后一个节点作为下一次的blankHead
            pre = cur;
            num-=k;
        }
        return preheader->next;
    }
};
```


#### 037 两个链表的第一个公共结点
**题目描述**  
输入两个链表，找出它们的第一个公共结点。

解题思路：  
利用快慢指针的方式，链表长的先走，链表短的后走。然后这里计算快慢指针的k步有一种比较geek的方法把：  
* 先同时遍历两个链表，如果长度不一致则比然有一个链表先到NULL，此时没到NULL的链表的剩余节点数就是快慢指针需要的差距.
* 这时候将到头的节点交换到另一条链表上，即将原本指向短链表的指针指向长链表，再继续遍历等待另一个指针也到NULL。
* 再将这个指针也交换到对面那个链表头。
* 这个过程中一直再往前走，直至p1==p2这个时候就是第一个交点了。

```cpp
class Solution {
public:
    ListNode* FindFirstCommonNode(ListNode *pHead1, ListNode *pHead2) {
        ListNode *p1 = pHead1;
        ListNode *p2 = pHead2;
        while(p1!=p2){
            p1 = (p1==NULL ? pHead2 : p1->next);
            p2 = (p2==NULL ? pHead1 : p2->next);
        }
        return p1;
    }
};
```

---

### 链表变形相关

1. 链表变形相关记住要设置头结点（又叫dummy节点），统一整个算法操作
2. 使用快慢指针可以快速找到链表中间节点

#### 删除链表中的节点

解题思路：
1. 首先链表需要加上一个Blank head 如果没有则自己加上
2. 使用pre指针，在链表中找到pre->next == target。

```cpp
class Solution {
public:
    ListNode* removeElements(ListNode* head, int target) {
        ListNode *blankNode = new ListNode(-1);
        blankNode->next = head;
        //使用pre指针，每次pre要处理的是pre->next的那个节点
        for(ListNode* pre=blankNode; pre->next!=NULL; 
            pre=pre->next){
            if(pre->next->val != target)
                continue;
            ListNode *tmp = pre->next;
            pre->next = tmp->next;
            delete tmp;           
        }
        return blankNode->next;
    }
};
```

#### 将链表去重但是保留所有出现过的元素一次
如：1->2->3->3->4->4->5处理后为1->2->3->4->5。而不是1->2->5

```cpp
class Solution {
public:
    ListNode* deleteDuplicates(ListNode *head) {
        //cur用于遍历所有节点，每当遇到cur->val==cur->next->val时
        //都将cur->next=cur->next->next并继续循环检测是否还在重复
        //直至cur->val!=cur->next->val时，cur进入下一个元素的检测
        ListNode* cur = head;
        while (cur) {
            while (cur->next != NULL && cur->val == cur->next->val)
                cur->next = cur->next->next;
            cur = cur->next;
        }
        return head;
    }
};
```


#### 删除链表中重复的结点
**题目描述**

在一个排序的链表中，存在重复的结点，请删除该链表中重复的结点，重复的结点不保留，返回链表头指针。  
> 例如，链表1->2->3->3->4->4->5  
处理后为 1->2->5

* 从头到尾判定每个结点是否是重复结点
* 如果不是重复结点：则尾部指针向后移动到这个结点，然后继续判定下一个结点的重复性。
* 如果是重复结点：那么修改当前尾部指针指向结点的next值，时尾部结点的next指针指向下一个非重复结点上。

```cpp
class Solution
{
public:
    ListNode* deleteDuplication(ListNode* pHead)
    {
        //设置一个trick, 作为头指针, 这样我们无需单独考虑第一个元素
        ListNode *blankHead = new ListNode(-1);
        blankHead->next = pHead;

        //right相当于哨兵用于标记当前链表的无重复节点的最后一个
        //left用来遍历链表的元素并检查出重复节点
        ListNode *left = pHead;
        ListNode *right = blankHead;
        while (left!=NULL && left->next!=NULL)
        {
            //如果有元素重复就跳过所有重复的数字
            if (left->val == left->next->val)
            {
                int val = left->val;
                while (left!=NULL && left->val==val)
                    left = left->next;
                //此时left指向了可能的一个非重复元素，我们设置right->next=left
                //但是此时left-val也可能是重复的,
                //因此我们不可以设置right=left
                //而是重新进入循环
                right->next = left;
            }
            else
            {
                right = left;
                left = left->next;
            }
        }
        return blankHead->next;
    }
};
```



#### 合并两个有序的链表

1. 合并两个及多个可以使用while循环，每次挑出当前最小节点然后进行合并。
2. 最后哪个链表还剩下的，就让其全部接上去。

```cpp
class Solution
{
public:
    ListNode* Merge(ListNode *pLeft, ListNode *pRight)
    {

        if(pLeft == NULL)
            return pRight;
        if(pRight == NULL)
            return pLeft;

        //生成辅助指针和新链表的头结点
        ListNode *left = pLeft;
        ListNode *right = pRight;
        ListNode *head = NULL;
        ListNode *curr = head;
        while(left != NULL && right != NULL)
        {
            //  每次找到一个小的加入新的链表
            if(left->val < right->val)
            {
                curr->next = left;
                curr = curr->next;
                left = left->next;
            }
            else
            {
                curr->next = right;
                curr = curr->next;
                right = right->next;
            }
        }
        //  处理较长链表的剩余部分
        if(left != NULL)
            curr->next = left;
        else
            curr->next = right;
        return head;

    }
};

```

##### 23. Merge k Sorted Lists

解题思路**：
* 这道题让我们合并k个有序链表，并且需要提高合并效率。
* **两两合并问题的高效率解法基本上就是分治法**。
  * 简单来说就是不停的对半划分，比如k个链表先划分为合并两个k/2个链表的任务，再不停的往下划分，直到划分成只有一个或两个链表的任务，开始合并。参见代码如下：

```cpp
class Solution {
public:
    ListNode *mergeKLists(vector<ListNode *> &lists) {
        if (lists.size() == 0) 
            return NULL;
        //记住这种迭代的divide&conquer计数法
        //首先取k=(n+1)/2, 然后i=0,i<n/2,i++
        //最后让i与i+k做divide&conquer
        int n = lists.size();
        while (n > 1) {
            int k = (n + 1) / 2;
            for (int i = 0; i < n / 2; ++i) {
                lists[i] = mergeTwoLists(lists[i], lists[i + k]);
            }
            n = k;
        }
        return lists[0];
    }

    ListNode *mergeTwoLists(ListNode *l1, ListNode *l2) {
        ListNode *head = new ListNode(-1);
        ListNode *cur = head;
        while (l1 && l2) {
            if (l1->val < l2->val) {
                cur->next = l1;
                l1 = l1->next;
            } else {
                cur->next = l2;
                l2 = l2->next;
            }
            cur = cur->next;
        }
        if (l1) cur->next = l1;
        if (l2) cur->next = l2;
        return head->next;
    }
};
```




#### 61. Rotate List
解题思路**：
分析题目可知，就是要找到倒数第k个节点，然后将[k,end]的部分截取出来拼接到链表头部
因此使用快慢指针可解。

```cpp
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode* rotateRight(ListNode* head, int k) {
        if (!head || !(head->next) || k == 0)
            return head;

        int S = 0;
        for (ListNode* i = head; i; i = i->next)
            ++S;

        if (k == S)
            return head;
        else
        {
            int remain = k % S;
            ListNode* pre = head;
            ListNode* cur = head;
            for (; remain > 0; --remain)
                cur = cur->next;

            while(cur->next)
            {
                pre = pre->next;
                cur = cur->next;
            }
            cur->next = head;
            cur = pre->next;
            pre->next = NULL;
            return cur;
        }
    }
};
```

#### 143. Reorder List

这道链表重排序问题可以拆分为以下三个小问题：

1. 使用快慢指针来找到链表的中点，并将链表从中点处断开，形成两个独立的链表。

2. 将第二个链翻转。

3. 将第二个链表的元素间隔地插入第一个链表中

```cpp
class Solution {
public:
    void reorderList(ListNode *head) {
        if (!head || !head->next || !head->next->next) return;
        ListNode *fast = head;
        ListNode *slow = head;
        while (fast->next && fast->next->next) {
            slow = slow->next;
            fast = fast->next->next;
        }
        ListNode *mid = slow->next;
        slow->next = NULL;
        ListNode *last = mid;
        ListNode *pre = NULL;
        while (last) {
            ListNode *next = last->next;
            last->next = pre;
            pre = last;
            last = next;
        }
        while (head && pre) {
            ListNode *next = head->next;
            head->next = pre;
            pre = pre->next;
            head->next->next = next;
            head = next;
        }
    }
};
```








