#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> v(n);
    for (int i = 0; i < n; i++) cin >> v[i];
    long long s1 = 0, s2 = 0, s3 = 0;
    // --8<-- [start:core]
    for (int i : views::iota(0, (int)v.size())) s1 += v[i];  // 終端を int にそろえる
    for (auto i : views::iota(0, ssize(v))) s2 += v[i];      // ssize は符号付き（ptrdiff_t）
    for (auto i : views::iota(0uz, v.size())) s3 += v[i];    // 0uz は size_t の 0（C++23）
    // --8<-- [end:core]
    static_assert(is_same_v<decltype(ssize(v)), ptrdiff_t>);
    static_assert(is_same_v<ranges::range_value_t<decltype(views::iota(0, ssize(v)))>, int>);  // 要素は始まりの型
    static_assert(is_same_v<ranges::range_value_t<decltype(views::iota(0uz, v.size()))>, size_t>);
    static_assert(is_same_v<decltype(0uz), size_t>);
    assert(s1 == s2 && s2 == s3);
    cout << s1 << '\n';
}
