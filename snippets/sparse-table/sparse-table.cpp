#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:core]
// 冪等な演算 op（min・max・gcd・AND・OR）の Sparse Table。区間は半開 [l, r)
template <class T, T (*op)(T, T)>
struct SparseTable {
    vector<int> lg;          // lg[L] = floor(log2 L)
    vector<vector<T>> st;    // st[k][i] = [i, i + 2^k) の op の結果

    explicit SparseTable(const vector<T>& a) {
        int n = a.size();
        lg.assign(n + 1, 0);
        for (int L = 2; L <= n; L++) lg[L] = lg[L / 2] + 1;
        int K = (n >= 1 ? lg[n] + 1 : 1);
        st.assign(K, vector<T>());
        st[0] = a;
        for (int k = 1; k < K; k++) {
            int half = 1 << (k - 1);
            st[k].resize(n - (1 << k) + 1);  // 始点は i + 2^k <= n の範囲だけ
            for (int i = 0; i + (1 << k) <= n; i++) {
                st[k][i] = op(st[k - 1][i], st[k - 1][i + half]);
            }
        }
    }

    // l < r が前提（空の区間には答えを持たない）
    T prod(int l, int r) const {  // [l, r) の op の結果
        assert(0 <= l && l < r && r <= (int)st[0].size());
        int k = lg[r - l];
        return op(st[k][l], st[k][r - (1 << k)]);  // 重なってよい 2 区間
    }
};

long long op_min(long long x, long long y) { return min(x, y); }
long long op_gcd(long long x, long long y) { return gcd(x, y); }
// --8<-- [end:core]

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, q;
    cin >> n >> q;
    vector<long long> a(n);
    for (auto& x : a) cin >> x;
    SparseTable<long long, op_min> mn(a);
    SparseTable<long long, op_gcd> g(a);
    for (int i = 0; i < q; i++) {
        int l, r;
        cin >> l >> r;
        // 素朴な計算と比べる
        long long m = a[l], h = a[l];
        for (int j = l; j < r; j++) m = min(m, a[j]), h = gcd(h, a[j]);
        assert(mn.prod(l, r) == m && g.prod(l, r) == h);
        cout << mn.prod(l, r) << ' ' << g.prod(l, r) << '\n';
    }
}
