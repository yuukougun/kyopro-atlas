// 重み付き Union-Find（自作。差は long long の加算）
// 入力：N Q、続く Q 行は「0 u v w」（x_v − x_u = w を加える。矛盾なら ng、そうでなければ ok を出力）
//   か「1 u v」（x_v − x_u を出力。決まらなければ ?）。最後に乱数の試験も行う
#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:core]
struct WeightedUnionFind {
    vector<int> par;         // par[v]：親。根なら −(成分の大きさ)
    vector<long long> diff;  // diff[v] = x_v − x_{par[v]}（根では 0）
    WeightedUnionFind(int n) : par(n, -1), diff(n, 0) {}

    int find(int v) {
        if (par[v] < 0) return v;
        int r = find(par[v]);     // 先に親を根まで圧縮する（diff[親] が x_親 − x_根 になる）
        diff[v] += diff[par[v]];  // x_v − x_親 に x_親 − x_根 を足して x_v − x_根 にする
        par[v] = r;
        return r;
    }
    long long potential(int v) {  // x_v − x_{根}
        find(v);
        return diff[v];
    }
    bool same(int u, int v) { return find(u) == find(v); }
    long long get_diff(int u, int v) {  // x_v − x_u（same(u, v) のときだけ呼ぶ）
        return potential(v) - potential(u);
    }
    // x_v − x_u = w を加える。すでに同じ成分なら、矛盾しないかだけを返す
    bool merge(int u, int v, long long w) {
        int ru = find(u), rv = find(v);
        if (ru == rv) return get_diff(u, v) == w;
        w += diff[u] - diff[v];  // 根どうしの差 x_{rv} − x_{ru} に直す
        if (-par[ru] < -par[rv]) {  // 小さい方を大きい方の下につなぐ
            swap(ru, rv);
            w = -w;                 // 向きを入れ替えたので符号を反転する
        }
        par[ru] += par[rv];
        par[rv] = ru;
        diff[rv] = w;               // x_{rv} − x_{ru} = w
        return true;
    }
};
// --8<-- [end:core]

// 乱数の試験：値 x を先に決めて正しい情報と、ときどき誤った情報を与え、
// 辺のリストからの BFS で求めた差・矛盾の有無と比べる
void random_test() {
    mt19937 rng(12345);
    for (int iter = 0; iter < 300; iter++) {
        int n = rng() % 40 + 1;  // 高さ 3 以上の木が残る大きさまで広げる（圧縮の順序の誤りを検出する）
        vector<long long> x(n);
        for (auto& v : x) v = (long long)(rng() % 21) - 10;
        WeightedUnionFind uf(n);
        vector<vector<pair<int, long long>>> g(n);  // 採用した情報（x_to − x_from = w）
        for (int q = 0; q < 80; q++) {
            int u = rng() % n, v = rng() % n;
            long long w = x[v] - x[u];
            if (rng() % 4 == 0) w += (long long)(rng() % 3) - 1;  // ときどき誤らせる
            // BFS で u からの差を求める
            vector<long long> d(n, LLONG_MIN);
            d[u] = 0;
            queue<int> que;
            que.push(u);
            while (!que.empty()) {
                int a = que.front();
                que.pop();
                for (auto [b, c] : g[a])
                    if (d[b] == LLONG_MIN) d[b] = d[a] + c, que.push(b);
            }
            bool expected = (d[v] == LLONG_MIN) || (d[v] == w);
            assert(uf.same(u, v) == (d[v] != LLONG_MIN));
            if (uf.same(u, v)) assert(uf.get_diff(u, v) == d[v]);
            bool ok = uf.merge(u, v, w);
            assert(ok == expected);
            if (ok && d[v] == LLONG_MIN) {
                g[u].push_back({v, w});
                g[v].push_back({u, -w});
            }
        }
    }
}

int main() {
    int n, q;
    cin >> n >> q;
    WeightedUnionFind uf(n);
    for (int i = 0; i < q; i++) {
        int t, u, v;
        cin >> t >> u >> v;
        if (t == 0) {
            long long w;
            cin >> w;
            cout << (uf.merge(u, v, w) ? "ok" : "ng") << '\n';
        } else {
            if (uf.same(u, v)) cout << uf.get_diff(u, v) << '\n';
            else cout << "?" << '\n';
        }
    }
    random_test();
}
