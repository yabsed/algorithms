#include <bits/stdc++.h>
using namespace std; 

using ll = long long; 

vector<ll> value; 

vector<ll> tree; 
vector<ll> lazy; 

void pull(int idx){
    tree[idx] = tree[2*idx] + tree[2*idx+1]; 
}

void apply(int idx, int l, int r, ll delta){
    tree[idx] += delta * (r - l + 1); 
    lazy[idx] += delta; 
}

void push(int idx, int l, int r){

    if (l == r) return; // useless but safe
    if (lazy[idx] == 0) return; 

    int mid = (l + r)/2; 

    apply(2*idx, l, mid, lazy[idx]); 
    apply(2*idx+1, mid+1, r, lazy[idx]); 

    lazy[idx] = 0; 
}

void build(int idx, int l, int r){

    // leaf
    if (l == r){
        tree[idx] = value[l]; 
        return; 
    }

    // not leaf
    int mid = (l+r)/2; 

    build(2*idx, l, mid); 
    build(2*idx+1, mid+1, r); 

    pull(idx); 
}

void update(int idx, 
    int l, int r, 
    int s, int e, 
    ll delta
){

    if(e < l || r < s)return; 

    if(s <= l && r <= e){
        apply(idx, l, r, delta); 
        return; 
    }

    int mid = (l+r)/2; 

    push(idx, l, r); 

    update(2*idx, 
        l, mid, 
        s, e,
        delta
    ); 

    update(2*idx+1, 
        mid+1, r, 
        s, e, 
        delta 
    ); 

    pull(idx); 

}

ll search(int idx, 
    int l, int r, 
    int s, int e
){

    if (e < l || r < s) return 0; 

    if (s <= l && r <= e){
        return tree[idx]; 
    }

    int mid = (l + r)/2; 

    push(idx, l, r); 

    return search(2*idx, 
        l, mid, 
        s, e
    ) + search(2*idx+1, 
        mid+1, r, 
        s, e
    ); 
}

int main(){

    int n; 
    scanf("%d", &n); 

    value.resize(n); 
    tree.resize(4*n); // initial values do not matter
    lazy.assign(4*n, 0); 

    for(int i=0;i<n;i++){
        scanf("%lld", &value[i]); 
    }

    build(1, 0, n-1); 

    // below comes queries

}

