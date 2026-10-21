#include <bits/stdc++.h>
using namespace std;

int main() {
    // --8<-- [start:core]
    pair<int, string> p = make_pair(3, "abc");  // pair{3, "abc"s} とも書ける
    tuple<long long, int, int> t{10, 0, 1};     // 辺 (重み, 始点, 終点)
    cout << p.first << ' ' << p.second << '\n';                       // 3 abc
    cout << get<0>(t) << ' ' << get<1>(t) << ' ' << get<2>(t) << '\n';  // 10 0 1

    vector<pair<int, int>> v{{2, 1}, {1, 5}, {2, 0}};
    sort(v.begin(), v.end());  // first で比べ、等しければ second で比べる（辞書順）
    for (auto [x, y] : v) cout << '(' << x << ',' << y << ") ";
    cout << '\n';  // (1,5) (2,0) (2,1)
    // --8<-- [end:core]
    assert(pair(1, 9) < pair(2, 0));
    assert(tuple(1, 2, 3) < tuple(1, 3, 0));
}
