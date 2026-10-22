// Static Top Tree：f(v) = A_v（葉）、A_v + Π f(子)（葉でない）の根の値を、A_v の 1 点変更のたびに求める
// 入力：N Q、親 p_1..p_{N-1}（0-indexed、p_i < i）、A_0..A_{N-1}、クエリ「v x」（A_v を x にする）
#include <bits/stdc++.h>
#include <atcoder/modint>
using namespace std;
using mint = atcoder::modint998244353;

enum Type { Vertex, AddVertex, AddEdge, Compress, Rake };

struct StaticTopTree {
    int n;
    vector<vector<int>> ch;           // 子の並び。先頭が重い子
    vector<int> P, L, R;              // 節点の親・左の子・右の子（-1 はなし）
    vector<Type> T;
    int root;                         // 節点の根
    StaticTopTree(vector<vector<int>> children) : n(children.size()), ch(children) {
        vector<int> sz(n, 1);
        for (int v = n - 1; v >= 0; v--) {          // 親の番号が小さいので逆順で部分木サイズが求まる
            for (int c : ch[v]) sz[v] += sz[c];
            for (int i = 1; i < (int)ch[v].size(); i++)
                if (sz[ch[v][i]] > sz[ch[v][0]]) swap(ch[v][0], ch[v][i]);
        }
        P.assign(n, -1); L.assign(n, -1); R.assign(n, -1); T.assign(n, Vertex);
        root = compress(0).first;
    }
    // 節点 k（-1 なら新しく作る）を (l, r, t) にする。頂点 v の節点は番号 v を使い回す
    int add(int k, int l, int r, Type t) {
        if (k == -1) {
            k = P.size();
            P.push_back(-1); L.push_back(-1); R.push_back(-1); T.push_back(t);
        }
        L[k] = l; R[k] = r; T[k] = t;
        if (l != -1) P[l] = k;
        if (r != -1) P[r] = k;
        return k;
    }
    // --8<-- [start:build]
    // (節点, 含む頂点数) の列を、頂点数がおよそ半分ずつになる位置で 2 つに分けて併せる
    pair<int, int> build_balanced(const vector<pair<int, int>>& a, Type t) {
        if (a.size() == 1) return a[0];
        int u = 0;
        for (auto [i, s] : a) u += s;
        vector<pair<int, int>> b, c;
        for (auto [i, s] : a) {
            (u > s ? b : c).emplace_back(i, s);
            u -= 2 * s;
        }
        auto [i, si] = build_balanced(b, t);
        auto [j, sj] = build_balanced(c, t);
        return {add(-1, i, j, t), si + sj};
    }
    pair<int, int> compress(int v) {                 // v から下へ重いパスを 1 本たどって圧縮する
        vector<pair<int, int>> path{add_vertex(v)};
        while (!ch[v].empty()) path.push_back(add_vertex(v = ch[v][0]));
        return build_balanced(path, Compress);       // 列の左が浅い側
    }
    pair<int, int> rake(int v) {                     // v の軽い子の部分木をまとめる
        vector<pair<int, int>> light;
        for (int i = 1; i < (int)ch[v].size(); i++) light.push_back(add_edge(ch[v][i]));
        if (light.empty()) return {-1, 0};
        return build_balanced(light, Rake);
    }
    pair<int, int> add_edge(int c) {
        auto [j, sj] = compress(c);
        return {add(-1, j, -1, AddEdge), sj};
    }
    pair<int, int> add_vertex(int v) {
        auto [j, sj] = rake(v);
        return {add(v, j, -1, j == -1 ? Vertex : AddVertex), sj + 1};
    }
    // --8<-- [end:build]
};

// --8<-- [start:dp]
// 節点の値。Path：f(上端) = a·x + b（x は下端の重い子の f）。Point：軽い子の f の積を a に持つ
struct Value { mint a, b; };

struct HashDP {
    const StaticTopTree& t;
    vector<mint> A;
    vector<Value> val;
    HashDP(const StaticTopTree& t, vector<mint> A) : t(t), A(A), val(t.P.size()) {
        dfs(t.root);
    }
    void calc(int k) {
        int l = t.L[k], r = t.R[k];
        switch (t.T[k]) {
            case Vertex:     // 軽い子がない頂点 k。重い子がなければ葉で定数
                val[k] = {t.ch[k].empty() ? mint(0) : mint(1), A[k]}; break;
            case AddVertex:  // f(k) = A_k + (軽い子の積)·x
                val[k] = {val[l].a, A[k]}; break;
            case AddEdge:    // 重いパスの末端は葉なので、圧縮した値は定数 b
                val[k] = {val[l].b, 0}; break;
            case Compress:   // 浅い側 l の x に深い側 r を代入する
                val[k] = {val[l].a * val[r].a, val[l].a * val[r].b + val[l].b}; break;
            case Rake:       // 軽い子の積どうしを掛ける（割り算は要らない）
                val[k] = {val[l].a * val[r].a, 0}; break;
        }
    }
    void dfs(int k) {
        if (t.L[k] != -1) dfs(t.L[k]);
        if (t.R[k] != -1) dfs(t.R[k]);
        calc(k);
    }
    mint update(int v, mint x) {                         // 根への道の O(log N) 個の節点だけ計算し直す
        A[v] = x;
        for (int k = v; k != -1; k = t.P[k]) calc(k);
        return val[t.root].b;
    }
};
// --8<-- [end:dp]

// 確かめ用：毎回すべて計算し直す
mint brute(const vector<vector<int>>& ch, const vector<mint>& A) {
    int n = ch.size();
    vector<mint> f(n);
    for (int v = n - 1; v >= 0; v--) {
        if (ch[v].empty()) { f[v] = A[v]; continue; }
        mint p = 1;
        for (int c : ch[v]) p *= f[c];
        f[v] = A[v] + p;
    }
    return f[0];
}

int height(const StaticTopTree& t, int k) {
    if (k == -1) return 0;
    return 1 + max(height(t, t.L[k]), height(t, t.R[k]));
}

void self_test() {
    mt19937 rng(12345);
    for (int iter = 0; iter < 300; iter++) {
        int n = rng() % 30 + 1;
        vector<vector<int>> ch(n);
        for (int i = 1; i < n; i++) ch[rng() % i].push_back(i);
        vector<mint> A(n);
        for (auto& x : A) x = rng() % 4;           // 0 を多く混ぜる
        StaticTopTree t(ch);
        HashDP dp(t, A);
        assert(dp.val[t.root].b == brute(ch, A));
        for (int q = 0; q < 30; q++) {
            int v = rng() % n;
            A[v] = rng() % 4;
            assert(dp.update(v, A[v]) == brute(ch, A));
        }
    }
    // 形の両極端（パスと星）でも高さが O(log N) に収まる
    for (int shape = 0; shape < 2; shape++) {
        int n = 1 << 17;
        vector<vector<int>> ch(n);
        for (int i = 1; i < n; i++) ch[shape == 0 ? i - 1 : 0].push_back(i);
        StaticTopTree t(ch);
        assert(height(t, t.root) <= 4 * 17 + 4);
    }
}

int main() {
    self_test();
    int n, q;
    cin >> n >> q;
    vector<vector<int>> ch(n);
    for (int i = 1; i < n; i++) {
        int p;
        cin >> p;
        ch[p].push_back(i);
    }
    vector<mint> A(n);
    for (auto& x : A) {
        int y;
        cin >> y;
        x = y;
    }
    StaticTopTree t(ch);
    HashDP dp(t, A);
    while (q--) {
        int v, x;
        cin >> v >> x;
        cout << dp.update(v, x).val() << '\n';
    }
}
