// N 種類が等確率で 1 つずつ出るとき、全種類がそろうまでの回数の期待値を mod 998244353 で求める。
// 入力：N。出力：期待値 mod 998244353
#include <bits/stdc++.h>
#include <atcoder/modint>
using namespace std;
using mint = atcoder::modint998244353;

// --8<-- [start:core]
mint coupon_collector_mod(int n) {
    mint e = 0;
    for (int k = 0; k < n; k++) {
        e += mint(n) / (n - k);  // n / (n - k) を逆元で表す
    }
    return e;
}
// --8<-- [end:core]

int main() {
    assert(coupon_collector_mod(1).val() == 1);
    assert(coupon_collector_mod(2).val() == 3);
    assert(coupon_collector_mod(4) * 3 == mint(25));  // 25/3
    int n;
    cin >> n;
    cout << coupon_collector_mod(n).val() << '\n';
}
