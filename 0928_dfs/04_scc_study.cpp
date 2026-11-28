#include <bits/stdc++.h>
using namespace std; 

// vertex with DFS
vector<int> disc; 
vector<int> low; 
int timer = 0; 

// graph
vector<vector<int>> adj; 

// SCCS 
vector<vector<int>> sccs; 

// SCC stack
vector<bool> in_stack; 
stack<int> vertex_stack; 

int n; // 노드의 갯수
int m; // 간선의 갯수 

int dfs(int u){

    low[u] = disc[u] = ++timer; 

    in_stack[u] = true; 
    vertex_stack.push(u); 

    // 방문 안한 나의 이웃
    for(auto v: adj[u]){
        if (disc[v] == 0){
            dfs(v); 
        }
    }

    // low[v] 갱신
    for(auto v: adj[u]){

        // stack에 없다는 건 이미 
        // 다른 SCC로 확정되었음을 의미함
        if(in_stack[v]){
            low[u] = min(
                low[u], 
                low[v]
            ); 
        }
    }

    // low[u] == disc[u]라면?
    if (disc[u] == low[u]){

        vector<int> scc = {}; 

        while(!vertex_stack.empty()){

            int v = vertex_stack.top(); 
            vertex_stack.pop(); 

            in_stack[v] = false;

            scc.push_back(v); 

            if (u == v){
                sccs.push_back(scc); 
                break; 
            } 

        }

    }


}

int main(){

    scanf("%d %d", &n, &m); 

    // 노드별 기본값 채우기 
    adj .resize(n+1); 
    disc.resize(n+1); 
    low .resize(n+1); 
    in_stack.resize(n+1); 

    // 방향 간선 입력받기 
    for(int i=0; i<m; i++){

        int u, v; 
        scanf("%d %d", &u, &v); 
        adj[u].push_back(v); 

    }

    // DFS 방문
    for(int v=1; v<=n; v++){
        if(disc[v] == 0){
            dfs(v); 
        }
    }

    // 결과 출력
    for(auto scc: sccs){

        for(int u: scc){
            printf("%d ", u); 
        }

        printf("\n"); 

    }

}