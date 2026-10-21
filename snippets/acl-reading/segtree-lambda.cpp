#include <bits/stdc++.h>
#include <atcoder/segtree>
using namespace std;
using namespace atcoder;

// --8<-- [start:named]
constexpr auto add = [](long long a, long long b) { return a + b; };
constexpr auto zero = [] { return 0LL; };
// --8<-- [end:named]

int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto& x : a) cin >> x;
    // --8<-- [start:core]
    segtree<int, [](int x, int y) { return min(x, y); }, [] { return INT_MAX; }> seg(a);
    // --8<-- [end:core]
    segtree<long long, add, zero> sum(vector<long long>(a.begin(), a.end()));
    cout << seg.all_prod() << ' ' << sum.all_prod() << '\n';
}
