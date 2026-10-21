#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:core]
struct Edge {
    long long cost;  // 1 番目に比べる
    int u, v;        // cost が等しければ u、さらに等しければ v
    auto operator<=>(const Edge&) const = default;
};
// --8<-- [end:core]

int main() {
    int m;
    cin >> m;
    vector<Edge> e(m);
    for (auto& [cost, u, v] : e) cin >> u >> v >> cost;
    // --8<-- [start:use]
    sort(e.begin(), e.end());          // cost → u → v の辞書順
    set<Edge> st(e.begin(), e.end());  // set のキーにもなる
    if (m > 0) assert(e[0] == e[0] && !(e[0] < e[0]));  // == と < が使える
    // --8<-- [end:use]
    for (auto& [cost, u, v] : e) cout << cost << ' ' << u << ' ' << v << '\n';
    cout << st.size() << '\n';
}
