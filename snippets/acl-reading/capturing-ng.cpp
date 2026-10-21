#include <bits/stdc++.h>
#include <atcoder/segtree>
using namespace std;
using namespace atcoder;

int main() {
    int m;
    cin >> m;
    vector<int> a = {5, 2, 7};
    // --8<-- [start:core]
    segtree<int, [&](int x, int y) { return (x + y) % m; }, [] { return 0; }> seg(a);  // m をキャプチャしているのでエラー
    // --8<-- [end:core]
    cout << seg.all_prod() << '\n';
}
