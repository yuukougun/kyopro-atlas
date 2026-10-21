#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto& x : a) cin >> x;
    // --8<-- [start:core]
    // repeat(x, k)：x を k 回並べた範囲
    for (char c : views::repeat('=', 3)) cout << c;
    cout << '\n';
    // join_with(sep)：範囲の範囲を、区切りを挟んで 1 列にする（末尾に区切りは付かない）
    auto strs = a | views::transform([](int x) { return to_string(x); });
    for (char c : strs | views::join_with(' ')) cout << c;
    cout << '\n';
    // as_const：要素を const 参照で見せる（書き換えるとコンパイルエラー）
    for (auto&& x : a | views::as_const) static_assert(is_same_v<decltype(x), const int&>);
    // --8<-- [end:core]
}
