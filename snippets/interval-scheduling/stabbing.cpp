#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:core]
// 閉区間 [l, r] をすべて突く点の位置を、最少の個数で返す
vector<long long> stab(vector<pair<long long, long long>> iv) {
    sort(iv.begin(), iv.end(), [](const auto& a, const auto& b) { return a.second < b.second; });
    vector<long long> pts;
    for (auto [l, r] : iv) {
        // 最後の点は r 以下にあるので、l 以上なら区間に入っている
        if (pts.empty() || pts.back() < l) pts.push_back(r);  // 入っていなければ右端に置く
    }
    return pts;
}
// --8<-- [end:core]

int main() {
    assert(stab({}).empty());
    assert(stab({{0, 3}, {3, 6}}).size() == 1);  // 閉区間は端の 3 を共有する
    int n;
    cin >> n;
    vector<pair<long long, long long>> iv(n);
    for (auto& [l, r] : iv) cin >> l >> r;
    vector<long long> pts = stab(iv);
    for (auto [l, r] : iv) {  // どの区間にも点が入っているか
        auto it = lower_bound(pts.begin(), pts.end(), l);
        assert(it != pts.end() && *it <= r);
    }
    cout << pts.size() << '\n';
    for (int i = 0; i < (int)pts.size(); i++) cout << pts[i] << (i + 1 == (int)pts.size() ? '\n' : ' ');
}
