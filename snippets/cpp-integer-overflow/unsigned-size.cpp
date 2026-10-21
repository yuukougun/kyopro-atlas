#include <bits/stdc++.h>
using namespace std;

int main() {
    vector<int> v;  // 空
    // --8<-- [start:core]
    cout << v.size() - 1 << '\n';     // 18446744073709551615（size_t は符号なし）
    cout << (-1 < v.size()) << '\n';  // 0。-1 が size_t に直されて最大値になる（-Wsign-compare の警告）
    cout << ssize(v) - 1 << ' ' << (int)v.size() - 1 << '\n';  // -1 -1
    // --8<-- [end:core]
}
