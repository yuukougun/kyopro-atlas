#include <bits/stdc++.h>
using namespace std;

int main() {
    string s = "abc", t = "z";
    // --8<-- [start:core]
    if (s.find(t) >= 0) cout << "found\n";  // 常に真（size_t は負にならない）。-Wextra で警告が出る
    // --8<-- [end:core]
}
