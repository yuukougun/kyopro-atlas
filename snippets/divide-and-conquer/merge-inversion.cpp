// マージソートで転倒数（i < j かつ a[i] > a[j] の組の数）を数える分割統治
// 入力：N、A_0 … A_{N-1}。出力：転倒数
// 素朴な O(N^2) の数え方と比べて assert する
#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:core]
// [l, r) を昇順に並べ替え、その中の転倒数を返す。buf は長さ N の作業用
long long sort_count(vector<long long>& a, vector<long long>& buf, int l, int r) {
    if (r - l <= 1) return 0;  // 長さ 0・1 の区間に組はない
    int m = (l + r) / 2;
    long long res = sort_count(a, buf, l, m) + sort_count(a, buf, m, r);
    // ここで [l, m) と [m, r) はどちらも昇順。またぐ組を数えながら合わせる
    int i = l, j = m, k = l;
    while (i < m || j < r) {
        if (j == r || (i < m && a[i] <= a[j])) {
            buf[k++] = a[i++];  // 等しいときは左を先に出す（等しい組は数えない）
        } else {
            res += m - i;  // 左に残る a[i..m) はすべて a[j] より大きい
            buf[k++] = a[j++];
        }
    }
    for (int t = l; t < r; t++) a[t] = buf[t];
    return res;
}
// --8<-- [end:core]

int main() {
    int n;
    cin >> n;
    vector<long long> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    long long naive = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (a[i] > a[j]) naive++;
        }
    }
    vector<long long> buf(n);
    long long res = sort_count(a, buf, 0, n);
    assert(res == naive);
    assert(is_sorted(a.begin(), a.end()));
    cout << res << '\n';
}
