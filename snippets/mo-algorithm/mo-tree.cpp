// 木上の Mo：パス u–v 上の頂点の値の種類数を、多数のクエリで答える
// 入りと出の両方を記録した長さ 2N の列で、パスを区間にする
// 入力：N Q、値 c_0 … c_{N-1}（0 ≤ c_v < N）、続く N-1 行は「p_i」（頂点 i の親。根は頂点 0）
//       続く Q 行は「u v」（0-indexed）
// 出力：各クエリの答え
// 起動時に、小さな乱数の木で素朴な数え方と答えを比べる（assert）
#include <bits/stdc++.h>
using namespace std;

template <class Add, class Remove, class Answer>
void mo(int n, const vector<pair<int, int>>& qs, Add add, Remove remove, Answer answer) {
    int q = qs.size();
    int B = max(1, (int)(n / sqrt(max(q, 1))));
    vector<int> ord(q);
    iota(ord.begin(), ord.end(), 0);
    sort(ord.begin(), ord.end(), [&](int i, int j) {
        int bi = qs[i].first / B, bj = qs[j].first / B;
        if (bi != bj) return bi < bj;
        return bi % 2 == 0 ? qs[i].second < qs[j].second : qs[i].second > qs[j].second;
    });
    int l = 0, r = 0;
    for (int k : ord) {
        auto [ql, qr] = qs[k];
        while (l > ql) add(--l);
        while (r < qr) add(r++);
        while (l < ql) remove(l++);
        while (r > qr) remove(--r);
        answer(k);
    }
}

vector<int> solve(int n, const vector<int>& c, const vector<int>& par,
                  const vector<pair<int, int>>& uv) {
    vector<vector<int>> g(n);
    for (int i = 1; i < n; i++) g[par[i]].push_back(i);
    vector<int> dep(n, 0);
    // 入りと出の両方を記録した列 seq（長さ 2N）と、各頂点の入りの位置 ST・出の位置 EN
    vector<int> seq, ST(n), EN(n);
    vector<int> st = {0};
    while (!st.empty()) {
        int v = st.back();
        st.pop_back();
        if (v >= 0) {
            ST[v] = seq.size();
            seq.push_back(v);
            st.push_back(~v);  // 出るときの印
            for (int ch : g[v]) {
                dep[ch] = dep[v] + 1;
                st.push_back(ch);
            }
        } else {
            v = ~v;
            EN[v] = seq.size();
            seq.push_back(v);
        }
    }
    // 確かめ用の素朴な LCA（1 回 O(N)）。本番は LCA のページの方法で O(log N) にする
    auto lca = [&](int u, int v) {
        while (dep[u] > dep[v]) u = par[u];
        while (dep[v] > dep[u]) v = par[v];
        while (u != v) u = par[u], v = par[v];
        return u;
    };

    // --8<-- [start:core]
    int q = uv.size();
    vector<pair<int, int>> qs(q);  // 列 seq の半開区間
    vector<int> extra(q, -1);      // 区間の外にある LCA（なければ -1）
    for (int k = 0; k < q; k++) {
        auto [u, v] = uv[k];
        if (ST[u] > ST[v]) swap(u, v);  // u を先に入る方にする
        int w = lca(u, v);
        if (w == u) {
            qs[k] = {ST[u], ST[v] + 1};  // u が v の祖先：閉区間 [ST(u), ST(v)]
        } else {
            qs[k] = {EN[u], ST[v] + 1};  // そうでなければ閉区間 [EN(u), ST(v)] と LCA
            extra[k] = w;
        }
    }

    vector<int> cnt(n, 0);           // cnt[x]：パス上にある値 x の頂点の数
    vector<char> inside(n, 0);       // 頂点が区間に奇数回現れているか
    int kinds = 0;                   // 値の種類数
    auto put = [&](int v) { if (cnt[c[v]]++ == 0) kinds++; };
    auto take = [&](int v) { if (--cnt[c[v]] == 0) kinds--; };
    // 列の 1 か所の出し入れは、その頂点の「奇数回か」を反転させる
    auto toggle = [&](int i) {
        int v = seq[i];
        if (inside[v]) take(v); else put(v);
        inside[v] ^= 1;
    };
    vector<int> ans(q);
    mo(2 * n, qs, toggle, toggle, [&](int k) {
        if (extra[k] >= 0) put(extra[k]);  // LCA を一時的に足して読み、すぐ戻す
        ans[k] = kinds;
        if (extra[k] >= 0) take(extra[k]);
    });
    // --8<-- [end:core]
    return ans;
}

int brute(int n, const vector<int>& c, const vector<int>& par, int u, int v) {
    vector<int> dep(n, 0);
    for (int i = 1; i < n; i++) dep[i] = dep[par[i]] + 1;  // 親の番号が小さい木だけで使う
    set<int> s;
    while (dep[u] > dep[v]) s.insert(c[u]), u = par[u];
    while (dep[v] > dep[u]) s.insert(c[v]), v = par[v];
    while (u != v) s.insert(c[u]), s.insert(c[v]), u = par[u], v = par[v];
    s.insert(c[u]);
    return s.size();
}

int main() {
    mt19937 rng(477);
    for (int t = 0; t < 200; t++) {
        int n = rng() % 20 + 1, q = rng() % 20 + 1;
        vector<int> c(n), par(n, -1);
        for (auto& x : c) x = rng() % min(n, 4);  // 値は 0 以上 N 未満
        for (int i = 1; i < n; i++) par[i] = rng() % i;
        vector<pair<int, int>> uv(q);
        for (auto& [u, v] : uv) u = rng() % n, v = rng() % n;
        auto ans = solve(n, c, par, uv);
        for (int k = 0; k < q; k++) assert(ans[k] == brute(n, c, par, uv[k].first, uv[k].second));
    }

    int n, q;
    cin >> n >> q;
    vector<int> c(n), par(n, -1);
    for (auto& x : c) cin >> x;
    for (int i = 1; i < n; i++) cin >> par[i];
    vector<pair<int, int>> uv(q);
    for (auto& [u, v] : uv) cin >> u >> v;
    for (int x : solve(n, c, par, uv)) cout << x << '\n';
}
