#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:core]
const long long MOD = 1000000007;

// a の全要素の lcm を MOD で割った余り（lcm そのものは作らない）
long long lcm_mod(const vector<long long>& a) {
    map<long long, int> maxe;  // 素数 p → 指数の最大
    for (long long x : a) {
        for (long long p = 2; p * p <= x; p++) {
            int e = 0;
            while (x % p == 0) {
                x /= p;
                e++;
            }
            if (e > 0) maxe[p] = max(maxe[p], e);
        }
        if (x > 1) maxe[x] = max(maxe[x], 1);
    }
    long long res = 1;
    for (auto [p, e] : maxe) {
        for (int i = 0; i < e; i++) res = res * (p % MOD) % MOD;
    }
    return res;
}
// --8<-- [end:core]

int main() {
    assert(lcm_mod({360, 84}) == 2520);
    assert(lcm_mod({1}) == 1);
    int n;
    cin >> n;
    vector<long long> a(n);
    for (auto& x : a) cin >> x;
    cout << lcm_mod(a) << '\n';
}
