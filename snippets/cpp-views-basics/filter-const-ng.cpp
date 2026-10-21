#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:core]
void print_all(const auto& r) {
    for (int x : r) cout << x << ' ';  // filter の view を const 参照で受けると回せない
    cout << '\n';
}
// --8<-- [end:core]

int main() {
    vector<int> a = {1, 2, 3, 4};
    print_all(a | views::filter([](int x) { return x % 2 == 0; }));  // コンパイルエラー
}
