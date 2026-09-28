#include <bits/stdc++.h>
using namespace std;

// vertex
vector<int> disc;
vector<int> low;
int timer = 0;

// graph
vector<vector<int>> adj;

// SCC
vector<vector<int>> sccs;

// SCC stack
vector<bool> in_stack;
stack<int> vertex_stack;

void dfs(int v) {

    disc[v] = low[v] = ++timer; 

    vertex_stack.push(v); 
    in_stack[v] = true; 

    for(auto u : adj[v]){

        if (!disc[u]) {
            dfs(u);
            low[v] = min(low[v], low[u]);
        }
        else if (in_stack[u]) {
            low[v] = min(low[v], disc[u]);
        }

        // okay to write as

        // if (!disc[u]){
        //     dfs(u); 
        // }
        // if (in_stack[u]){
        //     low[v] = min(low[v], low[u]); 
        // }

        // but the meaning of low then changes
    }

    if (disc[v] == low[v]){

        vector<int> scc; 

        while(!vertex_stack.empty()){

            int u = vertex_stack.top(); 
            vertex_stack.pop(); 

            in_stack[u] = false; 
            
            scc.push_back(u); 

            if (u == v){
                sccs.push_back(scc); 
                break; 
            }
        }
        
    }

}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    adj.resize(n + 1);
    disc.resize(n + 1);
    low.resize(n + 1);
    in_stack.resize(n + 1);
    
    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);

        adj[u].push_back(v);
    }

    for (int v = 1; v <= n; v++) {
        if (!disc[v])
            dfs(v);
    }

    // example output
    for (int i = 0; i < (int)sccs.size(); i++) {
        printf("SCC %d:", i);

        for (int v : sccs[i])
            printf(" %d", v);

        printf("\n");
    }
}