#include <bits/stdc++.h>
using namespace std;

// vertex
vector<int> disc, low;
vector<bool> cut;
int timer = 0;

// edge
struct Edge {
    int to, id;
};

vector<vector<Edge>> adj;
vector<pair<int, int>> edges;

// BCC
vector<vector<int>> bccs;
stack<int> edge_stack;

void pop_bcc(int until) {
    vector<int> bcc;

    while (true) {
        int id = edge_stack.top();
        edge_stack.pop();

        bcc.push_back(id);

        if (id == until)
            break;
    }

    bccs.push_back(bcc);
}

void dfs(int v, int parent_edge = -1) {
    disc[v] = low[v] = ++timer;

    int children = 0;

    for (auto [u, id] : adj[v]) {
        if (id == parent_edge)
            continue;

        // tree edge
        if (!disc[u]) {
            edge_stack.push(id);
            children++;

            dfs(u, id);

            low[v] = min(low[v], low[u]);

            // cut vertex
            if (parent_edge != -1 && low[u] >= disc[v])
                cut[v] = true;

            // one BCC is complete
            if (low[u] >= disc[v])
                pop_bcc(id);
        }

        // back edge to an ancestor
        else if (disc[u] < disc[v]) {
            edge_stack.push(id);
            low[v] = min(low[v], disc[u]);
        }
    }

    // DFS root
    if (parent_edge == -1 && children >= 2)
        cut[v] = true;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    adj.resize(n + 1);
    disc.resize(n + 1);
    low.resize(n + 1);
    cut.resize(n + 1);

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