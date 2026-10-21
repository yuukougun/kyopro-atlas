// ACL の fenwick_tree：一点加算と区間和
// 入力：N Q、a_0 … a_{N-1}、続く Q 行は「0 p x」（a_p に x を加える）か「1 l r」（[l, r) の和を出力）
#include <bits/stdc++.h>
#include <atcoder/fenwicktree>
using namespace std;

int main() {
    int n, q;
    cin >> n >> q;
    // --8<-- [start:core]
    atcoder::fenwick_tree<long long> fw(n);  // 全要素 0 で作る。和が int を超えるなら long long
    for (int i = 0; i < n; i++) {
        long long a;
        cin >> a;
        fw.add(i, a);  // 初期値は 1 つずつ足す（全体で O(N log N)）
    }
    // --8<-- [end:core]
    vector<long long> naive(n, 0);
    for (int i = 0; i < n; i++) naive[i] = fw.sum(i, i + 1);
    for (int i = 0; i < q; i++) {
        int t;
        cin >> t;
        if (t == 0) {
            int p;
            long long x;
            cin >> p >> x;
            fw.add(p, x);
            naive[p] += x;
        } else {
            int l, r;
            cin >> l >> r;
            long long res = fw.sum(l, r);  // 0-indexed の半開区間 [l, r)。l == r なら 0
            long long check = 0;
            for (int j = l; j < r; j++) check += naive[j];
            assert(res == check);
            cout << res << '\n';
        }
    }
}
