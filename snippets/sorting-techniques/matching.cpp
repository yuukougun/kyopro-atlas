// 2 つの列を 1 対 1 に対応させる：長さ n の列 a・b の要素を 1 対 1 に組み、
// |a_i - b_j| の和を最小にする。両方をソートして同じ順位どうしを組めばよい。
#include <bits/stdc++.h>
using namespace std;

long long min_matching(vector<long long> a, vector<long long> b) {
    // --8<-- [start:core]
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    long long total = 0;
    for (int i = 0; i < (int)a.size(); i++) {
        total += abs(a[i] - b[i]);  // i 番目に小さいものどうしを組む
    }
    // --8<-- [end:core]
    return total;
}

// 確かめ用：b の並べ方をすべて試す（n が小さいときだけ）
long long brute(const vector<long long>& a, vector<long long> b) {
    sort(b.begin(), b.end());
    long long best = LLONG_MAX;
    do {
        long long s = 0;
        for (int i = 0; i < (int)a.size(); i++) s += abs(a[i] - b[i]);
        best = min(best, s);
    } while (next_permutation(b.begin(), b.end()));
    return best;
}

int main() {
    int n;
    cin >> n;
    vector<long long> a(n), b(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int i = 0; i < n; i++) cin >> b[i];
    long long ans = min_matching(a, b);
    if (n <= 8) assert(ans == brute(a, b));
    cout << ans << '\n';
}
