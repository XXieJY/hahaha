#### strcpy算法
```cpp
char* myStrcpy(char* pre, const char* next)
{
    if (pre == nullptr || next == nullptr) //空指针直接返回
    {
        return nullptr;
    }
    if (pre == next)                       // 两者相等也无需拷贝了
        return pre;

    while ((*pre++ = *next++) != '\0');    // 依次赋值给主字符数组

    return pre;
}

char* myStrcat(char* pre, const char* next)
{
    if (pre == nullptr || next == nullptr) // 如果有一个为空指针，直接返回pre
        return pre;
    char* tmp_ptr = pre + strlen(pre); //strlen计算字符数，需要包含都文件string.h，当然也可以自己实现

    while ( (*tmp_ptr++ = *next++) != '\0'); // 依次接着赋值

    return pre;
}

```

#### LRU、FIFO、CLOCK内存置换算法的实现
```cpp
#include <iostream>  
#include<map>
#include<set>
#include <algorithm>
#include<cstdio>
#include<cstring> 
#include<cmath>
#define N 200
using namespace std;  
 
int page[N];//页面引用号 
int block[N];//物理块，内存 
int dist[N][N];//表示第i次访问内存的时候，内存中的页面j 在以后被访问的最小时间 

int n;//页面引用号个数 
int m;//物理块数目 
int page_max;//最大页面号 

int pre[N];//page[i]在page中的索引

int lru(){//最近最久未使用算法和opt算法差不多，只不过是lru是向前看， opt是向后看 
    int page_lack = 0;
    memset(pre, 0, sizeof(pre));
    memset(dist, 0x3f, sizeof(dist));
    memset(block, -1, sizeof(block));
    for(int i=1; i<=n; ++i){
         for(int j=0; j<=page_max; ++j) 
             if(pre[j])
                dist[i][j] = i - pre[j];
         pre[page[i]] = i; 
    }
    
    for(int i=1; i<=n; ++i){//开始访问页面，初始是内存中没有分页 
        int j;
        int max_dist = 0, p; 
        for(j=1; j<=m; ++j){
            if(block[j] == -1){//改块没有放入页面，则直接放入, 产生缺页 
                block[j] = page[i]; 
                cout<<"页面"<<page[i]<<"不在内存，直接放入物理块"<<j<<"中!"<<endl;
                page_lack++;
                break;
            } else if(block[j] == page[i])//页面存在内存中 
                break;
            
            if(max_dist < dist[i][block[j]]){
                max_dist = dist[i][block[j]];//说明block[j] 对应的页面以后会长时间不会用到 
                p = j;//block[] 第j个页面会被替换掉 
            }
        }
        if(j > m){//此时内存中不能在放入新的分页，而且没有找到page[i]对应的分页，接下来进行页面替换 
             cout<<"页面"<<page[i]<<"不在内存，将物理块"<<p<<"中的页面" <<block[p]<<"替换掉!"<<endl;
             block[p] = page[i];
             page_lack++; 
        }
        cout<<endl<<"当前内存中页面的情况:"<<endl; 
        for(int k=1; k<=m; ++k)//内存中页面加载情况 
            cout<<block[k]<<" ";
        cout<<endl<<endl;
    }
    return page_lack;//返回缺页次数 
} 

set<int>page_set;
int fifo(){//先进先出页面置换算法
    int page_lack = 0; 
    memset(block, -1, sizeof(block));
    int index = 1;
    for(int i=1; i<=n; ++i){
        if(index > m) index = 1;
        set<int>::iterator it;
        it = page_set.find(page[i]);  
        if(it == page_set.end()){
            if(block[index] != -1)
                page_set.erase(block[index]);
            page_set.insert(page[i]);
            block[index++] = page[i];
            ++page_lack;
        } 
        for(int k=1; k<=m; ++k)
            cout<<block[k]<<" ";
        cout<<endl;
    } 
    return page_lack;
}

int nru[N];//表示 物理块 i 最近时候被访问过 
int page_in_block[N];//页面 i 在 block的下标索引 
int clock(){
    int index = 1;
    int page_lack = 0;
    memset(block, -1, sizeof(block));
    for(int i=1; i<=n; ++i){
        if(page_in_block[page[i]]){//如果page[i]已经在内存中 
            nru[page_in_block[page[i]]] = 1;//重新标记这个物理块中的页面被访问过了 
            cout<<endl<<"第"<<i<<"次: 页面"<<page[i]<<"已经存在物理块"<< page_in_block[page[i]] << "中!"<<endl;
        }
        else {
            while(true){
                if(index > m) index = 1;
                if(block[index] == -1) {
                    nru[index] = 1;
                    page_in_block[page[i]] = index;
                    block[index++] = page[i];
                    ++page_lack;
                    break;
                }
                if(block[index] == page[i]){
                    nru[index++] = 1;
                    break;
                } else {
                    if(nru[index] == 0){//替换该页面 
                        nru[index] = 1;
                        page_in_block[block[index]] = 0;
                        cout<<endl<<"第"<<i<<"次: 物理块"<<index<<"中的页面"<< block[index] <<"最近未被使用，将要被页面"<<page[i]<<"替换!"<<endl;
                        page_in_block[page[i]] = index;
                        block[index++] = page[i];
                        ++page_lack;
                        break;
                    } else
                        nru[index++] = 0;
                }
            } 
        }
        for(int k=1; k<=m; ++k)    
            cout<<block[k]<<" ";
        cout<<endl;
    }
    return page_lack;
}

int main(){
    cin>>n>>m;
    for(int i=1; i<=n; ++i){ 
        cin>>page[i];
        page_max = max(page_max, page[i]) ;
    } 
     cout<<"opt缺页中断次数:"<<opt()<<endl;
     cout<<"***********************************"<<endl;
     cout<<"lru缺页中断次数:"<<lru()<<endl;
     cout<<"***********************************"<<endl;
     cout<<"fifo缺页中断次数:"<<fifo()<<endl;
     cout<<"***********************************"<<endl;
     cout<<"clock缺页中断次数:"<<clock()<<endl;
     return 0;
} 
/*
20 3
7 0 1 2 0 3 0 4 2 3 0 3 2 1 2 0 1 7 0 1

12 3
2 3 2 1 5 2 4 5 3 2 5 2
```



#### [线程池](https://blog.csdn.net/gcola007/article/details/78750220) [ref](https://blog.csdn.net/CSND_Ayo/article/details/72457190)
* 线程池管理器（ThreadPoolManager）:用于创建并管理线程池
* 工作线程（WorkThread）: 线程池中线程
* 任务接口（Task）:每个任务必须实现的接口，以供工作线程调度任务的执行。
* 任务队列:用于存放没有处理的任务。提供一种缓冲机制。
```cpp
#ifndef ThreadPool_h
#define ThreadPool_h

#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <future>
#include <functional>

class ThreadPool {
public:
    ThreadPool(size_t);    //构造函数，size_t n 表示连接数

    template<class F, class... Args>
    auto enqueue(F&& f, Args&&... args)   //任务管道函数
    -> std::future<typename std::result_of<F(Args...)>::type>;  //利用尾置限定符  std future用来获取异步任务的结果

    ~ThreadPool();
private:
    // need to keep track of threads so we can join them
    std::vector< std::thread > workers;   //追踪线程
    // the task queue
    std::queue< std::function<void()> > tasks;    //任务队列，用于存放没有处理的任务。提供缓冲机制

    // synchronization  同步？
    std::mutex queue_mutex;   //互斥锁
    std::condition_variable condition;   //条件变量？
    bool stop;
};

// the constructor just launches some amount of workers
inline ThreadPool::ThreadPool(size_t threads): stop(false)
{
    for(size_t i = 0;i<threads;++i)
        workers.emplace_back(     //以下为构造一个任务，即构造一个线程
            [this]
            {
                for(;;)
                {
                std::function<void()> task;   //线程中的函数对象
                    {//大括号作用：临时变量的生存期，即控制lock的时间
                    std::unique_lock<std::mutex> lock(this->queue_mutex);
                    this->condition.wait(lock,
                        [this]{ return this->stop || !this->tasks.empty(); }); //当stop==false&&tasks.empty(),该线程被阻塞 !this->stop&&this->tasks.empty()
                    if(this->stop && this->tasks.empty())
                        return;
                    task = std::move(this->tasks.front());
                    this->tasks.pop();

                    }

                task(); //调用函数，运行函数
                }
            }
         );
}

// add new work item to the pool
template<class F, class... Args>
auto ThreadPool::enqueue(F&& f, Args&&... args)  //&& 引用限定符，参数的右值引用，  此处表示参数传入一个函数
-> std::future<typename std::result_of<F(Args...)>::type>
{
    using return_type = typename std::result_of<F(Args...)>::type;
     //packaged_task是对任务的一个抽象，我们可以给其传递一个函数来完成其构造。之后将任务投递给任何线程去完成，通过
//packaged_task.get_future()方法获取的future来获取任务完成后的产出值
    auto task = std::make_shared<std::packaged_task<return_type()> >(  //指向F函数的智能指针
            std::bind(std::forward<F>(f), std::forward<Args>(args)...)  //传递函数进行构造
        );
    //future为期望，get_future获取任务完成后的产出值
    std::future<return_type> res = task->get_future();   //获取future对象，如果task的状态不为ready，会阻塞当前调用者
    {
        std::unique_lock<std::mutex> lock(queue_mutex);  //保持互斥性，避免多个线程同时运行一个任务

        // don't allow enqueueing after stopping the pool
        if(stop)
            throw std::runtime_error("enqueue on stopped ThreadPool");

        tasks.emplace([task](){ (*task)(); });  //将task投递给线程去完成，vector尾部压入
    }
    condition.notify_one();  //选择一个wait状态的线程进行唤醒，并使他获得对象上的锁来完成任务(即其他线程无法访问对象)
    return res;
}//notify_one不能保证获得锁的线程真正需要锁，并且因此可能产生死锁

// the destructor joins all threads
inline ThreadPool::~ThreadPool()
{
    {
        std::unique_lock<std::mutex> lock(queue_mutex);
        stop = true;
    }
    condition.notify_all();  //通知所有wait状态的线程竞争对象的控制权，唤醒所有线程执行
    for(std::thread &worker: workers)
        worker.join(); //因为线程都开始竞争了，所以一定会执行完，join可等待线程执行完
}

```


#### 实现LRU算法


#### 随机打乱一个数组洗牌算法
这其实是个洗牌算法，首先从所有元素中随机选取一个与第一个元素进行交换，然后在第二个之后选择一个元素与第二个交换，直到最后一个元素。这样能确保每个元素在每个位置的概率都是1/n。

```cpp
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
using namespace std;
 
void random(int a[], int n)
{
	int index, tmp, i;
	srand(time(NULL));
	for(i=0; i<n; i++)
	{
		index=rand()%(n-i)+i;	
		if(index!=i)
		{
			tmp=a[i];
			a[i]=a[index];
			a[index]=tmp;
		}
 
	}
 
} 
 
int main()
{
	int a[100];
	int i;
	for(i=0; i<100; i++)
		a[i]=i;
	random(a, 100);
	for(i=0; i<100; i++)
		cout<<a[i]<<"  ";
	cout<<endl;
	return 0;
}
```

#### rand5实现rand7
```cpp
public class Test {    
    public int rand7() {    
        int x = 22;    
        while(x > 21) {    
            x = rand5() + (rand5() - 1)*5;    
        }    
        return 1 + x%7;    
    }    
}    
```

#### 二进制转十进制
```cpp
#include <stdio.h>
#include <math.h>
 
int convertBinaryToDecimal(long long n);
 
int main()
{
    long long n;
    printf("输入一个二进制数: ");
    scanf("%lld", &n);
    printf("二进制数 %lld 转换为十进制为 %d", n, convertBinaryToDecimal(n));
    return 0;
}
 
int convertBinaryToDecimal(long long n)
{
    int decimalNumber = 0, i = 0, remainder;
    while (n!=0)
    {
        remainder = n%10;
        n /= 10;
        decimalNumber += remainder*pow(2,i);
        ++i;
    }
    return decimalNumber;
}
```



#### 二进制中1的个数
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

#### 011 数值的整数次方

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
