#include <bits/stdc++.h>

using namespace std; 

int n, m; 

// left side
vector<vector<int>> adj; 

// right side
vector<int> matchR; 
vector<bool> visited; 

bool dfs(int u){

    for (auto v : adj[u]){

        if (visited[v]){
            continue; 
        }

        visited[v] = true; 

        if(matchR[v] == -1 || dfs(matchR[v])){
            matchR[v] = u; 
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

        // if 1-based
        u--, v--; 

        adj[u].push_back(v); 
    }

    matchR.assign(m, -1); 

    int answer = 0; 

    for(int u=0;u<n;u++){

        visited.assign(m, 0); 

        if(dfs(u)){
            answer++; 
        }
    }

    printf("%d", answer);

}