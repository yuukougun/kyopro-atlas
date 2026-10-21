#include <bits/stdc++.h>
using namespace std;

int main() {
    vector<int> v = {1, 2, 3};
    // --8<-- [start:core]
    cout << ranges::fold_left(v, 0LL, plus{}) << '\n';  // -std=gnu++20 ではコンパイルエラー
    // --8<-- [end:core]
}
