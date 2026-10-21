#include <bits/stdc++.h>
using namespace std;

int main() {
    string s = "abc";
    // --8<-- [start:core]
    cout << s.contains("bc") << '\n';  // -std=gnu++20 ではコンパイルエラー
    // --8<-- [end:core]
}
