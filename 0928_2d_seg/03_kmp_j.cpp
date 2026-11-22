#include <bits/stdc++.h>
using namespace std;

typedef long long ll; 

vector<int> pi_gen(string &pattern){

    int m = pattern.size(); 
    vector<int> pi(m); 

    pi[0] = 0; 

    for(int idx=1; idx<m; idx++){

        int len = pi[idx-1]; 

        while(0 < len && pattern[len] != pattern[idx]){
            len = pi[len - 1]; 
        }

        if (pattern[len] == pattern[idx]){
            len++; 
        }

        pi[idx] = len; 

    }

    return pi; 
}

/*
           0         pi(idx-1)    idx-pi(idx-1)     idx-1
           |             |              |             |
 given :   [=============)              [=============]     --- definition of pi(idx-1)
 check :   [=============#]             [=============#]    --- if same, pi(idx) = pi(idx-1) + 1
  fail :   [=====)                              [=====]     --- shrink to k = pi(pi(idx-1) - 1), check again

 given :  [0, pi(idx-1))  == [idx - pi(idx-1), idx - 1]
 check :  [0, pi(idx-1)]  == [idx - pi(idx-1), idx]
  fail :  [0, k)          == [idx - k,         idx - 1]
*/ 


vector<int> ov_gen(string &text, string &pattern){

    if (pattern.empty()) return {}; 

    int n = text.size(); 
    int m = pattern.size(); 

    vector<int> pi = pi_gen(pattern); 
    vector<int> ov(n); 

    for(int idx=0; idx<n; idx++){

        int len = 0; 

        if(idx)      len = ov[idx-1]; 
        if(len == m) len = pi[len-1]; 

        while(0 < len && text[idx] != pattern[len]){
            len = pi[len-1]; 
        }

        if(text[idx] == pattern[len]){
            len++; 
        }

        ov[idx] = len; 
    }
    
    return ov; 
}

/*
               pattern                       text
           0         ov(idx-1)    idx-ov(idx-1)     idx-1
           |             |              |             |
 given :   [=============)              [=============]     --- definition of ov(idx-1)
 check :   [=============#]             [=============#]    --- if same, ov(idx) = ov(idx-1) + 1
  fail :   [=====)                              [=====]     --- shrink to k = pi(ov(idx-1) - 1), check again

 given :  pattern[0, ov(idx-1))  == text[idx - ov(idx-1), idx - 1]
 check :  pattern[0, ov(idx-1)]  == text[idx - ov(idx-1), idx]
  fail :  pattern[0, k)          == text[idx - k,         idx - 1]

  full :  ov(idx-1) == m  --->  no # left in pattern, go straight to fail
*/

vector<int> kmp_gen(string &text, string &pattern){

    if (pattern.empty()) return {}; 

    int          n =    text.size(); 
    int          m = pattern.size(); 
    vector<int> ov = ov_gen(text, pattern); 
    vector<int> kmp; 

    for(int idx=0; idx<n; idx++){
        if (ov[idx] == m){
            kmp.push_back(idx - m + 1); 
        }
    }

    return kmp; 

}