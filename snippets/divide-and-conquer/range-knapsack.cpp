// 区間の品物だけを使う 0-1 ナップサックのクエリを、区間の中央で分ける分割統治でオフラインに答える
// 入力：N Q、各品物の w v、各クエリの l r c（0-indexed の半開区間 [l, r)、l < r、容量 c ≤ CMAX）
// 出力：各クエリの価値の最大
// 素朴に区間ごとに DP した値と比べて assert する
#include <bits/stdc++.h>
using namespace std;

const int CMAX = 500;

int n;

// --8<-- [start:core]
vector<int> w;
vector<long long> v;
struct Query { int l, r, c; };
vector<Query> qs;
vector<long long> ans;
vector<array<long long, CMAX + 1>> tab;  // tab[i][c]：重さの和 c 以下での価値の最大

// [lo, hi) に収まるクエリ ids に答える
void solve(int lo, int hi, const vector<int>& ids) {
    if (ids.empty()) return;
    if (hi - lo == 1) {  // 区間がちょうど品物 lo だけのクエリ
        for (int id : ids) ans[id] = (w[lo] <= qs[id].c) ? v[lo] : 0;
        return;
    }
    int m = (lo + hi) / 2;
    vector<int> left, right, cross;
    for (int id : ids) {
        if (qs[id].r <= m) left.push_back(id);
        else if (qs[id].l >= m) right.push_back(id);
        else cross.push_back(id);  // l < m < r：中央をまたぐ
    }
    if (!cross.empty()) {
        tab[m].fill(0);  // 空の区間 [m, m)
        for (int i = m - 1; i >= lo; i--) {  // tab[i]：品物 [i, m) の表（左の接尾辞）
            for (int c = 0; c <= CMAX; c++) {
                tab[i][c] = tab[i + 1][c];
                if (c >= w[i]) tab[i][c] = max(tab[i][c], tab[i + 1][c - w[i]] + v[i]);
            }
        }
        for (int j = m; j < hi; j++) {  // tab[j + 1]：品物 [m, j + 1) の表（右の接頭辞）
            for (int c = 0; c <= CMAX; c++) {
                tab[j + 1][c] = tab[j][c];
                if (c >= w[j]) tab[j + 1][c] = max(tab[j + 1][c], tab[j][c - w[j]] + v[j]);
            }
        }
        for (int id : cross) {  // 容量を左に x、右に c - x 配る
            auto [l, r, c] = qs[id];
            long long best = 0;
            for (int x = 0; x <= c; x++) best = max(best, tab[l][x] + tab[r][c - x]);
            ans[id] = best;
        }
    }
    solve(lo, m, left);
    solve(m, hi, right);
}
// --8<-- [end:core]

int main() {
    int q;
    cin >> n >> q;
    w.resize(n);
    v.resize(n);
    for (int i = 0; i < n; i++) cin >> w[i] >> v[i];
    qs.resize(q);
    for (auto& [l, r, c] : qs) cin >> l >> r >> c;
    ans.assign(q, 0);
    tab.assign(n + 1, {});
    vector<int> ids(q);
    iota(ids.begin(), ids.end(), 0);
    solve(0, n, ids);
    for (int id = 0; id < q; id++) {
        auto [l, r, c] = qs[id];
        vector<long long> dp(c + 1, 0);
        for (int i = l; i < r; i++) {
            for (int x = c; x >= w[i]; x--) dp[x] = max(dp[x], dp[x - w[i]] + v[i]);
        }
        assert(ans[id] == dp[c]);
        cout << ans[id] << '\n';
    }
}
