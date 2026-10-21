#include <bits/stdc++.h>
using namespace std;

int main() {
    vector<int> v{3, 1, 4};
    long long s = 0;
    // --8<-- [start:core]
    // 読むだけなら as_const を先に挟む：x は const int& になり、代入はコンパイルエラー
    for (auto [i, x] : v | views::as_const | views::enumerate) {
        static_assert(is_same_v<decltype(x), const int&>);
        s += i * x;
    }
    // --8<-- [end:core]
    cout << s << '\n';
}
