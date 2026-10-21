#include <bits/stdc++.h>
using namespace std;

int main() {
    vector<int> v{3, 1, 4}, w{10, 20, 30};
    // --8<-- [start:core]
    for (auto [i, x] : v | views::enumerate) x *= 2;      // v が {6, 2, 8} になる
    for (auto [a, b] : views::zip(v, w)) b += a;          // w が {16, 22, 38} になる
    for (const auto& [i, x] : v | views::enumerate) {
        static_assert(is_same_v<decltype(x), int&>);      // const auto& でも x は int&
        x = 0;                                            // コンパイルが通り、v が {0, 0, 0} になる
    }
    // --8<-- [end:core]
    assert((w == vector<int>{16, 22, 38}));
    assert((v == vector<int>{0, 0, 0}));
    cout << "ok\n";
}
