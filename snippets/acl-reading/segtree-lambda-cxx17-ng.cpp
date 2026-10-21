#include <bits/stdc++.h>
#include <atcoder/segtree>
using namespace std;
using namespace atcoder;

int main() {
    vector<int> a = {5, 2, 7};
    // --8<-- [start:core]
    segtree<int, [](int x, int y) { return min(x, y); }, [] { return INT_MAX; }> seg(a);  // C++17 ではエラー
    // --8<-- [end:core]
    cout << seg.all_prod() << '\n';
}
