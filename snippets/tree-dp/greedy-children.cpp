// 子ごとの「得」を大きい順に取る木 DP：各頂点 v に接する選んだ辺が d[v] 本以下になる辺の選び方の、重みの和の最大
// 入力：N、d_1 … d_N、続く N - 1 行に辺 u v w（1-indexed、w は負もある）
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> d(n);
    for (int i = 0; i < n; i++) cin >> d[i];
    vector<vector<pair<int, long long>>> g(n);
    vector<array<long long, 3>> edges;
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        long long w;
        cin >> u >> v >> w;
        u--, v--;
        g[u].push_back({v, w});
        g[v].push_back({u, w});
        edges.push_back({u, v, w});
    }
    // --8<-- [start:core]
    const long long NEG = LLONG_MIN / 4;  // 「その状態にできない」
    // full[v]：v の部分木で、v に接する子への辺を d[v] 本まで選んだときの最大
    // rest[v]：親との辺も選ぶ前提で、子への辺を d[v] - 1 本まで選んだときの最大（d[v] = 0 なら NEG）
    vector<long long> full(n), rest(n);
    auto dfs = [&](auto&& self, int v, int p) -> void {
        long long base = 0;
        vector<long long> gain;  // 子 c への辺を選ぶと、選ばない場合よりいくら増えるか
        for (auto [c, w] : g[v]) {
            if (c == p) continue;
            self(self, c, v);
            base += full[c];
            if (rest[c] != NEG) gain.push_back(w + rest[c] - full[c]);
        }
        sort(gain.rbegin(), gain.rend());  // 得の大きい順
        auto best = [&](int limit) {       // 正の得を大きい方から limit 個まで足す
            long long s = base;
            for (int i = 0; i < limit && i < (int)gain.size() && gain[i] > 0; i++) s += gain[i];
            return s;
        };
        full[v] = best(d[v]);
        rest[v] = d[v] >= 1 ? best(d[v] - 1) : NEG;
    };
    dfs(dfs, 0, -1);
    long long ans = full[0];
    // --8<-- [end:core]
    // 小さい木では辺の部分集合を全部試して確かめる
    if (n - 1 <= 16) {
        long long brute = 0;
        for (int s = 0; s < (1 << (n - 1)); s++) {
            vector<int> deg(n, 0);
            long long sum = 0;
            for (int i = 0; i < n - 1; i++)
                if (s >> i & 1) deg[edges[i][0]]++, deg[edges[i][1]]++, sum += edges[i][2];
            bool ok = true;
            for (int v = 0; v < n; v++) if (deg[v] > d[v]) ok = false;
            if (ok) brute = max(brute, sum);
        }
        assert(ans == brute);
    }
    cout << ans << '\n';
}
