#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:core]
// adj[v]：v に隣接する頂点の集合（bit で表す）。n ≤ 20 を想定する
int chromatic_number(int n, const vector<int>& adj) {
    if (n == 0) return 0;
    int full = 1 << n;
    // ind[S]：S の部分集合のうち独立集合であるものの数（空集合を含む）
    vector<long long> ind(full);
    ind[0] = 1;
    for (int s = 1; s < full; s++) {
        int v = __builtin_ctz(s);
        int rest = s & ~(1 << v);
        ind[s] = ind[rest] + ind[rest & ~adj[v]];  // v を選ばない + v を選ぶ
    }
    // k 個の独立集合の組で全体を覆う数 = Σ_S (-1)^(n-|S|) ind[S]^k を 2 つの法で求める
    const long long mods[2] = {998244353, 1000000007};
    vector<long long> pw[2] = {vector<long long>(full, 1), vector<long long>(full, 1)};
    for (int k = 1; k < n; k++) {
        bool positive = false;
        for (int t = 0; t < 2; t++) {
            long long mod = mods[t], total = 0;
            for (int s = 0; s < full; s++) {
                pw[t][s] = pw[t][s] * ind[s] % mod;
                if ((n - __builtin_popcount(s)) % 2 == 0) total += pw[t][s];
                else total += mod - pw[t][s];
            }
            if (total % mod != 0) positive = true;
        }
        if (positive) return k;  // k 色で塗れる
    }
    return n;  // n 色あれば必ず塗れる
}
// --8<-- [end:core]

// 確かめ用：k 色で塗れるかを全探索する
bool brute(int n, const vector<int>& adj, int k, vector<int>& col, int v) {
    if (v == n) return true;
    for (int c = 0; c < k; c++) {
        bool ok = true;
        for (int u = 0; u < v; u++)
            if ((adj[v] >> u & 1) && col[u] == c) ok = false;
        if (!ok) continue;
        col[v] = c;
        if (brute(n, adj, k, col, v + 1)) return true;
    }
    return false;
}

int main() {
    int n, m;
    cin >> n >> m;
    vector<int> adj(n, 0);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u] |= 1 << v;
        adj[v] |= 1 << u;
    }
    int c = chromatic_number(n, adj);
    if (n <= 10) {
        vector<int> col(n);
        int b = 0;
        while (b < n && !brute(n, adj, b, col, 0)) b++;
        assert(b == c);
    }
    cout << c << '\n';
}
