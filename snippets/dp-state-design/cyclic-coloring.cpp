#include <bits/stdc++.h>
using namespace std;

// 円形に並ぶ N 人（N >= 2）に M 色を、隣り合う人どうしが異なるように塗る方法の数（mod 998244353）
const long long MOD = 998244353;

// --8<-- [start:core]
long long count_cyclic(int n, long long m) {
    // 1 人目の色を固定して切り開く。状態は「今の人が 1 人目と同じ色か」の 2 通り
    long long same = 1, diff = 0;  // 1 人目自身は「同じ」
    for (int i = 1; i < n; i++) {
        long long nsame = diff;                                   // 異なる → 同じ：1 色
        long long ndiff = (same * ((m - 1) % MOD) + diff * ((m - 2 + MOD) % MOD)) % MOD;
        same = nsame, diff = ndiff;
    }
    // N 人目は 1 人目と隣り合うので「異なる」だけを数え、1 人目の色の M 通りを掛ける
    return diff * (m % MOD) % MOD;
}
// --8<-- [end:core]

int main() {
    int n;
    long long m;
    cin >> n >> m;
    assert(n >= 2);
    cout << count_cyclic(n, m) << '\n';
}
