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