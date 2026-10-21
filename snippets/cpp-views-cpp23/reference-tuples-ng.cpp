#include <bits/stdc++.h>
using namespace std;

int main() {
    vector<int> v{3, 1, 4};
    // --8<-- [start:core]
    for (auto& [i, x] : v | views::enumerate) x = 0;  // コンパイルエラー
    // --8<-- [end:core]
}
