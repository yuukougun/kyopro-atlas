#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<long long> l(n);
    for (auto& v : l) cin >> v;
    // --8<-- [start:core]
    sort(l.begin(), l.end());
    long long ans = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            // 3 本目は j より右（l[j] 以上）から選び、l[i] + l[j] 未満なら三角形になる
            auto first = l.begin() + j + 1;
            auto last = lower_bound(first, l.end(), l[i] + l[j]);  // l[i] + l[j] 以上の最初
            ans += last - first;
        }
    }
    // --8<-- [end:core]
    cout << ans << '\n';
}
