#include <bits/stdc++.h>
using namespace std; 

int n; 
vector<long long> value; 
vector<long long> tree; 

void update(int i, long long v){
    for(;i<=n;i+= i & -i){
        tree[i] += v; 
    }
}

long long prefix(int i){

    long long result = 0; 
    for(;i>0;i-= i&-i){
        result += tree[i]; 
    }
    return result; 
}

int main() {

    scanf("%d", &n); 
    value.assign(n+1, 0); 
    tree.assign(n+1, 0); 

    for(int i=1;i<=n;i++){
        scanf("%lld", &value[i]); 
    }

}