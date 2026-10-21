#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<vector<int>> g(n);
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    // --8<-- [start:build]
    int LOG = 1;
    while ((1 << LOG) < n) LOG++;  // 2^LOG ≥ n。深さは n − 1 以下なので、どの深さも LOG 桁に収まる
    vector<int> dep(n, -1);
    vector<vector<int>> up(LOG, vector<int>(n));  // up[k][v]：v の 2^k 個上の祖先
    // BFS で親と深さを求める（パス状の木でも再帰が深くならない）
    queue<int> que;
    dep[0] = 0;
    up[0][0] = 0;  // 根の親は根自身にしておく（表が配列の外を指さない）
    que.push(0);
    while (!que.empty()) {
        int v = que.front();
        que.pop();
        for (int c : g[v]) {
            if (dep[c] != -1) continue;
            dep[c] = dep[v] + 1;
            up[0][c] = v;
            que.push(c);
        }
    }
    for (int k = 0; k + 1 < LOG; k++) {
        for (int v = 0; v < n; v++) up[k + 1][v] = up[k][up[k][v]];
    }
    // --8<-- [end:build]

    // --8<-- [start:lca]
    auto lca = [&](int u, int v) {
        if (dep[u] < dep[v]) swap(u, v);
        int diff = dep[u] - dep[v];
        for (int k = 0; k < LOG; k++) {
            if (diff >> k & 1) u = up[k][u];  // 深いほうを diff 個上げて深さをそろえる
        }
        if (u == v) return u;  // v が u の祖先だった
        for (int k = LOG - 1; k >= 0; k--) {
            if (up[k][u] != up[k][v]) {  // 2^k 個上がまだ違うときだけ両方を跳ばす
                u = up[k][u];
                v = up[k][v];
            }
        }
        return up[0][u];  // u と v は LCA の 1 つ下の子にいる
    };
    auto dist = [&](int u, int v) { return dep[u] + dep[v] - 2 * dep[lca(u, v)]; };
    // --8<-- [end:lca]

    // --8<-- [start:kth]
    auto kth = [&](int v, int K) {  // v の K 個上の祖先。根を越えるなら -1
        if (K > dep[v]) return -1;
        for (int k = 0; k < LOG; k++) {
            if (K >> k & 1) v = up[k][v];
        }
        return v;
    };
    // --8<-- [end:kth]

    // 親を 1 つずつたどる素朴な方法と比べる
    auto naive_lca = [&](int u, int v) {
        while (dep[u] > dep[v]) u = up[0][u];
        while (dep[v] > dep[u]) v = up[0][v];
        while (u != v) u = up[0][u], v = up[0][v];
        return u;
    };
    for (int u = 0; u < n; u++) {
        for (int v = 0; v < n; v++) assert(lca(u, v) == naive_lca(u, v));
    }

    int q;
    cin >> q;
    while (q--) {
        int t, a, b;
        cin >> t >> a >> b;
        if (t == 1) {
            a--, b--;
            cout << lca(a, b) + 1 << ' ' << dist(a, b) << '\n';
        } else {
            a--;
            int r = kth(a, b);
            cout << (r == -1 ? -1 : r + 1) << '\n';
        }
    }
}
