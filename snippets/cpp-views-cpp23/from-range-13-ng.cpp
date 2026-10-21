#include <bits/stdc++.h>
using namespace std;

int main() {
    vector<int> a{3, 1, 4};
    // --8<-- [start:core]
    vector<int> r(from_range, a);  // g++-13 ではコンパイルエラー（GCC 15 から）
    // --8<-- [end:core]
    cout << r.size() << '\n';
}
