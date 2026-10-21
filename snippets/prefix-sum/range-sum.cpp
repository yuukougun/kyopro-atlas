// 区間の和のクエリ：N 個の整数 A_1, …, A_N と Q 個のクエリ（閉区間 [L, R]、1-indexed）に、
// 区間の和を O(1) ずつで答える。実装は 0-indexed の半開区間 [l, r) = [L - 1, R) に直す。
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, q;
    cin >> n >> q;
    vector<long long> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    // --8<-- [start:core]
    // s[i] = a[0] + … + a[i-1]（先頭 i 個の和）。s[0] = 0 なので長さは n + 1
    vector<long long> s(n + 1, 0);
    for (int i = 0; i < n; i++) s[i + 1] = s[i] + a[i];

    for (int k = 0; k < q; k++) {
        int L, R;  // 問題文の閉区間 [L, R]（1-indexed）
        cin >> L >> R;
        int l = L - 1, r = R;  // 0-indexed の半開区間 [l, r)
        assert(0 <= l && l <= r && r <= n);
        cout << s[r] - s[l] << '\n';  // 空区間（l == r）なら 0
    }
    // --8<-- [end:core]
}
