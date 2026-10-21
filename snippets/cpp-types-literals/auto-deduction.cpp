#include <bits/stdc++.h>
using namespace std;

int main() {
    vector<int> v;  // 空
    // --8<-- [start:core]
    auto a = 0;           // int
    auto b = 0LL;         // long long
    auto n = v.size();    // size_t（符号なし）
    auto INF = 1e18;      // double
    static_assert(is_same_v<decltype(a), int>);
    static_assert(is_same_v<decltype(b), long long>);
    static_assert(is_same_v<decltype(n), size_t>);
    static_assert(is_same_v<decltype(INF), double>);
    cout << n - 1 << '\n';  // 空なので 0 - 1 が 18446744073709551615 になる
    // --8<-- [end:core]
    cout << a + b << ' ' << (INF > 0) << '\n';
}
