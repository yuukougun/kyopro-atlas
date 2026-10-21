// 辞書順 K 番目：長さ n の 0/1 列で 1 が 2 つ続かないもののうち、辞書順で k 番目（1-indexed）を求める。
// 後ろから「残りの完成のさせ方の数」を DP で数え、k を超えた数は k で頭打ちにする。
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    long long k;
    cin >> n >> k;
    assert(n >= 1 && k >= 1);

    // --8<-- [start:core]
    // cnt[i][p]：i 文字目まで決め、直前の文字が p のとき、残り n - i 文字の埋め方の数（k で頭打ち）
    vector cnt(n + 1, array<long long, 2>{});
    cnt[n][0] = cnt[n][1] = 1;
    for (int i = n - 1; i >= 0; i--) {
        cnt[i][0] = min(k, cnt[i + 1][0] + cnt[i + 1][1]);  // 次に 0 も 1 も置ける
        cnt[i][1] = cnt[i + 1][0];                          // 1 の後は 0 だけ
    }
    // 先頭の「直前」は 0 とみなす（1 を置いてよい）
    if (cnt[0][0] < k) {
        cout << -1 << '\n';  // k 個もない
        return 0;
    }
    string ans;
    int p = 0;
    for (int i = 0; i < n; i++) {
        // 小さい文字 0 から：0 を置いたときの個数 cnt[i + 1][0] と k を比べる
        if (k <= cnt[i + 1][0]) {
            ans += '0';
            p = 0;
        } else {
            k -= cnt[i + 1][0];  // 0 で始まるものはすべて答えより前にある
            assert(p == 0);      // 個数が足りていれば、ここで 1 を置ける
            ans += '1';
            p = 1;
        }
    }
    cout << ans << '\n';
    // --8<-- [end:core]
}
