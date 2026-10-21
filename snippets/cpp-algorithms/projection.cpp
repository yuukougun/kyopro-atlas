#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:struct]
struct P {
    string name;
    int score;
};
// --8<-- [end:struct]

int main() {
    int n;
    cin >> n;  // n >= 1
    vector<P> ps(n);
    for (auto& [name, score] : ps) cin >> name >> score;
    // --8<-- [start:core]
    ranges::sort(ps, {}, &P::score);         // score で比べて、P ごと並べ替える（{} は ranges::less{}）
    for (const auto& p : ps) cout << p.name << ' ';
    cout << '\n';
    const P& best = ranges::max(ps, {}, &P::score);  // score が最大の要素そのもの
    cout << best.name << '\n';

    vector<pair<int, int>> pr = {{1, 5}, {2, 9}, {3, 7}};
    ranges::sort(pr, greater{}, &pair<int, int>::second);  // second の降順
    ranges::sort(pr, {}, [](const pair<int, int>& q) { return -q.first; });  // ラムダも渡せる
    // --8<-- [end:core]
    for (auto [f, s] : pr) cout << f << ',' << s << ' ';
    cout << '\n';
}
