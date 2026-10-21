// 1 つ除いた gcd：各 i について、a[i] を除いた残りすべての gcd を出力する。
// gcd は引き算で戻せないので、左からの累積 pre と右からの累積 suf を組み合わせる。
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<long long> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    // --8<-- [start:core]
    // pre[i] = gcd(a[0], …, a[i-1])、suf[i] = gcd(a[i], …, a[n-1])。
    // 空の範囲は gcd の単位元 0 にする（gcd(0, x) = x）
    vector<long long> pre(n + 1, 0), suf(n + 1, 0);
    for (int i = 0; i < n; i++) pre[i + 1] = gcd(pre[i], a[i]);
    for (int i = n - 1; i >= 0; i--) suf[i] = gcd(suf[i + 1], a[i]);

    for (int i = 0; i < n; i++) {
        // a[i] を除く ＝ 左の [0, i) と右の [i+1, n) を合わせる
        long long without_i = gcd(pre[i], suf[i + 1]);
        cout << without_i << (i + 1 < n ? ' ' : '\n');
    }
    // --8<-- [end:core]
}
