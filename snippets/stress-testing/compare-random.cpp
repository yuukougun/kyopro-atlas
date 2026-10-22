#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:funcs]
// 本解：空でない区間の和の最大（誤りを含む。best を 0 で始めている）
long long solve(const vector<long long>& a) {
    long long best = 0, cur = 0;
    for (long long x : a) {
        cur = max(cur + x, x);
        best = max(best, cur);
    }
    return best;
}

// 愚直解：すべての区間 [l, r) の和を調べる。O(N^2) で遅いが確か
long long naive(const vector<long long>& a) {
    int n = a.size();
    long long best = LLONG_MIN;
    for (int l = 0; l < n; l++) {
        long long sum = 0;
        for (int r = l + 1; r <= n; r++) {
            sum += a[r - 1];
            best = max(best, sum);
        }
    }
    return best;
}
// --8<-- [end:funcs]

int main() {
    int trials;
    unsigned long long seed;
    long long lo, hi;
    cin >> trials >> seed >> lo >> hi;  // 本番では seed = random_device{}() にして表示しておく
    // --8<-- [start:core]
    mt19937_64 rng(seed);
    for (int t = 0; t < trials; t++) {
        // 生成器：小さい N と狭い値の範囲で作る
        int n = uniform_int_distribution<int>(1, 5)(rng);
        vector<long long> a(n);
        for (auto& x : a) x = uniform_int_distribution<long long>(lo, hi)(rng);

        long long got = solve(a), want = naive(a);
        if (got != want) {  // 食い違ったら入力と両方の答えを出して止める
            cout << "seed " << seed << ", trial " << t << '\n';
            cout << n << '\n';
            for (int i = 0; i < n; i++) cout << a[i] << (i + 1 < n ? ' ' : '\n');
            cout << "solve " << got << ", naive " << want << '\n';
            return 0;
        }
    }
    cout << "no difference in " << trials << " trials\n";
    // --8<-- [end:core]
}
