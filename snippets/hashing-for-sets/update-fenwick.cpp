// 点の更新つきの多重集合のハッシュ：数列 a と b（値は 1 以上 n 以下）に対して
//   0 p v : a[p] を v にする    1 l r L R : a[l, r) と b[L, R) が並べ替えで一致するか
#include <bits/stdc++.h>
#include <atcoder/fenwicktree>
using namespace std;

int main() {
    int n, q;
    cin >> n >> q;
    vector<int> a(n), b(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int i = 0; i < n; i++) cin >> b[i];

    // --8<-- [start:core]
    mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
    vector<unsigned long long> z(n + 1);
    for (int v = 1; v <= n; v++) z[v] = rng();

    // ull の BIT は 2^64 を法とする和を返すので、そのまま多重集合のハッシュになる
    atcoder::fenwick_tree<unsigned long long> fa(n), fb(n);
    for (int i = 0; i < n; i++) {
        fa.add(i, z[a[i]]);
        fb.add(i, z[b[i]]);
    }
    auto same = [&](int l, int r, int bl, int br) -> bool {
        return r - l == br - bl && fa.sum(l, r) == fb.sum(bl, br);
    };
    // --8<-- [end:core]

    for (int i = 0; i < q; i++) {
        int t;
        cin >> t;
        if (t == 0) {
            int p, v;
            cin >> p >> v;
            assert(0 <= p && p < n && 1 <= v && v <= n);
            fa.add(p, z[v] - z[a[p]]);  // 古い値の乱数を引き、新しい値の乱数を足す
            a[p] = v;
        } else {
            int l, r, bl, br;
            cin >> l >> r >> bl >> br;
            cout << (same(l, r, bl, br) ? "Yes" : "No") << '\n';
        }
    }
}
