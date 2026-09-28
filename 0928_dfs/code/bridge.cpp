#include <bits/stdc++.h> 
using namespace std; 

struct Edge {
    int to; 
    int id; 
}; 

vector<vector<Edge>> adj;

vector<int> disc; // discovery order
vector<int> low; 

int timer = 0; 

vector<pair<int, int>> bridges;  


void dfs(int v, int parentEdge = -1) {

    disc[v] = low[v] = ++timer; 
    
    for(auto [u, id] : adj[v]){

        if (parentEdge == id){
            continue; 
        }

        else if (disc[u] == 0){
            
            dfs(u, id); 
            low[v] = min(low[v], low[u]); 

            if (disc[v] < low[u]){
                bridges.push_back({u, v}); 
            }

        }

        else {
            low[v] = min(low[v], disc[u]); 
        }
    }
}

int main(){

    int n, m; 
    scanf("%d %d", &n, &m); 

    adj.assign(n+1, {}); 
    disc.assign(n+1, 0); 
    low.assign(n+1, 0); 

    for(int id = 0; id < m; ++id){
        int u, v; 
        scanf("%d %d", &u, &v); 

        adj[u].push_back({v, id}); 
        adj[v].push_back({u, id}); 
    }

    for (int v=1; v<=n; ++v){
        if (disc[v] == 0)
            dfs(v); 
    }

    for (auto [u, v] : bridges){
        printf("%d %d\n", u, v);
    }

}
