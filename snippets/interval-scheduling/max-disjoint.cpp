#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:core]
// 半開区間 [l, r) の列から、互いに重ならない区間の最大個数を返す
int max_disjoint(vector<pair<long long, long long>> iv) {
    // 右端の小さい順に並べる（右端が同じなら順は問わない）
    sort(iv.begin(), iv.end(), [](const auto& a, const auto& b) { return a.second < b.second; });
    int cnt = 0;
    long long last = LLONG_MIN;  // 最後に選んだ区間の右端（まだ選んでいないときの番兵）
    for (auto [l, r] : iv) {
        if (last <= l) {  // 半開区間なので、端が接するだけなら重ならない
            cnt++;
            last = r;
        }
    }
    return cnt;
}
// --8<-- [end:core]

int main() {
    assert(max_disjoint({}) == 0);
    assert(max_disjoint({{0, 10}, {1, 2}, {3, 4}}) == 2);  // 左端の順なら 1 個になる例
    assert(max_disjoint({{0, 5}, {4, 6}, {5, 10}}) == 2);  // 短い順なら 1 個になる例
    int n;
    cin >> n;
    vector<pair<long long, long long>> iv(n);
    for (auto& [l, r] : iv) cin >> l >> r;
    cout << max_disjoint(iv) << '\n';
}
