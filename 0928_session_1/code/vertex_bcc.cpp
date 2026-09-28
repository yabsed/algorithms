#include <bits/stdc++.h>
using namespace std;

// vertex
vector<int> disc, low;
vector<bool> cut;
int timer = 0;

// edge
struct Edge {
    int to; 
    int id;
};

vector<vector<Edge>> adj;
vector<pair<int, int>> edges;

// BCC
vector<vector<int>> bccs;
stack<int> edge_stack;

void pop_bcc(int until) {

    vector<int> bcc; 

    while(!edge_stack.empty()){

        int id = edge_stack.top(); 
        edge_stack.pop(); 

        bcc.push_back(id); 

        if (id == until){
            break; 
        }
    }
    bccs.push_back(bcc); 
}

void dfs(int v, int parent_edge = -1) {

    disc[v] = low[v] = ++timer; 

    int children = 0;

    for(auto [u, id]: adj[v]){

        if (id == parent_edge){
            continue; 
        }

        else if (disc[u] == 0){

            edge_stack.push(id); 
            children++; 
            
            dfs(u, id); 

            low[v] = min(low[v], low[u]); 
            
            // BCC complete
            if (disc[v] <= low[u]){
                pop_bcc(id); 

                // cut vertex
                if(parent_edge != -1){
                    cut[v] = true; 
                }
            }
        }

        // back edge to an ancestor
        else if (disc[v] > disc[u]){
            edge_stack.push(id); 
            low[v] = min(low[v], disc[u]); 
        }
    }

    // DFS root
    if (parent_edge == -1 && children >= 2){
        cut[v] = true; 
    }
}

int main() {

    // verticies, edges
    int n, m;
    scanf("%d %d", &n, &m);

    adj.resize(n + 1);
    disc.resize(n + 1);
    low.resize(n + 1);
    cut.resize(n + 1);

    // scan edges
    for (int id = 0; id < m; id++) {

        int u, v;
        scanf("%d %d", &u, &v);

        edges.push_back({u, v});

        adj[u].push_back({v, id});
        adj[v].push_back({u, id});
    }

    for (int v = 1; v <= n; v++) {
        if (!disc[v])
            dfs(v);
    }

    for (int v = 1; v <= n; v++) {
        if (cut[v])
            printf("%d\n", v);
    }
}