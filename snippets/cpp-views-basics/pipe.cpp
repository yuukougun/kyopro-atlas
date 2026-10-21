#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    int calls = 0;
    // --8<-- [start:core]
    auto r = a | views::filter([](int x) { return x % 2 == 0; })
               | views::transform([&](int x) { calls++; return x * x; });
    // ここまででは関数はまだ 1 回も呼ばれていない
    assert(calls == 0);
    for (int y : r) cout << y << ' ';  // 取り出すときに 1 つずつ計算する
    cout << '\n';
    // --8<-- [end:core]
    cout << calls << '\n';
}
