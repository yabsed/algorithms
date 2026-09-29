#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const ll INF = numeric_limits<ll>::max() / 4;

struct Edge {
    int to;
    int rev;
    ll cap;
};

int n, m;
int s, t;

vector<vector<Edge>> adj;

void append(int u, int v, ll c) {

    // u -----> v
    Edge fwd = {v, (int)adj[v].size(), c};
    Edge bwd = {u, (int)adj[u].size(), 0};

    adj[u].push_back(fwd);
    adj[v].push_back(bwd);
}

// parent[v] = {previous vertex, edge index}
bool bfs(vector<pair<int, int>> &parent) {

    parent.assign(n, {-1, -1});

    queue<int> q;
    q.push(s);

    parent[s] = {s, -1};

    while (!q.empty()) {

        int from = q.front();
        q.pop();

        for (int i = 0; i < (int)adj[from].size(); i++) {

            const Edge &fwd = adj[from][i];

            int to = fwd.to;

            // already visited
            if (parent[to].first != -1) {
                continue;
            }

            // zero capacity
            if (fwd.cap <= 0) {
                continue;
            }

            parent[to] = {from, i};

            if (to == t) {
                return true;
            }

            q.push(to);
        }
    }

    return false;
}

ll max_flow() {

    ll result = 0;

    vector<pair<int, int>> parent;

    while (bfs(parent)) {

        ll flow = INF;

        // find bottleneck
        for (int to = t; to != s; ) {

            auto [from, idx] = parent[to];

            Edge &fwd = adj[from][idx];

            flow = min(flow, fwd.cap);

            to = from;
        }

        // augment
        for (int to = t; to != s; ) {

            auto [from, idx] = parent[to];

            Edge &fwd = adj[from][idx];
            Edge &bwd = adj[fwd.to][fwd.rev];

            fwd.cap -= flow;
            bwd.cap += flow;

            to = from;
        }

        result += flow;
    }

    return result;
}

int main() {

    scanf("%d %d", &n, &m);

    adj.assign(n, {});

    scanf("%d %d", &s, &t);
    --s, --t;  // 1-based

    for (int i = 0; i < m; i++) {

        int u, v;
        ll c;

        scanf("%d %d %lld", &u, &v, &c);

        --u, --v;  // 1-based

        append(u, v, c);
    }

    printf("%lld\n", max_flow());
}