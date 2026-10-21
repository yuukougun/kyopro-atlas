// 連結な無向グラフで、u から v へのウォークの重み（通った辺の重みの XOR。同じ辺を何度通ってもよい）の最小値。
// 入力：n m、辺 a b w（1-indexed）× m、q、u v × q。出力：各クエリの最小値。
#include <bits/stdc++.h>
using namespace std;

const int B = 60;

struct XorBasis {
    long long b[B] = {};
    bool insert(long long x) {
        for (int i = B - 1; i >= 0; i--) {
            if ((x >> i & 1) == 0) continue;
            if (b[i] == 0) {
                b[i] = x;
                return true;
            }
            x ^= b[i];
        }
        return false;
    }
    long long reduce(long long x) const {
        for (int i = B - 1; i >= 0; i--) x = min(x, x ^ b[i]);
        return x;
    }
};

int main() {
    int n, m;
    cin >> n >> m;
    vector<array<long long, 3>> edges(m);
    vector<vector<pair<int, long long>>> g(n);
    for (int i = 0; i < m; i++) {
        int a, b;
        long long w;
        cin >> a >> b >> w;
        a--, b--;
        edges[i] = {a, b, w};
        g[a].push_back({b, w});
        g[b].push_back({a, w});
    }

    // --8<-- [start:core]
    // d[v]：頂点 0 からスタックで訪ねてできる全域木（木の形は問わない）をたどって v へ行くパスの XOR（-1 は未訪問）
    vector<long long> d(n, -1);
    d[0] = 0;
    vector<int> st = {0};
    while (!st.empty()) {
        int v = st.back();
        st.pop_back();
        for (auto [to, w] : g[v]) {
            if (d[to] != -1) continue;
            d[to] = d[v] ^ w;
            st.push_back(to);
        }
    }
    // どの辺 (a, b, w) も「閉路の XOR」d[a] ^ d[b] ^ w を基底に入れる（木の辺なら 0 で何も起きない）
    XorBasis xb;
    for (auto [a, b, w] : edges) xb.insert(d[a] ^ d[b] ^ w);
    // u から v へのウォークの XOR の最小値は xb.reduce(d[u] ^ d[v])
    // --8<-- [end:core]

    // 線形性：reduce(d[u]) ^ reduce(d[v]) == reduce(d[u] ^ d[v])
    for (int u = 0; u < n; u++) {
        for (int v = 0; v < n; v++) assert((xb.reduce(d[u]) ^ xb.reduce(d[v])) == xb.reduce(d[u] ^ d[v]));
    }
    // 重みが小さいときは（頂点, XOR の値）の BFS と比べる
    long long mx = 0;
    for (auto [a, b, w] : edges) mx = max(mx, w);
    if (mx < 16) {
        for (int s = 0; s < n; s++) {
            vector<array<bool, 16>> seen(n);
            for (auto& row : seen) row.fill(false);
            seen[s][0] = true;
            queue<pair<int, int>> que;
            que.push({s, 0});
            while (!que.empty()) {
                auto [v, x] = que.front();
                que.pop();
                for (auto [to, w] : g[v]) {
                    int y = x ^ (int)w;
                    if (!seen[to][y]) {
                        seen[to][y] = true;
                        que.push({to, y});
                    }
                }
            }
            for (int t = 0; t < n; t++) {
                int best = 0;
                while (!seen[t][best]) best++;
                assert(best == xb.reduce(d[s] ^ d[t]));
            }
        }
    }

    int q;
    cin >> q;
    for (int i = 0; i < q; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        cout << xb.reduce(d[u] ^ d[v]) << '\n';
    }
}
