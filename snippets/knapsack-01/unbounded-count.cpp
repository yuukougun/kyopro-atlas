// 個数制限なしの数え上げ：額面 a[i] の硬貨を何枚でも使って合計 s にする方法の数を、
// 順序を区別しない（組合せ）場合と、区別する（列）場合の 2 通りで求める（mod 998244353）。
#include <bits/stdc++.h>
using namespace std;

int main() {
    const long long MOD = 998244353;
    int n, s;
    cin >> n >> s;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int i = 0; i < n; i++) assert(1 <= a[i]);

    // --8<-- [start:core]
    // 組合せ：硬貨のループを外側にする。硬貨を決まった順に使う形だけが数えられる
    vector<long long> comb(s + 1, 0);
    comb[0] = 1;
    for (int i = 0; i < n; i++) {
        for (int j = a[i]; j <= s; j++) {  // 小さい方から：同じ硬貨を何枚でも使える
            comb[j] = (comb[j] + comb[j - a[i]]) % MOD;
        }
    }

    // 列：和のループを外側にする。最後に使う硬貨で場合分けするので、並べ方が区別される
    vector<long long> seq(s + 1, 0);
    seq[0] = 1;
    for (int j = 1; j <= s; j++) {
        for (int i = 0; i < n; i++) {
            if (j >= a[i]) seq[j] = (seq[j] + seq[j - a[i]]) % MOD;
        }
    }
    cout << comb[s] << ' ' << seq[s] << '\n';
    // --8<-- [end:core]
}
