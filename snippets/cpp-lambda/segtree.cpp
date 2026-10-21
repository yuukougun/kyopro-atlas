#include <bits/stdc++.h>
#include <atcoder/segtree>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    // --8<-- [start:core]
    auto op = [](int x, int y) { return max(x, y); };  // キャプチャのないラムダ
    auto e = [] { return INT_MIN; };
    atcoder::segtree<int, op, e> seg(a);  // op・e を型の一部（テンプレート引数）として渡す
    // --8<-- [end:core]
    cout << seg.all_prod() << '\n';
}
