首先从所有元素中随机选取一个与第一个元素进行交换，然后在第二个之后选择一个元素与第二个交换，直到最后一个元素。这样能确保每个元素在每个位置的概率都是1/n。


```cpp
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

using namespace std;

void shuffle(int &a[], int n){
    int index, temp;
    srand(time(NULL));
    for(int i=0; i<n; ++i){
        index = (rand() % (n - i)) + i;
        if(index != i){
            temp = a[i];
            a[i] = a[index];
            a[index] = temp;
        }
    }
}

```
