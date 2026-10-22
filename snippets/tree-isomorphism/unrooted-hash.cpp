// 根のない 2 つの木が同型かを、中心を根にした木のハッシュで判定する。
// 入力：N、木 A の辺 N-1 本、木 B の辺 N-1 本（頂点は 0-indexed）。
// 出力：同型なら Yes、そうでなければ No。
#include <bits/stdc++.h>
using namespace std;

const unsigned long long MOD = (1ULL << 61) - 1;

unsigned long long mul_mod(unsigned long long a, unsigned long long b) {
    unsigned __int128 t = (unsigned __int128)a * b;
    unsigned long long r = (unsigned long long)(t >> 61) + (unsigned long long)(t & MOD);
    return r >= MOD ? r - MOD : r;
}

// 中心：葉を外側から 1 層ずつはがし、最後に残った 1 個か 2 個の頂点
vector<int> centers(const vector<vector<int>>& g) {
    int n = g.size();
    if (n == 1) return {0};
    vector<int> deg(n), layer;
    for (int v = 0; v < n; v++) {
        deg[v] = g[v].size();
        if (deg[v] == 1) layer.push_back(v);
    }
    int remain = n;
    while (remain > 2) {
        remain -= layer.size();
        vector<int> next;
        for (int v : layer)
            for (int u : g[v])
                if (--deg[u] == 1) next.push_back(u);
        layer = next;
    }
    return layer;
}

// --8<-- [start:core]
// 高さ h の頂点 v のハッシュ：H(v) = (x[h] + H(c_1)) (x[h] + H(c_2)) ... mod 2^61 - 1
// 葉は空の積で H = 1。x は高さごとの乱数（実行のたびに選び直す）
unsigned long long rooted_hash(const vector<vector<int>>& g, int root,
                               const vector<unsigned long long>& x) {
    int n = g.size();
    vector<int> order, par(n, -1), height(n, 0);
    vector<unsigned long long> h(n, 1);
    order.push_back(root);
    for (int i = 0; i < (int)order.size(); i++) {  // BFS の順（親が子より先）
        int v = order[i];
        for (int u : g[v])
            if (u != par[v]) {
                par[u] = v;
                order.push_back(u);
            }
    }
    for (int i = n - 1; i >= 0; i--) {  // 逆順に見れば子が先に終わる
        int v = order[i];
        for (int u : g[v])
            if (u != par[v]) height[v] = max(height[v], height[u] + 1);
        for (int u : g[v])
            if (u != par[v]) h[v] = mul_mod(h[v], (x[height[v]] + h[u]) % MOD);
    }
    return h[root];
}

// 根のない木の名前：中心が 2 個なら両方を根にしたハッシュの組（小さい順）
pair<unsigned long long, unsigned long long> unrooted_hash(
    const vector<vector<int>>& g, const vector<unsigned long long>& x) {
    vector<unsigned long long> hs;
    for (int c : centers(g)) hs.push_back(rooted_hash(g, c, x));
    sort(hs.begin(), hs.end());
    if (hs.size() == 1) return {hs[0], hs[0]};
    return {hs[0], hs[1]};
}
// --8<-- [end:core]

int main() {
    int n;
    cin >> n;
    vector<vector<int>> a(n), b(n);
    for (auto* g : {&a, &b}) {
        for (int i = 0; i < n - 1; i++) {
            int u, v;
            cin >> u >> v;
            (*g)[u].push_back(v);
            (*g)[v].push_back(u);
        }
    }
    mt19937_64 rng(random_device{}());
    vector<unsigned long long> x(n + 1);
    for (auto& e : x) e = rng() % MOD;
    // 中心の個数が違えば同型ではない（組の作り方が違っても答えは No になる）
    bool same = centers(a).size() == centers(b).size() && unrooted_hash(a, x) == unrooted_hash(b, x);
    cout << (same ? "Yes" : "No") << '\n';
}
