#include <bits/stdc++.h>
using namespace std; 

vector<int> pi_gen(string &pattern){

    int m = pattern.size(); 
    vector<int> pi(m); 

    int len = 0; 
    for(int i=1;i<m;i++){

        while(len > 0 && pattern[len] != pattern[i]){
            len = pi[len-1]; 
        }

        if(pattern[len] == pattern[i]){
            pi[i] = ++len; 
        }
    }
    return pi; 
}

vector<int> kmp_gen(string &text, string &pattern){

    if (pattern.empty()){
        return {}; 
    }

    int n = text.size(); 
    int m = pattern.size(); 

    vector<int> pi = pi_gen(pattern); 
    vector<int> kmp; 

    int len = 0; 
    for(int i=0;i<n;i++){
        while(len > 0 && text[i] != pattern[len]){
            len = pi[len-1]; 
        }
        if(text[i] == pattern[len]){
            ++len; 
        }
        if(len == m){
            kmp.push_back(i-m+1); // starting point
            len = pi[m-1]; 
        }
    }
    return kmp; 
}