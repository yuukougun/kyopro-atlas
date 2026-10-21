// 和がちょうど k の区間 [l, r) の個数を数える。a は負の値を含んでよい。
// S_r − S_l = k ⇔ S_l = S_r − k なので、左から S_l の個数を連想配列に記録しながら足す。
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    long long k;
    cin >> n >> k;
    vector<long long> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    // --8<-- [start:core]
    map<long long, long long> cnt;  // cnt[v] = これまでに記録した S_l のうち値が v のものの個数
    cnt[0] = 1;                     // S_0 = 0（先頭から始まる区間のために最初に入れる）
    long long s = 0, ans = 0;
    for (int i = 0; i < n; i++) {
        s += a[i];  // s = S_{i+1}（右端 r = i + 1）
        auto it = cnt.find(s - k);  // [] で引くと、ない値の要素が作られる
        if (it != cnt.end()) ans += it->second;
        cnt[s]++;  // 調べてから記録する（l < r を保つ）
    }
    cout << ans << '\n';
    // --8<-- [end:core]

    // 小さい入力では全区間の和を直接調べた結果と比べる
    if (n <= 2000) {
        long long brute = 0;
        for (int l = 0; l < n; l++) {
            long long sum = 0;
            for (int r = l; r < n; r++) {
                sum += a[r];
                if (sum == k) brute++;
            }
        }
        assert(brute == ans);
    }
}
