#include <bits/stdc++.h>
using namespace std;

// 異なる N 点（N ≥ 3）のうち過半数を通る直線があるか。あれば (a, b, c)（a x + b y + c = 0）を返す
// --8<-- [start:core]
mt19937_64 rng(random_device{}());

optional<array<long long, 3>> majority_line(const vector<long long>& x, const vector<long long>& y) {
    int n = x.size();
    uniform_int_distribution<int> pick_i(0, n - 1), pick_j(0, n - 2);
    for (int t = 0; t < 100; t++) {                  // 失敗確率は (3/4)^100 ≒ 3×10^-13 以下
        int i = pick_i(rng), j = pick_j(rng);
        if (j >= i) j++;                             // i 以外の n - 1 点から一様に選ぶ
        long long dx = x[j] - x[i], dy = y[j] - y[i];
        int on = 0;
        for (int k = 0; k < n; k++)                  // 直線 i-j 上の点を数える（外積が 0）
            if (dx * (y[k] - y[i]) - dy * (x[k] - x[i]) == 0) on++;
        if (2 * on > n) return array<long long, 3>{dy, -dx, dx * y[i] - dy * x[i]};
    }
    return nullopt;                                  // 「ない」と答える（確率的に誤りうる側）
}
// --8<-- [end:core]

int main() {
    int n;
    cin >> n;
    vector<long long> x(n), y(n);
    for (int i = 0; i < n; i++) cin >> x[i] >> y[i];
    auto r = majority_line(x, y);
    if (r) {
        auto [a, b, c] = *r;
        int on = 0;
        for (int k = 0; k < n; k++)
            if (a * x[k] + b * y[k] + c == 0) on++;
        assert(2 * on > n);                          // 「ある」と答えたときは必ず正しい
        cout << "Yes\n";
    } else {
        cout << "No\n";
    }
}
