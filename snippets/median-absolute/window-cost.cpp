#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:core]
// 数直線上の点 a を、長さ l の区間 [x, x + l] にすべて入れるための
// 移動距離の和の最小値（x は自由に選ぶ）。a はソート済み
long long window_cost(const vector<long long>& a, long long l) {
    int n = a.size();
    long long cost = 0;
    for (int i = 0; i < n / 2; i++) {
        // 外側から組にした 2 点は、間隔が l に縮むまで寄せるしかない
        cost += max(0LL, a[n - 1 - i] - a[i] - l);
    }
    return cost;
}
// --8<-- [end:core]

int main() {
    // 確認：区間の左端 x を全探索した値と一致する
    vector<long long> t = {0, 2, 3, 9, 10};
    for (long long l = 0; l <= 12; l++) {
        long long best = LLONG_MAX;
        for (long long x = -20; x <= 20; x++) {
            long long s = 0;
            for (long long v : t) s += max(0LL, x - v) + max(0LL, v - (x + l));
            best = min(best, s);
        }
        assert(window_cost(t, l) == best);
    }

    int n;
    long long l;
    cin >> n >> l;
    vector<long long> a(n);
    for (auto& v : a) cin >> v;
    sort(a.begin(), a.end());
    cout << window_cost(a, l) << '\n';
}
