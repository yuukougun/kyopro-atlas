#include <bits/stdc++.h>
using namespace std;

int main() {
    vector<int> v = {3, 1, 4};
    // --8<-- [start:core]
    for (int i : views::iota(0, v.size())) cout << v[i] << '\n';  // コンパイルエラー
    // --8<-- [end:core]
}
