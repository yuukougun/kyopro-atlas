// N 種類が等確率で 1 つずつ出るとき、全種類がそろうまでの回数の期待値を求める。
// 入力：N。出力：期待値（小数点以下 10 桁）
#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:core]
// すでに k 種類持っている段階では、新しい種類が出る確率は (n - k) / n なので、
// その段階の回数の期待値は 1 / p = n / (n - k)。段階ごとに足す。
double coupon_collector(int n) {
    double e = 0;
    for (int k = 0; k < n; k++) {
        e += (double)n / (n - k);  // n / (n - k) と書くと整数の割り算になる
    }
    return e;
}
// --8<-- [end:core]

int main() {
    assert(abs(coupon_collector(1) - 1.0) < 1e-12);
    assert(abs(coupon_collector(2) - 3.0) < 1e-12);
    assert(abs(coupon_collector(6) - 14.7) < 1e-9);
    int n;
    cin >> n;
    cout << fixed << setprecision(10) << coupon_collector(n) << '\n';
}
