// 転倒数を BIT で数える（値は座標圧縮してから BIT の添字にする）
// 入力：N、A_0 … A_{N-1}（同じ値があってもよい）。出力：i < j かつ A_i > A_j の組の数
#include <bits/stdc++.h>
#include <atcoder/fenwicktree>
using namespace std;

// --8<-- [start:core]
long long count_inversions(const vector<long long>& a) {
    int n = a.size();
    vector<long long> vals = a;  // 座標圧縮：値を 0, 1, …, m-1 の番号に直す
    sort(vals.begin(), vals.end());
    vals.erase(unique(vals.begin(), vals.end()), vals.end());
    int m = vals.size();

    atcoder::fenwick_tree<int> bit(m);  // bit の v 番目 = これまでに出た「番号 v の値」の個数
    long long inv = 0;                  // 最大で N(N-1)/2 なので long long
    for (int j = 0; j < n; j++) {
        int v = lower_bound(vals.begin(), vals.end(), a[j]) - vals.begin();
        inv += bit.sum(v + 1, m);  // 既出で a[j] より真に大きいものの個数（等しいものは数えない）
        bit.add(v, 1);
    }
    return inv;
}
// --8<-- [end:core]

int main() {
    int n;
    cin >> n;
    vector<long long> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    long long inv = count_inversions(a);
    long long naive = 0;  // 素朴な O(N^2) で確かめる
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            if (a[i] > a[j]) naive++;
    assert(inv == naive);
    cout << inv << '\n';
}
