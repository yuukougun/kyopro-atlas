#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:core]
// x を n 回 op で結合した値を返す。op は結合法則を満たし、e は単位元（n = 0 の答え）
template <class T, class Op>
T power(T x, long long n, T e, Op op) {
    T res = e;
    while (n > 0) {
        if (n & 1) res = op(res, x);
        x = op(x, x);
        n >>= 1;
    }
    return res;
}
// --8<-- [end:core]

const long long MOD = 998244353;

int main() {
    // 1 次関数 f(x) = a x + b を n 回合成して x0 に適用する
    long long a, b, x0, n;
    cin >> a >> b >> x0 >> n;
    // --8<-- [start:affine]
    // (p, q) は関数 x ↦ p x + q。op(f, g) は「f の後に g」を表す g(f(x))
    using Affine = pair<long long, long long>;
    auto compose = [](Affine f, Affine g) -> Affine {
        return {g.first * f.first % MOD, (g.first * f.second + g.second) % MOD};
    };
    Affine fn = power(Affine{a, b}, n, Affine{1, 0}, compose);  // 単位元は x ↦ x
    long long ans = (fn.first * x0 + fn.second) % MOD;
    // --8<-- [end:affine]
    if (n <= 1000) {  // 小さい n は 1 回ずつ適用した結果と比べる
        long long x = x0;
        for (long long i = 0; i < n; i++) x = (a * x + b) % MOD;
        assert(x == ans);
    }
    cout << ans << '\n';
}
