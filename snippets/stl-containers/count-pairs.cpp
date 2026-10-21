// A_j − A_i = j − i を満たす組 (i, j)（i < j）の個数を数える。
// 式を A_i − i = A_j − j と「i だけの式 = j だけの式」に分け、
// 左から A_i − i の値の個数を map に記録しながら走査する。
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<long long> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    // --8<-- [start:core]
    map<long long, long long> cnt;  // cnt[v] = これまでの i のうち a[i] − i = v のものの個数
    long long ans = 0;
    for (int j = 0; j < n; j++) {
        long long key = a[j] - j;
        auto it = cnt.find(key);  // [] で引くと、ない値の要素が作られる
        if (it != cnt.end()) ans += it->second;
        cnt[key]++;  // 調べてから記録する（i < j を保つ）
    }
    cout << ans << '\n';
    // --8<-- [end:core]

    // 小さい入力では全部の組を直接調べた結果と比べる
    if (n <= 2000) {
        long long brute = 0;
        for (int i = 0; i < n; i++)
            for (int j = i + 1; j < n; j++)
                if (a[j] - a[i] == j - i) brute++;
        assert(brute == ans);
    }
}
