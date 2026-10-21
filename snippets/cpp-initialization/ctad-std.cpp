#include <bits/stdc++.h>
using namespace std;

int main() {
    // --8<-- [start:core]
    pair p{1, 2.5};          // pair<int, double>
    tuple t{1, 'a', 2LL};    // tuple<int, char, long long>
    array a{1, 2, 3};        // array<int, 3>
    priority_queue pq(greater<int>{}, vector<int>{});  // 最小値を取り出す優先度付きキュー
    static_assert(is_same_v<decltype(p), pair<int, double>>);
    static_assert(is_same_v<decltype(t), tuple<int, char, long long>>);
    static_assert(is_same_v<decltype(a), array<int, 3>>);
    static_assert(is_same_v<decltype(pq), priority_queue<int, vector<int>, greater<int>>>);
    // --8<-- [end:core]
    // --8<-- [start:pair-int]
    pair q{0, 0};            // pair<int, int>。long long を入れるとあふれる
    pair r{0LL, 0};          // pair<long long, int>
    static_assert(is_same_v<decltype(q), pair<int, int>>);
    static_assert(is_same_v<decltype(r), pair<long long, int>>);
    // --8<-- [end:pair-int]
    int x;
    while (cin >> x) pq.push(x);
    cout << p.second << ' ' << get<1>(t) << ' ' << a.size() << ' ' << (pq.empty() ? -1 : pq.top()) << '\n';
}
