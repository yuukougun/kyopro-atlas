// 計算順序が自明でない DP のメモ化再帰：辺に重み（負もある）のある有向グラフで、
// 頂点 0 から頂点 n-1 へ向かう有向路の重みの和の最大値を求める。
// 状態を「未計算・計算中・計算済み」の 3 値で持ち、計算中の頂点に戻ってきたら閉路があると分かる。
// 出力：最大値。n-1 へ行けなければ NA、0 から閉路に届けば cycle。
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    assert(1 <= n && 0 <= m);
    vector<vector<pair<int, long long>>> g(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        long long w;
        cin >> u >> v >> w;
        assert(0 <= u && u < n && 0 <= v && v < n);
        g[u].push_back({v, w});
    }

    // --8<-- [start:core]
    const long long NEG = LLONG_MIN / 4;  // n-1 に届かない（答えの値とは別の意味の印）
    vector<int> state(n, 0);              // 0：未計算、1：計算中、2：計算済み
    vector<long long> memo(n, NEG);       // memo[v] ＝ v から n-1 までの重みの和の最大
    bool has_cycle = false;
    auto f = [&](auto&& self, int v) -> long long {
        if (state[v] == 2) return memo[v];
        if (state[v] == 1) {              // 計算中の v に戻った：閉路があり、このままでは止まらない
            has_cycle = true;
            return NEG;
        }
        state[v] = 1;
        long long res = (v == n - 1 ? 0 : NEG);
        for (auto [to, w] : g[v]) {
            long long r = self(self, to);
            if (r != NEG) res = max(res, r + w);  // 届かない行き先は使わない
        }
        state[v] = 2;
        return memo[v] = res;
    };
    long long ans = f(f, 0);
    if (has_cycle) cout << "cycle\n";
    else if (ans == NEG) cout << "NA\n";
    else cout << ans << '\n';
    // --8<-- [end:core]
}
