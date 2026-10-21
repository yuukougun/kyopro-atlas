// mod の計算の基本：法 MOD = 998244353 で、負の数や 10^18 程度の値を含む足し算・引き算・掛け算を正しく行う。
// 入力：クエリ数 q と、各行に演算子（+ - *）と整数 x, y（|x|, |y| ≤ 10^18）。各クエリの値を MOD で割った余りを出力する。
#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:core]
const long long MOD = 998244353;

// 任意の long long を 0 以上 MOD 未満に直す（C++ の % は負の数に負の余りを返す）
long long norm(long long x) {
    x %= MOD;              // ここで -MOD < x < MOD
    if (x < 0) x += MOD;   // 負なら MOD を足して 0 以上に直す
    return x;
}
// 以下の 3 つは、a, b が 0 以上 MOD 未満であることを前提にする
long long add(long long a, long long b) { return (a + b) % MOD; }        // 和 < 2 MOD
long long sub(long long a, long long b) { return (a - b + MOD) % MOD; }  // 差 > -MOD なので MOD を足せば 0 以上
long long mul(long long a, long long b) { return a * b % MOD; }          // 積 < MOD^2 ≈ 10^18 は long long に収まる
// --8<-- [end:core]

int main() {
    int q;
    cin >> q;
    assert(q >= 0);
    for (int i = 0; i < q; i++) {
        char op;
        long long x, y;
        cin >> op >> x >> y;
        long long a = norm(x), b = norm(y);  // 先に両方を MOD 未満に収める
        long long r = 0;
        if (op == '+') r = add(a, b);
        else if (op == '-') r = sub(a, b);
        else if (op == '*') r = mul(a, b);
        else assert(false);
        assert(0 <= r && r < MOD);
        cout << r << '\n';
    }
}
