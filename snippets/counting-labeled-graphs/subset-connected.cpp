#include <bits/stdc++.h>
#include <atcoder/modint>
using namespace std;
using mint = atcoder::modint998244353;

// --8<-- [start:core]
// adj[v] ＝ v と辺で結ばれた頂点の bit。頂点集合 S ごとに、
// S の内側の辺から部分集合を選んで S 全体が連結になる選び方の数 c[S] を求める。O(3^n)
vector<mint> connected_by_subset(int n, const vector<int>& adj, int m) {
    int full = (1 << n) - 1;
    vector<int> e(1 << n, 0);                    // e[S] ＝ S の内側の辺の数
    for (int S = 1; S <= full; S++) {
        int v = __builtin_ctz(S);
        e[S] = e[S ^ (1 << v)] + __builtin_popcount(adj[v] & S);
    }
    vector<mint> pw(m + 1, 1);
    for (int i = 1; i <= m; i++) pw[i] = pw[i - 1] * 2;
    vector<mint> c(1 << n, 0);
    for (int S = 1; S <= full; S++) {
        c[S] = pw[e[S]];                         // 全体
        int low = S & -S, rest = S ^ low;        // 代表は S の最小の頂点
        if (rest == 0) continue;                 // 1 頂点なら連結
        // T ＝ low を含む S の真部分集合（low を含む連結成分）
        for (int t = (rest - 1) & rest; ; t = (t - 1) & rest) {
            int T = t | low;
            c[S] -= c[T] * pw[e[S ^ T]];         // T の外は自由、T とは辺なし
            if (t == 0) break;
        }
    }
    return c;
}
// --8<-- [end:core]

// 検算用：辺の部分集合をすべて試す
long long brute(int n, const vector<pair<int, int>>& edges) {
    int m = edges.size();
    long long cnt = 0;
    for (int bits = 0; bits < (1 << m); bits++) {
        vector<int> par(n);
        iota(par.begin(), par.end(), 0);
        auto find = [&](auto&& self, int x) -> int {
            return par[x] == x ? x : par[x] = self(self, par[x]);
        };
        int comp = n;
        for (int i = 0; i < m; i++) {
            if (!(bits >> i & 1)) continue;
            int a = find(find, edges[i].first), b = find(find, edges[i].second);
            if (a != b) { par[a] = b; comp--; }
        }
        if (comp == 1) cnt++;
    }
    return cnt;
}

int main() {
    int n, m;
    cin >> n >> m;
    vector<int> adj(n, 0);
    vector<pair<int, int>> edges(m);
    for (auto& [a, b] : edges) {
        cin >> a >> b;
        a--, b--;
        adj[a] |= 1 << b;
        adj[b] |= 1 << a;
    }
    vector<mint> c = connected_by_subset(n, adj, m);
    if (m <= 20) assert(c[(1 << n) - 1].val() == brute(n, edges));
    cout << c[(1 << n) - 1].val() << '\n';
}
