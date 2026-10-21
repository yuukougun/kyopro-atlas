#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:core]
auto sq(auto x) { return x * x; }  // template <class T> auto sq(T x) と同じ意味（C++20）

auto add(auto a, auto b) { return a + b; }  // a と b は別々の型引数になる
// --8<-- [end:core]

int main() {
    long long x;
    double y;
    cin >> x >> y;
    // --8<-- [start:call]
    cout << sq(x) << ' ' << sq(y) << '\n';
    cout << add(x, 1) << ' ' << add(1, y) << '\n';  // 型が違っても通る
    static_assert(is_same_v<decltype(add(1, 2.5)), double>);
    // --8<-- [end:call]
}
