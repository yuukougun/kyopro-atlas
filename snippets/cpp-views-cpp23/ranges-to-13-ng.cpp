#include <bits/stdc++.h>
using namespace std;

int main() {
    vector<int> a{3, 1, 4};
    // --8<-- [start:core]
    auto st = a | ranges::to<set>();  // g++-13 ではコンパイルエラー（ranges::to は GCC 14 から）
    // --8<-- [end:core]
    cout << st.size() << '\n';
}
