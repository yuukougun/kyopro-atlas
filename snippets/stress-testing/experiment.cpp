#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;  // 表を作る範囲（n ≤ 20 程度）
    // --8<-- [start:count]
    // 長さ k の 01 列のうち、1 が隣り合わないものを全探索で数える
    vector<long long> cnt(n + 1);
    for (int k = 1; k <= n; k++) {
        for (int s = 0; s < (1 << k); s++) {
            if ((s & (s >> 1)) == 0) cnt[k]++;  // 隣り合う 1 がない
        }
    }
    for (int k = 1; k <= n; k++) cout << cnt[k] << (k < n ? ' ' : '\n');
    // 表から予想した漸化式 cnt[k] = cnt[k-1] + cnt[k-2] を、表のすべてと照らし合わせる
    for (int k = 3; k <= n; k++) assert(cnt[k] == cnt[k - 1] + cnt[k - 2]);
    // --8<-- [end:count]

    // --8<-- [start:game]
    // 石が i 個の山から 1・3・4 個を取り合い、取れなくなった方が負け。
    // win[i]：石が i 個で手番の人が勝てるか（負けの局面へ動かせれば勝ち）
    vector<bool> win(n + 1, false);
    for (int i = 1; i <= n; i++) {
        for (int take : {1, 3, 4}) {
            if (take <= i && !win[i - take]) win[i] = true;
        }
    }
    for (int i = 0; i <= n; i++) cout << (win[i] ? 'W' : 'L');
    cout << '\n';
    // 予想：負けの局面は i mod 7 が 0 か 2 のときだけ
    for (int i = 0; i <= n; i++) assert(win[i] == !(i % 7 == 0 || i % 7 == 2));
    // --8<-- [end:game]
}
