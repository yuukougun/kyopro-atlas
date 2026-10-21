// 1 次元のいもす法：長さ n の列（初めはすべて 0）に、半開区間 [l, r) へ x を足す操作を q 回まとめて行い、
// 最後に各要素の値を出力する。添字は 0-indexed。
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, q;
    cin >> n >> q;
    assert(n >= 1 && q >= 0);

    // --8<-- [start:core]
    vector<long long> d(n + 1, 0);  // r = n のときも書けるよう 1 つ多く取る
    for (int i = 0; i < q; i++) {
        int l, r;
        long long x;
        cin >> l >> r >> x;
        assert(0 <= l && l <= r && r <= n);
        d[l] += x;  // l から先がすべて x 増える
        d[r] -= x;  // r から先は打ち消して元に戻す
    }
    vector<long long> a(n);
    long long cur = 0;
    for (int i = 0; i < n; i++) {
        cur += d[i];  // a[i] = d[0] + d[1] + … + d[i]
        a[i] = cur;
    }
    // --8<-- [end:core]

    for (int i = 0; i < n; i++) cout << a[i] << (i + 1 < n ? ' ' : '\n');
}
