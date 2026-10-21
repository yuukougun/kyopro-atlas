#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto& x : a) cin >> x;
    // --8<-- [start:core]
    auto bad = [](int x, int y) { return x <= y; };  // NG：等しい 2 つで true
    auto good = [](int x, int y) { return x < y; };  // OK：等しい 2 つで false
    assert(bad(1, 1));    // 自分自身より前になってしまい、約束を破る
    assert(!good(1, 1));
    sort(a.begin(), a.end(), good);  // bad を渡すと、同じ値が多いとき配列の外を読む
    // --8<-- [end:core]
    for (int i = 0; i < n; i++) cout << a[i] << " \n"[i == n - 1];
    if (n == 0) cout << '\n';
}
