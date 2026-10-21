#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:core]
// Σ|x − a_i| の最小値を返す（a は空でない）。x は中央値 a[n / 2] にする
long long min_abs_sum(vector<long long> a) {
    int n = a.size();
    nth_element(a.begin(), a.begin() + n / 2, a.end());  // 平均 O(N)。sort でもよい
    long long x = a[n / 2];
    long long sum = 0;
    for (long long v : a) sum += abs(v - x);
    return sum;
}
// --8<-- [end:core]

int main() {
    // 確認：中央値で全探索の最小と一致する
    vector<long long> t = {1, 3, 6, 8};
    long long best = LLONG_MAX;
    for (long long x = -5; x <= 15; x++) {
        long long s = 0;
        for (long long v : t) s += abs(v - x);
        best = min(best, s);
    }
    assert(min_abs_sum(t) == best && best == 10);

    int n;
    cin >> n;
    vector<long long> a(n);
    for (auto& v : a) cin >> v;
    cout << min_abs_sum(a) << '\n';
}
