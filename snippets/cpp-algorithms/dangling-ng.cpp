#include <bits/stdc++.h>
using namespace std;

vector<int> make() { return {3, 1, 4}; }

int main() {
    // --8<-- [start:core]
    cout << *ranges::max_element(make()) << '\n';  // 戻り値が ranges::dangling：コンパイルエラー
    // --8<-- [end:core]
}
