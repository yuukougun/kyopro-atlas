// 燃やす埋める：0/1 変数の項の和を最小カットで最小化する組み立て役。
// x[i] = 1（選ぶ）を s 側、x[i] = 0（選ばない）を t 側に対応させる。
// main は、小さいランダムな入力で 2^n 通りの全探索と答えが一致することを確かめる。
#include <bits/stdc++.h>
#include <atcoder/maxflow>
using namespace std;

// --8<-- [start:core]
struct ProjectSelection {
    static constexpr long long INF = 1LL << 50;  // 有限のコストの合計より大きく、足しても溢れない値
    int n;                                      // 頂点の数（補助の頂点を足すと増える）
    long long offset = 0;                       // 辺にできずに外へ出した定数
    vector<tuple<int, int, long long>> edges;   // (from, to, 容量)。s は -1、t は -2
    explicit ProjectSelection(int n) : n(n) {}

    int add_vertex() { return n++; }

    // x[i] = 0 ならコスト f0、x[i] = 1 ならコスト f1（負でもよい）
    void unary(int i, long long f0, long long f1) {
        offset += min(f0, f1);
        if (f1 > f0) edges.emplace_back(i, -2, f1 - f0);  // i → t：選ぶと切れる
        if (f0 > f1) edges.emplace_back(-1, i, f0 - f1);  // s → i：選ばないと切れる
    }
    // x[i] = 1 かつ x[j] = 0 ならコスト c（c ≥ 0）
    void penalty(int i, int j, long long c) {
        assert(c >= 0);
        if (c > 0) edges.emplace_back(i, j, c);
    }
    // x[i] = 1 なら x[j] = 1 でなければならない
    void require(int i, int j) { penalty(i, j, INF); }

    // 2 変数の一般の項：(x[i], x[j]) = (0,0), (0,1), (1,0), (1,1) のコストが a, b, c, d
    void binary(int i, int j, long long a, long long b, long long c, long long d) {
        assert(b + c >= a + d);  // 表せる条件（劣モジュラ）
        // a + (c - a) x_i + (d - c) x_j + (b + c - a - d)(1 - x_i) x_j と分ける
        offset += a;
        unary(i, 0, c - a);
        unary(j, 0, d - c);
        penalty(j, i, b + c - a - d);  // x[j] = 1 かつ x[i] = 0 のときだけ
    }
    // vs がすべて 1 なら利得 p（p ≥ 0）。補助の頂点 y = 1 を「利得を得る」とする
    void gain_all_one(const vector<int>& vs, long long p) {
        int y = add_vertex();
        offset -= p;
        edges.emplace_back(-1, y, p);       // 得ないとコスト p
        for (int v : vs) require(y, v);     // 得るなら全員が 1
    }
    // vs がすべて 0 なら利得 p（p ≥ 0）。補助の頂点 y = 0 を「利得を得る」とする
    void gain_all_zero(const vector<int>& vs, long long p) {
        int y = add_vertex();
        offset -= p;
        edges.emplace_back(y, -2, p);       // 得ないとコスト p
        for (int v : vs) require(v, y);     // 誰かが 1 なら得られない
    }

    // 最小のコストと、そのときの x（補助の頂点は除く）を返す
    pair<long long, vector<int>> solve(int num_vars) {
        int s = n, t = n + 1;
        atcoder::mf_graph<long long> g(n + 2);
        for (auto [u, v, cap] : edges) {
            g.add_edge(u == -1 ? s : u == -2 ? t : u, v == -1 ? s : v == -2 ? t : v, cap);
        }
        long long cut = g.flow(s, t);
        vector<bool> reach = g.min_cut(s);  // 残余グラフで s から届く頂点が s 側
        vector<int> x(num_vars);
        for (int i = 0; i < num_vars; i++) x[i] = reach[i] ? 1 : 0;
        return {cut + offset, x};
    }
};
// --8<-- [end:core]

// 全探索で確かめるための項
struct Term {
    int kind;  // 0: unary, 1: penalty, 2: require, 3: binary, 4: all one, 5: all zero
    vector<int> vs;
    array<long long, 4> c;
};

long long evaluate(const vector<Term>& terms, const vector<int>& x) {
    long long total = 0;
    for (const Term& t : terms) {
        if (t.kind == 0) total += x[t.vs[0]] ? t.c[1] : t.c[0];
        if (t.kind == 1 && x[t.vs[0]] == 1 && x[t.vs[1]] == 0) total += t.c[0];
        if (t.kind == 2 && x[t.vs[0]] == 1 && x[t.vs[1]] == 0) return LLONG_MAX;
        if (t.kind == 3) total += t.c[x[t.vs[0]] * 2 + x[t.vs[1]]];
        if (t.kind == 4 || t.kind == 5) {
            bool all = true;
            for (int v : t.vs) all = all && (x[v] == (t.kind == 4 ? 1 : 0));
            if (all) total -= t.c[0];
        }
    }
    return total;
}

int main() {
    unsigned seed;
    int iterations;
    cin >> seed >> iterations;
    mt19937 rng(seed);
    auto rnd = [&](int lo, int hi) { return (int)(rng() % (hi - lo + 1)) + lo; };
    for (int it = 0; it < iterations; it++) {
        int n = rnd(1, 7);
        int m = rnd(0, 8);
        ProjectSelection ps(n);
        vector<Term> terms;
        for (int k = 0; k < m; k++) {
            Term t;
            t.kind = rnd(0, 5);
            int i = rnd(0, n - 1), j = rnd(0, n - 1);
            if (t.kind != 0 && i == j) t.kind = 0;  // 2 変数の項は異なる変数で作る
            if (t.kind == 0) {
                t.vs = {i};
                t.c = {rnd(-9, 9), rnd(-9, 9), 0, 0};
                ps.unary(i, t.c[0], t.c[1]);
            } else if (t.kind == 1) {
                t.vs = {i, j};
                t.c = {rnd(0, 9), 0, 0, 0};
                ps.penalty(i, j, t.c[0]);
            } else if (t.kind == 2) {
                t.vs = {i, j};
                ps.require(i, j);
            } else if (t.kind == 3) {
                t.vs = {i, j};
                long long a = rnd(-9, 9), b = rnd(-9, 9), c = rnd(-9, 9), d = rnd(-9, 9);
                if (b + c < a + d) swap(a, b), swap(c, d);  // 入れ替えて b + c ≥ a + d にする
                t.c = {a, b, c, d};
                ps.binary(i, j, a, b, c, d);
            } else {
                int k2 = rnd(1, n);
                vector<int> vs(n);
                iota(vs.begin(), vs.end(), 0);
                shuffle(vs.begin(), vs.end(), rng);
                vs.resize(k2);
                t.vs = vs;
                t.c = {rnd(0, 9), 0, 0, 0};
                if (t.kind == 4) ps.gain_all_one(vs, t.c[0]);
                else ps.gain_all_zero(vs, t.c[0]);
            }
            terms.push_back(t);
        }
        long long best = LLONG_MAX;
        for (int mask = 0; mask < (1 << n); mask++) {
            vector<int> x(n);
            for (int i = 0; i < n; i++) x[i] = mask >> i & 1;
            best = min(best, evaluate(terms, x));
        }
        auto [cost, x] = ps.solve(n);
        assert(best != LLONG_MAX);  // x = 全部 0 は require を必ず満たす
        assert(cost == best);
        assert(evaluate(terms, x) == best);  // 復元した x も最適
    }
    cout << "ok" << '\n';
}
