// 赤い点と青い点を、x 座標も y 座標も青の方が真に大きい組にして、組の数を最大にする。
// x の小さい順に走査し、使える赤い点の y を multiset で持つ。青い点が来たら、
// 使える赤い点のうち y が最大のもの（ただし青の y 未満）と組にする。
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;  // 赤 n 個、青 m 個
    vector<pair<long long, long long>> red(n), blue(m);
    for (auto& [x, y] : red) cin >> x >> y;
    for (auto& [x, y] : blue) cin >> x >> y;

    // --8<-- [start:core]
    // (x, 種類, y)。同じ x では青（0）を赤（1）より先に処理する。
    // 条件は「x が真に大きい」なので、同じ x の赤はまだ使えない
    vector<tuple<long long, int, long long>> ev;
    for (auto [x, y] : red) ev.emplace_back(x, 1, y);
    for (auto [x, y] : blue) ev.emplace_back(x, 0, y);
    sort(ev.begin(), ev.end());

    multiset<long long> ys;  // x が今より真に小さく、まだ組になっていない赤の y
    int pairs = 0;
    for (auto [x, type, y] : ev) {
        if (type == 1) {
            ys.insert(y);
            continue;
        }
        auto it = ys.lower_bound(y);  // y 以上の最初の要素
        if (it == ys.begin()) continue;  // y 未満の赤がない
        --it;                            // y 未満で最大の y
        ys.erase(it);
        pairs++;
    }
    cout << pairs << '\n';
    // --8<-- [end:core]
}
