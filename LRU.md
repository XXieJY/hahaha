#### 实现一个LRU
[link1](https://songlee24.github.io/2015/05/10/design-LRU-Cache/)
[link2](https://zhuanlan.zhihu.com/p/34133067)

常用的替换策略有以下几种：
* 随机算法（Rand）：随机法是随机地确定替换的存储块。设置一个随机数产生器，依据所产生的随机数，确定替换块。这种方法简单、易于实现，但命中率比较低。
* 先进先出算法（FIFO, First In First Out）：先进先出法是选择那个最先调入的那个块进行替换。当最先调入并被多次命中的块，很可能被优先替换，因而不符合局部性规律。这种方法的命中率比随机法好些，但还不满足要求。
* 最久未使用算法（LRU, Least Recently Used）：LRU法是依据各块使用的情况， 总是选择那个最长时间未被使用的块替换。这种方法比较好地反映了程序局部性规律。
* 最不经常使用算法（LFU, Least Frequently Used）：将最近一段时期内，访问次数最少的块替换出Cache。



对一个Cache的操作无非三种：插入(insert)、替换(replace)、查找（lookup）。  
1. 为了能够快速删除最久没有访问的数据项和插入最新的数据项，我们使用 双向链表 连接Cache中的数据项，并且保证链表维持数据项从最近访问到最旧访问的顺序。
2. 插入：当Cache未满时，新的数据项只需插到双链表头部即可。时间复杂度为$O(1)$.
3. 替换：当Cache已满时，将新的数据项插到双链表头部，并删除双链表的尾结点即可。时间复杂度为$O(1)$.
4. 查找：每次数据项被查询到时，都将此数据项移动到链表头部。为了让查找效率也达到$O(1)$，很自然的会想到使用 hash table 。

从上述分析可知，我们需要使用两种数据结构：
1. 双向链表（Doubly Linked List）
2. 哈希表（Hash Table）

```cpp
#include<iostream>
#include<unordered_map>

using namespace std;

struct LRUCacheNode{
    int key;
    int value;
    LRUCacheNode* prev;
    LRUCacheNode* next;
    LRUCacheNode(): key(0),value(0),prev(NULL),next(NULL){}
};

class LRUCache{

private:
    unordered_map<int, LRUCacheNode*> m; //用于查找节点的hashtable
    LRUCacheNode* head; //双向链表的头尾节点
    LRUCacheNode* tail;
    int capacity, total;
    
    void removeLRUNode(); //按照最近最久未使用算法删除一个链表节点
    void detachNode(LRUCacheNode* node); //实际删除链表节点操作函数
    void insertToFront(LRUCacheNode* node); //实际插入节点操作函数

public:
    LRUCache(int capacity);
    ~LRUCache();
    int get(int key); //查询LRU链表的某个节点
    void set(int key, int value); //LRU链表未满时插入，满时替换
};

LRUCache::~LRUCache(){
    delete head;
    delete tail;
}

int LRUCache::get(int key){
    if(m.find(key) == m.end()) //在hashtable中不存在要查找的节点
        return -1;
    else{
        //当前最新访问过这个节点，根据LRU将该节点刷新
        //这里也就是移动到链表的头部
        LRUCacheNode* node = m[key];
        detachNode(node);
        insertToFront(node);
    }
}

void LRUCache::set(int key, int value){
    if(m.find(key) != m.end()){
        //说明插入LRU节点已经存在于内存中了，直接刷新他
        LRUCacheNode* node = m[key];
        detachNode(node);
        node->value = value;
        insertToFront(node);
    }
    else{
        //说明当前要插入的节点对于LRU来说是一个新的节点
        LRUCacheNode* node = new LRUCacheNode;
        //如果当前LRU内存已经满了那么替换出去一个节点
        if(total == capacity) 
            removeLRUNode();
        //插入操作
        node->key = key;
        node->value = value;
        m[key] = node;
        insertToFront(node);
        ++total;
    }
}

void LRUCache::removeLRUNode(){
    LRUCacheNode* node = tail->prev;
    detachNode(node);
    m.erase(node->key);
    --count;
}

void LRUCache::detachNode(LRUCacheNode* node){
    node->prev->next = node->next;
    node->next->prev = node->prev;
    delete node;
}

void LRUCache::insertToFront(LRUCacheNode* node){
    node->next = head->next;
    node->prev = head;
    head->next = node;
    node->next->prev = node;
```
