// 1 以上 n 以下の整数のうち、a[0], …, a[m-1] のどれでも割り切れないものの個数。
// 「a[i] で割り切れる」を破る条件とみて、条件の集合 S を bit 全探索して包除する。
#include <bits/stdc++.h>
using namespace std;

int main() {
    long long n;
    int m;
    cin >> n >> m;
    vector<long long> a(m);
    for (int i = 0; i < m; i++) cin >> a[i];
    assert(m <= 20);
    for (int i = 0; i < m; i++) assert(a[i] >= 1);

    // --8<-- [start:core]
    long long ans = 0;
    for (int mask = 0; mask < (1 << m); mask++) {
        // N(S)：S のすべての a[i] で割り切れる数の個数 = n / lcm(S)。空集合の lcm は 1
        long long l = 1;
        bool over = false;  // lcm が n を超えたら N(S) = 0（掛け算はしない）
        for (int i = 0; i < m && !over; i++) {
            if (!(mask >> i & 1)) continue;
            long long t = l / gcd(l, a[i]);
            if (t > n / a[i]) over = true;  // t * a[i] > n と同じ。積を作らずに比べる
            else l = t * a[i];
        }
        long long cnt = over ? 0 : n / l;
        if (__builtin_popcount(mask) % 2 == 0) ans += cnt;  // |S| が偶数なら足す
        else ans -= cnt;                                    // 奇数なら引く
    }
    // --8<-- [end:core]

    cout << ans << '\n';
}
