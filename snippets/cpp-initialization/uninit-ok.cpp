#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:core]
int g[3];              // グローバル：0 で初期化される

long long solve(int n, const vector<int>& a) {
    long long s = 0;   // 関数の中では自分で初期化する
    int cnt[3]{};      // {} で 0
    for (int i = 0; i < n; i++) {
        s += a[i];
        cnt[a[i] % 3]++;
    }
    return s * 1000 + cnt[0];
}
// --8<-- [end:core]

int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto& x : a) cin >> x;
    assert(g[0] == 0 && g[2] == 0);
    cout << solve(n, a) << '\n';
}
