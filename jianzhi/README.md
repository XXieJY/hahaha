

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
            return 1.0;
    
        //  指数为负数的情况下，底数不能为0
        if(Equal(base, 0.0) == true && exponent < 0)
            return 0.0;
       
        double res = 1.0;
        if(exponent > 0.0)
            res = PowerNormal(base, exponent);
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
            res *= base;
        return res;
    }
    
    double Equal(double left, double right)
    {
        if(fabs(left - right) <  0.0000001)
            return true;
        else
            return false;
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


