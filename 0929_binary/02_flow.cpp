#include <bits/stdc++.h>
using namespace std; 

const long long INF = numeric_limits<long long>::max() / 4;

struct Edge {
    int to; 
    int rev; 
    long long cap; 
};  

// adj[v] has many edges 
vector<vector<Edge>> adj;

// new edge u --(c)--> v
void append(int u, int v, long long c){

    // consider self-loop
    if(u == v) return; 

    Edge fwd = {v, (int)adj[v].size(), c}; 
    Edge bwd = {u, (int)adj[u].size(), 0}; 

    adj[u].push_back(fwd); 
    adj[v].push_back(bwd); 
}

// vertices, edges
int n, m; 

// start, finish
int s, t; 

bool bfs(vector<pair<int, int>> &parent){

    // in u --(idx)--> v connection
    // parent[v] saves {u, idx}

    parent.assign(n, {-1, -1}); 
    queue<int> q; 

    q.push(s); 
    parent[s] = {s, -1}; 

    while(!q.empty()){

        int from = q.front(); 
        q.pop(); 

        for(int i=0;i<adj[from].size();i++){

            Edge e = adj[from][i]; 

            // already visited
            if(parent[e.to].first != -1){
                continue; 
            }

            // no extra capacity
            if(e.cap <= 0){
                continue; 
            }

            parent[e.to] = {from, i}; 

            // arrived finishing point
            if (e.to == t){
                return true; 
            }

            q.push(e.to); 
        }

    }

    return false; 
    
}

int main(){

    scanf("%d %d", &n, &m); 
    adj.assign(n, {}); 

    scanf("%d %d", &s, &t); 
    // 1-based
    --s, --t; 

    for(int i=0;i<m;i++){

        int u, v; 
        long long c; 
        scanf("%d %d %lld", &u, &v, &c); 

        // 1-based
        --u, --v; 
        append(u, v, c); 
    }

    long long maxFlow = 0; 

    vector<pair<int, int>> parent;
    
    while(bfs(parent)){

        long long flow = INF; 

        // detect flow size
        for(int to = t; to != s; ){

            auto [from, idx] = parent[to]; 
            Edge &fwd = adj[from][idx]; 

            flow = min(flow, fwd.cap); 

            to = from; 
        }

        // move capacity from fwd to bwd
        for(int to = t; to != s; ){

            auto [from, idx] = parent[to]; 

            // GPT recommneds me to use reference

            Edge &fwd = adj[from][idx];
            Edge &bwd = adj[to]  [fwd.rev]; 

            fwd.cap -= flow; 
            bwd.cap += flow; 
            
            // alternative : use pointer 

            // Edge* fwd = &adj[from][idx]; 
            // Edge* bwd = &adj[to]  [fwd->rev]; 

            // fwd->cap -= flow; 
            // bwd->cap += flow; 

            to = from; 
        }

        maxFlow += flow; 
    }


    printf("%lld", maxFlow); 

    // adj represents final residual graph

}