#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:core]
// すべての区間 [l, r) の和の総和：a[i] は (i + 1) * (n - i) 個の区間に入る
// 値が大きいと long long を超えるので、mod を取るか __int128 を使う（落とし穴を参照）
long long sum_of_interval_sums(const vector<long long>& a) {
    long long n = a.size(), ans = 0;
    for (long long i = 0; i < n; i++) ans += a[i] * (i + 1) * (n - i);
    return ans;
}

// すべての組 i < j の |a[i] - a[j]| の総和：昇順で i 番目の値は i 回足され n - 1 - i 回引かれる
long long sum_of_pair_diffs(vector<long long> a) {
    sort(a.begin(), a.end());
    long long n = a.size(), ans = 0;
    for (long long i = 0; i < n; i++) ans += a[i] * (2 * i - (n - 1));
    return ans;
}
// --8<-- [end:core]

int main() {
    int n;
    cin >> n;
    vector<long long> a(n);
    for (auto& x : a) cin >> x;

    // 小さい入力では、対象を 1 つずつ列挙した結果と照らし合わせる
    if (n <= 300) {
        long long s1 = 0, s2 = 0;
        for (int l = 0; l < n; l++) {
            long long s = 0;
            for (int r = l + 1; r <= n; r++) s += a[r - 1], s1 += s;
        }
        for (int i = 0; i < n; i++)
            for (int j = i + 1; j < n; j++) s2 += abs(a[i] - a[j]);
        assert(s1 == sum_of_interval_sums(a));
        assert(s2 == sum_of_pair_diffs(a));
    }
    cout << sum_of_interval_sums(a) << '\n' << sum_of_pair_diffs(a) << '\n';
}
