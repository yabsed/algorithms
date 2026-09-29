#include <bits/stdc++.h>
using namespace std;

int main() {

    // random
    mt19937 rng(1234);
    uniform_int_distribution<int> distInt(1, 100);
    uniform_real_distribution<double> distDouble(0.0, 1.0);

    int x = distInt(rng);

    // shuffle
    vector<int> v(10);
    iota(v.begin(), v.end(), 0);
    shuffle(v.begin(), v.end(), rng);

    // sort - ascending
    sort(v.begin(), v.end());

    // sort - descending
    sort(v.begin(), v.end(), greater<>());

    // reverse
    reverse(v.begin(), v.end());

    // priority_queue - min heap
    priority_queue<int, vector<int>, greater<int>> pq;

    // customized sort with lambda
    int base = 3;

    sort(v.begin(), v.end(), [base](int x, int y) {

        int rx = ((x % base) + base) % base;
        int ry = ((y % base) + base) % base;

        if (rx != ry)
            return rx < ry;

        return x < y;
    });

    // generic lambda (C++14+)
    sort(v.begin(), v.end(), [](const auto& x, const auto& y) {
        return x < y;
    });

    // pair: first, then second
    vector<pair<int, int>> p;
    sort(p.begin(), p.end());

    // unique
    vector<int> w = {1,1,1,1,4,4,4,3,3,3};

    sort(w.begin(), w.end());
    w.erase(unique(w.begin(), w.end()), w.end());
}