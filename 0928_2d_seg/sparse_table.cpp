// idempotent
// min, max, gcd, bitwise AND, bitwise OR, lcm

#include <bits/stdc++.h>
using namespace std; 

// sparse table
vector<vector<int>> gen_table(vector<int> values){
    
    int n = values.size(); 
    vector<vector<int>> result; 

    result.push_back(values); 
    vector<int> prev = values; 
    for(int len=2;len<=n;len=len<<1){

        vector<int> curr = {}; 
        for(int i=0;i+len<=n;i++){

            // [i, i+len/2)
            // [i+len/2, i+len)
            curr.push_back(max(prev[i], prev[i + len/2])); 
        }
        result.push_back(curr); 
        prev = curr; 
    }

    return result; 
}

int query(vector<vector<int>> &table, int l, int r){
    
    // assume l <= r
    int len = r - l + 1; 

    int msb = __lg(len);
    return max(table[msb][l], table[msb][r-(1<<msb)+1]); 
}