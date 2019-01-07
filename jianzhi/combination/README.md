https://zhuanlan.zhihu.com/p/24523433

#### 028 字符串的排列

题目描述  
输入一个字符串,按字典序打印出该字符串中字符的所有排列。例如输入字符串abc,
则打印出由字符a,b,c所能排列出来的所有字符串abc,acb,bac,bca,cab和cba。

结果请按字母顺序输出。

注意 输入一个字符串,长度不超过9(可能有字符重复),字符只包括大小写字母

> 样例输入  
abc  
BCA

> 样例输出  
abc acb bac bca cab cba  
ABC ACB BAC BCA CAB CBA


解题思路：  
全排列问题是很典型的排列组合算法题，主要的解题方法有就是基于交换的全排列：

  * 生成全排列：  
  对abb，第一个数a与第二个数b交换得到bab，然后考虑第一个数与第三个数交换，此时由于第三个数等于第二个数，所以第一个数就不再用与第三个数交换了。再考虑bab，它的第二个数与第三个数交换可以解决bba。此时全排列生成完毕！

  * 全排列去重复：  
  在全排列中去掉重复的规则： 去重的全排列就是从第一个数字起，每个数分别与它后面非重复出现的数字交换。

  * 综上所述：  
  例如对于abc，用递归方法，把列表不断切断如‘abc’,第一次切成‘a’和‘bc’，第二次切成‘ab’和‘c’. 然后把后面的字符串中每一个都与前面的字符串最后一个作交换。 例如（'ab' 与‘c’交换就是，‘ac’和‘b’）最后再排序一下就好。

    * 首先，求所有可能出现在第一个位置的字符，

    * 其次，把第一个字符和其后面的字符一一交换。分别把第一个字符a和后面的b、c等字符交换的情形。

    * 接着，固定第一个字符，求后面所有字符的排列。这个时候我们仍把后面的所有字符分成两部分：后面字符的第一个字符，以及这个字符之后的所有字符。然后把第一个字符逐一和它后面的字符交换

  ```cpp
class Solution
{
  public:
      vector<string> m_res;

      vector<string> Permutation(string str)
      {
          m_res.clear( );

          //判断是否字符串非空
          if(str.empty( ) == true)
          {
              return m_res;
          }
          PermutationRecursion(str, 0);

          sort(m_res.begin( ), m_res.end( ));
          return m_res;
      }


      void PermutationRecursion(string str, int begin)
      {
          if(str[begin] == '\0')
          {
              m_res.push_back(str);
          }
          else
          {
              int i;
              i = begin;
              for(; str[i] != '\0'; i++)
              {
                  if(!HasDuplicate(str, begin, i))
                  {
                      swap(str[i], str[begin]);
                      PermutationRecursion(str, begin + 1);
                      swap(str[i], str[begin]);
                  }
              }
          }
      }

      //交换当前元素和首字母begin之前进行重复验证
      //如果当前i所指向元素已经出现在[begin, i)的范围内
      //则说明当前元素重复，因为在它之前的和它相等的元素已经和begin交换过了，则不进行交换
      bool HasDuplicate(string& str, int k, int i) const {
  		for (int p = k; p < i; p++)
  			if (str[p] == str[i]) return true;

  		return false;
  	}
  };
  ```

#### 033 把数组排成最小的数

题目描述

输入一个正整数数组，把数组里所有数字拼接起来排成一个数，打印能拼接出的所有数字中最小的一个。  

输入  
例如输入数组
{3，32，321}

输出  
则打印出这三个数字能排成的最小数字为321323

解题思路：  
 * 首先，这种将数组元素排序后输出成一个数字的大数问题，都不要用数值类型进行保存，而是去用字符串保存大数，因为有可能这个数组非常大导致数值类型越界。
 * 先将整数数组转为字符串数组，然后字符串数组进行排序，最后依次输出字符串数组即可。
 * 然后因为是将字符串经比较后组成一个最小的数，那么比较两个字符串时不是比较a和b，而是比较ab与 ba。比较函数的定义是本解决方案的关键。这道题其实就是希望我们能找到一个排序规则，根据这个规则排出来的数组能排成一个最小的数字。
    * 如果ab < ba，则a < b；
    * 如果ab > ba，则a > b；
    * 如果ab = ba，则a = b。

```cpp


class Solution
{
public:

    //将整数转为字符串的通用函数
    //使用ostringstream
    template<class T>
    static string ToString(const T& t)
    {

        ostringstream oss;  //  创建一个流

        oss << t;            //  把值传递如流中
        return oss.str( );  //  获取转换后的字符转并将其写入result
    }

    /// 要在sort方法传入的自定义比较函数
    //  注意返回的是AB是否小于BA
    //  如果是的话，就把A排在B前面。
    static bool Compare(const string &A, const string &B)
    {
        string AB = A + B;
        string BA = B + A;

        return AB < BA;
    }


    string PrintMinNumber(vector<int> E)
    {
        int S;
        string res, TMP;
        vector<string> ET;


        ///  将整数转换成字符串
        TMP = "";
        S = E.size();
        for(unsigned int i = 0; i < S; i++)
        {
            TMP = ToString(E[i]);
            ET.push_back(TMP);
        }

        ///  对字符串按照拼接后的大小进行排序
        sort(ET.begin( ), ET.end( ), Compare);

        ///  拼接结果
        res = "";
        for(unsigned int i = 0; i < ET.size( ); i++)
        {
            res += ET[i];
        }
        return res;
    }
};

```
