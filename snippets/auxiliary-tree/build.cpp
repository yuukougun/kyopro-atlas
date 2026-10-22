#include <bits/stdc++.h>
using namespace std;

// 入力：N、辺 N − 1 本（1-indexed）、Q、各クエリは K と指定頂点 K 個（相異なる）
// 出力：クエリごとに「圧縮木の頂点数」と「指定頂点を結ぶ最小の部分木の辺の数」
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

    // 行きがけ番号 in・出る番号 out・深さ・親を、非再帰の DFS で求める（根は 0）
    vector<int> in(n), out(n), dep(n), par(n, 0);
    int t = 0;
    vector<int> st = {0};
    while (!st.empty()) {
        int v = st.back();
        st.pop_back();
        if (v < 0) {
            out[~v] = t;  // 部分木は行きがけ順の区間 [in[v], out[v])
            continue;
        }
        in[v] = t++;
        st.push_back(~v);
        for (int c : g[v]) {
            if (c == par[v]) continue;  // 根の par は 0 で、根の隣は 0 でないので飛ばさない
            par[c] = v;
            dep[c] = dep[v] + 1;
            st.push_back(c);
        }
    }

    // ダブリングの LCA（前計算 O(N log N)、1 回 O(log N)）
    int LOG = 1;
    while ((1 << LOG) < n) LOG++;
    vector<vector<int>> up(LOG, par);
    for (int k = 0; k + 1 < LOG; k++) {
        for (int v = 0; v < n; v++) up[k + 1][v] = up[k][up[k][v]];
    }
    auto lca = [&](int u, int v) {
        if (dep[u] < dep[v]) swap(u, v);
        int diff = dep[u] - dep[v];
        for (int k = 0; k < LOG; k++) {
            if (diff >> k & 1) u = up[k][u];
        }
        if (u == v) return u;
        for (int k = LOG - 1; k >= 0; k--) {
            if (up[k][u] != up[k][v]) u = up[k][u], v = up[k][v];
        }
        return up[0][u];
    };
    auto dist = [&](int u, int v) { return dep[u] + dep[v] - 2 * dep[lca(u, v)]; };

    // --8<-- [start:core]
    // vs：指定頂点。返り値：圧縮木の頂点（行きがけ順）と、各頂点の親の添字（根は -1）
    auto build = [&](vector<int> vs) {
        auto by_in = [&](int a, int b) { return in[a] < in[b]; };
        sort(vs.begin(), vs.end(), by_in);
        int k = vs.size();
        for (int i = 0; i + 1 < k; i++) vs.push_back(lca(vs[i], vs[i + 1]));
        sort(vs.begin(), vs.end(), by_in);
        vs.erase(unique(vs.begin(), vs.end()), vs.end());  // 頂点は 2k − 1 個以下

        vector<int> parent(vs.size(), -1);
        vector<int> stk;  // 根から今の頂点までの祖先の鎖（添字）
        for (int i = 0; i < (int)vs.size(); i++) {
            // 先頭が vs[i] の祖先でない（部分木の区間を抜けた）間は取り除く
            while (!stk.empty() && out[vs[stk.back()]] <= in[vs[i]]) stk.pop_back();
            if (!stk.empty()) parent[i] = stk.back();
            stk.push_back(i);
        }
        return pair{vs, parent};
    };
    // --8<-- [end:core]

    int q;
    cin >> q;
    while (q--) {
        int k;
        cin >> k;
        vector<int> vs(k);
        for (int& v : vs) {
            cin >> v;
            v--;
        }
        auto [tv, parent] = build(vs);
        // 圧縮木の辺 (p, v) は元の木の dep[v] − dep[p] 本の辺を縮めたもの
        long long edges = 0;
        for (int i = 0; i < (int)tv.size(); i++) {
            if (parent[i] != -1) edges += dep[tv[i]] - dep[tv[parent[i]]];
        }
        // DFS 順で隣り合う 2 点の距離（最後と最初も）の和の半分と一致する
        sort(vs.begin(), vs.end(), [&](int a, int b) { return in[a] < in[b]; });
        long long around = 0;
        for (int i = 0; i < k; i++) around += dist(vs[i], vs[(i + 1) % k]);
        assert(around % 2 == 0 && around / 2 == edges);
        // 根以外の頂点の親は 1 つで、親は行きがけ順で前にある
        assert(parent[0] == -1);
        for (int i = 1; i < (int)tv.size(); i++) assert(parent[i] != -1 && parent[i] < i);
        assert((int)tv.size() <= 2 * k - 1);
        cout << tv.size() << ' ' << edges << '\n';
    }
}
