#include <bits/stdc++.h>
#include <atcoder/segtree>
using namespace std;

int main() {
    vector<int> a = {3, 1, 4};
    // --8<-- [start:core]
    int lower = 0;
    auto op = [&](int x, int y) { return max({x, y, lower}); };  // lower をキャプチャしている
    auto e = [] { return INT_MIN; };
    atcoder::segtree<int, op, e> seg(a);  // コンパイルエラー
    // --8<-- [end:core]
    cout << seg.all_prod() << '\n';
}
