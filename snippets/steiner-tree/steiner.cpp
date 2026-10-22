#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int u, v;
    long long w;
};

const long long INF = numeric_limits<long long>::max() / 4;

// 無向グラフ（重みは 0 以上）で、指定頂点 term をすべてつなぐ辺の集合の重みの最小と、その辺の番号を返す
pair<long long, vector<int>> steiner_tree(int n, const vector<Edge>& es, const vector<int>& term) {
    int k = term.size();
    vector<vector<tuple<int, long long, int>>> g(n);  // (行き先, 重み, 辺の番号)
    for (int i = 0; i < (int)es.size(); i++) {
        g[es[i].u].push_back({es[i].v, es[i].w, i});
        g[es[i].v].push_back({es[i].u, es[i].w, i});
    }
    // --8<-- [start:core]
    // dp[S][v]：指定頂点の集合 S と頂点 v をつなぐ辺の集合の重みの最小
    vector<vector<long long>> dp(1 << k, vector<long long>(n, INF));
    vector<vector<int>> by_mask(1 << k, vector<int>(n, 0));   // 合わせた片方の集合（0 なら使っていない）
    vector<vector<int>> by_edge(1 << k, vector<int>(n, -1));  // v に入ってきた辺の番号（-1 なら使っていない）
    for (int i = 0; i < k; i++) dp[1 << i][term[i]] = 0;
    for (int s = 1; s < (1 << k); s++) {
        // 部分集合を 2 つに分けて合わせる（s の最小の要素を含む側を t にして、同じ分け方を 2 回見ない）
        int low = s & -s;
        for (int t = (s - 1) & s; t > 0; t = (t - 1) & s) {
            if (!(t & low)) continue;
            for (int v = 0; v < n; v++) {
                if (dp[t][v] == INF || dp[s ^ t][v] == INF) continue;
                long long c = dp[t][v] + dp[s ^ t][v];
                if (c < dp[s][v]) {
                    dp[s][v] = c;
                    by_mask[s][v] = t;
                    by_edge[s][v] = -1;
                }
            }
        }
        // ダイクストラ法で v を動かす（すべての頂点の dp[s][v] を始点の距離にする）
        priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<>> pq;
        for (int v = 0; v < n; v++)
            if (dp[s][v] < INF) pq.push({dp[s][v], v});
        while (!pq.empty()) {
            auto [d, u] = pq.top();
            pq.pop();
            if (d > dp[s][u]) continue;
            for (auto [v, w, id] : g[u]) {
                if (d + w < dp[s][v]) {
                    dp[s][v] = d + w;
                    by_mask[s][v] = 0;
                    by_edge[s][v] = id;
                    pq.push({dp[s][v], v});
                }
            }
        }
    }
    int full = (1 << k) - 1;
    long long cost = dp[full][term[0]];
    // --8<-- [end:core]
    // --8<-- [start:restore]
    // 値がどこから来たかをたどって辺を集める（重み 0 の辺は 2 回出ることがあるので印で除く）
    vector<char> used(es.size(), 0);
    auto restore = [&](auto&& self, int s, int v) -> void {
        if (by_edge[s][v] >= 0) {
            int id = by_edge[s][v];
            used[id] = 1;
            self(self, s, es[id].u ^ es[id].v ^ v);  // 辺のもう一方の端点
        } else if (by_mask[s][v] > 0) {
            self(self, by_mask[s][v], v);
            self(self, s ^ by_mask[s][v], v);
        }
    };
    restore(restore, full, term[0]);
    // --8<-- [end:restore]
    vector<int> ids;
    for (int i = 0; i < (int)es.size(); i++)
        if (used[i]) ids.push_back(i);
    return {cost, ids};
}

// 辺の集合が指定頂点をすべてつなぐか
bool connects(int n, const vector<Edge>& es, const vector<int>& ids, const vector<int>& term) {
    vector<int> par(n);
    iota(par.begin(), par.end(), 0);
    auto root = [&](auto&& self, int x) -> int { return par[x] == x ? x : par[x] = self(self, par[x]); };
    for (int id : ids) par[root(root, es[id].u)] = root(root, es[id].v);
    for (int x : term)
        if (root(root, x) != root(root, term[0])) return false;
    return true;
}

// 素朴な方法：辺の部分集合をすべて試す
long long brute(int n, const vector<Edge>& es, const vector<int>& term) {
    int m = es.size();
    long long best = INF;
    for (int b = 0; b < (1 << m); b++) {
        vector<int> ids;
        long long c = 0;
        for (int i = 0; i < m; i++)
            if (b >> i & 1) ids.push_back(i), c += es[i].w;
        if (c < best && connects(n, es, ids, term)) best = c;
    }
    return best;
}

void check(int n, const vector<Edge>& es, const vector<int>& term, long long expected) {
    auto [cost, ids] = steiner_tree(n, es, term);
    assert(cost == expected);
    long long sum = 0;
    for (int id : ids) sum += es[id].w;
    assert(sum == cost);
    assert(connects(n, es, ids, term));
}

int main() {
    // 小さい乱数のグラフで、辺の部分集合をすべて試す方法と比べる
    mt19937 rng(12345);
    for (int iter = 0; iter < 300; iter++) {
        int n = rng() % 6 + 1;
        vector<Edge> es;
        for (int v = 1; v < n; v++) es.push_back({(int)(rng() % v), v, (long long)(rng() % 4)});  // 連結にする
        int extra = rng() % 5;
        for (int i = 0; i < extra && n >= 2; i++) es.push_back({(int)(rng() % n), (int)(rng() % n), (long long)(rng() % 4)});
        vector<int> perm(n);
        iota(perm.begin(), perm.end(), 0);
        shuffle(perm.begin(), perm.end(), rng);
        int k = rng() % n + 1;
        vector<int> term(perm.begin(), perm.begin() + k);
        check(n, es, term, brute(n, es, term));
    }

    int n, m, k;
    cin >> n >> m >> k;
    vector<Edge> es(m);
    for (auto& e : es) cin >> e.u >> e.v >> e.w;
    vector<int> term(k);
    for (auto& x : term) cin >> x;
    auto [cost, ids] = steiner_tree(n, es, term);
    if (m <= 16) check(n, es, term, brute(n, es, term));
    cout << cost << '\n';
}
