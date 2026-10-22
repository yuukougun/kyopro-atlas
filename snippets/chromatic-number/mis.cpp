#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:core]
// adj[v]：v に隣接する頂点の集合（bit で表す）。n ≤ 40 を想定する
// 前半 A = 頂点 [0, h)、後半 B = 頂点 [h, n) に分ける
vector<int> max_independent_set(int n, const vector<unsigned long long>& adj) {
    int h = n / 2, m = n - h;
    // 後半：best[Y] = Y の中の最大独立集合の大きさ、pick[Y] = その集合
    vector<int> best(1 << m, 0), pick(1 << m, 0);
    for (int y = 1; y < (1 << m); y++) {
        int i = __builtin_ctz(y);
        int rest = y & ~(1 << i);
        int nb = (int)(adj[h + i] >> h);
        int with = rest & ~nb;  // h + i を選ぶなら隣を除く
        if (best[rest] >= best[with] + 1) {
            best[y] = best[rest], pick[y] = pick[rest];
        } else {
            best[y] = best[with] + 1, pick[y] = pick[with] | (1 << i);
        }
    }
    // 前半：独立な X ごとに、X と隣接しない後半の頂点の中で最良のものと組み合わせる
    vector<char> ok(1 << h, 1);
    vector<int> ban(1 << h, 0);  // X の隣にある後半の頂点の集合
    int best_size = -1, best_x = 0, best_y = 0;
    for (int x = 0; x < (1 << h); x++) {
        if (x > 0) {
            int v = __builtin_ctz(x);
            int rest = x & ~(1 << v);
            ok[x] = ok[rest] && !(adj[v] & (unsigned long long)rest);
            ban[x] = ban[rest] | (int)(adj[v] >> h);
        }
        if (!ok[x]) continue;
        int y = ((1 << m) - 1) & ~ban[x];
        int size = __builtin_popcount(x) + best[y];
        if (size > best_size) best_size = size, best_x = x, best_y = pick[y];
    }
    vector<int> res;
    for (int v = 0; v < h; v++) if (best_x >> v & 1) res.push_back(v);
    for (int i = 0; i < m; i++) if (best_y >> i & 1) res.push_back(h + i);
    return res;
}
// --8<-- [end:core]

int main() {
    int n, m;
    cin >> n >> m;
    vector<unsigned long long> adj(n, 0);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u] |= 1ULL << v;
        adj[v] |= 1ULL << u;
    }
    vector<int> res = max_independent_set(n, adj);
    for (int a : res) for (int b : res) assert(!(adj[a] >> b & 1));  // 独立である
    if (n <= 16) {  // 全探索と大きさを比べる
        int bf = 0;
        for (int s = 0; s < (1 << n); s++) {
            bool ok = true;
            for (int v = 0; v < n; v++)
                if ((s >> v & 1) && (adj[v] & (unsigned long long)s)) ok = false;
            if (ok) bf = max(bf, __builtin_popcount(s));
        }
        assert(bf == (int)res.size());
    }
    cout << res.size() << '\n';
}
