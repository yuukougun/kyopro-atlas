#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:core]
// a は凸（隣との差が広義単調増加）、b は任意。c[k] = min_{i + j = k} (a[i] + b[j])
vector<long long> min_plus_convex_arbitrary(const vector<long long>& a, const vector<long long>& b) {
    int n = a.size(), m = b.size();
    vector<long long> c(n + m - 1);
    // 行 k・列 j の値は a[k - j] + b[j]。行 k で使える列は [max(0, k - n + 1), min(m - 1, k)]
    // 行 [top, bottom) を、最小の位置が閉区間 [lo, hi] にあると分かった状態で解く
    auto rec = [&](auto&& self, int top, int bottom, int lo, int hi) -> void {
        if (top >= bottom) return;
        int k = (top + bottom) / 2;
        int from = max(lo, k - n + 1), to = min(hi, k);
        int arg = from;
        for (int j = from + 1; j <= to; j++) {
            if (a[k - j] + b[j] < a[k - arg] + b[arg]) arg = j;  // 同じ値なら左を残す
        }
        c[k] = a[k - arg] + b[arg];
        self(self, top, k, lo, arg);         // 上の行の最小の位置は arg 以下
        self(self, k + 1, bottom, arg, hi);  // 下の行の最小の位置は arg 以上
    };
    rec(rec, 0, n + m - 1, 0, m - 1);
    return c;
}
// --8<-- [end:core]

// --8<-- [start:merge]
// a・b とも凸。差分を小さい順にマージする
vector<long long> min_plus_convex_convex(const vector<long long>& a, const vector<long long>& b) {
    int n = a.size(), m = b.size();
    vector<long long> c(n + m - 1);
    c[0] = a[0] + b[0];
    int i = 0, j = 0;
    for (int k = 1; k < n + m - 1; k++) {
        if (j == m - 1 || (i < n - 1 && a[i + 1] - a[i] <= b[j + 1] - b[j])) {
            c[k] = c[k - 1] + (a[i + 1] - a[i]);
            i++;
        } else {
            c[k] = c[k - 1] + (b[j + 1] - b[j]);
            j++;
        }
    }
    return c;
}
// --8<-- [end:merge]

vector<long long> naive(const vector<long long>& a, const vector<long long>& b) {
    int n = a.size(), m = b.size();
    vector<long long> c(n + m - 1, LLONG_MAX);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) c[i + j] = min(c[i + j], a[i] + b[j]);
    }
    return c;
}

bool is_convex(const vector<long long>& v) {
    for (int i = 0; i + 2 < (int)v.size(); i++) {
        if (v[i + 1] - v[i] > v[i + 2] - v[i + 1]) return false;
    }
    return true;
}

int main() {
    int n, m;
    cin >> n >> m;
    vector<long long> a(n), b(m);
    for (auto& x : a) cin >> x;
    for (auto& x : b) cin >> x;
    assert(is_convex(a));
    vector<long long> c = min_plus_convex_arbitrary(a, b);
    assert(c == naive(a, b));
    if (is_convex(b)) assert(min_plus_convex_convex(a, b) == c);

    // 乱数で愚直な方法と比べる
    mt19937 rng(1);
    for (int t = 0; t < 2000; t++) {
        int p = rng() % 8 + 1, q = rng() % 8 + 1;
        vector<long long> x(p), y(q), z(q);
        long long d = (long long)(rng() % 21) - 10, base = rng() % 50;
        for (int i = 0; i < p; i++) {
            x[i] = base;
            base += d;
            d += rng() % 4;  // 差分が増えるので凸
        }
        for (int j = 0; j < q; j++) y[j] = (long long)(rng() % 41) - 20;
        long long e = (long long)(rng() % 21) - 10, w = 0;
        for (int j = 0; j < q; j++) {
            z[j] = w;
            w += e;
            e += rng() % 3;
        }
        assert(min_plus_convex_arbitrary(x, y) == naive(x, y));
        assert(min_plus_convex_convex(x, z) == naive(x, z));
    }

    for (int k = 0; k < n + m - 1; k++) cout << c[k] << (k + 1 < n + m - 1 ? ' ' : '\n');
}
