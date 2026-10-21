// 操作列の累積：k 回目までの合成を 3×3 行列で前計算し、クエリに O(1) で答える
#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:core]
using Mat = array<array<long long, 3>, 3>;

Mat mul(const Mat& a, const Mat& b) {  // a * b（b を先に施し、a を後に施す）
    Mat c{};
    for (int i = 0; i < 3; i++)
        for (int k = 0; k < 3; k++)
            for (int j = 0; j < 3; j++) c[i][j] += a[i][k] * b[k][j];
    return c;
}

// 操作を 3×3 行列にする。t = 1：時計回りに 90 度、2：反時計回りに 90 度、
// 3：直線 x = p で反転、4：直線 y = p で反転（どれも原点まわり・整数のまま）
Mat op_matrix(int t, long long p) {
    if (t == 1) return Mat{{{0, 1, 0}, {-1, 0, 0}, {0, 0, 1}}};
    if (t == 2) return Mat{{{0, -1, 0}, {1, 0, 0}, {0, 0, 1}}};
    if (t == 3) return Mat{{{-1, 0, 2 * p}, {0, 1, 0}, {0, 0, 1}}};
    return Mat{{{1, 0, 0}, {0, -1, 2 * p}, {0, 0, 1}}};
}

// pre[k] = k 回目までの合成（pre[0] は単位行列）。後の操作を左から掛ける
vector<Mat> build_prefix(const vector<pair<int, long long>>& ops) {
    int m = ops.size();
    vector<Mat> pre(m + 1);
    pre[0] = Mat{{{1, 0, 0}, {0, 1, 0}, {0, 0, 1}}};
    for (int k = 0; k < m; k++) pre[k + 1] = mul(op_matrix(ops[k].first, ops[k].second), pre[k]);
    return pre;
}

pair<long long, long long> apply(const Mat& a, long long x, long long y) {  // a * (x, y, 1)^T
    return {a[0][0] * x + a[0][1] * y + a[0][2], a[1][0] * x + a[1][1] * y + a[1][2]};
}
// --8<-- [end:core]

int main() {
    // 入力：N、点 N 個、M、操作 M 個（t か t p）、Q、クエリ Q 個（k i：k 回目の後の点 i、0-indexed）
    int n;
    cin >> n;
    vector<long long> x(n), y(n);
    for (int i = 0; i < n; i++) cin >> x[i] >> y[i];
    int m;
    cin >> m;
    vector<pair<int, long long>> ops(m);
    for (auto& [t, p] : ops) {
        cin >> t;
        p = 0;
        if (t >= 3) cin >> p;
    }
    vector<Mat> pre = build_prefix(ops);

    // 確かめ：1 つずつ素朴に動かした結果と一致する
    for (int i = 0; i < n; i++) {
        long long cx = x[i], cy = y[i];
        for (int k = 0; k <= m; k++) {
            assert(apply(pre[k], x[i], y[i]) == make_pair(cx, cy));
            if (k == m) break;
            auto [t, p] = ops[k];
            if (t == 1) tie(cx, cy) = make_pair(cy, -cx);
            else if (t == 2) tie(cx, cy) = make_pair(-cy, cx);
            else if (t == 3) cx = 2 * p - cx;
            else cy = 2 * p - cy;
        }
    }

    int q;
    cin >> q;
    while (q--) {
        int k, i;
        cin >> k >> i;
        auto [ax, ay] = apply(pre[k], x[i], y[i]);
        cout << ax << ' ' << ay << '\n';
    }
}
