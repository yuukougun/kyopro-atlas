// 値を添字にして数える：各 i について、j < i かつ a_j ≤ a_i となる j の個数を出力する
// 入力：N、a_0 … a_{N-1}（|a_i| ≤ 10^9）
#include <bits/stdc++.h>
#include <atcoder/fenwicktree>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<long long> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    // --8<-- [start:core]
    vector<long long> vals = a;  // 座標圧縮：値を 0 … K-1 の番号にする
    sort(vals.begin(), vals.end());
    vals.erase(unique(vals.begin(), vals.end()), vals.end());
    int k = vals.size();
    atcoder::fenwick_tree<int> cnt(k);  // cnt の位置 v：これまでに出た「番号 v の値」の個数
    vector<long long> res(n);
    for (int i = 0; i < n; i++) {
        int id = lower_bound(vals.begin(), vals.end(), a[i]) - vals.begin();
        res[i] = cnt.sum(0, id + 1);  // 先に数える（自分を含めない）。a_j ≤ a_i なので id まで
        cnt.add(id, 1);               // 後で入れる
    }
    // --8<-- [end:core]
    for (int i = 0; i < n; i++) {
        long long check = 0;
        for (int j = 0; j < i; j++) check += (a[j] <= a[i]);
        assert(res[i] == check);
        cout << res[i] << (i + 1 < n ? ' ' : '\n');
    }
}
