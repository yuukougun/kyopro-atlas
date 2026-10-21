#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:core]
long long solve(int n, const vector<int>& a) {
    long long s;       // 初期化していない
    int cnt[3];        // 初期化していない
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
    cout << solve(n, a) << '\n';
}
