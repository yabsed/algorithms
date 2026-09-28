#include <bits/stdc++.h>
using namespace std; 

vector<int> pi_gen(const string &p){
    int m = p.size(); 

    vector<int> pi(m); 

    int ji = -1; 
    for(int i=1;i<m;i++){
        while(ji >= 0 && p[ji+1] != p[i]){
            ji = pi[ji] - 1; 
        }
        if (p[ji+1] == p[i]){
            ++ji; 
        }
        pi[i] = ji + 1; 
    }
    return pi; 
}

vector<int> kmp_gen(
    const string &t,
    const string &p
){

    int n = t.size(); 
    int m = p.size(); 

    vector<int> pi = pi_gen(p); 
    vector<int> kmp(n); 

    int ji = -1; 
    for(int i=0;i<n;i++){
        while(ji >= 0 && t[i] != p[ji + 1]){
            ji = pi[ji] - 1; 
        }
        if(t[i] == p[ji+1]){
            ++ji; 
        }
        kmp[i] = ji + 1; 

        if (ji == m-1){
            ji = pi[ji] - 1; 
        }
    }
    return kmp; 
}

int main(){

    ; 
    
}