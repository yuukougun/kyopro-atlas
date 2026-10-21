// N 個の荷物を 3 台のトラックに分けて積むとき、最も重いトラックの重さの最小値を 3 進の全探索で求める
#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:core]
long long min_max_load(const vector<long long>& a) {
    int n = a.size();
    int total = 1;
    for (int i = 0; i < n; i++) total *= 3;         // 3^N（pow は使わない）
    long long best = LLONG_MAX;
    for (int code = 0; code < total; code++) {
        long long load[3] = {0, 0, 0};
        int t = code;
        for (int i = 0; i < n; i++) {
            load[t % 3] += a[i];                    // 3 進の i 桁目＝要素 i の行き先
            t /= 3;
        }
        best = min(best, max({load[0], load[1], load[2]}));
    }
    return best;
}
// --8<-- [end:core]

int main() {
    int n;
    cin >> n;
    vector<long long> a(n);
    for (auto& v : a) cin >> v;
    assert(n <= 13);
    cout << min_max_load(a) << '\n';
}
