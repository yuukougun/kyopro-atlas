#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:core]
// 結合法則を満たす演算 op と単位元 e の Disjoint Sparse Table。区間は半開 [l, r)
template <class T, T (*op)(T, T), T (*e)()>
struct disjoint_sparse_table {
    int n;
    vector<T> a;
    vector<vector<T>> t;  // t[h][i]：段 h の塊で、左半分の i は [i, 中点) の積、右半分の i は [中点, i] の積

    disjoint_sparse_table(const vector<T>& v) : n(v.size()), a(v) {
        int H = 1;
        while ((1 << H) < n) H++;
        t.assign(H + 1, vector<T>(max(n, 1), e()));
        for (int h = 1; h <= H; h++) {
            int w = 1 << h;  // 塊の長さ。中点は塊の先頭 + w/2
            for (int s = 0; s < n; s += w) {
                int m = min(s + w / 2, n);
                if (m - 1 >= s) t[h][m - 1] = a[m - 1];  // 中点の左：右から左へ
                for (int i = m - 2; i >= s; i--) t[h][i] = op(a[i], t[h][i + 1]);
                if (m < n) t[h][m] = a[m];               // 中点の右：左から右へ
                for (int i = m + 1; i < min(s + w, n); i++) t[h][i] = op(t[h][i - 1], a[i]);
            }
        }
    }

    T query(int l, int r) const {  // l == r なら e()
        assert(0 <= l && l <= r && r <= n);
        if (l == r) return e();
        r--;  // 閉区間 [l, r] にする
        if (l == r) return a[l];
        int h = bit_width((unsigned)(l ^ r));  // l と r が別の半分に分かれる段
        return op(t[h][l], t[h][r]);
    }
};

long long op_add(long long x, long long y) { return x + y; }
long long e_add() { return 0; }
// --8<-- [end:core]

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, q;
    cin >> n >> q;
    vector<long long> a(n);
    for (auto& x : a) cin >> x;
    disjoint_sparse_table<long long, op_add, e_add> dst(a);
    for (int i = 0; i < q; i++) {
        int l, r;
        cin >> l >> r;
        long long s = 0;
        for (int j = l; j < r; j++) s += a[j];
        assert(dst.query(l, r) == s);
        cout << dst.query(l, r) << '\n';
    }
}
