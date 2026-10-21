#include <bits/stdc++.h>
using namespace std;

// クエリ (x, y)：頂点 x の今の色を返し、x とその隣接頂点すべてを色 y にする。
// 色の初期値は 0。頂点は 0-indexed。
struct NeighborPaint {
    int n;
    vector<vector<int>> g;
    // --8<-- [start:core]
    int B;                            // 次数が B 以上なら重い頂点
    vector<char> heavy;
    vector<vector<int>> hn;           // hn[v]：v に隣接する重い頂点
    vector<int> pushed;               // 軽い頂点が配った塗りの時刻（最新）
    vector<int> own;                  // 重い頂点が自分で持つ塗りの時刻（最新）
    vector<int> col;                  // col[t]：t 番目のクエリの色
    NeighborPaint(int n_, const vector<vector<int>>& g_) : n(n_), g(g_) {
        long long m2 = 0;             // 次数の和 = 2M
        for (int v = 0; v < n; v++) m2 += g[v].size();
        B = max(1, (int)sqrt((double)m2));   // B ≒ √(2M)
        heavy.assign(n, 0);
        for (int v = 0; v < n; v++) heavy[v] = (int)g[v].size() >= B;
        hn.assign(n, {});
        for (int v = 0; v < n; v++)
            for (int u : g[v])
                if (heavy[u]) hn[v].push_back(u);   // 合わせて 2M 個以下
        pushed.assign(n, -1);
        own.assign(n, -1);
    }
    int query(int x, int y) {
        int t = col.size();
        col.push_back(y);
        // 取りに行く：自分に配られた時刻と、隣の重い頂点の時刻の最大
        int last = max(pushed[x], own[x]);
        for (int h : hn[x]) last = max(last, own[h]);    // 2M/B 個以下
        int ans = (last == -1 ? 0 : col[last]);
        // 配る：軽い頂点だけが隣接頂点すべてに書く
        if (heavy[x]) {
            own[x] = t;                                  // O(1)
        } else {
            pushed[x] = t;
            for (int u : g[x]) pushed[u] = t;            // B 個未満
        }
        return ans;
    }
    // --8<-- [end:core]
};

// 素朴な方法：毎回 x と隣をすべて塗る
vector<int> naive(int n, const vector<vector<int>>& g, const vector<pair<int, int>>& qs) {
    vector<int> c(n, 0), res;
    for (auto [x, y] : qs) {
        res.push_back(c[x]);
        c[x] = y;
        for (int u : g[x]) c[u] = y;
    }
    return res;
}

void self_test() {
    mt19937 rng(12345);
    for (int iter = 0; iter < 300; iter++) {
        int n = rng() % 12 + 1;
        vector<vector<int>> g(n);
        set<pair<int, int>> used;
        bool star = iter % 3 == 0;   // 星形（中心 0）を混ぜる
        int m = star ? n - 1 : (int)(rng() % (n * (n - 1) / 2 + 1));
        for (int i = 0; i < m; i++) {
            int a, b;
            if (star) { a = 0; b = i + 1; }
            else { a = rng() % n; b = rng() % n; }
            if (a == b || used.count({min(a, b), max(a, b)})) continue;
            used.insert({min(a, b), max(a, b)});
            g[a].push_back(b);
            g[b].push_back(a);
        }
        vector<pair<int, int>> qs;
        for (int i = 0; i < 30; i++) qs.push_back({(int)(rng() % n), (int)(rng() % 5) + 1});
        NeighborPaint np(n, g);
        vector<int> got;
        for (auto [x, y] : qs) got.push_back(np.query(x, y));
        assert(got == naive(n, g, qs));
    }
}

int main() {
    self_test();
    int n, m;
    cin >> n >> m;
    vector<vector<int>> g(n);
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    int q;
    cin >> q;
    NeighborPaint np(n, g);
    for (int i = 0; i < q; i++) {
        int x, y;
        cin >> x >> y;
        x--;
        cout << np.query(x, y) << '\n';
    }
}
