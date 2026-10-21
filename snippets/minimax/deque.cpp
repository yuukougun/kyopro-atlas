// 列の両端から交互に 1 つずつ取るゲーム：先手の和 − 後手の和を、先手は最大化・後手は最小化する。
// f[l][r] ＝ 残りが a[l, r) のとき、手番の人が以後に得る「自分の和 − 相手の和」の最大値（negamax）。
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    assert(n >= 0);
    vector<long long> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    // --8<-- [start:core]
    // f[l][r]：残りが半開区間 [l, r) のときの、手番の人から見た得点差の最大値
    vector<vector<long long>> f(n + 1, vector<long long>(n + 1, 0));  // 空区間は 0
    for (int len = 1; len <= n; len++) {          // 短い区間から（次の局面は 1 つ短い）
        for (int l = 0; l + len <= n; l++) {
            int r = l + len;
            long long takeLeft = a[l] - f[l + 1][r];       // 左端を取る。相手の差は符号を反転
            long long takeRight = a[r - 1] - f[l][r - 1];  // 右端を取る
            f[l][r] = max(takeLeft, takeRight);
        }
    }
    cout << f[0][n] << '\n';  // 先手から見た差
    // --8<-- [end:core]
}
