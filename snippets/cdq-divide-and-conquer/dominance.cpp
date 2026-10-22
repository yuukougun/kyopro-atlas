#include <bits/stdc++.h>
using namespace std;

// 各点 i について、a_j <= a_i かつ b_j <= b_i かつ c_j <= c_i を満たす j（j != i）の個数を求める
vector<long long> count_dominated(const vector<array<int, 3>>& pts) {
    int n = pts.size();
    // 同じ点をまとめる（重みつきの点にする）
    vector<array<int, 3>> sorted_pts = pts;
    sort(sorted_pts.begin(), sorted_pts.end());
    vector<array<int, 3>> u;   // 異なる点を (a, b, c) の辞書順に
    vector<long long> w;       // その点の個数
    for (const auto& p : sorted_pts) {
        if (u.empty() || u.back() != p) {
            u.push_back(p);
            w.push_back(0);
        }
        w.back()++;
    }
    int m = u.size();
    // c を座標圧縮して BIT の添字にする
    vector<int> cs;
    for (const auto& p : u) cs.push_back(p[2]);
    sort(cs.begin(), cs.end());
    cs.erase(unique(cs.begin(), cs.end()), cs.end());
    vector<int> ci(m);
    for (int i = 0; i < m; i++) ci[i] = lower_bound(cs.begin(), cs.end(), u[i][2]) - cs.begin();
    vector<long long> bit(cs.size() + 1, 0);
    auto add = [&](int i, long long x) {
        for (i++; i < (int)bit.size(); i += i & -i) bit[i] += x;
    };
    auto sum = [&](int i) {  // [0, i] の和
        long long s = 0;
        for (i++; i > 0; i -= i & -i) s += bit[i];
        return s;
    };
    vector<long long> res(m, 0);  // 自分以外の、異なる点からの寄与
    // --8<-- [start:core]
    // u は (a, b, c) の辞書順。左半分の点は a が右半分以下なので、b と c だけを比べればよい
    auto cdq = [&](auto&& self, int l, int r) -> void {
        if (r - l <= 1) return;
        int mid = (l + r) / 2;
        self(self, l, mid);
        self(self, mid, r);
        // 左の点（追加）と右の点（質問）を b の順に並べる。同じ b なら追加を先に
        vector<pair<int, int>> ev;  // (b, 添字)
        for (int i = l; i < r; i++) ev.push_back({u[i][1], i});
        sort(ev.begin(), ev.end(), [&](const pair<int, int>& x, const pair<int, int>& y) {
            if (x.first != y.first) return x.first < y.first;
            return (x.second < mid) > (y.second < mid);
        });
        for (auto [b, i] : ev) {
            if (i < mid) add(ci[i], w[i]);        // 左：c の位置に個数を足す
            else res[i] += sum(ci[i]);            // 右：c 以下の個数を数える
        }
        for (int i = l; i < mid; i++) add(ci[i], -w[i]);  // BIT を空に戻す
    };
    cdq(cdq, 0, m);
    // --8<-- [end:core]
    vector<long long> ans(n);
    for (int i = 0; i < n; i++) {
        int k = lower_bound(u.begin(), u.end(), pts[i]) - u.begin();
        ans[i] = res[k] + w[k] - 1;  // 同じ点の自分以外も数える
    }
    return ans;
}

vector<long long> brute(const vector<array<int, 3>>& pts) {
    int n = pts.size();
    vector<long long> ans(n, 0);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (i != j && pts[j][0] <= pts[i][0] && pts[j][1] <= pts[i][1] && pts[j][2] <= pts[i][2]) ans[i]++;
    return ans;
}

int main() {
    // 小さい乱数の入力で愚直解と照らし合わせる（同じ値・同じ点が多く出る範囲）
    mt19937 rng(12345);
    for (int t = 0; t < 300; t++) {
        int n = rng() % 30;
        vector<array<int, 3>> p(n);
        for (auto& q : p) q = {(int)(rng() % 4), (int)(rng() % 4), (int)(rng() % 4)};
        assert(count_dominated(p) == brute(p));
    }
    int n;
    cin >> n;
    vector<array<int, 3>> p(n);
    for (auto& q : p) cin >> q[0] >> q[1] >> q[2];
    auto ans = count_dominated(p);
    for (int i = 0; i < n; i++) cout << ans[i] << (i + 1 < n ? ' ' : '\n');
    if (n == 0) cout << '\n';
}
