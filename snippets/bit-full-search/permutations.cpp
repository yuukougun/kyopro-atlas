// 数列を並べ替えたもののうち、隣り合う差の絶対値の和の最大値と、異なる並びの個数を順列全探索で求める
#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:core]
pair<long long, long long> best_order(vector<long long> a) {
    sort(a.begin(), a.end());                       // 昇順から始めないと全部は回らない
    long long best = LLONG_MIN, cnt = 0;
    do {
        long long s = 0;
        for (int i = 0; i + 1 < (int)a.size(); i++) s += abs(a[i + 1] - a[i]);
        best = max(best, s);
        cnt++;                                      // 同じ値は区別しないので、同じ並びは 1 回だけ
    } while (next_permutation(a.begin(), a.end()));  // 最後の並び（降順）の次で false
    return {best, cnt};
}
// --8<-- [end:core]

int main() {
    int n;
    cin >> n;
    vector<long long> a(n);
    for (auto& v : a) cin >> v;
    assert(1 <= n && n <= 10);
    auto [best, cnt] = best_order(a);
    cout << best << ' ' << cnt << '\n';
}
