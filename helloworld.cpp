#include <iostream>
#include <vector>

#define GO_UP 1;
#define GO_LEFT 2;
#define GO_DIAGONAL 3;

using namespace std;


class Solution {

public:
    int findLCSequence(const string& str1, const string& str2){
            if(str1.empty() || str2.empty())
                return 0;
            vector<vector<int> > dp(str1.size()+1, 
                vector<int>(str2.size()+1));
            vector<vector<int> > dpPath(str1.size()+1, 
                vector<int>(str2.size()+1));
            for(int i=0; i<=str1.length(); ++i)
                dp[i][0] = 0;
            for(int j=0; j<=str2.length(); ++j)
                dp[0][j] = 0;
            
            
            for(int i=1; i<=str1.length(); ++i){
                for(int j=1; j<=str2.length(); ++j){
                    if(str1[i-1]==str2[j-1]){
                        dp[i][j]=dp[i-1][j-1]+1;
                        dpPath[i][j] = GO_DIAGONAL;
                    }
                    //子串和子序列的差别在这里
                    else{
                        if(dp[i-1][j]>dp[i][j-1]){
                            dp[i][j]=dp[i-1][j];
                            dpPath[i][j]=GO_UP;
                        }
                        else{
                            dp[i][j]=dp[i][j-1];
                            dpPath[i][j]=GO_LEFT;
                        }
                    }
                }
            }
            int i = str1.size(), j = str2.size();
            while(i!=0&&j!=0){
                if(dpPath[i][j]==1)
                    cout << str1[i-1] << " ";
                else if(dpPath[i][j]==GO_UP)
                    --i;
                else if(dpPath[i][j]=GO_LEFT)
                    --j;
            }
            return dp[str1.size()][str2.size()];
        }
};
