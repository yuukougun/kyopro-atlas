#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto& x : a) cin >> x;
    // --8<-- [start:core]
    // （値, 添字）の組の vector を作って並べる
    auto p = views::zip(a, views::iota(0)) | ranges::to<vector<pair<int, int>>>();
    ranges::sort(p);
    // 異なる値の集合
    auto st = a | ranges::to<set>();
    // 入れ子：g[i] = {0, 1, ..., i - 1}
    auto g = views::iota(0, 3) | views::transform([](int i) { return views::iota(0, i); })
           | ranges::to<vector<vector<int>>>();
    // 要素の型を省くと推論される：vector<int>
    auto sq = a | views::transform([](int x) { return x * x; }) | ranges::to<vector>();
    // --8<-- [end:core]
    static_assert(is_same_v<decltype(sq), vector<int>>);
    for (auto [x, i] : p) cout << i << ' ';
    cout << '\n' << st.size() << ' ' << g[2].size() << ' ' << sq.size() << '\n';
}
