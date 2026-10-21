#include <bits/stdc++.h>
using namespace std;

int main() {
    // --8<-- [start:core]
    vector<int> v = {1, 2, 3};
    cout << format("{}\n", v);  // g++-13 には範囲の書式がなく、コンパイルエラー
    // --8<-- [end:core]
}
