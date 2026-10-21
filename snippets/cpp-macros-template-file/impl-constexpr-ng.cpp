#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:core]
constexpr int twice(int x);

int main() {
    constexpr int n = twice(3);  // エラー：定義より前に定数式の中で使っている
    array<int, n> a{};
    cout << a.size() << '\n';
}

constexpr int twice(int x) { return 2 * x; }
// --8<-- [end:core]
