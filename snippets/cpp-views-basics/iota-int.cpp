#include <bits/stdc++.h>
using namespace std;

int main() {
    long long n;
    cin >> n;
    // --8<-- [start:core]
    auto r1 = views::iota(0, n);    // 要素は int（始まりの 0 の型）
    auto r2 = views::iota(0LL, n);  // 要素は long long
    static_assert(is_same_v<ranges::range_value_t<decltype(r1)>, int>);
    static_assert(is_same_v<ranges::range_value_t<decltype(r2)>, long long>);
    // --8<-- [end:core]
    long long s = 0;
    for (long long i : r2) s += i;
    cout << s << '\n';
}
