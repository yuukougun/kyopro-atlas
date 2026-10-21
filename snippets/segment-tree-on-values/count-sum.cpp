// 値を添字にした BIT（個数と和の 2 本）。座標圧縮してから使う
// 入力：N、A_0 … A_{N-1}
// 出力：各 i について「j < i で A_j <= A_i の個数」と「j < i で A_j > A_i の和」を 1 行に
#include <bits/stdc++.h>
#include <atcoder/fenwicktree>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<long long> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    vector<long long> le(n), gt(n);

    // --8<-- [start:core]
    // 座標圧縮：出てくる値をすべて先に集め、ソートして重複を除く
    vector<long long> vals = a;
    sort(vals.begin(), vals.end());
    vals.erase(unique(vals.begin(), vals.end()), vals.end());
    int m = vals.size();

    atcoder::fenwick_tree<long long> cnt(m), sum(m);  // 添字 = 値の順位
    for (int i = 0; i < n; i++) {
        int k = lower_bound(vals.begin(), vals.end(), a[i]) - vals.begin();
        le[i] = cnt.sum(0, k + 1);  // A_i 以下の値の個数（添字 [0, k]）
        gt[i] = sum.sum(k + 1, m);  // A_i より大きい値の和（添字 [k + 1, m)）
        cnt.add(k, 1);              // A_i を 1 個追加する
        sum.add(k, a[i]);
    }
    // --8<-- [end:core]

    for (int i = 0; i < n; i++) {
        long long nle = 0, ngt = 0;  // 素朴な方法で確かめる
        for (int j = 0; j < i; j++) {
            if (a[j] <= a[i]) nle++;
            else ngt += a[j];
        }
        assert(le[i] == nle && gt[i] == ngt);
        cout << le[i] << ' ' << gt[i] << '\n';
    }
}
