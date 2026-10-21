// パスカルの漸化式で C(n, k)（0 ≤ n ≤ 66）を mod を取らずに表にする。
// k < 0・k > n の C(n, k) は 0 と約束し、関数の中で返す。
#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:core]
const int MAXN = 66;  // C(66, 33) ≈ 7.2 × 10^18 が long long に収まる最大の行
long long C[MAXN + 1][MAXN + 1];  // グローバルなので 0 で初期化される

void build() {
    for (int n = 0; n <= MAXN; n++) {
        C[n][0] = 1;
        for (int k = 1; k <= n; k++) {
            C[n][k] = C[n - 1][k - 1] + C[n - 1][k];  // 最後の 1 個を選ぶか選ばないか
        }
    }
}

// 範囲外は 0（和の式の端を場合分けせずに書ける）
long long binom(int n, int k) {
    if (n < 0 || k < 0 || k > n) return 0;
    return C[n][k];
}
// --8<-- [end:core]

int main() {
    build();
    // 対称性と、1 行の和が 2^n になることを確かめる
    for (int n = 0; n <= MAXN; n++) {
        unsigned long long sum = 0;
        for (int k = 0; k <= n; k++) {
            assert(binom(n, k) == binom(n, n - k));
            sum += binom(n, k);
        }
        if (n < 64) assert(sum == (1ULL << n));
    }
    int q;
    cin >> q;
    while (q--) {
        int n, k;
        cin >> n >> k;
        assert(0 <= n && n <= MAXN);
        cout << binom(n, k) << '\n';
    }
}
