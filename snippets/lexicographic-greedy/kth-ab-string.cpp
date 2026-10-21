// a を A 個、b を B 個並べた文字列のうち、辞書順で K 番目（1-indexed）を求める。
// 先頭を a にしたときの個数 cnt と K を比べ、K <= cnt なら a、そうでなければ K から cnt を引いて b にする。
#include <bits/stdc++.h>
using namespace std;

int main() {
    int A, B;
    long long K;
    cin >> A >> B >> K;
    assert(0 <= A && A <= 100 && 0 <= B && B <= 100 && A + B >= 1 && K >= 1);

    // --8<-- [start:core]
    // C[n][r]：二項係数。K <= 10^18 なので、それより大きい LIMIT で頭打ちにしても K との比較は変わらない（あふれ対策）。
    // 頭打ちの値どうしの和 2 * LIMIT も long long に収まる
    const long long LIMIT = 2'000'000'000'000'000'000LL;
    int n = A + B;
    vector<vector<long long>> C(n + 1, vector<long long>(n + 1, 0));
    for (int i = 0; i <= n; i++) {
        C[i][0] = 1;
        for (int r = 1; r <= i; r++) C[i][r] = min(LIMIT, C[i - 1][r - 1] + C[i - 1][r]);
    }
    assert(K <= C[n][A]);  // K 番目が存在する

    string ans;
    int a = A, b = B;
    while (a + b > 0) {
        // 先頭を a にしたとき、残り a + b - 1 文字に a を a - 1 個置く並べ方の数
        long long cnt = (a > 0) ? C[a + b - 1][a - 1] : 0;
        if (K <= cnt) {
            ans += 'a';
            a--;
        } else {
            K -= cnt;  // a で始まる cnt 個を飛ばす
            ans += 'b';
            b--;
        }
    }
    cout << ans << '\n';
    // --8<-- [end:core]
}
