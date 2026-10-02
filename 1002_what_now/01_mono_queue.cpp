#include <bits/stdc++.h>
using namespace std; 

template <typename T>
vector<vector<T>> transpose (const vector<vector<T>>& a){

    int n = a   .size(); 
    int m = a[0].size(); 

    vector<vector<T>> result(m, vector<T>(n)); 

    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            result[j][i] = a[i][j]; 
        }
    }
    
    return result; 
}

vector<int> sliding_max(const vector<int>& value, int k){

    int n = value.size(); 

    deque <int> dq; 
    vector<int> result; 

    for(int i=0;i<n;i++){

        while(!dq.empty() && dq.front() <= i - k){
            dq.pop_front(); 
        }

        while(!dq.empty() && value[dq.back()] <= value[i]){
            dq.pop_back(); 
        }

        dq.push_back(i); 

        if(k - 1 <= i){
            // modify this if you (reasonably) 
            // want index, not value
            result.push_back(value[dq.front()]); 
        }
    }

    return result; 

}

vector<vector<int>> sliding_max_2d(const vector<vector<int>>& value, int k1, int k2){

    vector<vector<int>> result; 

    for(const auto& row: value){
        result.push_back(sliding_max(row, k2)); 
    }

    result = transpose(result); 

    for(auto& row: result){
        row = sliding_max(row, k1); 
    }

    return transpose(result); 
}
