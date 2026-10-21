// --8<-- [start:core]
#pragma GCC target("avx2")
#include <bits/stdc++.h>
using namespace std;

int main() {
    string s = "abc";  // g++-13 ではここでコンパイルエラー（g++-15 では通る）
    cout << s << '\n';
}
// --8<-- [end:core]
