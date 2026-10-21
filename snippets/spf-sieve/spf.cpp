// 最小素因数の篩：m 以下の各数の最小素因数 spf を篩で記録し、
// それで割り続けて各 a[i] を素因数分解する。出力は「a: p^e p^e …」（a = 1 なら「1:」）。
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int i = 0; i < n; i++) assert(1 <= a[i] && a[i] <= 10000000);
    int m = 1;
    for (int i = 0; i < n; i++) m = max(m, a[i]);  // 表は値の最大まで（要素数ではない）

    // --8<-- [start:core]
    // spf[x] = x の最小素因数（x ≥ 2）。0 はまだ書かれていない印
    vector<int> spf(m + 1, 0);
    for (int p = 2; p <= m; p++) {
        if (spf[p] != 0) continue;  // 書かれていれば合成数
        spf[p] = p;                 // 書かれていなければ素数
        for (long long j = (long long)p * p; j <= m; j += p) {  // p * p は int だとあふれうる
            if (spf[j] == 0) spf[j] = p;  // 最初に来た素数（＝最小の素因数）だけを残す
        }
    }

    // x を素因数分解して (素数, 指数) の列を返す。割るたびに x は半分以下になる
    auto factorize = [&](int x) -> vector<pair<int, int>> {
        vector<pair<int, int>> res;
        while (x > 1) {  // x = 1 なら何も返さない
            int p = spf[x], e = 0;
            while (x % p == 0) {
                x /= p;
                e++;
            }
            res.push_back({p, e});
        }
        return res;
    };
    // --8<-- [end:core]

    for (int i = 0; i < n; i++) {
        auto f = factorize(a[i]);
        long long prod = 1;
        cout << a[i] << ':';
        for (auto [p, e] : f) {
            cout << ' ' << p << '^' << e;
            for (int k = 0; k < e; k++) prod *= p;
        }
        cout << '\n';
        assert(prod == a[i]);
    }
}
