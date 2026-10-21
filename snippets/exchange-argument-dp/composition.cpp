// 一次関数の合成：f_i(x) = a[i] x + b[i]（a[i], b[i] ≥ 1）から異なる k 個を選んで好きな順に合成し、
// 1 に適用した値の最大。i を j の外側にする方がよいのは b[j](a[i] − 1) ≥ b[i](a[j] − 1) のとき。
// (a − 1) / b の小さい順（内側から外側への順）に並べ、選んだ個数を状態にした DP をする。
// n が小さければ、選び方と合成の順をすべて試す素朴な方法と突き合わせる。
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;
    vector<long long> a(n), b(n);
    for (int i = 0; i < n; i++) cin >> a[i] >> b[i];
    assert(0 <= k && k <= n);
    for (int i = 0; i < n; i++) assert(1 <= a[i] && a[i] <= 50 && 1 <= b[i] && b[i] <= 50);

    // --8<-- [start:core]
    vector<int> ord(n);
    iota(ord.begin(), ord.end(), 0);
    // 内側（先に適用する方）が先：(a[i] − 1) / b[i] < (a[j] − 1) / b[j] を、b > 0 なので掛け算で比べる
    sort(ord.begin(), ord.end(), [&](int i, int j) { return (a[i] - 1) * b[j] < (a[j] - 1) * b[i]; });

    const long long NEG = -1;  // 値はいつも 1 以上なので、-1 を「まだ作れない」の印にする
    // dp[c] ＝ ここまでの関数から c 個を選んで、並べた順に 1 へ適用した値の最大
    vector<long long> dp(k + 1, NEG);
    dp[0] = 1;
    for (int i : ord) {
        for (int c = k - 1; c >= 0; c--) {  // 0-1 なので個数の大きい方から
            if (dp[c] == NEG) continue;
            // f は増加関数なので、今の値は大きいほどよい（最大だけ持てば足りる）
            dp[c + 1] = max(dp[c + 1], a[i] * dp[c] + b[i]);
        }
    }
    cout << dp[k] << '\n';
    // --8<-- [end:core]

    // 素朴な方法：k 個の選び方と、適用する順をすべて試す
    if (n <= 7) {
        long long best = NEG;
        for (int mask = 0; mask < (1 << n); mask++) {
            if (__builtin_popcount(mask) != k) continue;
            vector<int> p;
            for (int i = 0; i < n; i++)
                if (mask >> i & 1) p.push_back(i);
            do {
                long long x = 1;
                for (int i : p) x = a[i] * x + b[i];  // p の先頭から順に適用する
                best = max(best, x);
            } while (next_permutation(p.begin(), p.end()));
        }
        assert(best == dp[k]);
    }
}
