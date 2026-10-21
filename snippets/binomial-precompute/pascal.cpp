// 法 m が素数とは限らないとき、パスカルの三角形 C[i][j] = C[i-1][j-1] + C[i-1][j] で
// 0 ≤ j ≤ i ≤ n_max の表を O(n_max^2) で作る。割り算を使わないので、どの法でも使える。
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n_max, q;
    long long m;
    cin >> n_max >> m >> q;
    // --8<-- [start:core]
    // C[i][j] を m で割った余り（j > i の要素は 0 のまま）
    vector<vector<long long>> C(n_max + 1, vector<long long>(n_max + 1, 0));
    for (int i = 0; i <= n_max; i++) {
        C[i][0] = 1 % m;  // m = 1 でも正しく 0 になるように
        for (int j = 1; j <= i; j++) C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % m;
    }
    // --8<-- [end:core]
    for (int t = 0; t < q; t++) {
        int n, k;
        cin >> n >> k;
        cout << (0 <= k && k <= n ? C[n][k] : 0) << '\n';
    }
}
