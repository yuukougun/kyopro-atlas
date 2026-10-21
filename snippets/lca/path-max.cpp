#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<vector<pair<int, long long>>> g(n);
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        long long w;  // 1 ≤ w を仮定する（0 を最大値の単位元に使う）
        cin >> a >> b >> w;
        a--, b--;
        g[a].push_back({b, w});
        g[b].push_back({a, w});
    }

    int LOG = 1;
    while ((1 << LOG) < n) LOG++;
    vector<int> dep(n, -1);
    vector<vector<int>> up(LOG, vector<int>(n));
    // --8<-- [start:build]
    // mx[k][v]：v から 2^k 本の辺を上る間の、辺の重みの最大。辺 (v, 親) の重みは子 v に置く
    vector<vector<long long>> mx(LOG, vector<long long>(n, 0));
    queue<int> que;
    dep[0] = 0;
    up[0][0] = 0;
    mx[0][0] = 0;  // 根から上る辺はない。最大値の単位元 0 にしておく
    que.push(0);
    while (!que.empty()) {
        int v = que.front();
        que.pop();
        for (auto [c, w] : g[v]) {
            if (dep[c] != -1) continue;
            dep[c] = dep[v] + 1;
            up[0][c] = v;
            mx[0][c] = w;
            que.push(c);
        }
    }
    for (int k = 0; k + 1 < LOG; k++) {
        for (int v = 0; v < n; v++) {
            int mid = up[k][v];
            up[k + 1][v] = up[k][mid];
            mx[k + 1][v] = max(mx[k][v], mx[k][mid]);  // 前半の 2^k 本と後半の 2^k 本
        }
    }
    // --8<-- [end:build]

    // --8<-- [start:path-max]
    auto path_max = [&](int u, int v) {  // パス u–v 上の辺の重みの最大（u == v なら 0）
        long long res = 0;
        if (dep[u] < dep[v]) swap(u, v);
        int diff = dep[u] - dep[v];
        for (int k = 0; k < LOG; k++) {
            if (diff >> k & 1) {
                res = max(res, mx[k][u]);  // 跳ぶ前に、跳ぶ区間の最大を足す
                u = up[k][u];
            }
        }
        if (u == v) return res;
        for (int k = LOG - 1; k >= 0; k--) {
            if (up[k][u] != up[k][v]) {
                res = max({res, mx[k][u], mx[k][v]});  // u 側と v 側の両方を足す
                u = up[k][u];
                v = up[k][v];
            }
        }
        return max({res, mx[0][u], mx[0][v]});  // LCA へ上る最後の 2 本
    };
    // --8<-- [end:path-max]

    // --8<-- [start:farthest]
    // v から根へ、重みが X 以下の辺だけを通って行ける最も遠い祖先
    auto farthest = [&](int v, long long X) {
        for (int k = LOG - 1; k >= 0; k--) {
            // 根を越えない（2^k ≤ dep[v]）かつ、跳ぶ区間の辺がすべて X 以下なら跳ぶ
            if ((1 << k) <= dep[v] && mx[k][v] <= X) v = up[k][v];
        }
        return v;
    };
    // --8<-- [end:farthest]

    // 素朴な方法と比べる
    auto naive_max = [&](int u, int v) {
        long long res = 0;
        while (u != v) {
            if (dep[u] < dep[v]) swap(u, v);
            res = max(res, mx[0][u]);
            u = up[0][u];
        }
        return res;
    };
    auto naive_far = [&](int v, long long X) {
        while (v != 0 && mx[0][v] <= X) v = up[0][v];
        return v;
    };
    for (int u = 0; u < n; u++) {
        for (int v = 0; v < n; v++) assert(path_max(u, v) == naive_max(u, v));
        for (long long X = 0; X <= 10; X++) assert(farthest(u, X) == naive_far(u, X));
    }

    int q;
    cin >> q;
    while (q--) {
        int t, a;
        long long b;
        cin >> t >> a >> b;
        a--;
        if (t == 1) {
            cout << path_max(a, (int)b - 1) << '\n';
        } else {
            cout << farthest(a, b) + 1 << '\n';
        }
    }
}
