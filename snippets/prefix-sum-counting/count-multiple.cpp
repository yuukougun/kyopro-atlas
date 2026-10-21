// 和が m の倍数になる区間 [l, r) の個数を数える。a は負の値を含んでよい。
// (S_r − S_l) が m の倍数 ⇔ S_r と S_l の m で割った余りが等しい。余りは 0 以上 m 未満にそろえる。
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    long long m;
    cin >> n >> m;
    assert(m >= 1);
    vector<long long> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    // --8<-- [start:core]
    map<long long, long long> cnt;  // cnt[v] = 余りが v の S_l の個数
    cnt[0] = 1;                     // S_0 = 0 の余り
    long long rem = 0, ans = 0;     // rem = S_r を m で割った余り（0 以上 m 未満）
    for (int i = 0; i < n; i++) {
        rem = ((rem + a[i]) % m + m) % m;  // C++ の % は負になりうるので m を足して直す
        ans += cnt[rem];  // 余りが等しい S_l の個数
        cnt[rem]++;
    }
    cout << ans << '\n';
    // --8<-- [end:core]

    if (n <= 2000) {
        long long brute = 0;
        for (int l = 0; l < n; l++) {
            long long sum = 0;
            for (int r = l; r < n; r++) {
                sum += a[r];
                if (sum % m == 0) brute++;
            }
        }
        assert(brute == ans);
    }
}
