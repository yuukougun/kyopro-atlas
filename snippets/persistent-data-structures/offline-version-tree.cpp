// 操作の版を木にしてオフラインで処理する：版の木を DFS し、入るときに操作を施し、出るときに取り消す
// 入力は persistent-segtree.cpp と同じ：N M Q、続く Q 行は「0 x y」「1 x p v」「2 x l r」
#include <bits/stdc++.h>
using namespace std;

struct BIT {
    int n;
    vector<long long> d;
    BIT(int n) : n(n), d(n + 1, 0) {}
    void add(int p, long long x) {
        for (p++; p <= n; p += p & -p) d[p] += x;
    }
    long long sum(int r) const {  // [0, r) の和
        long long s = 0;
        for (; r > 0; r -= r & -r) s += d[r];
        return s;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m, q;
    cin >> n >> m >> q;
    // --8<-- [start:build]
    // 版の木を作る。頂点 0 はすべて 0 の列。代入 1 回で子を 1 つ作り、コピーは頂点を指し替えるだけ
    vector<vector<int>> child(1);
    vector<int> pos{-1};                 // 頂点の版を作った代入の位置（根は -1）
    vector<long long> newval{0};         // 代入した値
    vector<vector<array<int, 3>>> ask(1);  // 頂点ごとの和の質問 (l, r, 質問の番号)
    vector<int> cur(n, 0);               // 数列 x の今の版の頂点
    int nq = 0;
    for (int i = 0; i < q; i++) {
        int type, x;
        cin >> type >> x;
        if (type == 0) {
            int y;
            cin >> y;
            cur[x] = cur[y];
        } else if (type == 1) {
            int p;
            long long v;
            cin >> p >> v;
            int u = (int)child.size();
            child.emplace_back();
            ask.emplace_back();
            pos.push_back(p);
            newval.push_back(v);
            child[cur[x]].push_back(u);
            cur[x] = u;
        } else {
            int l, r;
            cin >> l >> r;
            ask[cur[x]].push_back({l, r, nq++});
        }
    }
    // --8<-- [end:build]
    // --8<-- [start:dfs]
    // DFS で頂点に入るときに代入を施し、出るときに元の値へ戻す（非再帰。出るときは ~v を積む）
    BIT bit(m);
    vector<long long> a(m, 0), old(child.size(), 0), ans(nq);
    vector<int> st{0};
    while (!st.empty()) {
        int v = st.back();
        st.pop_back();
        if (v >= 0) {
            if (pos[v] >= 0) {  // 代入を施す（変更前の値を覚える）
                old[v] = a[pos[v]];
                bit.add(pos[v], newval[v] - old[v]);
                a[pos[v]] = newval[v];
            }
            for (auto [l, r, id] : ask[v]) ans[id] = bit.sum(r) - bit.sum(l);
            st.push_back(~v);
            for (int c : child[v]) st.push_back(c);
        } else {
            v = ~v;
            if (pos[v] >= 0) {  // 取り消す
                bit.add(pos[v], old[v] - a[pos[v]]);
                a[pos[v]] = old[v];
            }
        }
    }
    // --8<-- [end:dfs]
    for (long long x : ans) cout << x << '\n';
}
