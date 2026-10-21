#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:core]
// 右端 r を固定した区間 [l, r + 1) の gcd を、値ごとの (gcd, 左端の個数) の組で持つ。
// 値は右端を伸ばすたびに約数へ下がるので、組は O(log A) 個しかない。
// 返り値：gcd が 1 の区間の数と、すべての区間の gcd の和
pair<long long, long long> count_subarray_gcd(const vector<long long>& a) {
    vector<pair<long long, long long>> cur;  // 左端の大きい順（gcd の大きい順）
    long long ones = 0, sum = 0;
    for (long long x : a) {
        vector<pair<long long, long long>> nxt = {{x, 1}};  // 左端 = r の区間
        for (auto [g, c] : cur) {
            long long h = gcd(g, x);
            if (nxt.back().first == h) nxt.back().second += c;  // 同じ値はまとめる
            else nxt.push_back({h, c});
        }
        cur = move(nxt);
        for (auto [g, c] : cur) {
            if (g == 1) ones += c;
            sum += g * c;
        }
    }
    return {ones, sum};
}
// --8<-- [end:core]

int main() {
    int n;
    cin >> n;
    vector<long long> a(n);
    for (auto& x : a) cin >> x;
    auto [ones, sum] = count_subarray_gcd(a);
    long long bo = 0, bs = 0;  // 素朴な O(N^2) で確かめる
    for (int l = 0; l < n; l++) {
        long long g = 0;
        for (int r = l; r < n; r++) {
            g = gcd(g, a[r]);
            if (g == 1) bo++;
            bs += g;
        }
    }
    assert(ones == bo && sum == bs);
    cout << ones << ' ' << sum << '\n';
}
