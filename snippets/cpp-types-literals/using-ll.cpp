#include <bits/stdc++.h>
using namespace std;
// --8<-- [start:core]
using ll = long long;

int main() {
    double d = 2.5;
    cout << ll(d) << '\n';  // 2（関数形式のキャストとして通る）
    vector<ll> a = {ll(1e18), 1};
    cout << a[0] + a[1] << '\n';
}
// --8<-- [end:core]
