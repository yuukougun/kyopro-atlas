#include <bits/stdc++.h>
using namespace std;

// N 以下で約数の個数が最大の数を、小さい素数の指数が単調に減る形に限って DFS で探す。
// N ≤ 10^18 でも調べる数は 3 万個あまり。

// --8<-- [start:core]
const vector<long long> P = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53};

// 答え：約数の個数の最大と、それを達成する最小の数
pair<long long, long long> most_divisors(long long n) {
    long long best_d = 1, best_x = 1;
    // i 番目の素数の指数を決める。x は今の値、d はその約数の個数、
    // lim は直前の素数の指数（これ以下にする）
    auto dfs = [&](auto&& self, int i, long long x, long long d, int lim) -> void {
        if (d > best_d || (d == best_d && x < best_x)) {
            best_d = d;
            best_x = x;
        }
        if (i == (int)P.size()) return;
        long long y = x;
        for (int e = 1; e <= lim; e++) {
            if (y > n / P[i]) break;  // y * P[i] > n（掛ける前に割り算で比べる）
            y *= P[i];
            self(self, i + 1, y, d * (e + 1), e);
        }
    };
    dfs(dfs, 0, 1, 1, 64);
    return {best_d, best_x};
}
// --8<-- [end:core]

int main() {
    assert(most_divisors(1000) == make_pair(32LL, 840LL));
    assert(most_divisors(1000000000) == make_pair(1344LL, 735134400LL));
    long long n;
    cin >> n;
    auto [d, x] = most_divisors(n);
    cout << d << ' ' << x << '\n';
}
