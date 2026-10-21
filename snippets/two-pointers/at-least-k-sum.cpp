// より大きい区間も満たす型：正の整数列で、和が k 以上の区間 [l, r) の個数を数える。
// 左端 l ごとに、条件を満たす最小の右端 r まで進める。r は l とともに右へしか動かない。
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    long long k;
    cin >> n >> k;
    vector<long long> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    assert(k >= 1);
    for (int i = 0; i < n; i++) assert(a[i] >= 1);

    // --8<-- [start:core]
    long long ans = 0, sum = 0;  // sum：区間 [l, r) の和
    int r = 0;
    for (int l = 0; l < n; l++) {
        while (r < n && sum < k) sum += a[r++];  // 和が k に届くまで右端を伸ばす
        if (sum < k) break;    // 右端まで伸ばしても届かない。これより右の左端も届かない
        ans += n - r + 1;      // 右端が r, r+1, …, n の区間はどれも和が k 以上
        sum -= a[l];           // sum >= k >= 1 なので r > l。空区間から取り除くことはない
    }
    // --8<-- [end:core]
    cout << ans << '\n';
}
