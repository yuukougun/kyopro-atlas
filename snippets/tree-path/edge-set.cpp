#include <bits/stdc++.h>
using namespace std;

// 入力：n と n − 1 本の辺（0-indexed）、m と m 組の頂点 u v
// 出力：各辺を白か黒に塗る 2^(n−1) 通りのうち、m 本のパスのどれにも黒い辺が 1 本以上ある塗り方の数
int main() {
    int n;
    cin >> n;
    vector<vector<int>> g(n);
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    int m;
    cin >> m;
    vector<int> us(m), vs(m);
    for (int i = 0; i < m; i++) cin >> us[i] >> vs[i];

    // --8<-- [start:mask]
    // 根を 0 にして親と深さを求める。辺 (c, par[c]) を子 c の番号の bit で表す（n ≤ 64 なら 1 つの整数に入る）
    vector<int> par(n, -1), dep(n, -1);
    queue<int> que;
    dep[0] = 0;
    que.push(0);
    while (!que.empty()) {
        int v = que.front();
        que.pop();
        for (int c : g[v]) {
            if (dep[c] != -1) continue;
            dep[c] = dep[v] + 1;
            par[c] = v;
            que.push(c);
        }
    }
    // パス u–v の辺の集合。深い方を 1 つずつ上げ、通った辺の bit を立てる（LCA に着いたら止まる）
    auto path_mask = [&](int u, int v) {
        unsigned long long mask = 0;
        while (u != v) {
            if (dep[u] < dep[v]) swap(u, v);
            mask |= 1ULL << u;  // 辺 (u, par[u])
            u = par[u];
        }
        return mask;
    };
    // --8<-- [end:mask]

    // --8<-- [start:count]
    vector<unsigned long long> mask(m);
    for (int i = 0; i < m; i++) mask[i] = path_mask(us[i], vs[i]);
    long long ans = 0;
    for (int S = 0; S < (1 << m); S++) {  // S のパスの辺をすべて白にする（条件を破る）
        unsigned long long uni = 0;
        for (int i = 0; i < m; i++) {
            if (S >> i & 1) uni |= mask[i];
        }
        long long ways = 1LL << (n - 1 - popcount(uni));  // 和集合の外の辺は自由に塗る
        ans += (popcount((unsigned)S) % 2 == 0) ? ways : -ways;
    }
    // --8<-- [end:count]
    cout << ans << '\n';

    // 小さい木では、塗り方を全部試して確かめる
    if (n <= 16) {
        long long brute = 0;
        for (int black = 0; black < (1 << n); black += 2) {  // bit c が 1 なら辺 (c, par[c]) が黒。根の bit 0 は使わない
            bool ok = true;
            for (int i = 0; i < m; i++) {
                if ((mask[i] & (unsigned long long)black) == 0) ok = false;
            }
            if (ok) brute++;
        }
        assert(brute == ans);
    }
}
