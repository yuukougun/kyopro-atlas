#include <bits/stdc++.h>
#include <atcoder/dsu>
using namespace std;

// 根 0 の根付き木で、親が子より先に来る順のうち
// X = Σ（前の頂点の d）×（後ろの頂点の c）を最小にする順と X を返す
// --8<-- [start:core]
pair<long long, vector<int>> min_order(const vector<int>& par, vector<long long> c, vector<long long> d) {
    int n = par.size();
    // 塊は先頭の頂点の番号で呼ぶ。c[v]・d[v] は塊 v の合計
    // a を b より先に併合する：(0, 0) を最優先し、ほかは c/d の大きい順（掛け算で比べる）
    auto comp = [&](int a, int b) {
        bool za = (c[a] == 0 && d[a] == 0), zb = (c[b] == 0 && d[b] == 0);
        if (za != zb) return za;
        __int128 l = (__int128)c[a] * d[b], r = (__int128)c[b] * d[a];
        if (l != r) return l > r;
        return a < b;
    };
    set<int, decltype(comp)> s(comp);
    for (int v = 1; v < n; v++) s.insert(v);
    atcoder::dsu uf(n);
    vector<int> top(n), nxt(n, -1), tail(n);
    for (int v = 0; v < n; v++) top[v] = tail[v] = v;
    long long x = 0;
    while (!s.empty()) {
        int v = *s.begin();
        s.erase(s.begin());
        int p = top[uf.leader(par[v])];  // 親の頂点を含む塊
        if (p != 0) s.erase(p);           // c[p]・d[p] を変える前に外す
        x += d[p] * c[v];                 // 塊 p の後ろに塊 v をつなぐ費用
        c[p] += c[v];
        d[p] += d[v];
        nxt[tail[p]] = v;                 // 頂点の並びをつなぐ
        tail[p] = tail[v];
        top[uf.merge(p, v)] = p;
        if (p != 0) s.insert(p);
    }
    vector<int> order;
    for (int v = 0; v != -1; v = nxt[v]) order.push_back(v);
    return {x, order};
}
// --8<-- [end:core]

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<int> par(n, -1);
    for (int i = 1; i < n; i++) cin >> par[i];
    vector<long long> c(n), d(n);
    for (auto& v : c) cin >> v;
    for (auto& v : d) cin >> v;
    auto [x, order] = min_order(par, c, d);
    // 親が子より先に来ていることと、X の値を確かめる
    assert((int)order.size() == n);
    vector<int> pos(n);
    for (int i = 0; i < n; i++) pos[order[i]] = i;
    for (int v = 1; v < n; v++) assert(pos[par[v]] < pos[v]);
    long long check = 0, sum_d = 0;
    for (int v : order) {
        check += sum_d * c[v];
        sum_d += d[v];
    }
    assert(check == x);
    cout << x << '\n';
    for (int i = 0; i < n; i++) cout << order[i] << (i + 1 < n ? ' ' : '\n');
}
