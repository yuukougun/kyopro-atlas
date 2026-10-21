// i < j のすべての組の積の和 Σ_{i<j} A_i A_j を、(S^2 − Σ A_i^2) / 2 で O(N) で求める（998244353 で割った余り）。
// mod の世界では 2 で「割る」代わりに 2 の逆元を掛ける。
#include <bits/stdc++.h>
#include <atcoder/modint>
using namespace std;
using mint = atcoder::modint998244353;

int main() {
    int n;
    cin >> n;
    vector<long long> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    // --8<-- [start:core]
    mint s = 0, sq = 0;  // S = Σ A_i と Σ A_i^2
    for (int i = 0; i < n; i++) {
        s += a[i];
        sq += mint(a[i]) * a[i];
    }
    // Σ_{i≠j} A_i A_j = S^2 − Σ A_i^2。i < j はその半分
    mint ans = (s * s - sq) * mint(2).inv();
    // --8<-- [end:core]

    // 愚直な二重ループと一致するか（N が小さいときだけ）
    if (n <= 2000) {
        mint naive = 0;
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) naive += mint(a[i]) * a[j];
        }
        assert(naive == ans);
    }
    cout << ans.val() << '\n';
}
