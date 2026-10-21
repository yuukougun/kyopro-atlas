// 転倒数がちょうど K の連続部分列の個数（「K 以下」の個数の差。窓を尺取りで動かし BIT で転倒数を増減する）
// 入力：N K、A_0 … A_{N-1}。出力：転倒数がちょうど K の区間 [l, r)（l < r）の個数
#include <bits/stdc++.h>
#include <atcoder/fenwicktree>
using namespace std;

// --8<-- [start:core]
// a は座標圧縮済み（0 〜 m-1）。転倒数が k 以下の区間の個数を返す
long long count_at_most(const vector<int>& a, int m, long long k) {
    if (k < 0) return 0;
    int n = a.size();
    atcoder::fenwick_tree<int> bit(m);  // 窓 [l, r] に入っている値の個数
    long long inv = 0, res = 0;
    int l = 0;
    for (int r = 0; r < n; r++) {
        inv += bit.sum(a[r] + 1, m);  // 右端に足す：窓の中で a[r] より大きい個数だけ増える
        bit.add(a[r], 1);
        while (inv > k) {             // 窓が 1 要素なら inv = 0 なので必ず止まる
            inv -= bit.sum(0, a[l]);  // 左端を外す：窓の中で a[l] より小さい個数だけ減る
            bit.add(a[l], -1);
            l++;
        }
        res += r - l + 1;  // 右端が r で転倒数が k 以下の区間は、左端が l, l+1, …, r の r-l+1 個
    }
    return res;
}
// ちょうど K：count_at_most(a, m, K) - count_at_most(a, m, K - 1)
// --8<-- [end:core]

int main() {
    int n;
    long long k;
    cin >> n >> k;
    vector<long long> raw(n);
    for (int i = 0; i < n; i++) cin >> raw[i];
    vector<long long> vals = raw;
    sort(vals.begin(), vals.end());
    vals.erase(unique(vals.begin(), vals.end()), vals.end());
    vector<int> a(n);
    for (int i = 0; i < n; i++) a[i] = lower_bound(vals.begin(), vals.end(), raw[i]) - vals.begin();
    int m = vals.size();
    long long ans = count_at_most(a, m, k) - count_at_most(a, m, k - 1);
    long long naive = 0;  // 素朴な方法で確かめる
    for (int l = 0; l < n; l++) {
        long long c = 0;
        for (int r = l; r < n; r++) {
            for (int i = l; i < r; i++)
                if (raw[i] > raw[r]) c++;
            if (c == k) naive++;
        }
    }
    assert(ans == naive);
    cout << ans << '\n';
}
