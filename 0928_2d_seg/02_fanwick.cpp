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

/* 

lowbit(idx)는 idx번 칸에서 끝나는 블록의 길이다. 

idx   1     2     3     4     5     6     7     8

L3  ===== ===== ===== ===== ===== ===== ===== [ 8 ]
                                              1000
L2  ===== ===== ===== [ 4 ]
                      0100
L1  ===== [ 2 ]             ===== [ 6 ]
          0010                    0110
L0  [ 1 ]       [ 3 ]       [ 5 ]       [ 7 ]
    0001        0011        0101        0111


L := lowbit(idx)

블록의 위치 = idx
블록의 길이 = lowbit(idx)
블록의 범위 = (idx - L, idx]

======================================

블록의 길이만큼 위치를 옮긴다. 

prefix : (idx - L, idx] ->       (어디든, idx - L]
update : (idx - L, idx] -> (idx - L 이하, idx + L]

*/ 


/* 

Fenwick update : blocks covering p

B(j) = (j - lowbit(j), j]  --- block of j

              + lowbit(j)
chain :  j ---------------> j + lowbit(j)

         p = j0 ---> j1 ---> j2 ---> ...

then B(k) covers p iff k is on the chain

======================================

Key fact (L = lowbit(j))

    j =  odd * L
j + L = even * L  --- multiple of 2L

∴ lowbit(j + L) >= 2L

======================================

Proof. (⇐) blocks on the chain are nested

            j - L          j         j + L
              |            |           |
B(j)     :    (------------]
B(j + L) : (---------------------------]
           ↑
      <= j - L

 left end of B(j + L)  = (j + L) - lowbit(j + L)
                      <= (j + L) - 2L             --- key fact
                       =  j - L                   --- left end of B(j)

right end of B(j + L)  =  j + L
                       >  j                       --- right end of B(j)

∴ p ∈ B(j0) ⊆ B(j1) ⊆ B(j2) ⊆ ...

======================================

Proof. (⇒) blocks off the chain miss p

 (i) k < p

     right end of B(k) = k < p   --- ends before p

(ii) j < k < j + L  (j on the chain, L = lowbit(j))

     k = j + d  with 0 < d < L

     lowbit(k)  = lowbit(d)      --- L divides j, d < L
               <= d

     left end of B(k)  = k - lowbit(k)
                      >= k - d
                       = j
                      >= p       --- starts after p

======================================
*/