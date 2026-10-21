// 重心木を作り、「頂点 v から距離 d 以内の頂点の数」のクエリに 1 回 O(log N) で答える。
// 入力：N、N-1 行の辺 a b（1-indexed）、Q、Q 行の v d（1-indexed、d ≥ 0）。
// 出力：1 行目に重心木の親（1-indexed、根は -1）、続けて各クエリの答え。
// main の最初で、小さな乱数の木について素朴な BFS の答えと照らし合わせ、重心木の深さも確かめる。
#include <bits/stdc++.h>
using namespace std;

int find_centroid(int r, const vector<vector<int>>& g, const vector<char>& removed,
                  vector<int>& sz, vector<int>& par) {
    vector<int> order = {r};
    par[r] = -1;
    for (int i = 0; i < (int)order.size(); i++) {
        int v = order[i];
        for (int to : g[v]) {
            if (to == par[v] || removed[to]) continue;
            par[to] = v;
            order.push_back(to);
        }
    }
    for (int i = (int)order.size() - 1; i >= 0; i--) {
        int v = order[i];
        sz[v] = 1;
        for (int to : g[v]) {
            if (to != par[v] && !removed[to]) sz[v] += sz[to];
        }
    }
    int total = order.size();
    int v = r;
    while (true) {
        int next = -1;
        for (int to : g[v]) {
            if (to != par[v] && !removed[to] && sz[to] * 2 > total) next = to;
        }
        if (next == -1) return v;
        v = next;
    }
}

struct CentroidTree {
    vector<int> cpar, level;           // 重心木の親（根は -1）と深さ
    vector<vector<int>> dist_to;       // dist_to[v][l]：v から、深さ l の祖先の重心までの距離
    vector<vector<int>> all, from_par; // 距離ごとの頂点数の累積（下で説明）
};

// --8<-- [start:build]
CentroidTree build(int n, const vector<vector<int>>& g) {
    CentroidTree t;
    t.cpar.assign(n, -1);
    t.level.assign(n, 0);
    t.dist_to.assign(n, {});
    t.all.assign(n, {});
    t.from_par.assign(n, {});
    vector<char> removed(n, 0);
    vector<int> sz(n), par(n);
    // all[c][d]      ：c の成分の頂点のうち、c からの距離が d 以下の数
    // from_par[c][d] ：c の成分の頂点のうち、重心木の親 cpar[c] からの距離が d 以下の数
    auto prefix = [](vector<int>& a) {
        for (int i = 1; i < (int)a.size(); i++) a[i] += a[i - 1];
    };

    vector<array<int, 3>> stk = {{0, -1, 0}};  // {成分の代表, 重心木の親, 深さ}
    while (!stk.empty()) {
        auto [r, p, lv] = stk.back();
        stk.pop_back();
        int c = find_centroid(r, g, removed, sz, par);
        t.cpar[c] = p;
        t.level[c] = lv;
        // c の成分を BFS し、各頂点に c までの距離を書き足す（深さ lv の祖先の分）
        vector<pair<int, int>> q = {{c, -1}};
        vector<int> d(1, 0);
        for (int i = 0; i < (int)q.size(); i++) {
            auto [v, pv] = q[i];
            t.dist_to[v].push_back(d[i]);
            for (int to : g[v]) {
                if (to == pv || removed[to]) continue;
                q.push_back({to, v});
                d.push_back(d[i] + 1);
            }
        }
        t.all[c].assign(d.back() + 1, 0);  // BFS なので d.back() が最大の距離
        for (int x : d) t.all[c][x]++;
        prefix(t.all[c]);
        if (p != -1) {  // 親の重心からの距離は、親を処理したときに書いた dist_to[v][lv - 1]
            for (auto [v, pv] : q) {
                int x = t.dist_to[v][lv - 1];
                if ((int)t.from_par[c].size() <= x) t.from_par[c].resize(x + 1, 0);
                t.from_par[c][x]++;
            }
            prefix(t.from_par[c]);
        }
        removed[c] = 1;
        for (int to : g[c]) {
            if (!removed[to]) stk.push_back({to, c, lv + 1});
        }
    }
    return t;
}
// --8<-- [end:build]

// --8<-- [start:query]
// 累積の配列 a で「距離が x 以下の数」を引く（x < 0 なら 0、範囲の外なら全部）
long long at_most(const vector<int>& a, int x) {
    if (x < 0 || a.empty()) return 0;
    return a[min(x, (int)a.size() - 1)];
}

// v から距離 d 以内の頂点の数。v から重心木の根へ上り、各祖先 c を通る頂点を数える
long long count_within(const CentroidTree& t, int v, int d) {
    long long res = 0;
    for (int c = v, prev = -1; c != -1; prev = c, c = t.cpar[c]) {
        int rest = d - t.dist_to[v][t.level[c]];  // c を経由して残りの距離
        res += at_most(t.all[c], rest);
        if (prev != -1) res -= at_most(t.from_par[prev], rest);  // v と同じ側の成分は下で数えた
    }
    return res;
}
// --8<-- [end:query]

int main() {
    mt19937 rng(2026);
    for (int iter = 0; iter < 400; iter++) {
        int n = rng() % 16 + 1;
        vector<vector<int>> g(n);
        for (int v = 1; v < n; v++) {
            int p = (iter % 3 == 0) ? v - 1 : (int)(rng() % v);
            g[v].push_back(p);
            g[p].push_back(v);
        }
        CentroidTree t = build(n, g);
        int lg = 0;
        while ((2 << lg) <= n) lg++;  // lg = floor(log2 n)
        for (int v = 0; v < n; v++) assert(t.level[v] <= lg);
        for (int s = 0; s < n; s++) {
            vector<int> dist(n, -1);
            queue<int> q;
            dist[s] = 0;
            q.push(s);
            while (!q.empty()) {
                int v = q.front();
                q.pop();
                for (int to : g[v]) {
                    if (dist[to] == -1) {
                        dist[to] = dist[v] + 1;
                        q.push(to);
                    }
                }
            }
            for (int d = 0; d <= n; d++) {
                long long expect = 0;
                for (int u = 0; u < n; u++) expect += (dist[u] <= d);
                assert(count_within(t, s, d) == expect);
            }
        }
    }

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
    CentroidTree t = build(n, g);
    for (int v = 0; v < n; v++) {
        cout << (t.cpar[v] == -1 ? -1 : t.cpar[v] + 1) << (v + 1 < n ? ' ' : '\n');
    }
    int q;
    cin >> q;
    while (q--) {
        int v, d;
        cin >> v >> d;
        cout << count_within(t, v - 1, d) << '\n';
    }
}
