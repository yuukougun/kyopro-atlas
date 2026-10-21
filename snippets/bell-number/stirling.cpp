#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;  // 0 <= n <= 25（B_25 までは long long に収まる）
    // --8<-- [start:core]
    // S[i][k]：区別できる i 個を、区別しない k 個の空でない組に分ける数
    vector<vector<long long>> S(n + 1, vector<long long>(n + 1, 0));
    S[0][0] = 1;  // 0 個を 0 組に分ける方法は「何もしない」の 1 通り
    for (int i = 1; i <= n; i++) {
        for (int k = 1; k <= i; k++) {
            // 要素 i が 1 人で新しい組を作る ＋ 既存の k 組のどれかに入る
            S[i][k] = S[i - 1][k - 1] + k * S[i - 1][k];
        }
    }
    long long bell = 0;  // B_n = S(n,0) + S(n,1) + ... + S(n,n)
    for (int k = 0; k <= n; k++) bell += S[n][k];
    // --8<-- [end:core]

    // --8<-- [start:bell]
    // B[m+1] = Σ_j C(m, j) B[j]：要素 m+1 と同じ組に入る相手 m-j 個を選び、残り j 個を分ける
    vector<vector<long long>> C(n + 1, vector<long long>(n + 1, 0));
    for (int i = 0; i <= n; i++) {
        C[i][0] = 1;
        for (int j = 1; j <= i; j++) C[i][j] = C[i - 1][j - 1] + C[i - 1][j];
    }
    vector<long long> B(n + 1, 0);
    B[0] = 1;
    for (int m = 0; m + 1 <= n; m++) {
        for (int j = 0; j <= m; j++) B[m + 1] += C[m][j] * B[j];
    }
    // --8<-- [end:bell]
    assert(B[n] == bell);

    cout << bell << '\n';
    for (int k = 0; k <= n; k++) cout << S[n][k] << (k == n ? '\n' : ' ');
}
