#include <bits/stdc++.h>
#include <atcoder/segtree>
using namespace std;
using namespace atcoder;

long long op(long long a, long long b) { return a + b; }
long long e() { return 0; }

int main() {
    int n;
    long long k;
    cin >> n >> k;
    vector<long long> a(n);
    for (auto& x : a) cin >> x;
    segtree<long long, op, e> seg(a);
    // --8<-- [start:core]
    // 先頭から足して k 以下に収まる最も長い区間 [0, r) の r。判定関数は k をキャプチャしてよい
    int r = seg.max_right(0, [&](long long s) { return s <= k; });
    // --8<-- [end:core]
    cout << r << '\n';
}
