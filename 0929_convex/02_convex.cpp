#include <bits/stdc++.h>
using namespace std; 

// C++11
using ll = long long; 
using P = pair<ll, ll>;

ll ccw(P a, P b, P c) {
    return (b.first - a.first) * (c.second - a.second)
         - (b.second - a.second) * (c.first - a.first);
}

vector<P> convex_hull(vector<P> p) {
    sort(p.begin(), p.end());
    p.erase(unique(p.begin(), p.end()), p.end());

    if (p.size() <= 1) return p;

    vector<P> lo, hi;

    for (auto cur : p) {
        while (lo.size() >= 2 &&
               ccw(lo[lo.size()-2], lo.back(), cur) <= 0)
            lo.pop_back();
        lo.push_back(cur);
    }

    for (int i = (int)p.size() - 1; i >= 0; --i) {
        while (hi.size() >= 2 &&
               ccw(hi[hi.size()-2], hi.back(), p[i]) <= 0)
            hi.pop_back();
        hi.push_back(p[i]);
    }

    lo.pop_back();
    hi.pop_back();

    lo.insert(lo.end(), hi.begin(), hi.end());
    return lo;
}