#include <bits/stdc++.h>
using namespace std;

int main() {

    set<int> s;

    // insert: O(log n)
    s.insert(5);
    s.insert(1);
    s.insert(7);
    s.insert(5);   // 중복 무시

    // {1, 5, 7}


    // find: O(log n)
    auto it = s.find(5);

    if (it != s.end()) {
        cout << *it << '\n';
    }


    // count: O(log n)
    // set에서는 결과가 0 또는 1
    if (s.count(5)) {
        cout << "exists\n";
    }


    // erase by value: O(log n)
    // 삭제한 원소 개수 반환 (set에서는 0 또는 1)
    int cnt = s.erase(5);


    // erase by iterator
    // 삭제한 원소의 다음 원소를 가리키는 iterator 반환
    it = s.find(7);

    if (it != s.end()) {
        it = s.erase(it);
    }


    // lower_bound(x): O(log n)
    // >= x 중 가장 작은 원소
    it = s.lower_bound(4);

    if (it != s.end()) {
        cout << *it << '\n';
    }


    // upper_bound(x): O(log n)
    // > x 중 가장 작은 원소
    it = s.upper_bound(4);

    if (it != s.end()) {
        cout << *it << '\n';
    }


    // <= x 중 가장 큰 원소
    it = s.upper_bound(4);

    if (it != s.begin()) {
        --it;
        cout << *it << '\n';
    }


    // < x 중 가장 큰 원소
    it = s.lower_bound(4);

    if (it != s.begin()) {
        --it;
        cout << *it << '\n';
    }


    // 순회: O(n)
    for (int x : s) {
        cout << x << ' ';
    }
    cout << '\n';


    // iterator로 순회하면서 삭제
    // erase(it)는 다음 원소 iterator를 반환
    for (auto it = s.begin(); it != s.end(); ) {

        if (*it % 2 == 1) {
            it = s.erase(it);
        }
        else {
            ++it;
        }
    }
}