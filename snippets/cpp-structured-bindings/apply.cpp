#include <bits/stdc++.h>
using namespace std;

int main() {
    // --8<-- [start:core]
    tuple<int, int, int> t{3, 4, 5};
    int s = apply([](int a, int b, int c) { return a + b + c; }, t);  // f(3, 4, 5) と同じ
    cout << s << '\n';  // 12

    vector<array<int, 3>> es{{2, 0, 1}, {1, 1, 2}};  // 同じ型の組：(重み, u, v)
    sort(es.begin(), es.end());                       // array も辞書順で比べられる
    for (auto [w, u, v] : es) cout << w << ' ' << u << ' ' << v << '\n';
    // --8<-- [end:core]
    assert(apply([](int a, int b, int c) { return a * b * c; }, es[0]) == 2);
}
