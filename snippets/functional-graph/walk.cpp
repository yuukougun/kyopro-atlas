#include <bits/stdc++.h>
using namespace std;

// 頂点 0..n-1、辺 v → a[v]、辺のコスト c[v]。
// 3 色の印を付けて辺をたどり、閉路ごとにその上の辺のコストの最小を足す。
int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    vector<long long> c(n);
    for (auto& x : a) cin >> x;
    for (auto& x : c) cin >> x;

    // --8<-- [start:core]
    vector<int> state(n, 0);  // 0 = 未訪問、1 = 今のたどりの途中、2 = 処理済み
    long long ans = 0;
    for (int s = 0; s < n; s++) {
        if (state[s] != 0) continue;
        vector<int> path;
        int v = s;
        while (state[v] == 0) {        // 印のある頂点に当たるまで進む
            state[v] = 1;
            path.push_back(v);
            v = a[v];
        }
        if (state[v] == 1) {           // 今のたどりの途中に戻った：v から先が新しい閉路
            long long mn = c[v];
            for (int u = a[v]; u != v; u = a[u]) mn = min(mn, c[u]);
            ans += mn;
        }                              // state[v] == 2 なら既知の閉路か木に合流しただけ
        for (int u : path) state[u] = 2;
    }
    // --8<-- [end:core]

    for (int v = 0; v < n; v++) assert(state[v] == 2);
    cout << ans << '\n';
}
