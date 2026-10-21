#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto& x : a) cin >> x;
    // --8<-- [start:core]
    // 隣り合う 2 個：狭義単調増加か
    bool inc = true;
    for (auto [p, q] : a | views::pairwise) inc = inc && p < q;
    // 隣り合う 3 個：山（p < q > r）の数
    int peaks = 0;
    for (auto [p, q, r] : a | views::adjacent<3>) peaks += (p < q && q > r);
    // 隣どうしの差の列 a[i+1] - a[i]
    vector<int> d;
    for (int x : a | views::pairwise_transform([](int p, int q) { return q - p; })) d.push_back(x);
    // --8<-- [end:core]
    cout << (inc ? "Yes" : "No") << ' ' << peaks << ' ' << d.size() << '\n';
    for (int x : d) cout << x << ' ';
    cout << '\n';
}
