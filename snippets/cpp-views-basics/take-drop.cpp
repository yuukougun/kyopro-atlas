#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    auto print = [](auto&& r) {
        for (int x : r) cout << x << ' ';
        cout << '\n';
    };
    // --8<-- [start:core]
    print(a | views::take(3));  // 先頭の 3 個（足りなければあるだけ）
    print(a | views::drop(3));  // 先頭の 3 個を除いた残り
    print(a | views::take_while([](int x) { return x > 0; }));  // 先頭から正の間だけ
    print(a | views::drop_while([](int x) { return x > 0; }));  // 先頭の正の並びを飛ばした残り
    // --8<-- [end:core]
}
