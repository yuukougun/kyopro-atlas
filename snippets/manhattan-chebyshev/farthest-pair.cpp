#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:core]
// 2 点間のマンハッタン距離の最大。u = x + y、v = x − y の幅の大きい方
long long farthest_pair(const vector<long long>& x, const vector<long long>& y) {
    const long long INF = LLONG_MAX;
    long long umax = -INF, umin = INF, vmax = -INF, vmin = INF;
    for (int i = 0; i < (int)x.size(); i++) {
        long long u = x[i] + y[i], v = x[i] - y[i];
        umax = max(umax, u);
        umin = min(umin, u);
        vmax = max(vmax, v);
        vmin = min(vmin, v);
    }
    return max(umax - umin, vmax - vmin);
}
// --8<-- [end:core]

long long brute(const vector<long long>& x, const vector<long long>& y) {
    long long best = 0;
    for (int i = 0; i < (int)x.size(); i++)
        for (int j = 0; j < (int)x.size(); j++)
            best = max(best, llabs(x[i] - x[j]) + llabs(y[i] - y[j]));
    return best;
}

int main() {
    int n;
    cin >> n;
    vector<long long> x(n), y(n);
    for (int i = 0; i < n; i++) cin >> x[i] >> y[i];
    long long ans = farthest_pair(x, y);
    if (n <= 2000) assert(ans == brute(x, y));
    cout << ans << '\n';
}
