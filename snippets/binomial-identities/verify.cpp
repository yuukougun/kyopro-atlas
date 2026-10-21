// 二項係数の恒等式を、パスカルの三角形の表（mod を取らない正確な値）で小さいケースすべてについて検算する。
// 入力の n_max（0 以上 30 以下）までのすべての引数で左辺と右辺を比べ、食い違えばその引数を出して止まる。
#include <bits/stdc++.h>
using namespace std;

const int TABLE = 64;  // C(63, k) まで。C(66, 33) までは long long に収まる
long long c_table[TABLE][TABLE];

// 範囲の外（k < 0、k > n、n < 0）は 0 とする約束
long long binom(int n, int k) {
    if (n < 0 || k < 0 || k > n) return 0;
    assert(n < TABLE);
    return c_table[n][k];
}

int main() {
    for (int n = 0; n < TABLE; n++) {
        c_table[n][0] = 1;
        for (int k = 1; k <= n; k++) c_table[n][k] = c_table[n - 1][k - 1] + (k <= n - 1 ? c_table[n - 1][k] : 0);
    }
    int n_max;
    cin >> n_max;
    assert(0 <= n_max && n_max <= 30);

    // --8<-- [start:core]
    // 左辺と右辺を比べ、違えば式の名前と引数を出して止まる
    auto check = [](const string& name, long long lhs, long long rhs, vector<int> args) {
        if (lhs == rhs) return;
        cout << name << " が合わない：引数";
        for (int x : args) cout << ' ' << x;
        cout << "  左辺 " << lhs << "  右辺 " << rhs << '\n';
        exit(0);
    };

    // 縦の和（hockey stick）：sum_{i=r}^{m} C(i, r) = C(m + 1, r + 1)
    for (int m = 0; m <= n_max; m++) {
        for (int r = 0; r <= m + 1; r++) {  // r = m + 1（空の和）も試す
            long long lhs = 0;
            for (int i = r; i <= m; i++) lhs += binom(i, r);
            check("hockey stick", lhs, binom(m + 1, r + 1), {m, r});
        }
    }
    // --8<-- [end:core]

    for (int n = 0; n <= n_max; n++) {
        long long all = 0, alt = 0, even = 0, weighted = 0;
        for (int k = 0; k <= n; k++) {
            all += binom(n, k);
            alt += (k % 2 == 0 ? 1 : -1) * binom(n, k);
            if (k % 2 == 0) even += binom(n, k);
            weighted += k * binom(n, k);
            // 吸収公式：k C(n, k) = n C(n - 1, k - 1)
            check("吸収公式", k * binom(n, k), n * binom(n - 1, k - 1), {n, k});
        }
        check("和 2^n", all, 1LL << n, {n});
        check("交代和 [n = 0]", alt, n == 0 ? 1 : 0, {n});
        check("偶数個の和", even, n == 0 ? 1 : 1LL << (n - 1), {n});
        check("sum k C(n, k) = n 2^(n-1)", weighted, n == 0 ? 0 : n * (1LL << (n - 1)), {n});
    }

    // Vandermonde：sum_i C(a, i) C(b, k - i) = C(a + b, k)
    for (int a = 0; a <= n_max; a++) {
        for (int b = 0; b <= n_max; b++) {
            for (int k = 0; k <= a + b; k++) {
                long long lhs = 0;
                for (int i = 0; i <= k; i++) lhs += binom(a, i) * binom(b, k - i);
                check("Vandermonde", lhs, binom(a + b, k), {a, b, k});
            }
        }
    }

    // 上の数が動く形：sum_{i=0}^{m} C(i, a) C(m - i, b) = C(m + 1, a + b + 1)
    for (int m = 0; m <= n_max; m++) {
        for (int a = 0; a <= m; a++) {
            for (int b = 0; a + b <= m; b++) {
                long long lhs = 0;
                for (int i = 0; i <= m; i++) lhs += binom(i, a) * binom(m - i, b);
                check("上の数が動く形", lhs, binom(m + 1, a + b + 1), {m, a, b});
            }
        }
    }

    cout << "ok" << '\n';
}
