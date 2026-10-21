#include <bits/stdc++.h>
using namespace std;

struct Item {
    int score;
    string name;
};

int main() {
    int n;
    cin >> n;
    vector<Item> v(n);
    for (auto& [score, name] : v) cin >> score >> name;
    // --8<-- [start:core]
    // score の大きい順、等しければ name の辞書順（小さい順）
    sort(v.begin(), v.end(), [](const Item& a, const Item& b) {
        return tie(b.score, a.name) < tie(a.score, b.name);
    });
    // --8<-- [end:core]
    for (auto& [score, name] : v) cout << score << ' ' << name << '\n';

    // --8<-- [start:pair]
    vector<pair<int, int>> p = {{2, 1}, {1, 3}, {2, 0}};
    sort(p.begin(), p.end());  // first で比べ、等しければ second で比べる（辞書順）
    assert((p == vector<pair<int, int>>{{1, 3}, {2, 0}, {2, 1}}));
    // --8<-- [end:pair]
}
