#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<long long> v(n);
    for (auto& x : v) cin >> x;
    long long big = 3'000'000'000LL;
    // --8<-- [start:core]
    auto x = 0;                                   // int
    auto s = accumulate(v.begin(), v.end(), 0);   // 戻り値も途中の和も int（v が long long でも）
    auto t = accumulate(v.begin(), v.end(), 0LL); // long long
    for (auto i : views::iota(0, big)) { static_assert(is_same_v<decltype(i), int>); break; }
    static_assert(is_same_v<decltype(x), int> && is_same_v<decltype(s), int>);
    static_assert(is_same_v<decltype(t), long long>);
    // --8<-- [end:core]
    cout << s << ' ' << t << '\n';
}
