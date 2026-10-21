#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:core]
// gcd の Sparse Table。gcd(x, x) = x なので、重なる 2 区間を合わせてよい。区間は半開 [l, r)
struct gcd_table {
    vector<vector<long long>> t;  // t[k][i] = gcd(a[i], ..., a[i + 2^k - 1])

    gcd_table(const vector<long long>& a) {
        int n = a.size();
        t.assign(1, a);
        for (int k = 1; (1 << k) <= n; k++) {
            t.emplace_back(n - (1 << k) + 1);
            for (int i = 0; i + (1 << k) <= n; i++) {
                t[k][i] = gcd(t[k - 1][i], t[k - 1][i + (1 << (k - 1))]);
            }
        }
    }

    long long query(int l, int r) const {  // l == r（空の区間）なら単位元の 0
        if (l >= r) return 0;
        int k = bit_width((unsigned)(r - l)) - 1;
        return gcd(t[k][l], t[k][r - (1 << k)]);
    }
};

// 隣接差の列。差は負になりうるので絶対値にする（std::gcd は絶対値で扱うが、意図を明示する）
vector<long long> diffs(const vector<long long>& a) {
    vector<long long> d;
    for (int i = 0; i + 1 < (int)a.size(); i++) d.push_back(abs(a[i + 1] - a[i]));
    return d;
}

// 行 [h1, h2)・列 [w1, w2) の A_i + B_j の gcd
// = gcd(A_h1 + B_w1, 行の隣接差の gcd, 列の隣接差の gcd)
long long rect_gcd(const vector<long long>& a, const vector<long long>& b,
                   const gcd_table& da, const gcd_table& db,
                   int h1, int h2, int w1, int w2) {
    long long g = a[h1] + b[w1];
    g = gcd(g, da.query(h1, h2 - 1));  // 差 d_i = A_{i+1} − A_i（h1 ≤ i < h2 − 1）
    g = gcd(g, db.query(w1, w2 - 1));
    return g;
}
// --8<-- [end:core]

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, q;
    cin >> n >> q;
    vector<long long> a(n), b(n);
    for (auto& x : a) cin >> x;
    for (auto& x : b) cin >> x;
    gcd_table da(diffs(a)), db(diffs(b));
    for (int t = 0; t < q; t++) {
        int h1, h2, w1, w2;  // 0-indexed・半開区間
        cin >> h1 >> h2 >> w1 >> w2;
        long long ans = rect_gcd(a, b, da, db, h1, h2, w1, w2);
        long long brute = 0;  // 素朴にすべての成分の gcd を取って確かめる
        for (int i = h1; i < h2; i++) {
            for (int j = w1; j < w2; j++) brute = gcd(brute, a[i] + b[j]);
        }
        assert(ans == brute);
        cout << ans << '\n';
    }
}
