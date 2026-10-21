#include <bits/stdc++.h>
using namespace std;

int main() {
    vector<int> a = {1, 2, 3}, b = {1, 2};
    // --8<-- [start:core]
    cout << ranges::starts_with(a, b) << '\n';  // GCC 16 から。GCC 15 ではコンパイルエラー
    // --8<-- [end:core]
}
