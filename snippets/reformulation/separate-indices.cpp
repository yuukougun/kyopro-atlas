// i と j を分離する：A_j − A_i = j − i となる組 (i < j) の数と、
// A_i + A_j + i − j（i < j）の最大値を、どちらも左から 1 回なめて求める。
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<long long> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    assert(n >= 1);

    // --8<-- [start:core]
    // 数える：A_j − A_i = j − i ⇔ A_i − i = A_j − j（同じ鍵の組を数える）
    map<long long, long long> cnt;  // 鍵 A_i − i ごとの、これまでに見た i の個数
    long long pairs = 0;
    for (int j = 0; j < n; j++) {
        long long key = a[j] - j;
        pairs += cnt[key];  // 自分より左で鍵が等しい i の個数
        cnt[key]++;
    }

    // 最大化：A_i + A_j + i − j = (A_i + i) + (A_j − j)。左側の A_i + i の最大を持ち歩く
    long long best = LLONG_MIN;        // 組がなければ LLONG_MIN のまま
    long long left_max = LLONG_MIN;    // i < j の範囲での A_i + i の最大
    for (int j = 0; j < n; j++) {
        if (j > 0) best = max(best, left_max + (a[j] - j));
        left_max = max(left_max, a[j] + j);
    }
    // --8<-- [end:core]

    cout << pairs << '\n';
    if (best == LLONG_MIN) cout << "none\n";
    else cout << best << '\n';
}
