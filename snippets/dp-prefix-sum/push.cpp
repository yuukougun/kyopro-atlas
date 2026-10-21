// 配る形＋いもす法：pull.cpp と同じ問題を、遷移先の区間に差分で配って解く。
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;
    vector<int> l(k), r(k);
    for (int t = 0; t < k; t++) {
        cin >> l[t] >> r[t];
        assert(1 <= l[t] && l[t] <= r[t]);
    }
    const long long MOD = 998244353;

    // --8<-- [start:core]
    vector<long long> diff(n + 1, 0);  // 差分：diff[x] に v を足すと、x 以降の値が v 増える
    long long cur = 0;                 // diff[0] + … + diff[i]。i に届いた値の合計
    long long last = 0;
    for (int i = 0; i < n; i++) {
        cur = (cur + diff[i]) % MOD;   // i へ配られる値はすべて i より前から来るので、ここで確定する
        long long v = (i == 0) ? 1 : cur;  // v = dp[i]
        last = v;
        for (int t = 0; t < k; t++) {
            // 遷移先は閉区間 [i + l, i + r]。始点に +v、終点の次に −v
            int a = i + l[t];
            if (a >= n) continue;
            int b = min(n, i + r[t] + 1);  // マス n 以降へ出る分は捨てる（diff[n] は番兵）
            diff[a] = (diff[a] + v) % MOD;
            diff[b] = (diff[b] - v + MOD) % MOD;
        }
    }
    cout << last << '\n';  // last = dp[n-1]
    // --8<-- [end:core]
}
