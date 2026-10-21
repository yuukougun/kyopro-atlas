// 2 階の差分：長さ n の列（初めはすべて 0）の半開区間 [l, r) に 1, 2, …, r − l を足す操作を q 回まとめて行う。
// 差分を 2 段に持ち、最後に累積和を 2 回取る。素朴な方法の結果と assert で照らし合わせる。添字は 0-indexed。
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, q;
    cin >> n >> q;
    assert(n >= 1 && q >= 0);
    vector<int> ls(q), rs(q);
    for (int i = 0; i < q; i++) {
        cin >> ls[i] >> rs[i];
        assert(0 <= ls[i] && ls[i] <= rs[i] && rs[i] <= n);
    }

    // --8<-- [start:core]
    vector<long long> e(n + 2, 0);  // 差分の差分。r + 1 まで書くので 2 つ多く取る
    for (int i = 0; i < q; i++) {
        int l = ls[i], r = rs[i];
        long long len = r - l;
        e[l] += 1;        // 差分の列の [l, r) に 1 を足す（傾き 1 で増え始める）
        e[r] -= 1;
        e[r] -= len;      // 差分の列の位置 r に −len を足す（r で値を 0 に戻す）
        e[r + 1] += len;
    }
    vector<long long> d(n + 1, 0), a(n, 0);
    for (int i = 0; i <= n; i++) d[i] = (i > 0 ? d[i - 1] : 0) + e[i];  // 1 回目の累積和：差分の列
    for (int i = 0; i < n; i++) a[i] = (i > 0 ? a[i - 1] : 0) + d[i];   // 2 回目の累積和：値
    // --8<-- [end:core]

    vector<long long> naive(n, 0);
    for (int i = 0; i < q; i++)
        for (int j = ls[i]; j < rs[i]; j++) naive[j] += j - ls[i] + 1;
    assert(a == naive);
    for (int i = 0; i < n; i++) cout << a[i] << (i + 1 < n ? ' ' : '\n');
}
