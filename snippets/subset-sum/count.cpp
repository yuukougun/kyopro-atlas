#include <bits/stdc++.h>
using namespace std;

const long long MOD = 998244353;

int main() {
    int n, s;
    cin >> n >> s;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    // --8<-- [start:core]
    // can[t]：ここまでの要素から選んで和を t にできるか
    // cnt[t]：和が t になる選び方の数（mod 998244353）
    vector<char> can(s + 1, false);
    vector<long long> cnt(s + 1, 0);
    can[0] = true;  // 何も選ばない
    cnt[0] = 1;
    for (int i = 0; i < n; i++) {
        // 大きい方から更新すると、a[i] を 2 回使わない
        for (int t = s; t >= a[i]; t--) {
            if (can[t - a[i]]) can[t] = true;
            cnt[t] = (cnt[t] + cnt[t - a[i]]) % MOD;
        }
    }
    // --8<-- [end:core]

    // 作れる和のうち s 以下で最大のもの（2 グループに分ける型で使う）
    int best = s;
    while (!can[best]) best--;
    assert(best >= 0);
    cout << (can[s] ? "Yes" : "No") << '\n';
    cout << cnt[s] << '\n';
    cout << best << '\n';
}
