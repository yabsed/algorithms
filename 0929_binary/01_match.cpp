#include <bits/stdc++.h>
using namespace std; 

int n, m; 

// from left
vector<vector<int>> adj; 

// from right
vector<int> match; 
vector<bool> visited; 

bool dfs(int u){

    for(auto v : adj[u]){

        if (visited[v]){
            continue; 
        }

        visited[v] = true; 

        if (match[v] == -1 
            || dfs(match[v]))
        {
            match[v] = u; 
            return true; 
        }
    }

    return false; 
}

int main(){

    scanf("%d %d", &n, &m); 
    adj.assign(n, {}); 

    int e; 
    scanf("%d", &e); 

    for(int i=0;i<e;i++){

        int u, v; 
        scanf("%d %d", &u, &v); 

        // 1-based
        --u, --v; 

        adj[u].push_back(v); 
    }

    // graph construction completed

    match.assign(m, -1); 

    int answer = 0; 

    for(int u=0;u<n;u++){

        visited.assign(m, false); 

        if (dfs(u)){
            ++answer; 
        }
    }

    printf("%d\n", answer); 

}

/*

     [1, k]번 사람들의 최대 취업   ---> m   (배치 M)

then [1, k+1]번 사람들의 최대 취업 ---> m 혹은 m+1   --- (k+1)을 빼면 최대 1명 줄어듦

---

chain : M을 기준으로 (k+1)을 취업시키는 한 줄의 재배치

(k+1)이 쫓아냄 -> 쫓겨난 사람이 쫓아냄 -> ... -> 마지막 사람

---

Case A. 마지막 사람이 빈 회사를 찾는 chain이 있음

∴ (m+1)명 취업 & 최적

---

Case B. 그런 chain이 없음

∴ m명 그대로

---

Claim : Case B에서 최적은 m명이다.

만약 (m+1)명을 취업시키는 배치 M'이 있다면

M에서 출발해서, 각자 M'에서 간 회사로 옮기는 chain을 만든다

(k+1)이 쫓아냄 -> 쫓겨난 사람이 쫓아냄 -> ... -> 마지막 사람

갈림길 없음 (옮길 회사는 M'이 정해 줌)

(a) 마지막 사람이 빈 회사를 찾음    ---> Case A의 chain ---> 모순
(b) 마지막 사람이 M'에서 취업 못함 ---> 이 줄의 인원 변화 없음
    ((k+1) 자신이 M'에서 취업 못한 경우 포함)

∴ 늘어난 1명은 (k+1)과 무관한 곳에서 나옴

   [1, k] 안에서만 m을 m+1로 늘리는 재배치가 존재

   M이 [1, k]의 최대였으므로 모순

*/