#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:core]
template <class... Ts>  // 型引数をいくつでも取る（可変長テンプレート）
void debug(const Ts&... xs) {
    ((cerr << xs << ' '), ...);  // x1 を出す, x2 を出す, ... と展開される（C++17）
    cerr << '\n';
}
// --8<-- [end:core]

// --8<-- [start:sum]
template <class... Ts>
auto sum(const Ts&... xs) {
    return (xs + ... + 0);  // x1 + (x2 + (... + 0))。引数が 0 個なら 0
}
// --8<-- [end:sum]

int main() {
    int n;
    long long m;
    string s;
    cin >> n >> m >> s;
    debug(n, m, s);  // 標準エラー出力に「n m s 」
    debug();         // 引数なしでも通る（改行だけ）
    cout << sum(n, m) << ' ' << sum() << '\n';
}
