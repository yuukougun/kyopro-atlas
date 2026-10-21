#include <bits/stdc++.h>
using namespace std;

int main() {
    long long l, r;
    cin >> l >> r;
    // --8<-- [start:core]
    mt19937_64 rng(random_device{}());              // 実行ごとに違う種
    uniform_int_distribution<long long> dist(l, r);  // 閉区間 [l, r] の一様な整数
    long long x = dist(rng);
    vector<int> v = {1, 2, 3, 4, 5};
    shuffle(v.begin(), v.end(), rng);                 // 一様にかき混ぜる

    mt19937_64 fixed1(42), fixed2(42);                // 種を固定すると毎回同じ列になる
    assert(fixed1() == fixed2());
    // --8<-- [end:core]
    assert(l <= x && x <= r);
    sort(v.begin(), v.end());
    assert(v == vector<int>({1, 2, 3, 4, 5}));
    bool seen_l = false, seen_r = false;
    for (int i = 0; i < 1000; i++) {
        long long y = dist(rng);
        assert(l <= y && y <= r);
        seen_l |= (y == l), seen_r |= (y == r);
    }
    cout << (seen_l && seen_r ? "both ends" : "missing") << '\n';
}
