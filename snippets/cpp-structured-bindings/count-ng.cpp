#include <bits/stdc++.h>
using namespace std;

int main() {
    // --8<-- [start:core]
    tuple<int, int, int> t{1, 2, 3};
    auto [a, b] = t;  // 名前が 2 つ、要素が 3 つ：コンパイルエラー
    // --8<-- [end:core]
    cout << a + b << '\n';
}
